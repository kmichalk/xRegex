#include "stdafx.h"
#include "StringBuffer.h"

#pragma warning(push)
#pragma warning(disable: 4996)

char * x::StringBuffer::append(char const * str) {
	size_t length = strlen(str);
	char* p = reserve(length + 1);
	strncpy(p, str, length);
	return p;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char * x::StringBuffer::append(char const * begin, char const * end) {
	size_t size = end - begin;
	char* p = reserve(size + 1);
	strncpy(p, begin, size);
	return p;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char * x::StringBuffer::append(char const * str, size_t size) {
	char* p = reserve(size + 1);
	strncpy(p, str, size);
	return p;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char * x::StringBuffer::append(char ch) {
	char* p = reserve(2);
	p[0] = ch;
	p[1] = '\0';
	return p;
}

#pragma warning(pop)