#ifndef _X_CHAR_CLASS_H_
#define _X_CHAR_CLASS_H_

#include "bitliteral.h"
#include "xarray.h"

namespace x
{
	using char_class_t = __int16;

	enum CharClass: char_class_t
	{
		WHITESPACE = x::BIT<0, char_class_t>,
		UPPER = x::BIT<1, char_class_t>,
		LOWER = x::BIT<2, char_class_t>,
		VISIBLE = x::BIT<3, char_class_t>,
		DIGIT = x::BIT<4, char_class_t>,
		LETTER = x::BIT<5, char_class_t>,
		BINARY = x::BIT<6, char_class_t>,
		OCTAL = x::BIT<7, char_class_t>,
		HEXADECIMAL = x::BIT<8, char_class_t>,
		ALPHANUMERIC = x::BIT<9, char_class_t>,
		PRINTABLE = x::BIT<10, char_class_t>,
		CONTROL = x::BIT<11, char_class_t>,
		WORD = x::BIT<12, char_class_t>,
		SYMBOL = x::BIT<13, char_class_t>,
		ASCII = x::BIT<14, char_class_t>,
		UTF8 = x::BIT<15, char_class_t>
	};

	constexpr char whitespace[] = {'	', ' '};
	constexpr char uppercase[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	constexpr char lowercase[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	constexpr char visible[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};
	constexpr char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	constexpr char letter[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	constexpr char binary[] = {'0', '1'};
	constexpr char octal[] = {'0', '1', '2', '3', '4', '5', '6', '7'};
	constexpr char hexadecimal[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f'};
	constexpr char hexupper[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	constexpr char hexlower[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	constexpr char alphanumeric[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	constexpr char printable[] = {'	', ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};
	constexpr char control[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, '	', 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x7f};
	constexpr char word[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	constexpr char symbol[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'};
	constexpr char ascii[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, '	', 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 0x7f};


	constexpr char_class_t CHAR_CLASS_MAP[256] = {
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL | WHITESPACE | PRINTABLE,

		UTF8 | ASCII | CONTROL | WHITESPACE | PRINTABLE,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,

		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,

		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | CONTROL,
		UTF8 | ASCII | WHITESPACE | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,

		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | BINARY | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | BINARY | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | OCTAL | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | DIGIT | HEXADECIMAL | ALPHANUMERIC | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,

		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | UPPER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | HEXADECIMAL | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,

		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | LETTER | ALPHANUMERIC | LOWER | WORD | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | VISIBLE | SYMBOL | PRINTABLE,
		UTF8 | ASCII | CONTROL,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,

		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8,
		UTF8
	};

	__forceinline constexpr bool is_whitespace(char ch) noexcept
	{
		return (ch >= 0x09 && ch <= 0x0D) || ch == 0x20;
	}

	__forceinline constexpr bool is_upper(char ch) noexcept
	{
		return ch >= 'A' && ch <= 'Z';
	}

	__forceinline constexpr bool is_lower(char ch) noexcept
	{
		return ch >= 'a' && ch <= 'z';
	}

	__forceinline constexpr bool is_visible(char ch) noexcept
	{
		return ch >= 0x21 && ch <= 0x7E;
	}

	__forceinline constexpr bool is_digit(char ch) noexcept
	{
		return ch >= '0' && ch <= '9';
	}

	__forceinline constexpr bool is_letter(char ch) noexcept
	{
		return is_upper(ch) || is_lower(ch);
	}

	__forceinline constexpr bool is_binary(char ch) noexcept
	{
		return ch == '0' || ch == '1';
	}

	__forceinline constexpr bool is_alphanumeric(char ch) noexcept
	{
		return is_letter(ch) || is_digit(ch);
	}

	__forceinline constexpr bool is_printable(char ch) noexcept
	{
		return is_alphanumeric(ch) || is_whitespace(ch);
	}

	__forceinline constexpr bool is_control(char ch) noexcept
	{
		return ch < 0x1F || ch == 0x7F;
	}

	__forceinline constexpr bool is_word(char ch) noexcept
	{
		return is_alphanumeric(ch) || ch == '_';
	}

	__forceinline constexpr bool has_class(char ch, char_class_t chclass) noexcept
	{
		return (CHAR_CLASS_MAP[ch] & chclass) != 0;
	}

	template<char_class_t _chclass>
	__forceinline constexpr bool is(char ch)
	{
		return CHAR_CLASS_MAP[ch] & _chclass;
	}


	__forceinline constexpr char_class_t class_of(char ch) noexcept
	{
		return CHAR_CLASS_MAP[ch];
	}
}
#endif //_X_CHAR_CLASS_H_
