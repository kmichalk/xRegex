#include "stdafx.h"
#include "Parser.h"
#include "escapeRangesTable.h"
#include "charHexValues.h"

#define GUARD(_pc) { if ((_pc) == nullptr) return nullptr; }
#define CASE_BREAK(_value) case _value: break;
#define CASE_FAIL(_value) case _value: return nullptr;
#define CASES_BREAK(...) APPLY(CASE_BREAK, __VA_ARGS__)
#define CASES_FAIL(...) APPLY(CASE_FAIL, __VA_ARGS__)
#define CASE_APPLY_SYMBOL(_value) case _value: goto APPLY_SYMBOL;
#define CASES_APPLY_SYMBOL(...) APPLY(CASE_APPLY_SYMBOL, __VA_ARGS__)
#define CASE_APPLY_SET(_value, _escsymb) case _value: _addNode(); _connectLast(ESCAPE_SET[(uint8_t)_escsymb]);
#define CASE_CALL(_value, _func) case _value: pc = _func(pc + 1); GUARD(pc); goto LOOP_BEGIN;
#define CASE_FINISH(_value) case _value: _sections.finish(_lastNode); return pc;
#define CASE_END_SECTION(_value) case _value: _sections.end(_lastNode); return pc + 1;

void x::RegexParser::_clear() {
	_nfa.clear();
	_sections.clear();
	_quantifiersOccurred = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_addNode() {
	_nfa.addNode();
	_lastNode = _nfa.lastNode();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_connectLast(char ch) {
	_lastNode->prev->connect(_lastNode->id, ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_connectLast(char const * chs) {
	_lastNode->prev->connect(_lastNode->id, chs);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_connectLast(bool const * symbolMap) {
	_lastNode->prev->connect(_lastNode->id, symbolMap);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
//char const* x::RegexParser::_parse(char const * pc) {
//	char c;
//LOOP_BEGIN:
//	c = *pc;
//	switch (c) {
//		CASE_FINISH('\0');
//		CASES_FAIL(0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08);
//		CASES_BREAK('\t', '\n', '\v', '\f', '\r');
//		CASES_FAIL(0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F);
//		CASES_APPLY_SYMBOL(' ', '!', '\"');
//		CASE_CALL('#', _processSymbolNumber);
//		CASE_FAIL('$');
//		CASE_CALL('%', _parseComment);
//		CASES_APPLY_SYMBOL('&', '\'');
//		CASE_CALL('(', _parseSection);
//		CASE_FAIL(')');
//		CASE_CALL('*', _processZeroOrMore);
//		CASE_CALL('+', _processOneOrMore);
//		CASES_APPLY_SYMBOL(',', '-');
//		CASE_APPLY_SET('.', 'p');
//		CASES_APPLY_SYMBOL('/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>');
//		CASE_CALL('?', _processZeroOrOne);
//		CASES_APPLY_SYMBOL('@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z');
//		CASE_CALL('[', _parseSet);
//		CASE_CALL('\\', _parseEscape);
//		CASE_FAIL(']');
//		CASE_FAIL('^');
//		CASE_APPLY_SYMBOL('_');
//		CASE_CALL('`', _parseExact);
//		CASES_APPLY_SYMBOL('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z');
//		CASE_CALL('{', _parseRepetitions);
//		CASE_CALL('|', _parseAlternative);
//		CASE_FAIL('}');
//		CASE_APPLY_SYMBOL('~');
//		CASE_FAIL(0x7F);
//	APPLY_SYMBOL:
//		_addNode();
//		_connectLast(c);
//	}
//	++pc;
//	goto LOOP_BEGIN;
//}

//
//char const* x::RegexParser::_parse(char const * input) {
//	Transition _transitionsDefault[1];
//	char const* pc = input;
//	char c = *pc;
//	while (c != '\0') {
//		//get the transition on symbol
//		Transition const& t = _transitionsDefault[c];
//		if (t.func != nullptr) {
//			//call the parsing function beginning on next char and continue parsing
//			pc = (this->*t.func)(pc + 1);
//			if (pc == nullptr)
//				return nullptr;
//			c = *pc;
//		} else {
//			//if (tls != nullptr) {
//				//literal symbol - add node and transition
//				_addNode();
//				_connectLast(c);
//			//}
//			c = *++pc;
//		}
//	}
//	//end parsing, set last node accepting 
//	_sections.finish(_lastNode);
//	return pc;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

char const* x::RegexParser::_parseSection(char const * pc) {
	_sections.push(_lastNode);
	char c;
LOOP_BEGIN:
	c = *pc;
	switch (c) {
		CASE_FAIL('\0');
		CASES_FAIL(0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08);
		CASES_BREAK('\t', '\n', '\v', '\f', '\r');
		CASES_FAIL(0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F);
		CASES_APPLY_SYMBOL(' ', '!', '\"');
		CASE_CALL('#', _processSymbolNumber);
		CASE_FAIL('$');
		CASE_CALL('%', _parseComment);
		CASES_APPLY_SYMBOL('&', '\'');
		CASE_CALL('(', _parseSection);
		CASE_END_SECTION(')');
		CASE_CALL('*', _processZeroOrMore);
		CASE_CALL('+', _processOneOrMore);
		CASES_APPLY_SYMBOL(',', '-');
		CASE_APPLY_SET('.', 'p');
		CASES_APPLY_SYMBOL('/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>');
		CASE_CALL('?', _processZeroOrOne);
		CASES_APPLY_SYMBOL('@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z');
		CASE_CALL('[', _parseSet);
		CASE_CALL('\\', _parseEscape);
		CASE_FAIL(']');
		CASE_FAIL('^');
		CASE_APPLY_SYMBOL('_');
		CASE_CALL('`', _parseExact);
		CASES_APPLY_SYMBOL('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z');
		CASE_CALL('{', _parseRepetitions);
		CASE_CALL('|', _parseAlternative);
		CASE_FAIL('}');
		CASE_APPLY_SYMBOL('~');
		CASE_FAIL(0x7F);
	APPLY_SYMBOL:
		_addNode();
		_connectLast(c);
	}
	++pc;
	goto LOOP_BEGIN;
}

//char const* x::RegexParser::_parseSection(char const * input) {
//	char const* pc = input;
//	char c = *pc;
//	_sections.push(_lastNode);
//	while (c != '\0') {
//		Transition const& t = _transitionsDefault[c];
//		if (t.pop) {
//			//go back in call stack
//			_sections.end(_lastNode);
//			return pc + 1;
//		} else if (t.func != nullptr) {
//			//call the parsing function beginning on next char and continue parsing
//			pc = (this->*t.func)(pc + 1);
//			if (pc == nullptr)
//				return nullptr;
//			c = *pc;
//		} else {
//			if (t.symbols != nullptr) {
//				//literal symbol - add node and transition
//				_addNode();
//				_connectLast(t.symbols);
//			}
//			c = *++pc;
//		}
//	}
//	return nullptr;
//}

////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_parseSet(char const * pc) {
	_addNode();
	if (*pc == '!') {
		::memset(_setCompl, 1, ASCII_RANGE);
		pc = _parseNegativeSet(pc + 1);
		_connectLast(_setCompl);
	} else {
		_setNegationOccurred = false;
		pc = _parsePositiveSet(pc);
		if (_setNegationOccurred)
			_connectLast(_setCompl);
	}
	return pc;
}

char const * x::RegexParser::_parseAlternative(char const * input) {
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_parsePositiveSet(char const * pc) {
	char cmax;
	char const* pr;
	char c;
LOOP_BEGIN:
	c = *pc;
	switch (c) {
	case '\0':
		return nullptr;
	case '!':
		return nullptr;
	case '[':
		return nullptr;
		/*if (*++pc == '!')
			pc = _parseNegativeSet(pc + 1);
		else
			pc = _parsePositiveSet(pc);
		goto LOOP_BEGIN;*/
	case ']':
		return pc + 1;
	case '-':
		c = pc[-1];
		switch (c) {
		case ']':
			return nullptr;
		case '!':
			return nullptr;
		case '-':
			return nullptr;
		default:
			cmax = *++pc;
			if (cmax < c)
				return nullptr;
			while (++c <= cmax)
				_connectLast(c);
		}
		break;
	case '\\':
		pr = ESCAPE_SET[*++pc];
		while (*pr != '\0')
			_connectLast(*pr++);
		break;
	default:
		_connectLast(c);
	}
	++pc;
	goto LOOP_BEGIN;
}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//char const * x::RegexParser::_parsePositiveSetAlt(char const * pc) {
//	char cmax;
//	char const* pr;
//	char c;
//LOOP_BEGIN:
//	c = *pc;
//	switch (c) {
//	case '\0':
//		return nullptr;
//	case '!':
//		return nullptr;
//	case '[':
//		if (*++pc == '!')
//			pc = _parseNegativeSetAlt(pc + 1);
//		else
//			pc = _parsePositiveSet(pc);
//		goto LOOP_BEGIN;
//	case ']':
//		return pc + 1;
//	case '-':
//		c = pc[-1];
//		switch (c) {
//		case ']':
//			return nullptr;
//		case '!':
//			return nullptr;
//		case '-':
//			return nullptr;
//		default:
//			cmax = *++pc;
//			if (cmax < c)
//				return nullptr;
//			while (++c <= cmax)
//				_setCompl[c] = true;
//		}
//		break;
//	case '\\':
//		pr = ESCAPE_SET[*++pc];
//		while (*pr != '\0')
//			_setCompl[*pr++] = true;
//		break;
//	default:
//		_setCompl[c] = true;
//	}
//	++pc;
//	goto LOOP_BEGIN;
//}

///////////////////////////////////////////////////////////////////////////////////////////////
//
//char const * x::RegexParser::_parsePositiveSetInt(char const * pc) {
//	char cmax;
//	char const* pr;
//	char c;
//LOOP_BEGIN:
//	c = *pc;
//	switch (c) {
//	case '\0':
//		return nullptr;
//	case '!':
//		return nullptr;
//	case '[':
//		if (*++pc == '!')
//			pc = _parseNegativeSetAlt(pc + 1);
//		else
//			pc = _parsePositiveSet(pc);
//		goto LOOP_BEGIN;
//	case ']':
//		return pc + 1;
//	case '-':
//		c = pc[-1];
//		switch (c) {
//		case ']':
//			return nullptr;
//		case '!':
//			return nullptr;
//		case '-':
//			return nullptr;
//		default:
//			cmax = *++pc;
//			if (cmax < c)
//				return nullptr;
//			while (++c <= cmax)
//				_setCompl[c] = true;
//		}
//		break;
//	case '\\':
//		pr = ESCAPE_SET[*++pc];
//		while (*pr != '\0')
//			_setCompl[*pr++] = true;
//		break;
//	default:
//		_setCompl[c] = true;
//	}
//	++pc;
//	goto LOOP_BEGIN;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_parseNegativeSet(char const * pc) {
	_setNegationOccurred = true;
	char cmax;
	char const* pr;
	char c;
LOOP_BEGIN:
	c = *pc;
	switch (c) {
	case '\0':
		return nullptr;
	case '!':
		return nullptr;
	case '[':
		return nullptr;
		/*++pc;  
		if (*pc == '!')
			pc = _parsePositiveSet(pc + 1);
		else
			pc = _parseNegativeSet(pc);
		goto LOOP_BEGIN;*/
	case ']':
		return pc + 1;
	case '-':
		c = pc[-1];
		switch (c) {
		case '[':
			return nullptr;
		case ']':
			return nullptr;
		case '!':
			return nullptr;
		case '-':
			return nullptr;
		default:
			cmax = *++pc;
			if (cmax < c)
				return nullptr;
			while (++c <= cmax)
				_setCompl[c] = false;
		}
		break;
	case '\\':
		pr = ESCAPE_SET[*++pc];
		while (*pr != '\0')
			_setCompl[*pr++] = false;
		break;
	default:
		_setCompl[c] = false;
	}
	++pc;
	goto LOOP_BEGIN;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//char const * x::RegexParser::_parseNegativeSetInt(char const * pc) {
//	return nullptr;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//char const * x::RegexParser::_parseComment(char const * pc) {
//	//skip all symbols to newline
//	return pc + strcspn(pc, "\n") + 1;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_processZeroOrOne(char const * input) {
	//if quantifier is after ), then consider last section, else create section between two last nodes
	//set the quantifier flags
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode)
		_sections.put(_lastNode->prev, _lastNode)->optional = true;
	else
		last->optional = true;
	_quantifiersOccurred = true;
	return input;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_processZeroOrMore(char const * input) {
	//if quantifier is after ), then consider last section, else create section between two last nodes
	//set the quantifier flags
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode) {
		Section* s = _sections.put(_lastNode->prev, _lastNode);
		s->looped = true;
		s->optional = true;
	} else {
		last->looped = true;
		last->optional = true;
	}
	_quantifiersOccurred = true;
	return input;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_processOneOrMore(char const * input) {
	//if quantifier is after ), then consider last section, else create section between two last nodes
	//set the quantifier flags
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode)
		_sections.put(_lastNode->prev, _lastNode)->looped = true;
	else
		last->looped = true;
	_quantifiersOccurred = true;
	return input;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//char const * x::RegexParser::_parseEscape(char const * input) {
//	//resolve the character class and connect nodes on all symbols
//	char const* pcr = ESCAPE_SET[*input];
//	if (pcr == nullptr)
//		return nullptr;
//	_addNode();
//	_connectLast(pcr);
//	return input + 1;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_processSymbolNumber(char const * input) {
	//parse the hex value of 2 digits and connect on resolved symbol
	char const* pc = input;
	char c = *pc;
	if (c == '\0')
		return nullptr;
	int8_t high = CHAR_HEX_VALUE[*pc];
	if (high < 0)
		return nullptr;
	int8_t low = CHAR_HEX_VALUE[*++pc];
	if (low < 0)
		return nullptr;
	char symbol = char(high * 16 + low);
	_addNode();
	_connectLast(symbol);
	return pc + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_parseExact(char const * input) {
	//iterate until ' occured, connect all symbols as they are
	char const* pc = input;
	char c = *pc;
	_sections.push(_lastNode);
	while (c != '\'') {
		if (c == '\0')
			return nullptr;
		else {
			_addNode();
			_connectLast(c);
			c = *++pc;
		}
	}
	_sections.end(_lastNode);
	return pc;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char const * x::RegexParser::_parseRepetitions(char const * input) {
	char const* pc = input;
	int reps;
	int repsmax;
	if (*pc == ',') {
		//max reps expr
		pc = _parseDecimal(pc + 1, repsmax);
		if (pc == nullptr)
			return nullptr;
		if (pc != nullptr && *pc == '}') {
			_processRepetitionsMax(repsmax);
			return pc + 1;
		}
	} else {
		//parse min reps
		if (pc = _parseDecimal(pc, reps)) {
			if (pc == nullptr)
				return nullptr;
			if (*pc == ',') {
				//min or min-max expr
				if (*++pc == '}') {
					//min expr
					_processRepetitionsMin(reps);
					return pc + 1;
				} else {
					//min-max expr
					pc = _parseDecimal(pc, repsmax);
					if (pc == nullptr)
						return nullptr;
					else if (*pc == '}') {
						if (repsmax == reps) {
							//optimize repetition processing
							if (reps != 1)
								_processRepetitionsExact(reps);
							return pc + 1;
						} else if (repsmax < reps)
							return nullptr;
						_processRepetitions(reps, repsmax);
						return pc + 1;
					}
				}
			} else if (*pc == '}') {
				//exact reps expr
				_processRepetitionsExact(reps);
				return pc + 1;
			}
		}
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//char const * x::RegexParser::_parseDecimal(char const * pc, int & num) {
//	//calculate the numerical value from string, store in num, return the end of number, or nullpre if failed
//	int value;
//	char c = *pc;
//	if (isdigit(c))
//		value = c - '0';
//	else
//		return nullptr;
//	c = *++pc;
//	while (isdigit(c)) {
//		value *= 10;
//		value += (c - '0');
//		c = *++pc;
//	}
//	num = value;
//	return pc;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_processRepetitionsExact(int reps) {
	//clone last section or last node n times
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode) {
		while (--reps > 0)
			_cloneLast();
	} else {
		while (--reps > 0)
			_cloneLastSection();
	}
}

/////////////////////////////////////////////////////////////////////// ////////////////////////

void x::RegexParser::_processRepetitions(int min, int max) {
	//clone last section or last node max times, but make reps from min to max optional
	if (min == 0)
		return _processRepetitionsMax(max);
	Section* last = _sections.last();
	int i = 0;
	if (last == nullptr || last->end != _lastNode) {
		while (++i < min)
			_cloneLast();
		_sections.store();
		NFA::Node* n = _lastNode;
		while (++i <= max)
			_cloneLast();
		while (n != _lastNode) {
			_sections.push(n, _lastNode)->optional = true;
			n = n->next;
		}
		_sections.restore();
	} else {
		while (++i < min)
			_cloneLastSection();
		if (++i <= max) {
			_cloneLastSection();
			_sections.last()->optional = true;
			while (++i <= max)
				_cloneLastSection();
		}
	}
	_quantifiersOccurred = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_processRepetitionsMin(int min) {
	//clone last section or last node min times, loop last section or node
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode) {
		while (--min > 0)
			_cloneLast();
		Section* s = _sections.put(_lastNode->prev, _lastNode);
		s->looped = true;
	} else {
		while (--min > 0)
			_cloneLastSection();
		_sections.last()->looped = true;
	}
	_quantifiersOccurred = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_processRepetitionsMax(int max) {
	//clone last section or last node max times, make all optional
	Section* last = _sections.last();
	if (last == nullptr || last->end != _lastNode) {
		NFA::Node* entry = _lastNode->prev;
		while (--max > 0)
			_cloneLast();
		_sections.store();
		NFA::Node* n = entry;
		while (n != _lastNode) {
			_sections.push(n, _lastNode)->optional = true;
			n = n->next;
		}
		_sections.restore();
	} else {
		_sections.last()->optional = true;
		while (--max > 0)
			_cloneLastSection();
	}
	_quantifiersOccurred = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexParser::_cloneLast() {
	NFA::Node const* prev = _lastNode->prev;
	_addNode();
	_connectLast(prev->symbols.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::NFA::Node* x::RegexParser::_cloneLastSection() {
	Section* last = _sections.last();
	NFA::Node* begin = _lastNode;
	NFA::Node* n = last->begin;
	//add the same number of nodes os the cloned section had
	do {
		_addNode();
		//clone all transitions
		_connectLast(n->symbols.data());
		n = n->next;
	} while (n != last->end);
	//clone sections
	_sections.clone(last, begin);
	return begin;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexParser::RegexParser():
	_setCompl(_data.rangeComplTable),
	_nfa(_data.nfa),
	_lastNode(nullptr) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexParser::~RegexParser() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<x::DFA> x::RegexParser::parse(std::string const & input) {
	//prepare the parser and begin parsing
	_clear();
	_nfa.initNode();
	_lastNode = _nfa.lastNode();
	_sections.init(_lastNode);
	if (_parse(input.data()) != nullptr) {
		//apply quantifiers on all sections if they were encountered
		if (_quantifiersOccurred)
			_sections.top()->applyQuantifiers();
		//convert to dfa
		return std::make_shared<DFA>((DFA&&)_nfa.toDFA());
	} else {
		return nullptr;
	}
}

