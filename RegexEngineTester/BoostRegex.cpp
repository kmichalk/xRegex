#include "stdafx.h"
#include "BoostRegex.h"
#include "RegexValidityTest.h"


timeunit_t BoostRegex::benchmarkCompile(std::string const & regex) {
	Timer t;
	t.reset();
	boost::regex r(regex);
	return t.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t BoostRegex::benchmarkSearch(std::string const & expr, std::string const & input) {
	boost::regex r(expr, boost::regex_constants::no_except);
	Timer t;
	t.reset();
	char const* begin = input.data();
	char const* i = begin;
	char const* end = begin + input.length();
	boost::match_results<char const*> match;
	boost::match_flag_type flags = boost::match_default;
	while (boost::regex_search(i, end, match, r, flags)) {
		auto next = match[0].second;
		if (next == i)
			++i;
		else
			i = next;
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}
	return t.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexSearchData BoostRegex::search(std::string const & expr, std::string const & input) {
	RegexSearchData results;
	try {
		boost::regex r(expr);
		results.compilationSucceeded = true;
		results.input = input;
		results.regex = expr;
		char const* begin = results.input.data();
		char const* i = begin;
		char const* end = begin + input.length();
		boost::match_results<char const*> match;
		boost::match_flag_type flags = boost::match_default;
		while (boost::regex_search(i, end, match, r, flags)) {
			boost::csub_match const& whole = match[0];
			results.add({whole.first, (size_t)whole.length(), (size_t)(whole.first - begin)});
			auto next = match[0].second;
			if (next == i)
				++i;
			else
				i = next;
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
	} catch (boost::bad_expression e) {
		results.compilationSucceeded = false;
	}
	return results;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void BoostRegex::match(std::string const & regex, std::string const & input, x::MatchTestResult& result) {
	try {
		boost::regex r(regex);
		result.parsed = true;
		result.match = boost::regex_match(input.c_str(), r);
	} catch (std::runtime_error e) {
		result.message = e.what();
		result.exception = true;
	} catch (...) {
		result.message = "Unexpected exception";
		result.exception = true;
	}
}
