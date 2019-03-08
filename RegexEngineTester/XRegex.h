#pragma once
#include "RegexEngine.h"
#include "Regex.h"

//implementation of basic operations on x::Regex engine
class XRegex: public RegexEngine
{
	x::SearchResult _results;
public:
	XRegex();
	virtual timeunit_t benchmarkCompile(std::string const& regex) override;
	virtual timeunit_t benchmarkSearch(std::string const& expr, std::string const& input) override;
	virtual RegexSearchData search(std::string const& expr, std::string const& input) override;
	virtual void match(std::string const& regex, std::string const& input, x::MatchTestResult& result) override;
};

