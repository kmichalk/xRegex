#pragma once

//structure representing single regex search result, its position in text and length
struct SearchResult {
	char const* text;
	size_t length;
	size_t position;

	//convert to std::string
	std::string asString() const;
	//convert to QString
	QString asQString() const;
	//generate compact information string
	QString matchInfo() const;
	//begin and end methods to enable range-based for loop
	char const* begin() const;
	char const* end() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////

inline char const * SearchResult::begin() const {
	return text + position;
}

///////////////////////////////////////////////////////////////////////////////////////////////

inline char const * SearchResult::end() const {
	return text + position + length;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//detailed statistics generated in benchmarks
struct ResultStat {
	//average length of found expressions
	float avgLength;
	//min length of found expressions
	size_t minLength;
	//max length of found expressions
	size_t maxLength;
	//length of the input text
	size_t inputLength;
	//sum length of all found matches
	size_t matchedLength;
	//inputLength-matchedLength
	size_t unmatchedLength;
	//count of all matches
	size_t matchCount;
	//count of matches of empty string
	size_t emptyMatches;
	//average, min, max compile and search times
	timeunit_t compileTime;
	timeunit_t searchTime;
	timeunit_t compileMinTime;
	timeunit_t searchMinTime;
	timeunit_t compileMaxTime;
	timeunit_t searchMaxTime;
	//total times of compilation and search benchmarks
	timeunit_t compileTestTime;
	timeunit_t searchTestTime;
	//number of benchmark repetitions
	unsigned iterations;

	//generate compact full info
	QString info(float multiplier, int precision) const;
	//geenrate compact info of benchmark times
	QString timeInfo(float multiplier, int precision) const;
	//generate compact info of the rest of statistics
	QString matchInfo() const;
	//generate line of information to be put in csv file
	QString timeCsvLine(QString const& engineName, bool all) const;
	//generate column header to be put in csv file
	static QString timeCsvHeader(bool all);
};

//unified data format to store search results for all regex engines
class RegexSearchData
{
public:
	//the input string
	std::string input;
	//the regex
	std::string regex;
	//search results
	std::vector<SearchResult> results;
	//flag specifying if regex was parsed
	bool compilationSucceeded;

	RegexSearchData();
	~RegexSearchData() = default;
	void add(SearchResult const& result);
	//begin and end methods to enable range-based for loop
	auto begin() const;
	auto end() const;
	//the number of results
	size_t count() const;
	//generate compact info of matches found
	QString matchInfo() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////

inline auto RegexSearchData::begin() const {
	return results.cbegin();
}

///////////////////////////////////////////////////////////////////////////////////////////////

inline auto RegexSearchData::end() const {
	return results.cend();
}

///////////////////////////////////////////////////////////////////////////////////////////////

inline size_t RegexSearchData::count() const {
	return results.size();
}


