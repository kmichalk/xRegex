#include "stdafx.h"
#include "RegexSearchData.h"
#include "SearchResultHighlighter.h"


char * SearchResultHighlighter::placeFormatHeader(char * buf) const {
	memcpy(buf, HIGHLIGHTED_TEXT_STYLE_HEADER[_color], sizeof(HIGHLIGHTED_TEXT_STYLE_HEADER_1) - 1);
	//change color
	_color = !_color;
	return buf + (sizeof(HIGHLIGHTED_TEXT_STYLE_HEADER_1) - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////

char * SearchResultHighlighter::placeFormatFooter(char * buf) const {
	memcpy(buf, HIGHLIGHTED_TEXT_STYLE_FOOTER, sizeof(HIGHLIGHTED_TEXT_STYLE_FOOTER) - 1);
	return buf + (sizeof(HIGHLIGHTED_TEXT_STYLE_FOOTER) - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////

char * SearchResultHighlighter::allocateBuffer(QString const& input, RegexSearchData const & searchData) const {
	return new char[HIGHLIGHTER_BUFFER_MIN_SIZE + input.length() + searchData.count()*HIGHLIGHTER_BUFFER_INPUT_SIZE_MULT]{0};
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString SearchResultHighlighter::highlight(QString const & input, RegexSearchData const & searchData) const {
	//reset color as first of 2 possible
	_color = 0;
	if (searchData.results.empty())
		return input;
	QByteArray arr = input.toLatin1();
	char const* inputData = arr.cbegin();
	char const* pinput = inputData;
	char* buffer = allocateBuffer(input, searchData);
	char* pbuf = buffer;	
	//iterate through results
	for (auto const& r : searchData) {
		//calculate the length of match
		size_t length = r.position - (pinput - inputData);
		//place the unmatched text into buffer
		memcpy(pbuf, pinput, length);
		pbuf += length;
		pinput += length;
		//place header
		pbuf = placeFormatHeader(pbuf);		
		//place colored text
		memcpy(pbuf, pinput, r.length);
		pbuf += r.length;
		pinput += r.length;
		//place closing footer
		pbuf = placeFormatFooter(pbuf);
	}
	//copy the rest 
	memcpy(pbuf, pinput, (inputData + arr.size() - pinput));
	QString r = QString::fromLatin1(buffer);
	r.replace('\n', "<br>");
	return r;
}
