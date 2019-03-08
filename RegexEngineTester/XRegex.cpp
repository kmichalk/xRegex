#include "stdafx.h"
#include "XRegex.h"
#include "RegexValidityTest.h"


XRegex::XRegex():
	_results(1000) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t XRegex::benchmarkCompile(std::string const & regex) {
	Timer timer;
	timer.reset();
	x::Regex r(regex);
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t XRegex::benchmarkSearch(std::string const & expr, std::string const & input) {
	Timer timer;
	x::Regex regex(expr);
	timer.reset();
	regex.search(input, _results);
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexSearchData XRegex::search(std::string const & expr, std::string const & input) {
	RegexSearchData results;
	results.input = input;
	results.regex = expr;
	x::Regex regex(expr);
	x::SearchResult searchResults = regex.search(results.input, input.length() / (expr.length() + 1));
	results.results.reserve(searchResults.size());
	for (auto& r : searchResults)
		results.add({r.begin, r.length, r.srcpos});
	results.compilationSucceeded = true;
	return results;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void XRegex::match(std::string const & regex, std::string const & input, x::MatchTestResult& result) {
	try {
		x::Regex r(regex);
		if (r.valid()) {
			result.parsed = true;
			result.match = r.match(input);
		}
	} catch (...) {
		result.message = "Unexpected exception";
		result.exception = true;
	}
}
