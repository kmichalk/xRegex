#pragma once

#include "Buffer.h"

namespace x
{
	//the string buffer class, extending functionalities of buffer, adding string handling
	class StringBuffer: public Buffer<char>
	{
	public:
		using Buffer<char>::Buffer;
		//reserve mem and put string in buffer
		char* append(char const* str);
		//reserve mem and put string in buffer, optimized, because of known size
		char* append(char const* begin, char const* end);
		//reserve mem and put string in buffer, optimized, because of known size
		char* append(char const* str, size_t size);
		//reserve mem for single char
		char* append(char ch);

		//reserve mem and put static string of known size
		template<size_t _size>
		char* append(char const(&str)[_size]);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////

template<size_t _size>
char* x::StringBuffer::append(char const(&str)[_size]) {
	char* p = reserve(_size);
	strncpy(p, str, _size - 1);
	return p;
}
