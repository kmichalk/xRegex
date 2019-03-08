#pragma once

#include "Parser.h"
#include "SearchResult.h"

namespace x
{
	//the representation of regular expression
	class Regex 
	{
	public:
		using mode_t = uint32_t;

		enum Mode : mode_t {
			Default = 0, 
			SkipEmpty = 1 << 0,
			Minimize = 1 << 1,
			IndependentSearch = 1 << 2
		};
	private:
		//instance of regex parser
		static RegexParser _parser;
		//the mode of regex
		mode_t _mode = Default;
		//the dfa containing nodes of the automaton
		//because of the shared_ptr, the dfa needs not to be copied when the regex object is copied
		std::shared_ptr<DFA> _dfa;

	public:
		Regex() = default;
		Regex(std::string const& regex, mode_t mode = Default);
		Regex(char const* regex, mode_t mode = Default);
		Regex(Regex const& other);
		Regex(Regex&& other);
		~Regex() = default;

		//discard the old dfa and reparse regex
		bool parse(std::string const& regex);
		//try to match the whole string 
		bool match(char const* str) const;
		//try to match the whole string 
		bool match(std::string const& str) const;
		//search for occurences of regex in input string, expected number of matches can be specified for optimization
		SearchResult search(char const* begin, size_t expected = DEFAULT_EXPECTED_SEARCH_RESULTS) const;
		//search for occurences of regex in input string, expected number of matches can be specified for optimization
		SearchResult search(std::string const& text, size_t expected = DEFAULT_EXPECTED_SEARCH_RESULTS) const;
		//search for occurences of regex in input string, store results in given results object
		void search(char const* begin, SearchResult& results) const;
		//search for occurences of regex in input string, store results in given results object
		void search(std::string const& text, SearchResult& results) const;

		void setMode(mode_t mode);
		mode_t mode() const;
		DFA const& dfa() const;
		//true if the regex contains nonempty automaton
		bool valid() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline bool x::Regex::match(std::string const & str) const {
	return match(str.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::SearchResult x::Regex::search(std::string const& text, size_t expected) const {
	return search(text.data(), expected);
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::Regex::search(std::string const & text, SearchResult & results) const {
	search(text.data(), results);
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::Regex::setMode(mode_t mode) {
	_mode = mode;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Regex::mode_t x::Regex::mode() const {
	return _mode;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::DFA const& x::Regex::dfa() const {
	return *_dfa;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline bool x::Regex::valid() const {
	return _dfa != nullptr;
}
