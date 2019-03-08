#pragma once

namespace x
{
	//the buffer object of static size, used for preallocating memory, and reserving parts of it
	template<class _Type>
	class Buffer
	{
	protected:
		//the data to allocated mem
		_Type* _data;
		//the last added element
		_Type* _back;
		//the end of mem block
		_Type* _end;

		//uses low-level mem management for performance
		__forceinline static _Type* _alloc(size_t size) {
			return reinterpret_cast<_Type*>(::malloc(size * sizeof(_Type)));
		}

		__forceinline static void _dealloc(_Type* data) {
			::free(data);
		}

		__forceinline static _Type* _realloc(_Type* data, size_t capacity) {
			return ::realloc(data, capacity * sizeof(_Type));
		}

	public:
		//create buffer of given capacity
		Buffer(size_t capacity):
			_data(_alloc(capacity)),
			_back(_data - 1),
			_end(_data + capacity)
		{ }

		~Buffer() {
			_dealloc(_data);
		}

		Buffer(Buffer const&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(Buffer const&) = delete;
		Buffer& operator=(Buffer&&) = delete;

		//reserve mem for number of objects
		_Type* reserve(size_t size) {
			_Type* ptr = _back + 1;
			_back += size;
			return ptr;
		}

		//reserve mem for single object
		__forceinline _Type* next() {
			return ++_back;
		}

		//clear the buffer
		__forceinline void clear() {
			_back = _data - 1;
		}

		//clear mem with zeros
		__forceinline void zero() {
			::memset(_data, 0, (_end - _data) * sizeof(_Type));
		}

		//the size of buffer
		__forceinline size_t size() const {
			return _back - _data + 1;
		}

		//the size of allocated mem
		__forceinline size_t capacity() const {
			return _end - _data;
		}

		__forceinline bool empty() const {
			return _back < _data;
		}

		__forceinline _Type* begin() {
			return _data;
		}

		__forceinline _Type* end() {
			return _back + 1;
		}

		__forceinline _Type const* begin() const {
			return _data;
		}

		__forceinline _Type const* end() const {
			return _back + 1;
		}
	};
}
