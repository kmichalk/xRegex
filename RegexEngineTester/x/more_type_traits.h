#ifndef	MORE_TYPE_TRAITS_H
#define MORE_TYPE_TRAITS_H

#include <type_traits>
#include "vamacros.h"

//////////////////////////////////////////////////////////////////////////////

namespace x
{

	struct _True
	{
		constexpr _True() {}
	};

	struct _False
	{
		constexpr _False(_True) {}
	};

	//////////////////////////////////////////////////////////////////////////////

	class triv_cpy {};
	class pod {};

//////////////////////////////////////////////////////////////////////////////

	template<typename T, typename Y>
	constexpr bool same = false;

	template<typename T>
	constexpr bool same<T, T> = true;

//////////////////////////////////////////////////////////////////////////////

#define ADVANCED_MEMBER_TEST(TestName, R_template, member, parameters, ...) \
template<typename T_, R_template, __VA_ARGS__>\
class TestName\
{\
protected:\
	template<typename Y_, R_template, __VA_ARGS__>\
	using MemberType_ = typename std::conditional<std::is_class<T_>::value,\
		R_template(Y_::*)(__VA_ARGS__) parameters, x::_True>::type;\
	template<typename Y_> static x::_False test(x::_False);\
	template<typename Y_> static typename std::conditional<std::is_class<T_>::value,\
		decltype(&Y_::member), x::_False>::type test(x::_True);\
public:\
	static constexpr bool value = \
		std::is_same<decltype(test<T_>(x::_True())),\
		MemberType_<T_,R_template,__VA_ARGS__>>::value;\
};

//////////////////////////////////////////////////////////////////////////////

#define EXPLICIT_MEMBER_TEST(TestName, ReturnType, member, arguments, parameters) \
template<typename T_>\
class TestName\
{\
private:\
	template<typename Y_>\
	using MemberType_ = typename std::conditional<std::is_class<T_>::value,\
		ReturnType(Y_::*)##arguments parameters, x::_True>::type;\
	template<typename Y_> static x::_False test(x::_False);\
	template<typename Y_> static typename std::conditional<std::is_class<T_>::value,\
		decltype(&Y_::member), x::_False>::type test(x::_True);\
public:\
	static constexpr bool value = \
		std::is_same<decltype(test<T_>(x::_True())), MemberType_<T_>>::value;\
};

//////////////////////////////////////////////////////////////////////////////

#define MEMBER_TEST(TestName, member) \
template<typename T>\
class TestName\
{\
private:\
	template <typename Y> static x::_False test(x::_False);\
	template <typename Y> static typename std::conditional<std::is_class<T>::value,\
		decltype(&Y::member), x::_False>::type test(x::_True);\
public:\
	static constexpr bool value = \
		!std::is_same<decltype(test<T>(x::_True())), x::_False>::value;\
};

//////////////////////////////////////////////////////////////////////////////

	template<typename T, const bool test, const T a, const T b>
	struct condition;
	template<typename T, const T a, const T b>
	struct condition<T, true, a, b>
	{
		static constexpr T value = a;
	};
	template<typename T, const T a, const T b>
	struct condition<T, false, a, b>
	{
		static constexpr T value = b;
	};

	template<typename T>
	constexpr T _if(const bool test, const T a, const T b)
	{
		return condition<T, test, a, b>::value;
	}


	//////////////////////////////////////////////////////////////////////////////

		template<typename T>
	struct is_free_func_ptr
	{
		static constexpr bool value = false;
	};

	template<typename R, typename... A>
	struct is_free_func_ptr<R(*)(A...)>
	{
		static constexpr bool value = true;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct is_member_func_ptr
	{
		static constexpr bool value = false;
	};

	template<typename R, typename T, typename... A>
	struct is_member_func_ptr<R(T::*)(A...)>
	{
		static constexpr bool value = true;
	};

	//////////////////////////////////////////////////////////////////////////////

	/*template<typename T>
	struct is_func_ptr
	{
		static constexpr bool value =
			is_free_func_ptr<T>::value ||
			is_member_func_ptr<T>::value;
	};*/

	template<class _Type>
	struct is_func_type
	{
		static constexpr bool value = false;
	};

	template<class _Ret, class... _Arg>
	struct is_func_type<_Ret(_Arg...)>
	{
		static constexpr bool value = true;
	};

	///////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	struct is_func_ref
	{
		static constexpr bool value = false;
	};

	template<class _Ret, class... _Arg>
	struct is_func_ref<_Ret(&)(_Arg...)>
	{
		static constexpr bool value = true;
	};

	///////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	struct is_free_func
	{
		static constexpr bool value =
			is_func_ref<_Type>::value ||
			is_free_func_ptr<_Type>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	struct is_callable
	{
		__if_exists(_Type::operator()) {
			static constexpr bool value = true;
		}
		__if_not_exists(_Type::operator()) {
			static constexpr bool value = is_free_func_ptr<_Type>::value;
		}
	};

	template<class _Type>
	constexpr bool is_callable_v = is_callable<_Type>::value;

	//////////////////////////////////////////////////////////////////////////////

	template<typename T, typename... Y_>
	struct is_any_of {};

	template<typename T, typename Y, typename... Y_>
	struct is_any_of<T, Y, Y_...>
	{
		static constexpr bool value = std::is_same<T, Y>::value ||
			is_any_of<T, Y_...>::value;
	};
	template<typename T, typename Y_>
	struct is_any_of<T, Y_>
	{
		static constexpr bool value = std::is_same<T, Y_>::value;
	};

#define IS_ANY_OF(...) is_any_of<__VA_ARGS__>::value

//////////////////////////////////////////////////////////////////////////////

	template<typename T, typename... Y>
	using select_any = typename
		std::conditional<is_any_of<T, Y...>::value,
		T, _False>::type;

//////////////////////////////////////////////////////////////////////////////

	template<typename R1, typename T, typename R2, typename... A>
	constexpr bool is_return_type_of(R2(T::*const)(A...))
	{
		return std::is_same<R1, R2>::value;
	};
	template<typename R1, typename T, typename R2>
	constexpr bool is_return_type_of(R2(T::*const)(...))
	{
		return std::is_same<R1, R2>::value;
	};
	template<typename R1, typename R2, typename... A>
	constexpr bool is_return_type_of(R2(*const)(A...))
	{
		return std::is_same<R1, R2>::value;
	};
	template<typename R1, typename R2>
	constexpr bool is_return_type_of(R2(*const)(...))
	{
		return std::is_same<R1, R2>::value;
	};
	template<typename T, typename Y>
	constexpr bool is_return_type_of(Y)
	{
		return std::is_same<T, Y>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename T, typename C, typename R, typename... A>
	constexpr bool is_argument_of(R(C::* const)(A...))
	{
		return is_any_of<T, A...>::value;
	}
	template<typename T, typename C, typename R>
	constexpr bool is_argument_of(R(C::*const)())
	{
		return false;
	}
	template<typename T, typename R, typename... A>
	constexpr bool is_argument_of(R(*const)(A...))
	{
		return is_any_of<T, A...>::value;
	}
	template<typename T, typename R>
	constexpr bool is_argument_of(R(*const)())
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////

	template<class...>
	struct argnum;

	template<class _Func>
	struct argnum<_Func> {
		__if_exists(_Func::operator()) {
			static constexpr unsigned value = argnum<decltype(&_Func::operator())>::value;
		}
		__if_not_exists(_Func::operator()) {
			static constexpr unsigned value = 0;
		}
	};

	template<class _Ret, class... _Arg>
	struct argnum<_Ret(_Arg...)> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class... _Arg>
	struct argnum<_Ret(*)(_Arg...)> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class... _Arg>
	struct argnum<_Ret(&)(_Arg...)> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class _Owner, class... _Arg>
	struct argnum<_Ret(_Owner::*)(_Arg...)> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class _Owner, class... _Arg>
	struct argnum<_Ret(_Owner::*)(_Arg...)const> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class _Owner, class... _Arg>
	struct argnum<_Ret(_Owner::*)(_Arg...)volatile> {
		static constexpr unsigned value = sizeof...(_Arg);
	};

	template<class _Ret, class _Owner, class... _Arg>
	struct argnum<_Ret(_Owner::*)(_Arg...)const volatile> {
		static constexpr unsigned value = sizeof...(_Arg);
	};


	template<class _Func>
	constexpr size_t argnum_v = argnum<_Func>::value;

	/*template<typename R, typename... A>
	constexpr unsigned argnum(R(*)(A...))
	{
		return sizeof...(A);
	}

	template<typename T, typename R, typename... A>
	constexpr unsigned argnum(R(T::*)(A...))
	{
		return sizeof...(A);
	}

	template<typename _Func>
	unsigned argnum(_Func&&)
	{
		return argnum(&_Func::operator());
	}

	template<typename _Func>
	constexpr unsigned argnum()
	{
		return argnum(&_Func::operator());
	}*/

	//////////////////////////////////////////////////////////////////////////////

	//template<typename...>
	//struct owner_of {};
	//
	//template<typename T, typename R, typename... A>
	//__forceinline constexpr owner_of<T, R, A...>& _owner_of(R(T::*)(A...))
	//{
	//	return owner_of<T, R, A...>{};
	//}
	//
	//template<

	//////////////////////////////////////////////////////////////////////////////

	template<bool...>
	struct any_true;

	template<bool b, bool... b_>
	struct any_true<b, b_...>
	{
		static constexpr bool value = b || any_true<b_...>::value;
	};

	template<bool b>
	struct any_true<b>
	{
		static constexpr bool value = b;
	};

#define ANY_TRUE(...) any_true<__VA_ARGS__>::value

//////////////////////////////////////////////////////////////////////////////

	template<bool...>
	struct all_true;

	template<bool b, bool... b_>
	struct all_true<b, b_...>
	{
		static constexpr bool value = b && all_true<b_...>::value;
	};

	template<bool b>
	struct all_true<b>
	{
		static constexpr bool value = b;
	};

#define ALL_TRUE(...) all_true<__VA_ARGS__>::value

//////////////////////////////////////////////////////////////////////////////

//template<int...>
//struct sum;
//
//template<int n, int... rest>
//struct sum<n, rest...>
//{
//	static constexpr int value = n + sum<rest...>::value;
//};
//
//template<int n>
//struct sum<n>
//{
//	static constexpr int value = n;
//};
//
//template<>
//struct sum<>
//{
//	static constexpr int value = 0;
//};

//////////////////////////////////////////////////////////////////////////////

	template<typename...>
	struct every_is;

	template<typename C, typename T, typename... Y>
	struct every_is<C, T, Y...>
	{
		static constexpr bool value =
			std::is_same<C, T>::value &&
			every_is<C, Y...>::value;
	};

	template<typename C, typename T>
	struct every_is<C, T>
	{
		static constexpr bool value =
			std::is_same<C, T>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<class... _Type>
	struct all_same
	{
		static constexpr bool value =
			every_is<typename select<1, _Type...>::type, _Type...>::value;
	};

	template<class... _Type>
	constexpr bool all_same_v = all_same<_Type...>::value;

	//template<typename T, typename Y, typename... U>
	//struct all_same<T, Y, U...> {
	//	static constexpr bool value =
	//		std::is_same<T, Y>::value &&
	//		all_same<Y, U...>::value;
	//};
	//
	//template<typename T, typename Y>
	//struct all_same<T, Y> {
	//	static constexpr bool value =
	//		std::is_same<T, Y>::value;
	//};
	//
	//template<typename T>
	//struct all_same<T> {
	//	static constexpr bool value =
	//		true;
	//};
	//
	//template<>
	//struct all_same<> {
	//	static constexpr bool value =
	//		false;
	//};


	//////////////////////////////////////////////////////////////////////////////

	template<class, unsigned = 1>
	struct nested_type;

	template<class _Type>
	struct nested_type<_Type, 0> {
		using type = _Type;
	};

	template<template<class> class _Temp, class _Type, unsigned _depth>
	struct nested_type<_Temp<_Type>, _depth> {
		using type = typename nested_type<_Type, _depth - 1>::type;
	};

	template<template<class> class _Temp, class _Type>
	struct nested_type<_Temp<_Type>, 0> {
		using type = _Temp<_Type>;
	};

	template<class _Type, unsigned _depth>
	using nested_type_t = typename nested_type<_Type, _depth>::type;

	//////////////////////////////////////////////////////////////////////////////

	template<size_t n, typename... T_>
	struct select;
	template<size_t n, typename T, typename... T_>
	struct select<n, T, T_...>
	{
		static_assert(n > 0,
			"Given iterator value is 0, which is not valid and equivalent to error-type.");
		typedef typename select<n - 1, T_...>::type type;

		/*static T value(T v, T_... v_)
		{
			static_assert(all_true<std::is_same<T, T_>::value...>::value,
				"Value types must be the same.");
			return select<n-1, T_...>::value(v_...);
		}

		template<T v, T_... v_>
		struct elem
		{
			static_assert(all_true<std::is_same<T, T_>::value...>::value,
				"Value types must be the same.");
			static constexpr T value = select<n-1, T_...>::elem<v_...>::value;
		};*/
	};
	template<size_t n, typename T>
	struct select<n, T>
	{
		static_assert(n < 2,
			"Type selection iterator exceeds the parameter pack.");
		typename T type;

		/*static T value(T v)
		{
			return v;
		}

		template<T v>
		struct elem
		{
			static constexpr T value = v;
		};*/
	};
	template<typename T, typename... T_>
	struct select<1, T, T_...>
	{
		typedef T type;

		/*static T value(T v, T_... v_)
		{
			return v;
		}

		template<T v, T_... v_>
		struct elem
		{
			static constexpr T value = v;
		};*/
	};

	template<size_t n, typename... T_>
	using select_t = typename select<n, T_...>::type;

	template<class... _Type>
	using first_t = select_t<1, _Type...>;

	template<class... _Type>
	using last_t = select_t<sizeof...(_Type), _Type...>;

	//////////////////////////////////////////////////////////////////////////////

	template<typename, size_t, typename...>
	struct find_;

	template<typename T, size_t current, typename Y, typename... Y_>
	struct find_<T, current, Y, Y_...>
	{
		static constexpr size_t value =
			condition<size_t,
			std::is_same<T, Y>::value,
			current,
			find_<T, current + 1, Y_...>::value>::value;

	};

	template<typename T, size_t current, typename Y>
	struct find_<T, current, Y>
	{
		static constexpr size_t value =
			condition<size_t,
			std::is_same<T, Y>::value,
			current,
			0>::value;
	};

	template<typename T>
	struct find_type
	{
		template<typename... Y_>
		struct in
		{
			static constexpr size_t value =
				find_<T, 1, Y_...>::value;
		};
	};

	
	//////////////////////////////////////////////////////////////////////////////

	template<class _Type, _Type, _Type...>
	struct contains_value;

	template<class _Type, _Type _value, _Type _first, _Type... _rest>
	struct contains_value<_Type, _value, _first, _rest...>
	{
		static constexpr bool value = (_value == _first) ? true :
			contains_value<_Type, _value, _rest...>::value;
	};

	template<class _Type, _Type _value, _Type _first>
	struct contains_value<_Type, _value, _first>
	{
		static constexpr bool value = (_value == _first);
	};

	template<class _Type, _Type _value>
	struct contains_value<_Type, _value>
	{
		static constexpr bool value = false;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<class _Type, int, _Type...>
	struct select_value;

	template<class _Type, int _index, _Type _first, _Type... _rest>
	struct select_value<_Type, _index, _first, _rest...>
	{
		static constexpr _Type value = (_index == 0) ? _first :
			(_index < 0 ? (_Type)0 :
				select_value<_Type, _index - 1, _rest...>::value);
	};

	//template<class _Type, int _index, _Type _first>
	//struct select_value<_Type, _index, _first>
	//{
	//	static constexpr _Type value = (_index == 0) ? _first : (_Type)0;
	//};

	template<class _Type, int _index>
	struct select_value<_Type, _index>
	{
		static constexpr _Type value = (_Type)0;
	};


	/*template<class _Type>
	struct contains
	{
		template<_Type _value, _Type... _pack>
		static constexpr bool value = contains_value<_Type, _value, _pack...>::value;
	};
*/

	//////////////////////////////////////////////////////////////////////////////
	
	template<size_t size, typename... T>
	struct same_packs_;

	template<size_t size, typename T>
	struct same_packs_<size, T>
	{
		static constexpr bool value = false;
	};

	template<typename... T>
	struct same_packs_<0, T...>
	{
		static constexpr bool value = false;
	};

	template<typename... T>
	struct same_packs_<1, T...>
	{
		static constexpr bool value = false;
	};

	template<size_t size, typename T, typename... Y>
	struct same_packs_<size, T, Y...>
	{
		static constexpr bool value =
			std::is_same<T, typename select<size / 2, T, Y...>::type>::value &&
			(sizeof...(Y) <= size / 2 ? true : same_packs_<size, Y...>::value);
	};

	template<typename... T>
	struct same_packs
	{
		static constexpr bool value =
			same_packs_<sizeof...(T), T...>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<size_t _i, class...>
	struct argument_of {
		//__if_exists(_Func::operator()) {
		//	using type = typename argument_of<_i, decltype(&_Func::operator())>::type;
		//}
		//__if_not_exists(_Func::operator()) {
			using type = void;
		//}
	};

	template<size_t _i, class _Ret, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_First, _Rest...)> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _First, class... _Rest>
	struct argument_of<_i, _Ret(*)(_First, _Rest...)> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _First, class... _Rest>
	struct argument_of<_i, _Ret(&)(_First, _Rest...)> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _Owner, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_Owner::*)(_First, _Rest...)> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _Owner, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_Owner::*)(_First, _Rest...) const> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _Owner, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_Owner::*)(_First, _Rest...) volatile> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Ret, class _Owner, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_Owner::*)(_First, _Rest...) const volatile> {
		using type = select_t<_i, _First, _Rest...>;
	};

	template<size_t _i, class _Func>
	using argument_of_t = typename argument_of<_i, _Func>::type;

	/*template<size_t _i, class _Ret, class _First, class... _Rest>
	struct argument_of<_i, _Ret(_First, _Rest...)> {
		using type = typename argument_of<_i-1, _Ret(_Rest...)>::type;
	};

	template<size_t _i, class _Ret>
	struct argument_of<_i, _Ret()> {
		using type = typename argument_of<_i-1, _Ret(_Rest...)>::type;
	};

	template<class _Ret, class _First, class... _Rest>
	struct argument_of<0, _Ret(_First, _Rest...)> {
		using type = _First;
	};
*/



	//template<typename T, typename R, typename... A>
	//std::tuple<A...> args_to_tuple(R(T::*)(A...))
	//{
	//	return std::tuple<A...>;
	//}

	//////////////////////////////////////////////////////////////////////////////

	template<unsigned...>
	struct seq {};

	template<unsigned N, unsigned... Is>
	struct gen_seq: gen_seq<N - 1, N - 1, Is...> {};

	template<unsigned... Is>
	struct gen_seq<0, Is...>: seq<Is...> {};

	template<size_t _n>
	constexpr gen_seq<_n> seq_v = gen_seq<_n>{};

	template<typename... Ts>
	struct type_seq: gen_seq<sizeof...(Ts)> {};


	template<class, class>
	struct join_seq;

	template<unsigned... _i1, unsigned... _i2>
	struct join_seq<seq<_i1...>, seq<_i2...>> {
		using type = seq<_i1..., _i2...>;
	};

	template<class _SeqL, class _SeqR>
	using join_seq_t = typename join_seq<_SeqL, _SeqR>::type;

	//////////////////////////////////////////////////////////////////////////////

	template<typename...>
	struct same_template
	{
		static constexpr bool value = false;
	};

	//template<
	//	template<typename...> typename T1,
	//	template<typename...> typename T2,
	//	typename... Y1,
	//	typename... Y2>
	//struct same_template<T1, T2<Y2...>>
	//{
	//	static constexpr bool value = false;
	//};

	template<
		template<typename...> typename T1,
		typename... Y1,
		typename... Y2>
		struct same_template<T1<Y1...>, T1<Y2...>>
	{
		static constexpr bool value = true;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename T, typename... Y>
	struct is_comparable
	{
		ADVANCED_MEMBER_TEST(has_compare_op, typename R, operator==, const, typename C);
		static constexpr bool value = any_true<has_compare_op<T, bool, Y>::value...>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct is_trivially_copyable
	{
		static constexpr bool value =
			std::is_trivially_copyable<T>::value ||
			std::is_base_of<triv_cpy, T>::value;
	};

	template<class _Type>
	struct is_pod
	{
		static constexpr bool value =
			std::is_pod<_Type>::value ||
			std::is_base_of<pod, _Type>::value;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<bool>
	struct _StaticIf;

	template<>
	struct _StaticIf<true>
	{};

	//////////////////////////////////////////////////////////////////////////////

	template<typename _Member>
	struct owner_of;

	template<class _Owner, typename _Ret, typename... _Args>
	struct owner_of<_Ret(_Owner::*)(_Args...)>
	{
		using type = _Owner;
	};

	template<class _Owner, typename _Ret>
	struct owner_of<_Ret(_Owner::*)>
	{
		using type = _Owner;
	};

	template<class _Member>
	using owner_of_t = typename owner_of<_Member>::type;

	//////////////////////////////////////////////////////////////////////////////

	template<class... _Func>
	struct return_type_of;
	//{
	//	__if_exists(_Func::operator()) {
	//		using type = typename return_type_of<_Func::operator()>::type;
	//	}
	//	/*__if_not_exists(_Func::operator()) {
	//		
	//	}*/
	//};

	/*template<class _Func>
	struct return_type_of<_Func>
	{
		using type = typename return_type_of<decltype(&_Func::operator())>::type;
	};*/

	template<class _Owner, class _Ret, class... _Arg>
	struct return_type_of<_Ret(_Owner::*)(_Arg...)>
	{
		using type = _Ret;
	};

	template<class _Owner, class _Ret, class... _Arg>
	struct return_type_of<_Ret(_Owner::*)(_Arg...) const>
	{
		using type = _Ret;
	};

	template<class _Owner, class _Ret, class... _Arg>
	struct return_type_of<_Ret(_Owner::*)(_Arg...) volatile>
	{
		using type = _Ret;
	};

	template<class _Owner, class _Ret, class... _Arg>
	struct return_type_of<_Ret(_Owner::*)(_Arg...) const volatile>
	{
		using type = _Ret;
	};

	template<class _Owner, class _Type>
	struct return_type_of<_Type(_Owner::*)>
	{
		using type = _Type;
	};

	template<class _Ret, class... _Arg>
	struct return_type_of<_Ret(*)(_Arg...)>
	{
		using type = _Ret;
	};

	template<class _Ret, class... _Arg>
	struct return_type_of<_Ret(_Arg...)>
	{
		using type = _Ret;
	};

	template<class _Member>
	using return_type_of_t = typename return_type_of<_Member>::type;

	//////////////////////////////////////////////////////////////////////////////

	template<class...>
	struct function_type_of;

	template<class _Owner, class _Ret, class... _Args>
	struct function_type_of<_Ret(_Owner::*)(_Args...)>
	{
		using type = _Ret(_Args...);
	};

	template<class _Ret, class... _Args>
	struct function_type_of<_Ret(*)(_Args...)>
	{
		using type = _Ret(_Args...);
	};

	template<class _Ret, class... _Args>
	struct function_type_of<_Ret(_Args...)>
	{
		using type = _Ret(_Args...);
	};

	template<class _Member>
	using function_type_of_t = typename function_type_of<_Member>::type;

//#define owner_of(...) typename x::_OwnerOf<decltype(__VA_ARGS__)>::type

	template<typename...>
	struct _result;

	template<typename R, typename... A>
	struct _result<R(A...)>
	{
		using type = R;
	};

	template<class T, typename R, typename... A>
	struct _result<R(T::*)(A...)>
	{
		using type = R;
	};

	template<class _Type>
	using same_type = _Type;

	//////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	struct is_naked
	{
		static constexpr bool value = 
			(std::is_fundamental<_Type>::value || std::is_class<_Type>::value) &&
			!std::is_const<_Type>::value && !std::is_volatile<_Type>::value;
	};

	template<class _Outer>
	using in_type = typename _Outer::type;

	template<class _Outer>
	using in_raw_type = typename _Outer::raw_type;

	template<class _Type>
	struct nested
	{
		using type = _Type;
	};

	template<class _Type>
	struct naked
	{
		using raw_type = _Type;
		using type = std::conditional_t<
			is_naked<_Type>::value,
			_Type, in_type<
				std::conditional_t<is_naked<_Type>::value, 
					nested<void>,
					naked<std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<_Type>>>>
				>
			>
		>;
	};

	template<class _Type>
	using naked_t = typename naked<_Type>::type;

	/*template<class _Type>
	using naked = std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<_Type>>>;*/



	//////////////////////////////////////////////////////////////////////////////

	template<class _OnTrue, class _OnFalse>
	struct StaticSelector
	{
		_OnTrue& onTrue;
		_OnFalse& onFalse;

		inline StaticSelector(
			_OnTrue& onTrue,
			_OnFalse& onFalse)
			:
			onTrue{onTrue},
			onFalse{onFalse}
		{
		}

		template<bool _cond>
		__forceinline std::enable_if_t<_cond == true,
			_OnTrue&> select() const
		{
			return onTrue;
		}

		template<bool _cond>
		__forceinline std::enable_if_t<_cond == false,
			_OnFalse&> select() const
		{
			return onFalse;
		}
	};


	///////////////////////////////////////////////////////////////////////////////


	template<class _Type, unsigned _dim>
	struct multi_ptr
	{
		using type = typename multi_ptr<_Type, _dim - 1>::type*;
	};

	template<class _Type>
	struct multi_ptr<_Type, 0>
	{
		using type = _Type;
	};

	template<class _Type, unsigned _dim>
	using multi_ptr_t = typename multi_ptr<_Type, _dim>::type;

	template<class _Type, unsigned _dim>
	using ptr_t = typename multi_ptr<_Type, _dim>::type;

	///////////////////////////////////////////////////////////////////////////////


	template<template<class> class _Temp>
	struct make_variadic
	{
		template<class... _Type>
		class type: public _Temp<_Type...>
		{
			using Base = _Temp<_Type...>;
		public:
			using Base::Base;
		};
	};

	
	/*template<class _Base, class _Der>
	class is_virtual_base_of
	{
		template<class = void>
		struct Derived: _Der
		{
		};

		template<class = void>
		struct VirtuallyDerived: virtual _Base, _Der
		{
		};

		static constexpr Derived

	public:
		static constexpr bool value = 
			std::is_base_of<_Base, _Der>::value && 
			sizeof(Derived) == sizeof(VirtuallyDerived);
	};*/

	template<class _Type>
	struct is_void
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_void<void>
	{
		static constexpr bool value = true;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<class>
	struct is_literal_string {
		static constexpr bool value = false;
	};

	template<size_t _size>
	struct is_literal_string<char const[_size]> {
		static constexpr bool value = true;
	};

	template<size_t _size>
	struct is_literal_string<char const(&)[_size]> {
		static constexpr bool value = true;
	};

	template<size_t _size>
	struct is_literal_string<char const(&&)[_size]> {
		static constexpr bool value = true;
	};

	template<class _Type>
	constexpr bool is_literal_string_v = is_literal_string<_Type>::value;

	///////////////////////////////////////////////////////////////////////////////
	

	template<class _Type, unsigned _dim>
	struct pointer
	{
		using type = typename pointer<_Type, _dim - 1>::type *;
	};

	template<class _Type>
	struct pointer<_Type, 1>
	{
		using type = _Type*;
	};

	template<class _Type>
	struct pointer<_Type, 0>
	{
		using type = _Type;
	};

	template<class _Type, unsigned _dim>
	using pointer_t = typename pointer<_Type, _dim>::type;

	///////////////////////////////////////////////////////////////////////////////


	template<class _Ret, class... _Args>
	using function_t = _Ret(_Args...);


	template<class... _Type>
	struct pack
	{
		template<class _Added>
		using add_type = pack<_Type..., _Added>;
	};

	template<class...>
	struct unpack_func_args;

	template<class _Ret, class... _PackedTypes>
	struct unpack_func_args<_Ret, pack<_PackedTypes...>>
	{
		using type = function_t<_Ret, _PackedTypes...>;
	};

	template<class _Type, int _size, class... _Buffer>
	struct uni_pack
	{
		using type = typename uni_pack<_Type, _size - 1, _Buffer..., _Type>::type;
	};

	template<class _Type, class... _Buffer>
	struct uni_pack<_Type, 0, _Buffer...>
	{
		using type = pack<_Buffer...>;
	};

	template<class _Ret, class _Arg, unsigned _narg>
	using gen_func_t = typename unpack_func_args<_Ret, typename uni_pack<_Arg, _narg>::type>::type;

	template<class _Ret, class _Arg, unsigned _narg>
	using gen_func_ptr_t = std::add_pointer_t<gen_func_t<_Ret, _Arg, _narg>>;


	///////////////////////////////////////////////////////////////////////////////////////////////


	//template<class _Stream, class _Type>
	//class is_output_streamable
	//{
	//	template<class _S, class _T>
	//	static auto test(int)
	//		-> decltype( std::declval<_S>() << std::declval<_T>(), std::true_type() );

	//	template<class, class>
	//	static auto test(...) 
	//		-> std::false_type;

	//public:
	//	static const bool value = 
	//		decltype(test<_Stream,_Type>(0))::value;
	//};

	//template<class _Stream, class _Type>
	//constexpr bool is_output_streamable_v = is_output_streamable<_Stream, _Type>::value;

	/////////////////////////////////////////////////////////////////////////////////////////////////

	//template<class _Stream, class _Type>
	//class is_input_streamable
	//{
	//	template<class _S, class _T>
	//	static constexpr auto test(int)
	//		-> decltype( std::declval<_S>() >> std::declval<_T>(), std::true_type() );

	//	template<class, class>
	//	static constexpr auto test(...) 
	//		-> std::false_type;

	//public:
	//	static constexpr bool value = 
	//		decltype(test<_Stream,_Type>(0))::value;
	//};

	//template<class _Stream, class _Type>
	//constexpr bool is_input_streamable_v = is_input_streamable<_Stream, _Type>::value;

	///////////////////////////////////////////////////////////////////////////////////////////////

	MEMBER_TEST(is_functor, operator());

	template<class _Func>
	constexpr bool is_functor_v = is_functor<_Func>::value;

	/*template<class _Func>
	struct is_callable {
		static constexpr bool value = is_functor_v<_Func> || std::is_function_v<_Func>;
	};

	template<class _Func>
	constexpr bool is_callable_v = is_callable<_Func>::value;*/

#define _GENERATE_PREFIX_UNARY_OPERATOR_CHECK(_name, _operator) \
	template<class _Type> \
	class _name \
	{ \
		template<class _T> \
		static constexpr auto test_(int) \
			-> decltype( _operator std::declval<_T&>(), std::true_type() ); \
		template<class, class> \
		static constexpr auto test_(...) \
			-> std::false_type; \
	public: \
		static constexpr bool value = \
			decltype(test_<_Type>(0))::value; \
	}; \
	template<class _Type> \
	constexpr bool _name##_v = _name<_Type>::value;


#define _GENERATE_POSTFIX_UNARY_OPERATOR_CHECK(_name, _operator) \
	template<class _Type> \
	class _name \
	{ \
		template<class _T> \
		static constexpr auto test_(int) \
			-> decltype( std::declval<_T&>() _operator, std::true_type() ); \
		template<class, class> \
		static constexpr auto test_(...) \
			-> std::false_type; \
	public: \
		static constexpr bool value = \
			decltype(test_<_Type>(0))::value; \
	}; \
	template<class _Type> \
	constexpr bool _name##_v = _name<_Type>::value;


#define _GENERATE_BINARY_OPERATOR_CHECK(_name, _operator) \
	template<class _Left, class _Right> \
	class _name \
	{ \
		template<class _L, class _R> \
		static constexpr auto test_(int) \
			-> decltype( std::declval<_L>() _operator std::declval<_R>(), std::true_type() ); \
		template<class, class> \
		static constexpr auto test_(...) \
			-> std::false_type; \
	public: \
		static constexpr bool value = \
			decltype(test_<_Left,_Right>(0))::value; \
	}; \
	template<class _Left, class _Right> \
	constexpr bool _name##_v = _name<_Left, _Right>::value;
	

	template<class _Left, class _Right>
	class is_functionally_callable
	{ 
		template<class _L, class _R> 
		static constexpr auto test_(int) 
			-> decltype( std::declval<_L>()(std::declval<_R>()), std::true_type() ); 
		template<class, class> 
		static constexpr auto test_(...) 
			-> std::false_type; 
	public: 
		static constexpr bool value = 
			decltype(test_<_Left,_Right>(0))::value; 
	}; 
	template<class _Left, class _Right> 
	constexpr bool is_functionally_callable_v = is_functionally_callable<_Left, _Right>::value;


	template<class _Left, class _Right>
	class is_indexable
	{ 
		template<class _L, class _R> 
		static constexpr auto test_(int) 
			-> decltype( std::declval<_L>()[std::declval<_R>()], std::true_type() ); 
		template<class, class> 
		static constexpr auto test_(...) 
			-> std::false_type; 
	public: 
		static constexpr bool value = 
		decltype(test_<_Left,_Right>(0))::value; 
	}; 
	template<class _Left, class _Right> 
	constexpr bool is_indexable_v = is_indexable<_Left, _Right>::value;


	APPLY_T(_GENERATE_BINARY_OPERATOR_CHECK,
			(is_assignable, =),
			(is_equal_comparable, ==),
			(is_not_equal_comparable, !=),
			(is_less_comparable, <),
			(is_less_or_equal_comparable, <=),
			(is_greater_comparable, >),
			(is_greater_or_equal_comparable, >=),
			(is_subtractable, -),
			(is_subtract_assignable, -=),
			(is_addible, +),
			(is_add_assignable, +=),
			(is_multipliable, *),
			(is_multiply_assignable, *=),
			(is_dividable, /),
			(is_divide_assignable, /=),
			(is_and_connectible, &&),
			(is_or_connectible, ||),
			(is_xor_connectible, ^),
			(is_xor_assignable, ^=),
			(is_bitand_connectible, &),
			(is_bitand_assignable, &=),
			(is_bitor_connectible, |),
			(is_bitor_assignable, |=),
			(is_left_shiftable, <<),
			(is_left_shift_assignable, <<=),
			(is_right_shiftable, >>),
			(is_right_shift_assignable, >>=),
			(is_modulo_computable, %),
			(is_modulo_assignable, %=));

	//template<class _Type> 
	//class is_predecrementable
	//{ 
	//	template<class _T> 
	//	static constexpr auto test_(int) 
	//	-> decltype( (--std::declval<_T>()), std::true_type() ); 
	//	template<class, class> 
	//	static constexpr auto test_(...) 
	//	-> std::false_type; 
	//public: 
	//	static constexpr bool value = 
	//	decltype(test_<_Type>(0))::value; 
	//}; 
	//	template<class _Type> 
	//	constexpr bool _name##_v = _name<_Type>::value;

	APPLY_T(_GENERATE_PREFIX_UNARY_OPERATOR_CHECK,
			(is_predecrementable, --),
			(is_preincrementable, ++),
			(is_negatable, !),
			(is_bitwise_negatable, ~),
			(is_addressable, &),
			//(is_dereferencable, *),
			(is_inversible, -),
			(is_promotable, +));

	/*APPLY_T(_GENERATE_POSTFIX_UNARY_OPERATOR_CHECK,
			(is_postdecrementable, --),
			(is_postincrementable, ++));*/



	/*template<class _Type> 
	class is_promotable 
	{ 
		template<class _T> 
		static constexpr auto test_(int) 
			-> decltype(+std::declval<_T>(), std::true_type());
		template<class, class> 
		static constexpr auto test_(...) 
			-> std::false_type; 
	public: 
		static constexpr bool value = 
			decltype(test_<_Type>(0))::value; 
	}; 
	template<class _Type> 
	constexpr bool is_promotable_v = is_promotable<_Type>::value;*/


		using opid_t = size_t;

		constexpr opid_t operator_id(char op) {
			switch (op) {
			case '!': return 0;
			case '%': return 1;
			case '&': return 2;
			case '*': return 3;
			case '+': return 4;
			case '-': return 5;
			case '/': return 6;
			case '<': return 7;
			case '=': return 8;
			case '>': return 9;
			case '^': return 10;
			case '|': return 11;
			case '~': return 12;
			default: return -1;
			}
		}

		constexpr opid_t operator_id(const char(&op)[2]) {
			return operator_id(op[0]);
		}

		template<class _Left, class _Right = _Left>
		constexpr bool has_operator(char op) {
			switch (op) {
			case '!': return is_negatable_v<_Left>;
			case '%': return is_modulo_computable_v<_Left, _Right>;
			case '&': return is_addressable_v<_Left> || is_bitand_connectible_v<_Left, _Right>;
			//case '*': return is_dereferencable_v<_Left>;
			case '+': return is_promotable_v<_Left> || is_addible_v<_Left, _Right>;
			case '-': return is_inversible_v<_Left> || is_subtractable_v<_Left, _Right>;
			case '/': return is_dividable_v<_Left, _Right>;
			case '<': return is_less_comparable_v<_Left, _Right>;
			case '=': return is_assignable_v<_Left&, _Right>;
			case '>': return is_greater_comparable_v<_Left, _Right>;
			case '^': return is_xor_connectible_v<_Left, _Right>;
			case '|': return is_bitor_connectible_v<_Left, _Right>;
			case '~': return is_bitwise_negatable_v<_Left>;
			default: return false;
			}
		}

		template<class _Left, class _Right = _Left>
		constexpr bool has_operator(const char(&op)[2]) {
			switch (op[0]) {
			case '!': return is_negatable_v<_Left>;
			case '%': return is_modulo_computable_v<_Left, _Right>;
			case '&': return is_addressable_v<_Left>;
			//case '*': return is_dereferencable_v<_Left>;
			case '+': return is_promotable_v<_Left> || is_addible_v<_Left, _Right>;
			case '-': return is_inversible_v<_Left> || is_subtractable_v<_Left, _Right>;
			case '/': return is_dividable_v<_Left, _Right>;
			case '<': return is_less_comparable_v<_Left, _Right>;
			case '=': return is_assignable_v<_Left&, _Right>;
			case '>': return is_greater_comparable_v<_Left, _Right>;
			case '^': return is_xor_connectible_v<_Left, _Right>;
			case '|': return is_bitor_connectible_v<_Left, _Right>;
			case '~': return is_bitwise_negatable_v<_Left>;
			default: return false;
			}
		}

		template<class _Left, class _Right = _Left>
		constexpr bool has_operator(const char(&op)[3]) {
			//static_assert(op[2] == '\0');
			switch (op[0]) {
			case '!': 
				switch (op[1]) {
				case '=': return is_not_equal_comparable_v<_Left, _Right>;
				default: return false;
				}
			case '%':
				switch (op[1]) {
				case '=': return is_modulo_assignable_v<_Left, _Right>;
				default: return false;
				}
			case '&':
				switch (op[1]) {
				case '=': return is_bitor_assignable_v<_Left, _Right>;
				case '&': return is_and_connectible_v<_Left, _Right>;
				default: return false;
				}
			case '*':
				switch (op[1]) {
				case '=': return is_multiply_assignable_v<_Left&, _Right>;
				default: return false;
				}
			case '+':
				switch (op[1]) {
				case '=': return is_add_assignable_v<_Left&, _Right>;
				//case '+': return is_preincrementable_v<_Left> || is_postincrementable_v<_Left>;
				default: return false;
				}
			case '-':
				switch (op[1]) {
				case '=': return is_subtract_assignable_v<_Left&, _Right>;
				//case '-': return is_predecrementable_v<_Left> || is_postdecrementable_v<_Left>;
				default: return false;
				}
			case '/':
				switch (op[1]) {
				case '=': return is_divide_assignable_v<_Left&, _Right>;
				default: return false;
				}
			case '<':
				switch (op[1]) {
				case '=': return is_less_or_equal_comparable_v<_Left, _Right>;
				case '<': return is_left_shiftable_v<_Left, _Right>;
				default: return false;
				}
			case '=':
				switch (op[1]) {
				case '=': return is_equal_comparable_v<_Left, _Right>;
				default: return false;
				}
			case '>':
				switch (op[1]) {
				case '=': return is_greater_or_equal_comparable_v<_Left, _Right>;
				case '>': return is_right_shiftable_v<_Left, _Right>;
				default: return false;
				}
			case '^':
				switch (op[1]) {
				case '=': return is_xor_assignable_v<_Left&, _Right>;
				default: return false;
				}
			case '|':
				switch (op[1]) {
				case '=': return is_bitor_assignable_v<_Left&, _Right>;
				case '|': return is_or_connectible_v<_Left, _Right>;
				default: return false;
				}
			default: return false;
			}
		}

		template<class _Left, class _Right = _Left>
		constexpr bool has_operator(const char(&op)[4]) {
			switch (op[0]) {
			case '<':
				switch (op[1]) {
				case '<':
					switch (op[2]) {
					case '=': return is_left_shift_assignable_v<_Left&, _Right>;
					default: return false;
					}
				default: return false;
				}
			case '>':
				switch (op[1]) {
				case '>':
					switch (op[2]) {
					case '=': return is_right_shift_assignable_v<_Left&, _Right>;
					default: return false;
					}
				default: return false;
				}
			default: return false;
			}
		}

#define DECLARE_THIS_T \
__if_not_exists(this_t) { \
private: \
	void _member_() { } \
public: \
	using this_t = x::owner_of_t<decltype(&_member_)>; \
}

//#define _result(_fn) x::_result<std::remove_pointer_t<decltype(_fn)>>::type
#define _concept class = std::enable_if_t
#define _capture(_Type) class _Type = _Type
#define _suspend template<class _Suspender = void>

#define THIS_TYPE template<class=void> inline constexpr void __member__(){}\
	using this_type = x::owner_of_t<decltype(&__member__<>)>;
}

#endif //MORE_TYPE_TRAITS_H