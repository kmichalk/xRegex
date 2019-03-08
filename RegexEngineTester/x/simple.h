#ifndef _SIMPLE_H_
#define _SIMPLE_H_

#include "more_type_traits.h"
#include "ctmath.h"
#include "_void.h"
#include "two.h"
#include "wkey.h"
#include "fake.h"
#include <cmath>

#define PI 3.141592653589793
#define FPI 3.141592653589793f
#define FPI2 1.570796326794896f

#undef min
#undef max

#define enable_if std::enable_if_t

namespace x
{
	template<typename T1, typename T2>
	inline constexpr auto min(T1 n1, T2 n2) noexcept
	{
		return n1 < n2 ? n1 : n2;
	}

	template<typename T1, typename T2>
	inline constexpr auto max(T1 n1, T2 n2) noexcept
	{
		return n1 > n2 ? n1 : n2;
	}

	template<typename T1, typename T2 = int>
	inline constexpr auto cutl(T1 val, T2 limit = 0) noexcept
	{
		return val < limit ? limit : val;
	}

	template<typename T1, typename T2 = int>
	inline constexpr auto cutg(T1 val, T2 limit = 0) noexcept
	{
		return val > limit ? limit : val;
	}

	template<typename T1, typename T2, typename T3>
	inline constexpr auto cutr(T1 val, T2 a, T3 b) noexcept
	{
		return val < a ? a : val > b ? b : val;
	}

	template<class _Type/*, class _TypeConst = std::conditional_t<sizeof(_Type) <= 4, _Type, _Type const&>*/>
	__inline bool between(_Type const& value, _Type const& min, _Type const& max) {
		return value >= min && value <= max;
	}

	template<class _Type/*, class _TypeConst = std::conditional_t<sizeof(_Type) <= 4, _Type, _Type const&>*/>
	__inline bool beyond(_Type const& value, _Type const& min, _Type const& max) {
		return value < min || value > max;
	}

	template <typename _Type, typename _Ret = int>
	inline constexpr _Ret sgn(_Type val) noexcept
	{
		return (_Type(0) < val) - (val < _Type(0));
	}

	template<typename _Type>
	inline constexpr enable_if<std::is_floating_point<_Type>::value,
		_Type> mant(_Type val) noexcept
	{
		return val - int(val);
	}

	template<typename _Type, typename = enable_if<true>>
	inline constexpr enable_if<std::is_integral<_Type>::value,
		double> mant(_Type val) noexcept
	{
		return 0;
	}

	template<class _Type>
	__forceinline _Type& negate(_Type& value)
	{
		return (value = -value);
	}

	namespace va
	{



		template<class... _Type>
		using _operation_result = std::conditional_t<x::every_is<int, _Type...>::value, int, double>;

		/*template<typename _Ret = double, typename... _Args>
		inline _operation_result<_Args...> sum(_Args... args)
		{
			_operation_result<_Args...> result = 0;
			x::va::x::va::expand((result += args)...);
			return result;
		}

		template<typename _Ret = double, typename... _Args>
		inline _operation_result<_Args...> mult(_Args... args)
		{
			_operation_result<_Args...> result = 1;
			x::va::x::va::expand((result *= args)...);
			return result;
		}*/

		template<class... _Arg>
		constexpr auto sum(_Arg... args) {
			return (args + ...);
		}

		template<class _First>
		__forceinline auto min(_First first)
		{
			return first;
		}

		template<class _First, class _Rest>
		__forceinline auto min(_First first, _Rest rest)
		{
			return first < rest ? first : rest;
		}

		template<class _First, class... _Rest>
		__forceinline auto min(_First first, _Rest... rest)
		{
			return min(first, min(rest...));
		}


		template<class _First, class _Rest>
		__forceinline auto max(_First first, _Rest rest)
		{
			return first > rest ? first : rest;
		}

		template<class _First, class... _Rest>
		__forceinline auto max(_First first, _Rest... rest)
		{
			return max(first, max(rest...));
		}

		/*template<typename _Ret = double, typename... _Args>
		inline _operation_result<_Args...> sum(_Args... args)
		{
			_operation_result<_Args...> result = 0;
			x::va::x::va::expand((result += args)...);
			return result;
		}

		template<typename _Ret = double, typename... _Args>
		inline _operation_result<_Args...> vmult(_Args... args)
		{
			_operation_result<_Args...> result = 1;
			x::va::x::va::expand((result *= args)...);
			return result;
		}*/
	}

	/*Function checking if floating point number is near to 0 with specified error.*/
	template<unsigned rangePow = 6, typename _Type>
	inline constexpr enable_if<std::is_floating_point<_Type>::value,
		_Type> is_zero(_Type val)
	{
		return val > -x::ct::pow(0.1, rangePow) && val < x::ct::pow(0.1, rangePow);
	}

	/*Function checking if floating point number is near to 0 with specified error.*/
	template<typename _Type>
	inline constexpr enable_if<std::is_integral<_Type>::value,
		double> is_zero(_Type val)
	{
		return val == 0;
	}

	/*Function checking if floating point number is NOT near to 0 with specified error.*/
	template<unsigned rangePow = 6, typename _Type>
	inline constexpr enable_if<std::is_floating_point<_Type>::value,
		_Type> not_zero(_Type val)
	{
		return val < -x::ct::pow(0.1, rangePow) || val > x::ct::pow(0.1, rangePow);
	}

	/*Function checking if floating point number is NOT near to 0 with specified error.*/
	template<typename _Type, typename = enable_if<true>>
	inline constexpr enable_if<std::is_integral<_Type>::value,
		double> not_zero(_Type val)
	{
		return val;
	}

	template<typename _Type>
	two<_Type> solve_eq(_Type a, _Type b, _Type c)
	{
		auto delta = sqrt(b*b - 4 * a*c);
		return{(-b - delta) / (2 * a),(-b + delta) / (2 * a)};
	}

	/*Normalize angle value in radians to fit range [0,360).*/
	template<typename _Type>
	_Type norm_rf(_Type val)
	{
		val = fmod(val, 2 * PI);
		if (val < 0) val += 2 * PI;
		return val;
	}

	/*Normalize angle value in radians to fit range [-180,180).*/
	template<typename _Type>
	_Type norm_rh(_Type val)
	{
		val = fmod(val + PI, 2 * PI);
		if (val < 0) val += 2 * PI;
		return val - PI;
	}

	/*Normalize angle value in degrees to fit range [0,360).*/
	template<typename _Type>
	_Type norm_df(_Type val)
	{
		val = fmod(x, 360.0);
		if (val < 0) val += 360.0;
		return val;
	}

	/*Normalize angle value in degrees to fit range [-180,180).*/
	template<typename _Type>
	_Type norm_dh(_Type val)
	{
		val = fmod(val + 180.0, 360.0);
		if (val < 0) val += 360.0;
		return val - 180.0;
	}
	/*enum SolveMode{ NORMAL, ENABLE_1, THROW};

	template<typename _Type, SolveMode mode = NORMAL>
	enable_if<mode==NORMAL,
		two<_Type>> solve_eq(_Type a, _Type b, _Type c)
	{
		auto delta = sqrt(b*b-4*a*c);
		return{(-b-delta)/(2*a),(-b+delta)/(2*a)};
	}

	template<typename _Type, SolveMode mode = NORMAL>
	enable_if<mode==ENABLE_1,
		two<_Type>> solve_eq(_Type a, _Type b, _Type c)
	{
		auto delta = sqrt(b*b-4*a*c);
		return{
			(-b-delta)/(2*a),
			delta ? (-b+delta)/(2*a) : nan()};
	}

	template<typename _Type, SolveMode mode = NORMAL>
	enable_if<mode==THROW,
		two<_Type>> solve_eq2(_Type a, _Type b, _Type c)
	{
		auto delta = b*b-4*a*c;
		if (delta<0) throw 0;
		delta = sqrt(delta);
		return{(-b-delta)/(2*a),(-b+delta)/(2*a)};
	}*/

	template<typename _Type>
	__forceinline constexpr auto pow2(_Type value) noexcept
	{
		return value*value;
	}

	template<typename _Type>
	__forceinline constexpr auto pow3(_Type value) noexcept
	{
		return value*value*value;
	}

	template<typename _Type>
	__forceinline constexpr bool is_nan(_Type value) noexcept
	{
		return value != value;
	}

	template<typename _Type>
	__forceinline constexpr auto to_deg(_Type value) noexcept
	{
		return value / PI*180.0;
	}

	template<typename _Type>
	__forceinline constexpr auto to_rad(_Type value) noexcept
	{
		return value*PI / 180.0;
	}

	__forceinline constexpr bool even(int value) noexcept
	{
		return (value % 2) == 0;
	}

	__forceinline constexpr bool odd(int value) noexcept
	{
		return (value % 2) != 0;
	}

	template<class _Type>
	__forceinline _Type round(_Type value, _Type to = _Type(1))
	{
		if (abs(to) < abs(value))
			return value - fmod(value, to);
		else
			return to;
	}

	template<class _A, class... _As>
	bool constexpr none_of(_A a, _As... as) {
		return ((a != as) && ...);
	}

	template<class _A>
	bool constexpr none_of(_A a) {
		return false;
	}

	template<class _A, class... _As>
	bool constexpr any_of(_A a, _As... as) {
		return ((a == as) || ...);
	}

	template<class _A>
	bool constexpr any_of(_A a) {
		return false;
	}

	template<class... _Arg>
	constexpr auto bitor(_Arg... args) {
		return (args | ...);
	}

	///////////////////////////////////////////////////////////////////////////////


	template<class _Type>
	__inline void swap(_Type& a, _Type& b) noexcept {
		fake<_Type> t = reinterpret_cast<fake<_Type>&>(a);
		reinterpret_cast<fake<_Type>&>(a) = reinterpret_cast<fake<_Type>&>(b);
		reinterpret_cast<fake<_Type>&>(b) = t;
	}

	template<class _Type>
	__inline void swapp(_Type* a, _Type* b) noexcept {
		fake<_Type> t = *reinterpret_cast<fake<_Type>*>(a);
		*reinterpret_cast<fake<_Type>*>(a) = *reinterpret_cast<fake<_Type>*>(b);
		*reinterpret_cast<fake<_Type>*>(b) = t;
	}

	/*template<class _Type>
	__forceinline void assign(_Type& dest, _Type const& src) noexcept {
		if constexpr (std::is_trivially_copy_assignable_v<_Type>)
			dest = src;
		else
			reinterpret_cast<fake<_Type>&>(dest) = reinterpret_cast<fake<_Type> const&>(src);
	}*/

	template<class _Type>
	__forceinline void assign(_Type* dest, _Type const* src) noexcept {
		if constexpr (std::is_trivially_copy_assignable_v<_Type> &&
					  std::is_trivially_copy_constructible_v<_Type>)
			*dest = *src;
		else
			*reinterpret_cast<fake<_Type>*>(dest) = *reinterpret_cast<fake<_Type> const*>(src);
	}

	/*template<class _Type>
	__forceinline void assign(_Type* dest, _Type const& src) noexcept {
		if constexpr (std::is_trivially_copy_assignable_v<_Type>)
			*dest = src;
		else
			*reinterpret_cast<fake<_Type>*>(dest) = reinterpret_cast<fake<_Type> const&>(src);
	}*/

	/*template<class _Type, size_t _size>
	__inline void assign(_Type(&dest)[_size], _Type const(&src)[_size]) noexcept {
		reinterpret_cast<fake<_Type>&>(dest) = reinterpret_cast<fake<_Type> const&>(src);
	}*/

#define _SWAP_DWORD(_i) \
	if constexpr (_i < sizeof(_Type) / 4) { \
		_asm mov ecx, [eax+_i*4] \
		_asm mov edx, [ebx+_i*4] \
		_asm mov [eax+_i*4], edx \
		_asm mov [ebx+_i*4], ecx \
	}

	//_asm xchg ecx, [ebx+_i] \

	template<class _Type>
	void asm_swap(_Type& a, _Type& b) {
		//__int8 copydata[sizeof(_Type)];
		_asm mov eax, [a]
		_asm mov ebx, [b]
		APPLY(_SWAP_DWORD, RANGE(64));
	}

}



#undef enable_if
#endif //SIMPLE_H
