#include "stdafx.h"
#include "CharRangeMap.h"


void x::CharRangeMap::_set() {
	set('s', CharClass::WHITESPACE);
	set('u', CharClass::UPPER);
	set('l', CharClass::LOWER);
	set('v', CharClass::VISIBLE);
	set('d', CharClass::DIGIT);
	set('e', CharClass::LETTER);
	set('b', CharClass::BINARY);
	set('o', CharClass::OCTAL);
	set('h', CharClass::HEXADECIMAL);
	set('a', CharClass::ALPHANUMERIC);
	set('p', CharClass::PRINTABLE);
	set('c', CharClass::CONTROL);
	set('w', CharClass::WORD);
	set('m', CharClass::SYMBOL);
	set('i', CharClass::ASCII);
	set('8', CharClass::UTF8);
	setInverse('S', CharClass::WHITESPACE);
	setInverse('U', CharClass::UPPER);
	setInverse('L', CharClass::LOWER);
	setInverse('V', CharClass::VISIBLE);
	setInverse('D', CharClass::DIGIT);
	setInverse('E', CharClass::LETTER);
	setInverse('B', CharClass::BINARY);
	setInverse('O', CharClass::OCTAL);
	setInverse('H', CharClass::HEXADECIMAL);
	setInverse('A', CharClass::ALPHANUMERIC);
	setInverse('P', CharClass::PRINTABLE);
	setInverse('C', CharClass::CONTROL);
	setInverse('W', CharClass::WORD);
	setInverse('M', CharClass::SYMBOL);
	setInverse('I', CharClass::ASCII);
	setSame("\\[]()+?*#%.|'!");
	set('n', '\n');
	set('t', '\t');
	set('r', '\r');
	set('f', '\f');
	//set('0', '\0');
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::CharRangeMap::CharRangeMap() {
	_set();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::set(char ch, x::CharClass chcl) {
	x::vector<char>& range = charRanges_[ch];
	for (int c = 0; c < 256; ++c) {
		if (has_class((char)c, chcl))
			range.push_back(c);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::set(char ch, x::vector<char> const & range) {
	charRanges_[ch] = range;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::set(char ch, x::vector<char>&& range) {
	charRanges_[ch] = range.move();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::set(char ch, char symbol) {
	charRanges_[ch] = {symbol};
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::setSame(char ch) {
	set(ch, ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::setSame(char const * chs) {
	char c = *chs;
	while (c != '\0') {
		set(c, c);
		c = *++chs;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::setInverse(char ch, CharClass chcl) {
	x::vector<char>& range = charRanges_[ch];
	for (int c = 0; c < 256; ++c) {
		if (has_class((char)c, PRINTABLE) && !has_class((char)c, chcl))
			range.push_back(c);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::setInverse(char ch, x::vector<char> const & range) {
	bool map[256] = {false};
	for (char c : range)
		map[(size_t)c] = true;
	x::vector<char>& r = charRanges_[ch];
	for (size_t c = 0; c < 256; ++c) {
		if (has_class((char)c, PRINTABLE) && map[(size_t)c])
			r.push_back(c);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::vector<char> const & x::CharRangeMap::operator[](char ch) const {
	return charRanges_[ch];
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::print(std::ostream & os) const {
	for (int ch = 0; ch < 256; ++ch) {
		auto const& range = charRanges_[ch];
		os << "\"";
		for (char c : range)
			os << c;
		os << "\"\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::CharRangeMap::generateRangeTable(std::string const& tableName, std::ostream & os) const {
	os << "constexpr char const* " << tableName << "[256] = {\n";
	os << std::hex;
	for (int ch = 0; ch < 256; ++ch) {
		auto const& range = charRanges_[ch];
		os << "\t";
		if (range.empty())
			os << "nullptr,\n";
		else {
			os << "\"";
			for (char c : range)
				os << "\\x" << (unsigned)c;
			if (ch == 255)
				os << "\"\n";
			else
				os << "\",\n";
		}
	}
	os << "};\n";
}
