#pragma once

#include "RegexEngine.h"

//implementation of basic operations on QRegularExpression engine
class QtRegex: public RegexEngine
{
	QRegularExpression _regex;
public:
	virtual timeunit_t benchmarkCompile(std::string const& regex) override;
	virtual RegexSearchData search(std::string const& expr, std::string const& input) override;
	virtual timeunit_t benchmarkSearch(std::string const& expr, std::string const& input) override;
	virtual void match(std::string const& regex, std::string const& input, x::MatchTestResult& result) override;
};
