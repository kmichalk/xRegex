#pragma once

#include "RegexEngine.h"

//implementation of basic operations on std::regex engine
class StdRegex: public RegexEngine
{
public:
	virtual timeunit_t benchmarkCompile(std::string const& regex) override;
	virtual timeunit_t benchmarkSearch(std::string const& expr, std::string const& input) override;
	virtual RegexSearchData search(std::string const& expr, std::string const& input) override;
	virtual void match(std::string const& regex, std::string const& input, x::MatchTestResult& result) override;
};

