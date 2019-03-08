#pragma once

#include "StringBuffer.h"
#include "NFA.h"
#include "Section.h"

#pragma pack(push)
#pragma pack(1)

namespace x
{
	//the regular expression parser used in construction and parsing regexes
	class RegexParser
	{
		enum class State: uint8_t {
			NONE, DEFAULT, RANGE, CLASS, NUMBER, EXACT, COMMENT, _SIZE
		};

		//object containing temporary data used by parser, instance kept static
		class Data {
			void _initIsQuantifierTable();
			void _initCanBeFirstTable();
		public:
			//the temporary data for generating symbols set compliment [!...]
			NFA nfa;
			bool rangeComplTable[CHAR_RANGE];
			bool canBeFirst[CHAR_RANGE];
			bool isQuantifier[CHAR_RANGE];
			//the nfa representation
			Data();
			~Data();
		};

		//the instance of data used by parsers
		static Data _data;

		//pointers to static data kept private in parsers for possible slight optimization
		//Transition const* _transitionsDefault;
		//[[offset(0), size(8)]]
		bool* _setCompl;
		//[[offset(8), size(1)]]
		bool _setNegationOccurred;
		//[[offset(9), size(1)]]
		bool _quantifiersOccurred;
		//reference to nfa in static data
		//[[offset(10), size(8)]]
		NFA& _nfa;
		//the section stack built while parsing
		//[[offset(18), size(26)]]
		SectionStack _sections;
		//[[offset(44), size(8)]]
		NFA::Node* _lastNode;
		
		//clear the parser
		void _clear();
		//add new nfa node
		void _addNode();
		//connect last node on char
		void _connectLast(char ch);
		//connect last node on multiple chars
		void _connectLast(char const* chs);
		void _connectLast(bool const* symbolMap);
		//process the nfa in case of {n}
		void _processRepetitionsExact(int reps);
		//process the nfa in case of {m,n}
		void _processRepetitions(int min, int max);
		//process the nfa in case of {n,}
		void _processRepetitionsMin(int min);
		//process the nfa in case of {,n}
		void _processRepetitionsMax(int max);
		//clone last node and all associated sections
		void _cloneLast();
		//clone the last section
		NFA::Node* _cloneLastSection();

		//function that begins parsing
		char const* _parse(char const* input);
		//called when ( occurs
		char const* _parseSection(char const* input);
		//called when [ occurs
		char const* _parseSet(char const* input);
		char const* _parseAlternative(char const* input);
		//called when % occurs
		char const* _parsePositiveSet(char const* input);
		//char const* _parsePositiveSetAlt(char const* input);
		//char const* _parsePositiveSetInt(char const* input);
		char const* _parseNegativeSet(char const* input);
		//char const* _parseNegativeSetInt(char const* input);
		char const* _parseComment(char const* input);
		//called when ? occurs
		char const* _processZeroOrOne(char const* input);
		//called when * occurs
		char const* _processZeroOrMore(char const* input);
		//called when + occurs
		char const* _processOneOrMore(char const* input);
		//called when \ occurs
		char const* _parseEscape(char const* input);
		//called when # occurs
		char const* _processSymbolNumber(char const* input);
		//called when ' occurs
		char const* _parseExact(char const* input);
		//called when { occurs
		char const* _parseRepetitions(char const* input);
		//parses the decimal number in repetitions e.g. {m,n}
		char const* _parseDecimal(char const* input, int& num);

	public:
		RegexParser();
		~RegexParser();
		//entry function for parsing process
		std::shared_ptr<DFA> parse(std::string const& input);
	};
}

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline void x::RegexParser::_addNode() {
//	_nfa.addNode();
//	_lastNode = _nfa.lastNode();
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline void x::RegexParser::_connectLast(char ch) {
//	_lastNode->prev->connect(_lastNode->id, ch);
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline void x::RegexParser::_connectLast(char const * chs) {
//	_lastNode->prev->connect(_lastNode->id, chs);
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline void x::RegexParser::_connectLast(bool const * symbolMap) {
//	_lastNode->prev->connect(_lastNode->id, symbolMap);
//}
