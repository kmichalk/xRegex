#include "stdafx.h"
#include "StdRegex.h"
#include "RegexValidityTest.h"


timeunit_t StdRegex::benchmarkCompile(std::string const & regex) {
	Timer timer;
	timer.reset();
	std::regex r(regex);
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t StdRegex::benchmarkSearch(std::string const & expr, std::string const & input) {
	Timer timer;
	std::regex regex;
	try {
		timer.reset();
		regex.assign(expr);
		timeunit_t compileTime = timer.get();
	} catch (std::regex_error e) {
		return 0;
	}
	std::cmatch match;
	char const* inputData = input.data();
	char const* s = inputData;
	timer.reset();
	while (std::regex_search(s, match, regex)) {
		size_t length = match.length();
		s = s + match.position() + (length == 0 ? 1 : length);
	}
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexSearchData StdRegex::search(std::string const& expr, std::string const & input) {
	RegexSearchData results;
	results.input = input;
	results.regex = expr;
	if (expr.empty())
		return results;
	results.results.reserve(input.size() / expr.size() + 2);
	std::regex regex;
	try {
		regex.assign(expr);
	} catch (std::regex_error e) {
		results.compilationSucceeded = false;
		return results;
	}
	results.compilationSucceeded = true;
	if (input.empty())
		return results;
	std::cmatch match;
	char const* inputData = results.input.data();
	char const* s = inputData;
	while (std::regex_search(s, match, regex)) {
		results.add({inputData, (size_t)match.length(), s - inputData + (size_t)match.position()});
		size_t length = match.length();
		s = s + match.position() + (length == 0 ? 1 : length);
	}
	return results;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void StdRegex::match(std::string const & regex, std::string const & input, x::MatchTestResult& result) {
	try {
		std::regex r(regex);
		result.parsed = true;
		result.match = std::regex_match(input, r);
	} catch (std::exception e) {
		result.message = e.what();
		result.exception = true;
	} catch (...) {
		result.message = "Unexpected exception";
		result.exception = true;
	}
}
