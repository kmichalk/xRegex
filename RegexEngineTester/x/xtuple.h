#ifndef _X_TUPLE_H_
#define _X_TUPLE_H_

#include "vamacros.h"
#include "more_type_traits.h"
#include <iostream>
#include <stddef.h>


#define _REMOVE_FIRST(_0, ...) __VA_ARGS__
//#define _APPLY_CONDITIONAL_TUPLE_FUNCTION_BODY(...) APPLY(_CONDITIONAL_TUPLE_FUNCTION_BODY, __VA_ARGS__)
//#define _NATURAL_RANGE(_n) SEPARATE(_REMOVE_FIRST, (RANGE(_n)))
#define _TUPLE_N_RANGE SEPARATE(_REMOVE_FIRST, (RANGE(65)))

#define _FIELD_PREFIX _
#define _FIELD_NAME(_n) _##_n
#define _DECLARE_FIELD(_prefix, _n) x::select_t<_n+1, _Type...> _prefix##_n;
#define _TUPLE_NAME(_n) _tuple_##_n
#define _TUPLE_NAME_WITH_PARAMETERS(_args,_n) _TUPLE_NAME(_n) _args,


#define _CONDITIONAL_PASS_TO_OSTREAM(_n) \
	if constexpr (sizeof...(_Type) >= _n) { \
		os << _FIELD_NAME(_n); \
	}

#define _TO_OSTREAM(_var, _n) \
		os << _var._FIELD_NAME(_n) << ' ';

#define _FROM_ISTREAM(_var, _n) \
		is >> _var._FIELD_NAME(_n);

#define _GENERATE_OSTREAM_OPERATOR(_n) \
	inline friend std::ostream& operator << (std::ostream& os, _TUPLE_NAME(_n) const& t) { \
		APPLY_2(_TO_OSTREAM, t, RANGE(_n)); \
		return os; \
	}

#define _GENERATE_ISTREAM_OPERATOR(_n) \
	inline friend std::istream& operator >> (std::istream& is, _TUPLE_NAME(_n) & t) { \
		APPLY_2(_FROM_ISTREAM, t, RANGE(_n)); \
		return is; \
	}

#define _DECLARE_SIZE(_n) static constexpr size_t size = _n

//#define _CONDITIONAL_TUPLE_FUNCTION_BODY(_n) \
//	if constexpr (_n == sizeof...(_Type)) { \
//		_GENERATE_TUPLE_STRUCT(_n); \
//		return _TUPLE_NAME(_n)<_Type...>{values...}; \
//	}

#define _ELEM_OFFSET(_Tuple, _i) offsetof(_Tuple, _FIELD_NAME(_i))
#define _OFFSET_OF_CASE(_Tuple, _i) case _i: return _ELEM_OFFSET(_Tuple, _i);

#define _GENERATE_OFFSET_TABLE(_Self, _n) \
	static constexpr size_t OFFSET_[_n] = { \
		APPLY_2(_ELEM_OFFSET, self, RANGE(_n)); \
	};

#define _DECLARE_OFFSETOF static constexpr size_t offset_of(size_t i)

#define _GENERATE_OFFSET_OF(_Tuple, _n) \
	template<class... _Type> \
	constexpr size_t _Tuple<_Type...>::offset_of(size_t i) { \
		using _Self = _Tuple<_Type...>; \
		switch (i) { \
			APPLY_2(_OFFSET_OF_CASE, _Self, RANGE(_n)); \
			default: return -1; \
		} \
	}

#define _COMPARE_EQUAL(_i) _FIELD_NAME(_i) == other._FIELD_NAME(_i)

#define _GENERATE_OPERATOR_EQUAL(_Tuple, _n) \
	bool operator==(_Tuple const& other) const { \
		return APPLY_S(_COMPARE_EQUAL, &&, RANGE(_n)); \
	}

#define _COMPARE_NOT_EQUAL(_i) _FIELD_NAME(_i) != other._FIELD_NAME(_i)

#define _GENERATE_OPERATOR_NOT_EQUAL(_Tuple, _n) \
	bool operator!=(_Tuple const& other) const { \
		return APPLY_S(_COMPARE_NOT_EQUAL, ||, RANGE(_n)); \
	}

template<class _Type, size_t _size>
using array_ref = _Type(&)[_size];

#define _GENERATE_TUPLE_STRUCT(_n) \
	template<class... _Type> \
	struct _TUPLE_NAME(_n) { \
		using self = _TUPLE_NAME(_n)<_Type...>; \
		APPLY_2(_DECLARE_FIELD, _FIELD_PREFIX, RANGE(_n)); \
		_GENERATE_OSTREAM_OPERATOR(_n); \
		_GENERATE_ISTREAM_OPERATOR(_n); \
		_DECLARE_SIZE(_n); \
		_DECLARE_OFFSETOF; \
		_GENERATE_OPERATOR_EQUAL(_TUPLE_NAME(_n), _n); \
		_GENERATE_OPERATOR_NOT_EQUAL(_TUPLE_NAME(_n), _n); \
	}; \
	_GENERATE_OFFSET_OF(_TUPLE_NAME(_n), _n); 

//template<class _Void = void> \
//__forceinline std::enable_if_t<std::is_void_v<_Void> && x::all_same<_Type...>::value, \
//	array_ref<x::first_t<_Type...>, sizeof...(_Type)>> to_array() { \
//	return reinterpret_cast<array_ref<x::first_t<_Type...>,sizeof...(_Type)>>(*this); \
//} \
//template<class _Void = void> \
//__forceinline std::enable_if_t<std::is_void_v<_Void> && x::all_same<_Type...>::value, \
//	const array_ref<x::first_t<_Type...>, sizeof...(_Type)>> to_array() const { \
//	return reinterpret_cast<const array_ref<x::first_t<_Type...>,sizeof...(_Type)>>(*this); \
//} \

namespace x
{
	APPLY(_GENERATE_TUPLE_STRUCT, _TUPLE_N_RANGE);

	template<class... _Type>
	using tuple = select_t<sizeof...(_Type), APPLY_2(_TUPLE_NAME_WITH_PARAMETERS,<_Type...>,_TUPLE_N_RANGE) void>;

	template<class... _Type>
	__forceinline constexpr auto make_tuple(_Type... values) {
		return tuple<_Type...>{values...};
	}
}

//#undef offsetof

#endif //_X_TUPLE_H_
