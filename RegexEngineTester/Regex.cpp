#include "stdafx.h"
#include "Regex.h"

x::RegexParser x::Regex::_parser;

///////////////////////////////////////////////////////////////////////////////////////////////

x::Regex::Regex(std::string const& regex, mode_t mode):
	_mode(mode),
	_dfa(_parser.parse(regex)) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Regex::Regex(char const * regex, mode_t mode):
	_mode(mode),
	_dfa(_parser.parse(regex))
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Regex::Regex(Regex const & other):
	_mode(other._mode),
	_dfa(other._dfa) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Regex::Regex(Regex && other):
	_mode(other._mode),
	_dfa(other._dfa) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool x::Regex::parse(std::string const & regex) {
	_dfa = _parser.parse(regex);
	return _dfa != nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool x::Regex::match(char const * str) const {
	if (_dfa == nullptr)
		return false;
	char const* c = str;
	//begin in the starting node
	DFA::Node const* current = _dfa->entry();
	//iterate through string
	while (*c) {
		//try to resolve the next state
		current = current->transitions[(uint8_t)*c];
		//no transition: FAIL
		if (current == nullptr)
			return false;
		//next character
		++c;
	}
	//when the string ends check if ended on accepting state
	return current->accepting;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult x::Regex::search(char const * begin, size_t expected) const {
	if (_dfa == nullptr || _dfa->empty())
		return {};
	SearchResult results(expected);
	search(begin, results);
	return results;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::Regex::search(char const * begin, SearchResult & results) const {
	if (_dfa == nullptr || _dfa->empty())
		return;
	char const* pc = begin; //string iterator pointer
	char const* pmatch; //pointer to begin of current match
	char const* plastacc = nullptr; //pointer to last symbol leading to accepting state
	DFA::Node const* entry = _dfa->entry(); //entry state of the machine
	DFA::Node const* n; //current state
	DFA::Node const* next; //next state
	size_t id = 0; //id of the next found match
	results.clear();
	//set the sentinel value on string-end symbol
	const_cast<DFA::Node*>(entry)->transitions['\0'] = const_cast<DFA::Node*>(entry);
	//find the first matching symbol
	while ((n = entry->transitions[*pc]) == nullptr)
		++pc;
	if (*pc == '\0') { //not found, unset the sentinel value
		const_cast<DFA::Node*>(entry)->transitions['\0'] = nullptr;
		return;
	}
	pmatch = pc; //match starts at the current iterator
	if (n->accepting) //update last accepting symbol
		plastacc = pc;
	while (*++pc) {
		if (next = n->transitions[*pc]) { //check transition on current symbol
			n = next; //move to the next state
			if (n->accepting) //update last accepting symbol
				plastacc = pc;
		} else {
			//if ended on accepting state or a match was found, add result
			if (n->accepting)
				results._add({pmatch, size_t(pc - pmatch), size_t(pmatch - begin), id++});
			else if (plastacc > pmatch)
				results._add({pmatch, size_t(plastacc - pmatch + 1), size_t(pmatch - begin), id++});
			//find next matching symbol
			while ((n = entry->transitions[*pc]) == nullptr)
				++pc;
			
			if (*pc == '\0') //not found, end search
				goto RETURN;
			else {
				pmatch = pc; //found, mark begin of the maatch
				if (n->accepting) //update last accepting symbol
					plastacc = pc;
			}
		}
	}
	//if ended on accepting state or a match was found, add result
	if (n->accepting)
		results._add({pmatch, size_t(pc - pmatch), size_t(pmatch - begin), id++});
	else if (plastacc > pmatch)
		results._add({pmatch, size_t(plastacc - pmatch + 1), size_t(pmatch - begin), id++});
RETURN:
	//unset the sentinel value
	const_cast<DFA::Node*>(entry)->transitions['\0'] = nullptr;
	if (_mode & IndependentSearch)
		results._makeIndependent();
}
