#include "stdafx.h"
#include "RandomString.h"
#include "Random.h"


std::string RandomString::get(std::string const& symbols, size_t length) {
	std::string s(length, 0);
	size_t symbolslen = symbols.length();
	for (size_t i = 0; i < length; ++i)
		s[i] = symbols[Random::nextInt((int)symbolslen)];
	return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::string RandomString::get(std::string const& symbols, size_t nSub, size_t minSubLength, size_t maxSubLength) {
	std::string s;
	s.resize(nSub*maxSubLength);
	size_t symbolslen = symbols.length();
	size_t i = 0;
	char prevSymbol = 0;
	char symbol;
	for (size_t n = 0; n < nSub; ++n) {
		int subLength = Random::nextInt((int)minSubLength, (int)maxSubLength);
		do {
			symbol = symbols[Random::nextInt((int)symbolslen)];
		} while (symbol == prevSymbol);
		prevSymbol = symbol;
		size_t iSubMax = i + subLength;
		while (i < iSubMax) {
			s[i] = symbol;
			++i;
		}
	}
	s.shrink_to_fit();
	return s;
}
