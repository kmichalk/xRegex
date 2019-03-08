#pragma once

#include <cstdlib>
#include "more_type_traits.h"

namespace x
{
	template<class _Type>
	class pool {
		size_t capacity_;
		size_t free_;
		_Type* data_;
		_Type** ptrs_;

		template<class _T>
		static __inline _T* allocate_(size_t size) {
			return reinterpret_cast<_T*>(::malloc(size * sizeof(_T)));
		}

		__inline void deallocate_() {
			::free(data_);
			::free(ptrs_);
		}

		void initPointers_() {
			_Type** pp = ptrs_;
			_Type* p = data_ + capacity_ - 1;
			while (p >= data_) {
				*pp = p;
				++pp;
				--p;
			}
			/*ptrs_[0] = data_;
			_Type* p = data_ + capacity_ - 1;
			for (_Type** pp = ptrs_ + 1; p > data_; ++pp, --p)
				*pp = p;*/
		}

		void restorePointers_(_Type* begin, size_t size) {
			_Type** pp = ptrs_ + free_;
			_Type* p = begin + size - 1;
			while (p >= begin) {
				*pp = p;
				++pp;
				--p;
			}
			free_ += size;
		}


	public:
		static constexpr size_t DEFAULT_SIZE = 1024;

		pool(){
			capacity_ = 0;
			free_ = 0;
			data_ = nullptr;
			ptrs_ = nullptr;
		}
		
		pool(size_t size) {
			capacity_ = size;
			free_ = capacity_;
			data_ = allocate_<_Type>(capacity_);
			ptrs_ = allocate_<_Type*>(capacity_);
			initPointers_();
		}

		~pool() {
			deallocate_();
		}

		/*static void initialize(size_t size) {
			new (&instance) pool<_Type>(size);
		}*/

		__forceinline _Type* alloc() {
			return ptrs_[--free_];
		}

		__forceinline void dealloc(_Type* ptr) {
			ptrs_[free_++] = ptr;
		}

		_Type* const* multialloc(size_t size) {
			 return ptrs_ + (free_ -= size);
		}
		
		void dealloc(_Type* begin, size_t size) {
			restorePointers_(begin, size);
		}

		void reserve(size_t size) {
			
		}
	};

	/*template<class _Type>
	pool<_Type> pool<_Type>::instance;*/
}


#define POOL_OBJECT(_poolSize) \
private: \
	DECLARE_THIS_T; \
	inline static x::pool<this_t> _pool_ = (_poolSize); \
public: \
	inline static void* operator new (size_t size) { \
		return reinterpret_cast<this_t*>(_pool_.alloc()); \
	} \
	inline static void* operator new (size_t size, void* dest) noexcept { \
		return dest; \
	} \
	inline static void operator delete (void* ptr) { \
		_pool_.dealloc(reinterpret_cast<this_t*>(ptr)); \
	} \
private: