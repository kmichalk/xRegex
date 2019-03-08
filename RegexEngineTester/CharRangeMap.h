#pragma once

namespace x
{
	//a class used for generating tables of symbols assigned to a character representing a specific character class
	class CharRangeMap
	{
		x::vector<char> charRanges_[256];
		void _set();

	public:
		CharRangeMap();

		void set(char ch, CharClass chcl);
		void set(char ch, x::vector<char> const& range);
		void set(char ch, x::vector<char> && range);
		void set(char ch, char symbol);
		void setSame(char ch);
		void setSame(char const* chs);
		void setInverse(char ch, CharClass chcl);
		void setInverse(char ch, x::vector<char> const& range);
		x::vector<char> const& operator[](char ch) const;
		void print(std::ostream& os) const;
		void generateRangeTable(std::string const& tableName, std::ostream& os) const;
	};
}
