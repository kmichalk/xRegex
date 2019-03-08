#include "stdafx.h"
#include "Parser.h"
#include "escapeRangesTable.h"


x::RegexParser::Data x::RegexParser::_data;

///////////////////////////////////////////////////////////////////////////////////////////////
//
//void x::RegexParser::Data::_setr(State state, char begin, char end, parse_fn func, bool pop) {
//	//for (char c = begin; c <= end; ++c)
//		//transitions[(size_t)state][c] = {func, pop};
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void x::RegexParser::Data::_set(State state, char ch, parse_fn func, bool pop) {
//	//transitions[(size_t)state][ch] = {func, pop};
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void x::RegexParser::Data::_set(State state, char ch, char const * connections, parse_fn func, bool pop) {
//	//transitions[(size_t)state][ch] = {func, pop};
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void x::RegexParser::Data::_set(State state, char const * chs, parse_fn func, bool pop) {
//	char const* ic = chs;
//	char c = *ic;
//	while (c != '\0') {
//		//transitions[(size_t)state][c] = {func, pop};
//		c = *++ic;
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void x::RegexParser::Data::_set(State state, char ch, char_class_t chclass, parse_fn func, bool pop) {
//	//transitions[(size_t)state][ch] = {func, pop};
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::Data::_initIsQuantifierTable() {
	x64::map_cb(isQuantifier, "?+*");
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::Data::_initCanBeFirstTable() {
	x64::map_cb(canBeFirst, "\t\n\v\f\r !\"#$%&'(,-./0123456789:;<=>@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\_`abcdefghijklmnopqrstuvwxyz");
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexParser::Data::Data():
	//_symbolBuffer(1024),
	rangeComplTable{0},
	canBeFirst{0},
	isQuantifier{0}
	//transitions{0}
{
	nfa.reserve(DEFAULT_RESERVE_NODES);
	/*_setr(State::DEFAULT, 'a', 'z');
	_setr(State::DEFAULT, 'A', 'Z');
	_setr(State::DEFAULT, '0', '9');
	_set(State::DEFAULT, " _!@$^&-=~`/\":;<>{},");
	_set(State::DEFAULT, '.', PRINTABLE);
	_set(State::DEFAULT, '[', &_parseSet);
	_set(State::DEFAULT, '(', &_parseSection);
	_set(State::DEFAULT, ')', nullptr, true);
	_set(State::DEFAULT, '?', &_processZeroOrOne);
	_set(State::DEFAULT, '*', &_processZeroOrMore);
	_set(State::DEFAULT, '+', &_processOneOrMore);
	_set(State::DEFAULT, '\\', &_parseEscape);
	_set(State::DEFAULT, '#', &_processSymbolNumber);
	_set(State::DEFAULT, '\'', &_parseExact);
	_set(State::DEFAULT, '%', &_parseComment);
	_set(State::DEFAULT, '{', &_parseRepetitions);*/
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexParser::Data::~Data() {
}
