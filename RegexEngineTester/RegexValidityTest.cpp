#include "stdafx.h"
#include "RegexValidityTest.h"
#include "DFA.h"


std::istream & x::operator>>(std::istream & is, x::RegexValidityTest::TestCase & test) {
	is >> test.expected;
	is.get();
	std::getline(is, test.input);
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & x::operator<<(std::ostream & os, x::RegexValidityTest::TestCase const& test) {
	if (test.result.parsed)
		os << test.input << ": ";
	return os << test.result.format(test.expected);
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::istream & x::operator>>(std::istream & is, x::RegexValidityTest & test) {
	std::getline(is, test._regexstr);
	test._testCases.clear();
	std::string line;
	while (std::getline(is, line)) {
		if (line.empty())
			break;
		RegexValidityTest::TestCase tc;
		std::istringstream(line) >> tc;
		test._testCases.push_back(tc);
	}
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & x::operator<<(std::ostream & os, x::RegexValidityTest const& test) {
	test.write(os);
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::istream & x::operator>>(std::istream & is, RegexTestSet & ts) {
	ts._tests.read(is);
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & x::operator<<(std::ostream & os, RegexTestSet const & ts) {
	ts._tests.write(os, '\n');
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexValidityTest::RegexValidityTest(std::string const & regex, x::vector<TestCase> const & cases):
	_regexstr(regex),
	_testCases(cases){
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexValidityTest::execute(RegexEngine * r) {
	for (TestCase& t : _testCases) {
		r->safeMatch(_regexstr, t.input, t.result);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexValidityTest::write(std::ostream & os) const {
	os << _regexstr << '\n';
	_testCases.write(os, '\n');
	os << '\n';
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString x::RegexValidityTest::toQString() const {
	std::ostringstream oss;
	oss << *this;
	return QString::fromStdString(oss.str());
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::RegexValidityTest::TestCase::TestCase(std::string const & input, bool expected):
	input(input) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexTestSet::execute(RegexEngine * r) {
	for (auto& t : _tests)
		t.execute(r);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexTestSet::write(std::ostream & os) const {
	for (auto& t : _tests)
		t.write(os);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::RegexTestSet::read(QString const & input) {
	std::string sinput = input.toStdString();
	std::istringstream iss(sinput);
	iss >> *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString x::RegexTestSet::toQString() const {
	std::ostringstream oss;
	write(oss);
	return QString::fromStdString(oss.str());
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::string x::MatchTestResult::format(bool expected) const {
	std::string s;
	if (parsed) {
		if (exception) {
			s += " [NOT MATCHED; EXCEPTION";
			if (!message.empty())
				((s += ": \"") += message) += "\"]";
			else
				s += "]";
		} else {
			s += (match ? "true" : "false");
			if (match != expected)
				s += " [FAIL]";
			else
				s += " [OK]";
		}
	} else {
		s += " [NOT PARSED";
		if (exception)
			s += "; EXCEPTION";
		if (!message.empty())
			((s += ": \"") += message) += "\"]";
		else
			s += "]";
	}
	return s;
}
