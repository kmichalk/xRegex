#include "stdafx.h"
#include "QtRegex.h"
#include "RegexValidityTest.h"


timeunit_t QtRegex::benchmarkCompile(std::string const & regex) {
	Timer timer;
	QString qregex = QString(regex.data());
	timer.reset();
	_regex = QRegularExpression(qregex);
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexSearchData QtRegex::search(std::string const & expr, std::string const & input) {
	QString qinput = QString(input.data());
	QString qexpr = QString(expr.data());
	RegexSearchData results;
	results.regex = expr;
	results.input = input;
	if (expr.empty()) {
		results.compilationSucceeded = false;
		return results;
	}
	char const* pinput = input.data();
	QRegularExpression regex(qexpr);
	if (!regex.isValid()) {
		results.compilationSucceeded = false;
		return results;
	}
	results.compilationSucceeded = true;
	QRegularExpressionMatchIterator i = regex.globalMatch(qinput);
	while (i.hasNext()) {
		QRegularExpressionMatch match = i.next();
		int pos = match.capturedStart();
		results.add({pinput + (size_t)pos, (size_t)match.capturedLength(), (size_t)pos});
	}
	return results;
}

///////////////////////////////////////////////////////////////////////////////////////////////

timeunit_t QtRegex::benchmarkSearch(std::string const & expr, std::string const & input) {
	Timer timer;
	QString qinput = QString(input.data());
	QString qexpr = QString(expr.data());
	QRegularExpression regex(qexpr);
	timer.reset();
	QRegularExpressionMatchIterator i = regex.globalMatch(qinput);
	while (i.hasNext()) {
		QRegularExpressionMatch match = i.next();
	}
	return timer.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void QtRegex::match(std::string const & regex, std::string const & input, x::MatchTestResult& result) {
	try {
		QRegularExpression r(QString::fromStdString(regex));
		if (!r.isValid()) {
			result.message = r.errorString().toStdString();
			return;
		}
		result.parsed = true;
		QString qinput = QString::fromStdString(input);
		auto match = r.match(qinput);
		result.match = match.capturedLength(0) == qinput.length();
	} catch (...) {
		result.message = "Unexpected exception";
		result.exception = true;
	}
}
