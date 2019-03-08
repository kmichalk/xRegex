#pragma once

namespace x
{
	//a set of regex search results. created by user to be passed to search function or returned by search function
	class SearchResult
	{
		friend class Regex;
	public:
		//a single match data
		struct Entry {
			friend class SearchResult;
		private:
			//formatting data for printing results
			static constexpr size_t _BUFSIZE = 1024;
			static constexpr const char _FORMAT[] = "%*i. %*i:  %.*s{%.*s}%.*s";
			static constexpr const char _FORMAT_LINE[] = "%*i. %*i:  %.*s{%.*s}%.*s\n";
			//length of the part of input string to be printed around the match
			static size_t _previewLength;
			//the alignment of the number of match from left border
			static size_t _idAlign;
			//the alignment of the position in text of match from left border
			static size_t _textPosAlign;

			//print the result with its surrounding to the buffer
			char* _print(char const* format, char* buffer) const;

			__forceinline char* _print(char* buffer) const {
				return _print(_FORMAT, buffer);
			}

			__forceinline char* _println(char* buffer) const {
				return _print(_FORMAT_LINE, buffer);
			}

		public:
			//the pointer to the begin of match in input text
			char const* begin;
			//the length of match
			size_t length;
			//the position in input text
			size_t srcpos;
			//the order number of match
			size_t id;

			//convert to string
			__forceinline std::string str() const {
				return std::string(begin, begin + length);
			}

			friend std::ostream& operator<<(std::ostream& os, x::SearchResult::Entry const& sre);
			friend std::ostream& operator<<(std::ostream & os, x::SearchResult const & sr);
		};

	private:
		//the number of memory defaultly allocated for results for optimization
		static constexpr size_t _DEFAULT_EXPECTED = 32;

		//the results
		x::vector<Entry> _data;
		//the sum length of all matches
		size_t _sumLength;
		//the data of string representation of printed results
		mutable char* _printBuffer;
		//the data of copied contents of matches in IndependentResults mode
		char* _dataBuffer;
		//flag indicationg that the object has created the buffers data
		bool _bufferOwner;


		__forceinline void _add(Entry&& result) {
			_data.push_back((Entry&&)result);
			_sumLength += result.length;
		}

		//process all matches to make them independent of the original input string
		void _makeIndependent();
		//preallocate an empty buffer
		void _prepareBuffer() const;

	public:
		SearchResult();
		SearchResult(size_t expected);
		SearchResult(SearchResult const& other);
		SearchResult(SearchResult&& other);
		SearchResult& operator=(SearchResult const&) = default;
		SearchResult& operator=(SearchResult&&) = default;
		~SearchResult();

		__forceinline Entry& get(size_t idx) {
			return _data[idx];
		}

		__forceinline Entry const& get(size_t idx) const {
			return _data[idx];
		}

		__forceinline Entry& operator[](size_t idx) {
			return _data[idx];
		}

		__forceinline Entry const& operator[](size_t idx) const {
			return _data[idx];
		}

		__forceinline size_t size() const {
			return _data.size();
		}

		__forceinline auto begin() const {
			return _data.cbegin();
		}

		__forceinline auto end() const {
			return _data.cend();
		}

		__forceinline vector<Entry> const& data() const {
			return _data;
		}

		__forceinline void clear() {
			_data.clear();
		}

		friend std::ostream& operator<<(std::ostream& os, SearchResult const& sr);
	};
}
