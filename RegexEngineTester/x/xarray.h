#pragma once

#include <xutility>
#include <iostream>

namespace x
{
	template<class _Type, class _Size, size_t _capacity>
	class _array
	{
		static constexpr size_t capacity_ = _capacity;
		_Type data_[capacity_];
		_Size size_;


		static void quicksort_(_Type* r1, _Type* r2) {
			if (r2 - r1 > 9) {
				_Type* pivot = (_Type*)(random32(uint32_t(r1 + 1), uint32_t(r2), sizeof(_Type)));
				_Type* last = r2;
				x::swapp(pivot, r2);
				for (_Type* e = r1; e < last; ++e) {
					if (*r2 < *e) {
						--last;
						while (e < last && *r2 < *last)
							--last;
						x::swapp(e, last);
					}
				}
				x::swapp(last, r2);
				if (r1 < last - 1) quicksort_(r1, last - 1);
				if (last + 1 < r2) quicksort_(last + 1, r2);
			} else {
				for (_Type* e = r1 + 1; e <= r2; ++e) {
					_Type temp;
					temp = *e;
					_Type* o = e - 1;
					while (o >= r1 && temp < *o) {
						*(o + 1) = *o;
						--o;
					}
					*(o + 1) = temp;
				}
			}
		}


		/*void quicksort_(int r1, int r2) {
			int last = r1;
			for (int i = r1; i < r2; ++i) {
				if (data_[i] < data_[r2]) {
					if (last != i)
						this->swap(i, last);
					++last;
				}
			}
			this->swap(last, r2);
			if (r1 < last - 1) quicksort_(r1, last - 1);
			if (last + 1 < r2) quicksort_(last + 1, r2);
		}*/

	public:
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = _Type;
		using pointer = _Type*;
		using reference = _Type&;


		__forceinline _array() = default;

		_array(_Size size):
			data_{0},
			size_(size)
		{
		}

		_array(_array<_Type, _Size, _capacity> const& other) :
			data_{},
			size_(other.size_)
		{
			memcpy(data_, other.data_, size_ * sizeof(_Type));
		}


		_array(_array<_Type, _Size, _capacity> && other):
			data_{},
			size_(other.size_)
		{
			memcpy(data_, other.data_, size_ * sizeof(_Type));
		}


		_array(std::initializer_list<_Type> data_):
			data_{},
			size_(0)
		{
			for (auto& v : data_)
				push_back(v);
		}

		///////////////////////////////////////////////////////////////////////////////
		
		struct const_iterator
		{
			using difference_type = ptrdiff_t;
			using value_type = _Type;
			using reference = _Type const&;
			using pointer = _Type const*;
			using iterator_category = std::bidirectional_iterator_tag;

			const _array<_Type, _Size, _capacity>& owner;
			size_t pos;

			const_iterator(const _array<_Type, _Size, _capacity>& owner):
				owner{owner},
				pos{0} {
			}

			const_iterator(const _array<_Type, _Size, _capacity>& owner, size_t pos):
				owner{owner},
				pos{pos} {
			}

			const_iterator(const const_iterator& other):
				owner{other.owner},
				pos{other.pos} {
			}

			const_iterator(const_iterator&& other):
				owner{other.owner},
				pos{other.pos} {
			}

			__forceinline const_iterator& operator++() {
				++pos;
				return *this;
			}

			__forceinline const_iterator& operator--() {
				--pos;
				return *this;
			}

			inline const_iterator operator++(int) {
				const_iterator copy{*this};
				++pos;
				return copy;
			}

			inline const_iterator operator--(int) {
				const_iterator copy{*this};
				--pos;
				return copy;
			}

			__forceinline const_iterator operator+(int i) {
				return const_iterator(owner, pos + i);
			}

			__forceinline const_iterator operator-(int i) {
				return const_iterator(owner, pos - i);
			}

			__forceinline const_iterator& operator+=(int i) {
				pos += i;
				return *this;
			}

			__forceinline const_iterator& operator-=(int i) {
				pos -= i;
				return *this;
			}

			__forceinline const_iterator operator+(size_t i) {
				return const_iterator(owner, pos + i);
			}

			__forceinline const_iterator operator-(size_t i) {
				return const_iterator(owner, pos - i);
			}

			__forceinline const_iterator& operator+=(size_t i) {
				pos += i; return *this;
			}

			__forceinline const_iterator& operator-=(size_t i) {
				pos -= i; return *this;
			}

			__forceinline const _Type& operator*() const {
				return owner.data_[pos];
			}

			__forceinline bool operator==(const const_iterator& other) const {
				return pos == other.pos;
			}

			__forceinline bool operator!=(const const_iterator& other) const {
				return pos != other.pos;
			}

			__forceinline bool operator<(const const_iterator& other) const {
				return pos < other.pos;
			}

			__forceinline bool operator>(const const_iterator& other) const {
				return pos > other.pos;
			}

			__forceinline bool operator<=(const const_iterator& other) const {
				return pos <= other.pos;
			}

			__forceinline bool operator>=(const const_iterator& other) const {
				return pos >= other.pos;
			}

			__forceinline const_iterator& operator=(const const_iterator& other) {
				pos = other.pos; return *this;
			}

			__forceinline operator bool() const {
				return pos < owner.size_;
			}

			__forceinline bool operator !() const {
				return pos >= owner.size_;
			}

			__forceinline auto operator->() const {
				return x::pointer(owner.data_[pos]);
			}

			__forceinline _Type const* ptr() const {
				return owner.data_ + pos;
			}
		};


		struct iterator
		{
			using difference_type = ptrdiff_t;
			using value_type = _Type;
			using reference = _Type &;
			using pointer = _Type *;
			using iterator_category = std::bidirectional_iterator_tag;

			_array<_Type, _Size, _capacity>& owner;
			size_t pos;

			iterator(_array<_Type, _Size, _capacity>& owner):
				owner{owner},
				pos{0} {
			}

			iterator(_array<_Type, _Size, _capacity>& owner, size_t pos):
				owner{owner},
				pos{pos} {
			}

			iterator(const iterator& other):
				owner{other.owner},
				pos{other.pos} {
			}

			iterator(iterator&& other):
				owner{other.owner},
				pos{other.pos} {
			}

			__forceinline iterator& operator++() {
				++pos;
				return *this;
			}

			__forceinline iterator& operator--() {
				--pos;
				return *this;
			}

			inline iterator operator++(int) {
				iterator copy{*this};
				++pos;
				return copy;
			}

			inline iterator operator--(int) {
				iterator copy{*this};
				--pos;
				return copy;
			}

			__forceinline iterator operator+(int i) {
				return iterator(owner, pos + i);
			}

			__forceinline iterator operator-(int i) {
				return iterator(owner, pos - i);
			}

			__forceinline iterator& operator+=(int i) {
				pos += i;
				return *this;
			}

			__forceinline iterator& operator-=(int i) {
				pos -= i;
				return *this;
			}

			__forceinline iterator operator+(size_t i) {
				return iterator(owner, pos + i);
			}

			__forceinline iterator operator-(size_t i) {
				return iterator(owner, pos - i);
			}

			__forceinline iterator& operator+=(size_t i) {
				pos += i;
				return *this;
			}

			__forceinline iterator& operator-=(size_t i) {
				pos -= i;
				return *this;
			}

			__forceinline _Type& operator*() {
				return owner.data_[pos];
			}

			__forceinline bool operator==(const iterator& other) const {
				return pos == other.pos;
			}

			__forceinline bool operator!=(const iterator& other) const {
				return pos != other.pos;
			}

			__forceinline bool operator<(const iterator& other) const {
				return pos < other.pos;
			}

			__forceinline bool operator>(const iterator& other) const {
				return pos > other.pos;
			}

			__forceinline bool operator<=(const iterator& other) const {
				return pos <= other.pos;
			}

			__forceinline bool operator>=(const iterator& other) const {
				return pos >= other.pos;
			}

			__forceinline iterator& operator=(const iterator& other) {
				pos = other.pos; return *this;
			}

			__forceinline operator bool() const {
				return pos < owner.size_;
			}

			__forceinline bool operator !() const {
				return pos >= owner.size_;
			}

			__forceinline auto operator->() {
				return x::pointer(owner.data_[pos]);
			}

			__forceinline operator const_iterator& () {
				return reinterpret_cast<const_iterator&>(*this);
			}

			__forceinline operator const_iterator const& () const {
				return reinterpret_cast<const_iterator const&>(*this);
			}
			
			__forceinline _Type* ptr() const {
				return owner.data_ + pos;
			}
		};
		
		///////////////////////////////////////////////////////////////////////////////
		
		__forceinline _Type& operator[](size_t i) {
			return data_[i];
		}

		__forceinline const _Type& operator[](size_t i) const {
			return data_[i];
		}

		__forceinline operator bool() const {
			return size_ > 0;
		}

		__forceinline void push_back(_Type const& value) {
			data_[size_++] = value;
		}

		__forceinline void pop_back() {
			--size_;
		}

		__forceinline iterator begin() {
			return iterator(*this, 0);
		}

		__forceinline iterator end() {
			return iterator(*this, size_);
		}

		__forceinline const_iterator begin() const {
			return const_iterator(*this, 0);
		}

		__forceinline const_iterator end() const {
			return const_iterator(*this, size_);
		}

		__forceinline const_iterator cbegin() const {
			return const_iterator(*this, 0);
		}

		__forceinline const_iterator cend() const {
			return const_iterator(*this, size_);
		}

		__forceinline bool empty() const {
			return size_ == 0;
		}

		__forceinline _Type* data() {
			return data_;
		}

		__forceinline _Type const* data() const {
			return data_;
		}

		__forceinline size_t size() const {
			return size_;
		}

		__forceinline static constexpr size_t capacity() {
			return _capacity;
		}

		__forceinline void clear() {
			size_ = 0;
		}

		__forceinline _Type& front() {
			return data_[0];
		}

		__forceinline _Type const& front() const {
			return data_[0];
		}

		__forceinline _Type& back() {
			return data_[size_ - 1];
		}

		__forceinline _Type const& back() const {
			return data_[size_ - 1];
		}

		void insert(_Type const& value, size_t pos) {
			memmove(data_ + pos + 1, data_ + pos, pos);
			data_[pos] = value;
		}

		void insert_sorted(_Type const& value) {
			size_t i = 0;
			for (; i < size_; ++i) {
				if (data_[i] >= value) 
					break;
			}
			memmove(data_ + i + 1, data_ + i, (size_ - i)*sizeof(_Type));
			data_[i] = value;
			++size_;
		}

		void insert_unique_sorted(_Type const& value) {
			_Type* e = data_;
			_Type* end = data_ + size_;
			while (e < end) {
				if (*e >= value) {
					if (*e == value)
						return;
					else
						break;
				}
				++e;
			}
			memmove(e + 1, e, (end - e)*sizeof(_Type));
			*e = value;
			++size_;
		}

		void insert_unique(_Type const& value) {
			_Type* e = data_;
			_Type* end = data_ + size_;
			while (e < end) {
				if (*e == value)
					return;
				++e;
			}
			*e = value;
			++size_;
		}

		__forceinline void sort() {
			quicksort_(data_, data_ + size_ - 1);
		}

		/*__forceinline void sort(size_t i1, size_t i2) {
			quicksort_(, (int)i2);
			return *this;
		}*/

		/*template<size_t _oCap>
		__inline void put(_array<_Type, _oCap> const& other) {
		}

		__inline operator=(_array<_Type> const& other) {
			memcpy(data_, other.data_, size_ * sizeof(_Type));
		}*/

		friend std::ostream& operator<<(std::ostream& os, _array<_Type, _Size, _capacity> const& a) {
			using Cast = std::conditional_t<std::is_same<_Type, unsigned char>::value, int, _Type>;
			os << "{ ";
			for (size_t i = 0, max = a.size_ - 1; i < max; ++i)
				os << (Cast)a.data_[i] << ',';
			return os << (Cast)a.data_[a.size_ - 1] << " }";
		}

	};

	///////////////////////////////////////////////////////////////////////////////

	template<class _Type, size_t _capacity>
	using array = _array<_Type, size_t, _capacity>;

	template<class _Type, size_t _capacity>
	using grouped_array = _array<_Type, size_t&, _capacity>;
}
