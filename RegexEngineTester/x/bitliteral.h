#ifndef BITLITERAL_H
#define BITLITERAL_H

#include <cstdint>
#include <limits>
#include "typearr.h"
////#include "__int8.h"


template<typename _Type, char... _rest>
struct conv2bin;

template<typename _Type, char _first, char... _rest>
struct conv2bin<_Type, _first, _rest...>
{
	static_assert(_first == '0' || _first == '1',
		"Not valid binary number.");

	_Type static constexpr value =
		(_first - '0') * (1 << sizeof...(_rest)) +
		conv2bin<_Type, _rest...>::value;
};

template<typename _Type, char _first>
struct conv2bin<_Type, _first>
{
	static_assert(_first == '0' || _first == '1',
		"Not valid binary number.");

	_Type static constexpr value =
		(_first - '0');
};

using _IntTypes = x::TypeArray<
	__int8,
	int16_t,
	int32_t,
	int64_t>;

using _UIntTypes = x::TypeArray<
	uint8_t,
	uint16_t,
	uint32_t,
	uint64_t>;

template<unsigned _nBits>
using _MinFitType =
_IntTypes::get<
	1 +
	(_nBits > 8) +
	(_nBits > 16) +
	(_nBits > 32)>;

template<unsigned _nBits>
using _MaxLessType =
_IntTypes::get<
(_nBits <= 8) +
(_nBits <= 16) +
(_nBits <= 32) +
(_nBits <= 64)>;

template<char... _digits>
__forceinline constexpr typename _MinFitType<sizeof...(_digits)> operator "" _b()
{
	return conv2bin<_MinFitType<sizeof...(_digits)>, _digits...>::value;
}



namespace x
{
	template<size_t _bitNum, class _Type = unsigned __int32>
	constexpr _Type BIT = _Type(1) << _bitNum;

	template<class _Type>
	constexpr _Type FIRST_BIT = _Type(1) << (sizeof(_Type) * 8 - 1);

	template<class _Type>
	constexpr _Type LAST_BIT = _Type(1);

	template<class _Type, size_t _n>
	constexpr _Type BYTE = (_Type)0xFF << (_n * 8);

	template<class _Type>
	static constexpr size_t BIT_SIZE = sizeof(_Type) * 8;

	template<uint64_t _value>
	using smallest_type =
		_UIntTypes::get <
		1 +
		(_value > (1ull << 8)) + 
		(_value > (1ull << 16)) +
		(_value > (1ull << 32))
		//(_value > std::numeric_limits<uint16_t>::max() + 1) +
		//(_value > std::numeric_limits<uint32_t>::max() + 1)>;
	>;
}

#define bitsizeof(_Type) x::BIT_SIZE<_Type>


#endif //BITLITERAL_H
