#include "stdafx.h"
#include "SearchResult.h"


size_t x::SearchResult::Entry::_previewLength = 50;
size_t x::SearchResult::Entry::_idAlign = 4;
size_t x::SearchResult::Entry::_textPosAlign = 7;

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & x::operator<<(std::ostream & os, x::SearchResult::Entry const & sre) {
	//using temporary buffer needed because of usage of printf
	char buffer[x::SearchResult::Entry::_BUFSIZE];
	sre._print(buffer);
	return os << buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & x::operator<<(std::ostream & os, x::SearchResult const & sr) {
	//allocate buffer if it is not present and print results to the buffer
	//then pass the buffer to stream and keep the buffer for future printing
	if (sr._data.empty())
		return os;
	if (sr._printBuffer == nullptr)
		sr._prepareBuffer();
	os << sr._printBuffer;
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char* x::SearchResult::Entry::_print(char const* format, char * buffer) const {
	//calculate the length of match info, center align and print to buffer
	size_t sidePreviewLength = (x::SearchResult::Entry::_previewLength - length) / 2;
	size_t leftSidePreviewLength = x::min(sidePreviewLength, srcpos);

	return buffer + 
		sprintf(buffer,
			format,
			x::SearchResult::Entry::_idAlign, id,
			x::SearchResult::Entry::_textPosAlign, srcpos,
			leftSidePreviewLength, begin - leftSidePreviewLength,
			length, begin,
			sidePreviewLength, begin + length);
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult::SearchResult():
	_data(_DEFAULT_EXPECTED),
	_sumLength(0),
	_printBuffer(nullptr),
	_dataBuffer(nullptr),
	_bufferOwner(true) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult::SearchResult(size_t expected):
	_data(expected),
	_sumLength(0),
	_printBuffer(nullptr),
	_dataBuffer(nullptr),
	_bufferOwner(true) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SearchResult::_makeIndependent() {
	//iterate through all matches, print them to a buffer and update the pointers to the input text
	_dataBuffer = static_cast<char*>(::malloc(_sumLength + _data.size()));
	_bufferOwner = true;
	char* pbuf = _dataBuffer;
	for (Entry& e : _data) {
		::memcpy(pbuf, e.begin, e.length);
		e.begin = pbuf;
		pbuf += e.length;
		*pbuf++ = '\0';
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SearchResult::_prepareBuffer() const {
	//allocate memory
	_printBuffer = static_cast<char*>(::malloc((20 + x::SearchResult::Entry::_previewLength) * _data.size()));
	//end buffer with NULL
	_printBuffer[0] = '\0';
	char* pbuf = _printBuffer;
	auto psre = _data.pcbegin();
	auto psreend = _data.pcend();
	//print all entries to buffer in new lines
	while (psre < psreend) {
		pbuf = psre->_println(pbuf);
		++psre;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult::SearchResult(SearchResult const & other):
	_data(other._data),
	_sumLength(other._sumLength),
	_printBuffer(other._printBuffer),
	_dataBuffer(other._dataBuffer),
	_bufferOwner(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult::SearchResult(SearchResult && other):
	_data(other._data.move()),
	_sumLength(other._sumLength),
	_printBuffer(other._printBuffer),
	_dataBuffer(other._dataBuffer),
	_bufferOwner(true)
{
	other._bufferOwner = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SearchResult::~SearchResult() {
	if (_bufferOwner) {
		//deallocate the buffers
		::free(_printBuffer);
		::free(_dataBuffer);
	}
}
