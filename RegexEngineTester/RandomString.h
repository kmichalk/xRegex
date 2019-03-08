#pragma once

//utility for randomizing strings. used to generate strings in testing application
class RandomString
{
public:
	//generate string of specified length using all possible characters from specified string
	static std::string get(std::string const& symbols, size_t length);
	//generate string of specified length using all possible characters from specified string, split into 'nSub' words of min and max length
	static std::string get(std::string const& symbols, size_t nSub, size_t minSubLength, size_t maxSubLength);
};

