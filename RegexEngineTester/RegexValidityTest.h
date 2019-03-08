#pragma once

#include "RegexEngine.h"

namespace x
{
	//structure containing info about validity test result
	struct MatchTestResult {
		std::string message;
		bool match = false;
		bool parsed = false;
		bool exception = false;
		std::string format(bool expected) const;
	};

	//class representing test of matching specified regex against multiple test cases
	class RegexValidityTest
	{
	public:
		//structure of test case containing information about input text, result of the test and expected result
		struct TestCase {
			std::string input;
			bool expected = false;
			MatchTestResult result;
			TestCase() = default;
			TestCase(std::string const& input, bool expected);
			friend std::istream& operator>>(std::istream& is, TestCase& test);
			friend std::ostream& operator<<(std::ostream& os, TestCase const& test);
		};

	private:
		std::string _regexstr;
		x::vector<TestCase> _testCases;
		bool allPassed;
	public:
		RegexValidityTest() = default;
		RegexValidityTest(std::string const& regex, x::vector<TestCase> const& cases);
		//execute test using specified regex engine
		void execute(RegexEngine* r);
		//write results to output stream
		void write(std::ostream& os) const;
		//generate QString with results info
		QString toQString() const;
		friend std::istream& operator>>(std::istream& is, RegexValidityTest& test);
		friend std::ostream& operator<<(std::ostream& os, RegexValidityTest const& test);
	};

	//a set of multiple validity tests for simplification of test usage and more automation
	class RegexTestSet
	{
		x::vector<RegexValidityTest> _tests;
	public:
		//exectute all tests using specified regex engine
		void execute(RegexEngine* r);
		//write info about results of all tests to output stream
		void write(std::ostream& os) const;
		//parse input string and generate test cases
		void read(QString const& input);
		//generate QString with results info of all tests
		QString toQString() const;
		friend std::istream& operator>>(std::istream& is, RegexTestSet& ts);
		friend std::ostream& operator<<(std::ostream& os, RegexTestSet const& ts);
	};
}

