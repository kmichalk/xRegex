#pragma once

#include "RegexSearchData.h"

namespace x 
{
	struct MatchTestResult;
}

//an abstrction over basic operations on a regex engine. this class also alows to perform benchmarks
//on regex engines, details of which are implemented in concrete classes, representing 4 regex engines
//taken into consideration in the project
class RegexEngine
{
	void _benchmarkSearch(ResultStat& stat, std::string const& expr, std::string const& input, unsigned reps);
	void _benchmarkCompile(ResultStat& stat, std::string const& expr, unsigned reps);
public:
	virtual ~RegexEngine() = default;
	//perform benchmark of cmpilation of specified regex, return time taken
	virtual timeunit_t benchmarkCompile(std::string const& regex) = 0;
	//perform benchmark of search of specified regex over input text, return time taken
	virtual timeunit_t benchmarkSearch(std::string const& expr, std::string const& input) = 0;
	//perform search of specifier regex over input text. return search results in unified data representation
	virtual RegexSearchData search(std::string const& expr, std::string const& input) = 0;
	//test matching validity of specified regex over input text. store results in results structure
	virtual void match(std::string const& regex, std::string const& input, x::MatchTestResult& result) = 0;
	//perform the match test but catch system/memory violation exceptions
	void safeMatch(std::string const& regex, std::string const& input, x::MatchTestResult& result);
	//perform multiple search benchmarks and return average time taken
	timeunit_t benchmarkSearch(std::string const& expr, std::string const& input, unsigned reps);
	//perform multiple compilation benchmarks and return average time taken
	timeunit_t benchmarkCompile(std::string const& regex, unsigned reps);
	//perform all benchmarks of regex over input text and returned detailed information about the results
	ResultStat benchmark(std::string const& expr, std::string const& input, unsigned reps);
};

