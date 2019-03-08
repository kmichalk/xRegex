#include "stdafx.h"
#include "RegexEngine.h"
#include "RegexValidityTest.h"


void RegexEngine::_benchmarkSearch(ResultStat & stat, std::string const & expr, std::string const & input, unsigned reps) {
	stat.searchMinTime = std::numeric_limits<timeunit_t>::max();
	stat.searchMaxTime = 0;
	timeunit_t timesum = 0;
	for (unsigned i = 0; i < reps; ++i) {
		timeunit_t time = benchmarkSearch(expr, input);
		timesum += time;
		if (time < stat.searchMinTime)
			stat.searchMinTime = time;
		if (time > stat.searchMaxTime)
			stat.searchMaxTime = time;
	}
	stat.searchTestTime = timesum;
	stat.searchTime = timesum / reps;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngine::_benchmarkCompile(ResultStat & stat, std::string const & expr, unsigned reps) {
	stat.compileMinTime = std::numeric_limits<timeunit_t>::max();
	stat.compileMaxTime = 0;
	timeunit_t timesum = 0;
	for (unsigned i = 0; i < reps; ++i) {
		timeunit_t time = benchmarkCompile(expr);
		timesum += time;
		if (time < stat.compileMinTime)
			stat.compileMinTime = time;
		if (time > stat.compileMaxTime)
			stat.compileMaxTime = time;
	}
	stat.compileTestTime = timesum;
	stat.compileTime = timesum / reps;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngine::safeMatch(std::string const & regex, std::string const & input, x::MatchTestResult & result) {
	//consume a system/memory violation exception
	__try {
		match(regex, input, result);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		result.message = "System error/Memory violation";
		result.exception = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t RegexEngine::benchmarkSearch(std::string const & expr, std::string const & input, unsigned reps) {
	timeunit_t time = 0;
	for (unsigned i = 0; i < reps; ++i)
		time += benchmarkSearch(expr, input);
	return time / reps;
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t RegexEngine::benchmarkCompile(std::string const & regex, unsigned reps) {
	timeunit_t time = 0;
	for (unsigned i = 0; i < reps; ++i)
		time += benchmarkCompile(regex);
	return time/reps;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ResultStat RegexEngine::benchmark(std::string const & expr, std::string const & input, unsigned reps) {
	ResultStat stat;
	stat.inputLength = input.length();
	_benchmarkCompile(stat, expr, reps);
	_benchmarkSearch(stat, expr, input, reps);
	RegexSearchData results = search(expr, input);
	size_t sum = 0;
	stat.minLength = std::numeric_limits<size_t>::max();
	stat.maxLength = 0;
	stat.emptyMatches = 0;
	for (auto& r : results) {
		if (r.length < stat.minLength)
			stat.minLength = r.length;
		if (r.length > stat.maxLength)
			stat.maxLength = r.length;
		sum += r.length;
		if (r.length == 0)
			++stat.emptyMatches;
	}
	stat.avgLength = float(sum) / results.count();
	stat.matchedLength = sum;
	stat.unmatchedLength = stat.inputLength - sum;
	stat.matchCount = results.count();
	stat.iterations = reps;
	return stat;
}
