#pragma once

//the low-level, optimized highlighter of search results found
class SearchResultHighlighter
{
	//1 or 0 - for coloring with 2 different colors
	mutable size_t _color;
	//place the format html into buffer
	char* placeFormatHeader(char* buf) const;
	//place the format html closing footer into buffer
	char* placeFormatFooter(char* buf) const;
	char* allocateBuffer(QString const& input, RegexSearchData const & searchData) const;
public:
	QString highlight(QString const& input, RegexSearchData const& searchData) const;
};

