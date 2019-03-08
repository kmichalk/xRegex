#include "stdafx.h"
#include "RegexSearchData.h"


RegexSearchData::RegexSearchData():
	compilationSucceeded(true)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexSearchData::add(SearchResult const & result) {
	results.push_back(result);
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::string SearchResult::asString() const {
	return std::string(begin(), end());
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString SearchResult::asQString() const {
	return QString::fromLatin1(begin(), (int)length);
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString SearchResult::matchInfo() const {
	return "{" + QString::number(position) + ": '" + asQString() + "'}";
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString RegexSearchData::matchInfo() const {
	QString buffer = QString((int)results.size() * SEARCH_RESULT_INFO_PREALLOC_SIZE + 80, QChar('\0'));
	for (auto const& r : results)
		(buffer += r.matchInfo()) += '\n';
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString ResultStat::info(float multiplier, int precision) const {
	QString buffer;
	buffer += "Input length: ";
	buffer += QString::number(inputLength);
	buffer += "\nMin length: ";
	buffer += QString::number(minLength);
	buffer += "\nMax length: ";
	buffer += QString::number(maxLength);
	buffer += "\nAverage length: ";
	buffer += QString::number(avgLength, 'f', 2);
	buffer += "\nMatched length: ";
	buffer += QString::number(matchedLength);
	buffer += "\nUnmatched length: ";
	buffer += QString::number(unmatchedLength);
	buffer += "\nMatches found: ";
	buffer += QString::number(matchCount);
	buffer += "\nEmpty matches: ";
	buffer += QString::number(emptyMatches);
	buffer += "\nIterations: ";
	buffer += QString::number(iterations);
	buffer += "\nCompile test time: ";
	buffer += QString::number(compileTestTime*multiplier, 'f', precision);
	buffer += "\nCompile average time: ";
	buffer += QString::number(compileTime*multiplier, 'f', precision);
	buffer += "\nCompile min time: ";
	buffer += QString::number(compileMinTime*multiplier, 'f', precision);
	buffer += "\nCompile max time: ";
	buffer += QString::number(compileMaxTime*multiplier, 'f', precision);
	buffer += "\nSearch test time: ";
	buffer += QString::number(searchTestTime*multiplier, 'f', precision);
	buffer += "\nSearch average time: ";
	buffer += QString::number(searchTime*multiplier, 'f', precision);
	buffer += "\nSearch min time: ";
	buffer += QString::number(searchMinTime*multiplier, 'f', precision);
	buffer += "\nSearch max time: ";
	buffer += QString::number(searchMaxTime*multiplier, 'f', precision);
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString ResultStat::timeInfo(float multiplier, int precision) const {
	QString buffer;
	buffer += "Compile test time: ";
	buffer += QString::number(compileTestTime*multiplier, 'f', precision);
	buffer += "\nCompile average time: ";
	buffer += QString::number(compileTime*multiplier, 'f', precision);
	buffer += "\nCompile min time: ";
	buffer += QString::number(compileMinTime*multiplier, 'f', precision);
	buffer += "\nCompile max time: ";
	buffer += QString::number(compileMaxTime*multiplier, 'f', precision);
	buffer += "\nSearch test time: ";
	buffer += QString::number(searchTestTime*multiplier, 'f', precision);
	buffer += "\nSearch average time: ";
	buffer += QString::number(searchTime*multiplier, 'f', precision);
	buffer += "\nSearch min time: ";
	buffer += QString::number(searchMinTime*multiplier, 'f', precision);
	buffer += "\nSearch max time: ";
	buffer += QString::number(searchMaxTime*multiplier, 'f', precision);
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString ResultStat::matchInfo() const {
	QString buffer;
	buffer += "Input length: ";
	buffer += QString::number(inputLength);
	buffer += "\nMin length: ";
	buffer += QString::number(minLength);
	buffer += "\nMax length: ";
	buffer += QString::number(maxLength);
	buffer += "\nAverage length: ";
	buffer += QString::number(avgLength, 'f', 2);
	buffer += "\nMatched length: ";
	buffer += QString::number(matchedLength);
	buffer += "\nUnmatched length: ";
	buffer += QString::number(unmatchedLength);
	buffer += "\nMatches found: ";
	buffer += QString::number(matchCount);
	buffer += "\nEmpty matches: ";
	buffer += QString::number(emptyMatches);
	buffer += "\nIterations: ";
	buffer += QString::number(iterations);
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString ResultStat::timeCsvLine(QString const & engineName, bool all) const {
	QString buffer = engineName;
	buffer += ";";
	buffer += QString::number(compileTime*1000.0, 'f', 6);
	buffer += ";";
	if (all) {
		buffer += QString::number(compileMinTime*1000.0, 'f', 6);
		buffer += ";";
		buffer += QString::number(compileMaxTime*1000.0, 'f', 6);
		buffer += ";";
	}
	buffer += QString::number(searchTime*1000.0, 'f', 6);
	if (all) {
		buffer += ";";
		buffer += QString::number(searchMinTime*1000.0, 'f', 6);
		buffer += ";";
		buffer += QString::number(searchMaxTime*1000.0, 'f', 6);
	}
	buffer += "\n";
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString ResultStat::timeCsvHeader(bool all) {
	if (all) 
		return ";compile avg;compile min;compile max;search avg;search min;search max\n";
	else
		return ";compile;search\n";
}
