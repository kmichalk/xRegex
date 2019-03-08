#ifndef _X_VECTOR_H_
#define _X_VECTOR_H_

//! VERSION: latest

#include "more_type_traits.h"
#include "result.h"
#include "simple.h"
#include "bitliteral.h"
#include "rand32.h"
#include "xtuple.h"
#include "pred.h"
#include "bitstr.h"
#include "bitcount.h"
#include "va_handler.h"
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <fstream>
#include "loops.h"

///////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning(push)
#pragma warning(disable: 4522) //Multiple assignment operators specified
#pragma warning(disable: 4005) //Macro redefinition

///////////////////////////////////////////////////////////////////////////////////////////////
//Default macro settings values

#ifndef	XVECTOR_DEBUG
#define XVECTOR_DEBUG false
#endif

#ifndef	XVECTOR_EXTENSION_MODE
#define XVECTOR_EXTENSION_MODE Constant
#endif

#ifndef	XVECTOR_ITERATOR_MODE
#define XVECTOR_ITERATOR_MODE Index
#endif

#ifndef XVECTOR_THREAD_SAFE
#define XVECTOR_THREAD_SAFE false
#endif

#ifndef XVECTOR_USE_THREAD_LOCAL
#define XVECTOR_USE_THREAD_LOCAL false
#endif

#ifndef XVECTOR_LOCK_ENABLED
#define XVECTOR_LOCK_ENABLED false
#endif

#ifndef XVECTOR_USE_REALLOC
#define XVECTOR_USE_REALLOC true
#endif

#ifndef XVECTOR_NO_INLINE
#define XVECTOR_NO_INLINE false
#endif

#ifndef XVECTOR_OPTIMIZE_CONSTRUCT_FOR_TRIVIALLY_COPYABLE
#define XVECTOR_OPTIMIZE_CONSTRUCT_FOR_TRIVIALLY_COPYABLE true
#endif

#ifndef XVECTOR_ALLOW_AGGREGATE_CONSTRUCT
#define XVECTOR_ALLOW_AGGREGATE_CONSTRUCT true
#endif

#ifndef XVECTOR_MOVE_FROM_INITIALIZER_LIST
#define XVECTOR_MOVE_FROM_INITIALIZER_LIST true
#endif

#ifndef XVECTOR_DEFAULT_ALLOCATION_MODE
#define XVECTOR_DEFAULT_ALLOCATION_MODE NoAlloc
#endif

#ifndef XVECTOR_FIELD_ACCESS
#define XVECTOR_FIELD_ACCESS private
#endif

#ifndef XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
#define XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER true
#endif

#ifndef XVECTOR_DEFAULT_METHOD_MODE
#define XVECTOR_DEFAULT_METHOD_MODE Default
#endif

#ifndef XVECTOR_ENABLE_EXCEPTIONS
#define XVECTOR_ENABLE_EXCEPTIONS false
#endif

#ifndef XVECTOR_FORCEINLINE_DESTRUCT
#define XVECTOR_FORCEINLINE_DESTRUCT true
#endif

#ifndef XVECTOR_PREALLOC_POLICY
#define XVECTOR_PREALLOC_POLICY Reasonable
#endif

#ifndef XVECTOR_USE_CALLOC
#define XVECTOR_USE_CALLOC false
#endif

#ifndef XVECTOR_ZERO_SIZE_ON_MOVE
#define XVECTOR_ZERO_SIZE_ON_MOVE false
#endif

#ifndef XVECTOR_ENABLE_ITERATORS
#define XVECTOR_ENABLE_ITERATORS true
#endif

#ifndef XVECTOR_ENABLE_NODISCARD
#define XVECTOR_ENABLE_NODISCARD true
#endif

#ifndef XVECTOR_QUICKSORT_PIVOT
#define XVECTOR_QUICKSORT_PIVOT Random
#endif

#ifndef XVECTOR_DEFAULT_SORT_ALGORITHM
#define XVECTOR_DEFAULT_SORT_ALGORITHM Quicksort
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
//Internal default macro settings values

#ifndef _DEFAULT_MIN_SIZE
#define _DEFAULT_MIN_SIZE 4
#endif

#ifndef _RESERVE_CHECK_NULLPTR
#define _RESERVE_CHECK_NULLPTR false
#endif

#ifndef _MOVE_STD_VECTOR
#define _MOVE_STD_VECTOR true
#endif

#ifndef _INITIAL_STATIC_BUFFER_SIZE
#define _INITIAL_STATIC_BUFFER_SIZE 1024
#endif

#ifndef _INNER_MERGESORT_MIN_RESERVE
#define _INNER_MERGESORT_MIN_RESERVE 4
#endif

///////////////////////////////////////////////////////////////////////////////////////////////

#define ExtensionMode_Constant	1
#define ExtensionMode_Local		2
#define ExtensionMode_Static	3
#define ExtensionMode_Custom	4

#define IteratorMode_Index		1
#define IteratorMode_Pointer	2

#define FieldAccess_private		1
#define FieldAccess_protected	2
#define FieldAccess_public		3

#define PreallocPolicyMode_None			1
#define PreallocPolicyMode_Reasonable	2
#define PreallocPolicyMode_Generous		3
#define PreallocPolicyMode_Custom		4

#define QuicksortPivotMode_Random	1
#define QuicksortPivotMode_Split	2
#define QuicksortPivotMode_First	3
#define QuicksortPivotMode_Last		4

#define DefualtSortAlgorithmMode_Quicksort	1
#define DefualtSortAlgorithmMode_Mergesort	2

///////////////////////////////////////////////////////////////////////////////////////////////

#define MODE(_mode, _value) (_mode##Mode == _mode##Mode_##_value)
#define MODE_NOT(_mode, _value) (_mode##Mode != _mode##Mode_##_value)
#define MODE_ONE_OF(_mode, ...) APPLY_2_S(MODE, ||, _mode, __VA_ARGS__)
#define MODE_NONE_OF(_mode, ...) APPLY_2_S(MODE_NOT, &&, _mode, __VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////////////////////

#define ExtensionMode CAT(ExtensionMode_, XVECTOR_EXTENSION_MODE)
#define IteratorMode CAT(IteratorMode_, XVECTOR_ITERATOR_MODE)
#define FieldAccessMode CAT(FieldAccessMode_, XVECTOR_FIELD_ACCESS)
#define PreallocPolicyMode CAT(PreallocPolicyMode_, XVECTOR_PREALLOC_POLICY)
#define QuicksortPivotMode CAT(QuicksortPivotMode_, XVECTOR_QUICKSORT_PIVOT)
#define DefaultSortAlgorithmMode CAT(DefaultSortAlgorithmMode_, XVECTOR_DEFAULT_SORT_ALGORITHM)

///////////////////////////////////////////////////////////////////////////////////////////////

#if MODE_NONE_OF(Extension, Constant, Local, Static, Custom)
#error x::vector: Invalid value of ExtensionMode. Possible values are: Constant, Local, Static, Custom.
#endif

#if MODE_NONE_OF(Iterator, Index, Pointer)
#error x::vector: Invalid value of IteratorMode. Possible values are: Index, Pointer.
#endif

#if MODE_NONE_OF(FieldAccess, private, protected, public)
#error x::vector: Invalid value of FieldAccessMode. Possible values are: private, protected, public.
#endif

#if MODE_NONE_OF(PreallocPolicy, None, Reasonable, Generous, Custom)
#error x::vector: Invalid value of PreallocPolicyMode. Possible values are: None, Reasonable, Generous, Custom.
#endif

#if MODE_NONE_OF(QuicksortPivot, Random, Split, First, Last)
#error x::vector: Invalid value of QuicksortPivotMode. Possible values are: Random, Split, First, Last.
#endif

#if MODE_NONE_OF(DefaultSortAlgorithm, Quicksort, Mergesort)
#error x::vector: Invalid value of DefaultSortAlgorithmMode. Possible values are: Quicksort, Mergesort.
#endif

///////////////////////////////////////////////////////////////////////////////////////////////

#define _MUTEX_NAME lock_
#define _MUTEX_TYPE x::mutex
#define _LOCK_TYPE x::lock

#if XVECTOR_DEBUG
#define XVECTOR_NO_INLINE true
#endif

#if XVECTOR_THREAD_SAFE
#define XVECTOR_LOCK_ENABLED true
#define XVECTOR_USE_THREAD_LOCAL true
#define _LOCK_MODE_SET (!_mode_set(NoLock))
#define _OPT_LOCK x::lock_wrapper<_LOCK_TYPE, _LOCK_MODE_SET> _scopeLock_(_MUTEX_NAME)
#else
#define _LOCK_MODE_SET (_mode_set(Lock))
#if XVECTOR_LOCK_ENABLED
#define _OPT_LOCK x::lock_wrapper<_LOCK_TYPE, _LOCK_MODE_SET> _scopeLock_(_MUTEX_NAME)
#else
#define _OPT_LOCK static_assert(!_LOCK_MODE_SET, "Lock option usage is invalid because XVECTOR_LOCK_ENABLED is set to false.")
#endif
#endif

#if XVECTOR_USE_THREAD_LOCAL
#define OPT_THREAD_LOCAL 
#else 
#define OPT_THREAD_LOCAL thread_local
#endif

#if XVECTOR_NO_INLINE
#define INLINE __declspec(noinline)
#define FORCEINLINE __declspec(noinline)
#else
#define INLINE __inline
#define FORCEINLINE __forceinline
#endif

#ifndef _MSC_VER
#define XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER false
#elif defined _WIN64
#define XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER false
#endif 

#if XVECTOR_FORCEINLINE_DESTRUCT
#define _destruct_all() { if constexpr (!std::is_trivially_destructible_v<_Type>) { destruct_all_(); } }
#define _destruct_from(_begin) { if constexpr (!std::is_trivially_destructible_v<_Type>) { destruct_from_(_begin); } }
#define _destruct_range(_begin, _end) { if constexpr (!std::is_trivially_destructible_v<_Type>) { destruct_range_(_begin, _end); } }
#else
#define _destruct_all() destruct_all_()
#define _destruct_from(_begin) destruct_from_(_begin)
#define _destruct_range(_begin, _end) destruct_range_(_begin, _end)
#endif

#if XVECTOR_ENABLE_NODISCARD
#define NODISCARD [[nodiscard]]
#else
#define NODISCARD
#endif

#define _DefaultMode XVECTOR_DEFAULT_METHOD_MODE




//TODO is this useful?
//#if MODE(FieldAcces, private)
//#define reserved_ reserved_
//#define size_ size_
//#define data_ data_
//#define lock_ lock_
//#elif MODE(FieldAccess, protected)
//#define reserved_ reserved_
//#define size_ size_
//#define data_ data_
//#define lock_ lock_
//#elif MODE(FieldAccess, public)
//#define reserved_ reserved
//#define size_ size
//#define data_ data
//#define lock_ lock
//#else
//#endif



//#if defined XVECTOR_USE_STATIC_BUFFERS
//#define _STATIC_BUFFER_NAME(_name) _name##_
//#define _VECTOR_BUFFER(_name, _size) _vector<_Type>& _name = x::_VectorTemp::_STATIC_BUFFER_NAME(_name); _name.resize(_size)
////#define _ARRAY_BUFFER(_name, _size) _Type* _name = x::_VectorTemp::_STATIC_BUFFER_NAME(_name).data_;
//#else
//#define _VECTOR_BUFFER(_name, _size) _vector<_Type> _name(_size)
//#endif


///////////////////////////////////////////////////////////////////////////////////////////////

#define SPEC OPT(XVECTOR_NO_INLINE, noinline)
#define _SPEC _OPT(XVECTOR_NO_INLINE, noinline)

//ENABLE_DEBUG;
//ENABLE_STACK_DISPLAY;

///////////////////////////////////////////////////////////////////////////////////////////////

#define enable_if std::enable_if_t
#define enable_if_(...) std::enable_if_t<__VA_ARGS__>
//#define enable_if

///////////////////////////////////////////////////////////////////////////////////////////////

////? moving from const && (??)
////? index policy: begin-end / first-last / begin-count (?)
//TODO add _depth option in all adequate functions
//TODO _vector<_Type&> _vector<_Type&&>
//TODO initializer_list overloads in functions taking _vector
//TODO vector_subset as separate class
////TODO _vector() and _vector{} non allocating + check other functions compatibility
////TODO universal class _iterator with template parameters
//TODO prepend, insert with amount parameter
////TODO filter
//TODO _depth in generate
//TODO calloc is a valid initialization of array of vectors...
//TODO multisizes in all randomize functions
//? auto ... -> enable_if
////TODO calloc in fill constructor for value 0
////TODO size extension on int arithmetic
////TODO replace [...].move() with macro _rv([...])
//! rewrite compare_
//TODO insert_before insert_after
//TODO variadic args in all ..._if functions
//TODO array variants of functons with variadic sizes
//TODO remove as much enable_if as possible
////TODO _VECTOR_THREAD_SAFE
//TODO finish merge_sort
//TODO begin end -> begin size
////TODO remove fill constructor
////TODO bring back (capacity,size) constructor
//? reallocation multiplier as vector member ?

#define _mode _modeval
#define _mode_set(_val) (_mode & _val)
#define _assert_mode(...) static_assert((bitor(__VA_ARGS__) & _mode) == _mode)
	//#define _mode_set(_val) is_set(_mode, _val)
	//#define _assert_mode(...) static_assert(any_of(_mode,__VA_ARGS__))
#define _validate_depth static_assert(_depth >= 1 && _depth <= DIM_)
#define _foreach(_i) for (_Type* _i = data_, *__end__ = data_ + size_; _i < __end__; ++_i)
#define _foreach_o(_i, _offset) for (_Type* _i = data_ + (_offset), *__end__ = data_ + size_; _i < __end__; ++_i)
#define _foreach_v(_i, _vec) for (_Type* _i = _vec.data_, *__end__ = _vec.data_ + _vec.size_; _i < __end__; ++_i)
#define _step_foreach(_i, _step) for (_Type* _i = data_, *__end__ = data_ + size_; _i < __end__; _i += (_step))
#define _const_step_foreach(_i, _step) for (_Type const* _i = data_, *__end__ = data_ + size_; _i < __end__; _i += (_step))
#define _step_foreach_v(_i, _vec, _step) for (_Type* _i = (_vec).data_, *__end__ = _i + size_; _i < __end__; _i += (_step))
#define _const_step_foreach_v(_i, _vec, _step) for (_Type const* _i = (_vec).data_, *__end__ = _i + size_; _i < __end__; _i += (_step))
#define _step_foreach_o(_i, _offset, _step) for (_Type* _i = data_ + (_offset), *__end__ = data_ + size_; _i < __end__; _i += (_step))
#define _const_step_foreach_o(_i, _offset, _step) for (_Type const* _i = data_ + (_offset), *__end__ = data_ + size_; _i < __end__; _i += (_step))
#define _step_foreach_os(_i, _offset, _step, _size) for (_Type* _i = data_ + (_offset), *__end__ = data_ + (_size); _i < __end__; _i += (_step))
#define _const_step_foreach_os(_i, _offset, _step, _size) for (_Type const* _i = data_ + (_offset), *__end__ = data_ + (_size); _i < __end__; _i += (_step))
#define _reverse_foreach(_i) for (_Type* _i = data_ + size_ - 1; _i >= data_; --_i)
#define _const_reverse_foreach(_i) for (_Type const* _i = data_ + size_ - 1; _i >= data_; --_i)
#define _const_foreach(_i) for (_Type const* _i = data_, *__end__ = data_ + size_; _i < __end__; ++_i)
#define _const_foreach_o(_i, _offset) for (_Type const* _i = data_ + (_offset), *__end__ = data_ + size_; _i < __end__; ++_i)
#define _foreach_from(_i, _begin) for (_Type* _i = (_begin), *__end__ = data_ + size_; _i < __end__; ++_i)
#define _const_foreach_from(_i, _begin) for (_Type const* _i = (_begin), *__end__ = data_ + size_; _i < __end__; ++_i)
#define _foreach_from_s(_i, _begin, _size) for (_Type* _i = (_begin), *__end__ = data_ + (_size); _i < __end__; ++_i)
#define _const_foreach_from_s(_i, _begin, _size) for (_Type const* _i = (_begin), *__end__ = data_ + (_size); _i < __end__; ++_i)
#define _foreach_from_i(_i) for (_Type* __end__ = data_ + size_; _i < __end__; ++_i)
#define _const_foreach_from_i(_i) for (_Type const* __end__ = data_ + size_; _i < __end__; ++_i)
	//#define _const_pair_foreach(_v0, _i0, _v1, _i1) for (_Type const* _i0 = (_v0).data_, *__end0__ = _i0 + (_v0).size_, *_i1 = (_v1).data_, *__end1__ = _i1 + (_v1).size_; _i0 < __end0__; ++_i0, ++_i1)
#define _for_range(_i, _begin, _end) for (_Type* _i = (_begin); _i < (_end); ++_i)
#define _const_for_range(_i, _begin, _end) for (_Type const* _i = (_begin); _i < (_end); ++_i)
#define _foreach_uninit(_i) for (_Type* _i = data_ + size_, *__end__ = data_ + reserved_; _i < __end__; ++_i)
#define _const_foreach_uninit(_i) for (_Type const* _i = data_ + size_, *__end__ = data_ + reserved_; _i < __end__; ++_i)
#define _foreach_reserved(_i) for (_Type* _i = data_, *__end__ = data_ + reserved_; _i < __end__; ++_i)
#define _const_foreach_reserved(_i) for (_Type const* _i = data_, *__end__ = data_ + reserved_; _i < __end__; ++_i)
#define _pair_foreach(_v0, _i0, _v1, _i1) \
	auto _i0 = (_v0).data_; \
	auto _i1 = (_v1).data_; \
	auto __end0__ = _i0 + (_v0).size_; \
	for ( ; _i0 < __end0__; ++_i0, ++_i1)

///////////////////////////////////////////////////////////////////////////////////////////////

#if XVECTOR_OPTIMIZE_CONSTRUCT_FOR_TRIVIALLY_COPYABLE
	#if XVECTOR_ALLOW_AGGREGATE_CONSTRUCT
		#define _construct_t(_Type, _ptr, ...) { \
			if constexpr (std::is_aggregate_v<_Type>) { \
				if constexpr (std::is_trivially_copyable_v<_Type>) { \
					*(_ptr) = _Type{__VA_ARGS__}; \
				} else { \
					new (_ptr) _Type{__VA_ARGS__}; \
				} \
			} else { \
				if constexpr (std::is_trivially_copyable_v<_Type>) { \
					*(_ptr) = _Type(__VA_ARGS__); \
				} else { \
					new (_ptr) _Type(__VA_ARGS__); \
				} \
			} \
		}	
	#else
		#define _construct_t(_Type, _ptr, ...) { \
			if constexpr (std::is_trivially_copyable_v<_Type>) { \
				*(_ptr) = _Type(__VA_ARGS__); \
			} else { \
				new (_ptr) _Type(__VA_ARGS__); \
			} \
		}	
	#endif
#else
	#if XVECTOR_ALLOW_AGGREGATE_CONSTRUCT
		#define _construct_t(_Type, _ptr, ...) { \
			if constexpr (std::is_aggregate_v<_Type>) { \
				new (_ptr) _Type{__VA_ARGS__}; \
			} else { \
				new (_ptr) _Type(__VA_ARGS__); \
			} \
		}	
	#else
		#define _construct_t(_Type, _ptr, ...) { new (_ptr) _Type(__VA_ARGS__); } 
	#endif
#endif

#define _construct(_ptr, ...) _construct_t(_Type, _ptr, __VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////////////////////

	//#define _construct(_ptr, ...) 
#define _destruct_t(_Type, _ptr) (_ptr)->~_Type()
#define _destruct(_ptr) (_ptr)->~_Type()
#define _reconstruct_t(_Type, _ptr, ...) { _destruct_t(_Type, _ptr); _construct_t(_Type, _ptr, __VA_ARGS__); }
#define _reconstruct(_ptr, ...) { _destruct(_ptr); _construct(_ptr, __VA_ARGS__); }
#define _trivcopy(_dest, _src) { *reinterpret_cast<::x::fake<::x::naked_t<decltype(_dest)>>*>(_dest) = *reinterpret_cast<::x::fake<::x::naked_t<decltype(_dest)>> const*>(_src); }
#define _trivcopy_t(_Type, _dest, _src) { *reinterpret_cast<::x::fake<_Type>*>(_dest) = *reinterpret_cast<::x::fake<_Type> const*>(_src); }

#define _rvthis ((_vector<_Type>&&)(*this))
#define _rv (_vector<_Type>&&)
#define _rv_t(_Type, _vec) ((_vector<_Type>&&)(_vec))

#define _enable_if(...) std::enable_if_t<__VA_ARGS__>

///////////////////////////////////////////////////////////////////////////////////////////////

namespace x
{
	using mode_t = uint32_t;

	enum mode: mode_t
	{
		Default = BIT<0>,
		NoSizeCheck = BIT<1>,
		NoIndexCheck = BIT<2>,
		NoArgCheck = BIT<3>,
		NoExtend = BIT<4>,
		AllowReorder = BIT<5>,
		NoDynamic = BIT<6>,
		AssumeSorted = BIT<7>,
		NoDestruct = BIT<8>,
		Lock = BIT<9>,
		NoLock = BIT<10>,
		AssumeEmpty = BIT<11>,
		//Extended = BIT<11>,
		NoCheck = NoSizeCheck | NoIndexCheck | NoArgCheck,
		Naked = NoCheck | NoLock
	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<class> class _vector;
	template<class> class _vector_backwards;
	template<class> class _refvector;

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<class _Type, unsigned _dim>
	struct _vector_nd {
		using type = _vector<typename _vector_nd<_Type, _dim - 1>::type>;
	};

	template<class _Type>
	struct _vector_nd<_Type, 0> {
		using type = _Type;
	};

	template<class _Type, unsigned _dim>
	using _vector_nd_t = typename _vector_nd<_Type, _dim>::type;

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<class _Type, unsigned _dim = 1>
	using vector = std::conditional_t<_dim == 1, _vector<_Type>, _vector_nd_t<_Type, _dim>>;

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	struct range {
		_Type begin;
		_Type end;

		__forceinline range(_Type begin, _Type end):
			begin(begin),
			end(end) {
		}
	};


	template<class _Type>
	struct iterative_range {
	private:
		static constexpr _Type defaultStep_() {
			if constexpr (std::is_convertible_v<int, _Type>)
				return _Type(1);
			else
				return _Type();
		}
	public:
		_Type from;
		_Type to;
		_Type step;

		__forceinline iterative_range(_Type begin, _Type end, _Type step = defaultStep_()):
			begin(begin),
			end(end),
			step(step) {
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////

#define XVECTOR_EXTEND_FUNCTION(_Type) \
	__forceinline constexpr size_t x::_vector<_Type>::extended_capacity_(size_t capacity) noexcept

#if MODE(PreallocPolicy, Custom) 
#define XVECTOR_PREALLOC_FUNCTION(_Type) \
	__forceinline constexpr size_t x::_vector<_Type>::prealloc_size_(size_t size) noexcept
#endif

	///////////////////////////////////////////////////////////////////////////////////////////////

#if XVECTOR_ENABLE_ITERATORS
	#if MODE(IteratorMode, Index)
		template<int _step, class _Value, class _Ref, class _Ptr, class _Owner, bool _deref = false>
		class __iterator
		{
		public:
			template<class>
			friend class _vector;

			template<class>
			friend class _refvector;

			using difference_type = ptrdiff_t;
			using value_type = _Value;
			using reference = _Ref;
			using pointer = _Ptr;
			using iterator_category = std::bidirectional_iterator_tag;

			_Owner& owner;
			size_t pos;


			__iterator(_Owner& owner) noexcept:
				owner(owner),
				pos(0) {
			}

			__iterator(_Owner& owner, size_t pos) noexcept:
				owner(owner),
				pos(pos) {
			}

			__iterator(const __iterator& other) noexcept:
				owner(other.owner),
				pos(other.pos) {
			}

			__iterator(__iterator&& other) noexcept:
				owner(other.owner),
				pos(other.pos) {
			}

			FORCEINLINE __iterator& operator++() noexcept {
				pos += _step;
				return *this;
			}


			FORCEINLINE __iterator& operator--() noexcept {
				pos -= _step;
				return *this;
			}


			INLINE __iterator operator++(int) const noexcept {
				__iterator copy{*this};
				pos += _step;
				return copy;
			}

			INLINE __iterator operator--(int) const noexcept {
				__iterator copy{*this};
				pos -= _step;
				return copy;
			}

			FORCEINLINE __iterator operator+(int i) const noexcept {
				return __iterator(owner, pos + i);
			}

			FORCEINLINE friend __iterator operator+(int offset, __iterator const& i) noexcept {
				return __iterator(i.owner, i.pos + offset);
			}

			FORCEINLINE __iterator operator-(int i) const noexcept {
				return __iterator(owner, pos - i);
			}

			FORCEINLINE __iterator& operator+=(int i) noexcept {
				pos += i;
				return *this;
			}

			FORCEINLINE __iterator& operator-=(int i) noexcept {
				pos -= i;
				return *this;
			}

			FORCEINLINE __iterator operator+(size_t i) const noexcept {
				return __iterator(owner, pos + i);
			}

			FORCEINLINE friend __iterator operator+(size_t offset, __iterator const& i) noexcept {
				return __iterator(i.owner, i.pos + offset);
			}

			FORCEINLINE __iterator operator-(size_t i) const noexcept {
				return __iterator(owner, pos - i);
			}

			FORCEINLINE __iterator& operator+=(size_t i) noexcept {
				pos += i;
				return *this;
			}

			FORCEINLINE __iterator& operator-=(size_t i) noexcept {
				pos -= i;
				return *this;
			}

			FORCEINLINE int operator-(__iterator const& other) const noexcept {
				return (int)pos - (int)other.pos;
			}

			FORCEINLINE _Ref operator*() const {
				//if constexpr (_deref)
				//	return (_Ref)(*owner.data_[pos]);
				//else
				return (_Ref)owner.data_[pos];
			}

			FORCEINLINE _Ref operator[](size_t i) const {
				//if constexpr (_deref)
				//	return (_Ref)(*owner.data_[pos + i]);
				//else
				return (_Ref)owner.data_[pos + i];
			}

			FORCEINLINE _Ref operator[](int i) const {
				//if constexpr (_deref)
				//	return (_Ref)(*owner.data_[pos + i]);
				//else
				return (_Ref)owner.data_[pos + i];
			}

			FORCEINLINE bool operator==(const __iterator& other) const noexcept {
				return pos == other.pos;
			}

			FORCEINLINE bool operator!=(const __iterator& other) const noexcept {
				return pos != other.pos;
			}

			FORCEINLINE bool operator<(const __iterator& other) const noexcept {
				return pos < other.pos;
			}

			FORCEINLINE bool operator>(const __iterator& other) const noexcept {
				return pos > other.pos;
			}

			FORCEINLINE bool operator<=(const __iterator& other) const noexcept {
				return pos <= other.pos;
			}

			FORCEINLINE bool operator>=(const __iterator& other) const noexcept {
				return pos >= other.pos;
			}

			FORCEINLINE __iterator& operator=(const __iterator& other) noexcept {
				_trivcopy(this, &other);
				return *this;
			}

			FORCEINLINE __iterator& operator=(__iterator&& other) noexcept {
				_trivcopy(this, &other);
				return *this;
			}

			FORCEINLINE __iterator& operator=(size_t pos) noexcept {
				this->pos = pos;
				return *this;
			}

			FORCEINLINE explicit operator bool() const noexcept {
				return pos < owner.size_;
			}

			FORCEINLINE bool operator !() const noexcept {
				return pos >= owner.size_;
			}

			FORCEINLINE auto operator->() const {
				if constexpr (std::is_pointer_v<_Value>)
					return owner.data_[pos];
				else
					return owner.data_ + pos;
			}

			FORCEINLINE __iterator operator~() const noexcept {
				return __iterator(owner, owner.size_ - 1 - pos);
			}

			template<class _Member, class _T>
			FORCEINLINE auto operator->*(_Member(_T::*member)) {
				if constexpr (std::is_pointer_v<_Value>) {
					return (*static_cast<_Ptr>(owner.data_ + pos))->*member;
				} else {
					return (static_cast<_Ptr>(owner.data_ + pos))->*member;
				}
			}


			template<class _Member, class _T, class... _Arg>
			FORCEINLINE auto operator->*(_Member(_T::*member)(_Arg...)) {
				if constexpr (std::is_pointer_v<_Value>) {
					return [=](_Arg... args) {
						return ((*static_cast<_Ptr>(owner.data_ + pos))->*member)((_Arg)args...);
					};
				} else {
					return [=](_Arg... args) {
						return ((static_cast<_Ptr>(owner.data_ + pos))->*member)((_Arg)args...);
					};
				}
			}

			FORCEINLINE _Ptr ptr() const noexcept {
				return owner.data_ + pos;
			}

			FORCEINLINE void reset() noexcept {
				pos = 0;
			}

			INLINE void swap(__iterator& other) noexcept {
				x::swap(*this, other);
			}

			FORCEINLINE _Value&& move() const {
				static_assert(!std::is_const_v<_Value>);
				return (_Value&&)owner.data_[pos];
			}

			INLINE void erase() {
				owner.erase(pos);
			}

			INLINE void erase(size_t n) {
				owner.erase(pos, pos + n - 1);
			}

			INLINE void insert(_Value const& value) {
				owner.insert(value, pos);
			}

			INLINE void insert(_Value&& value) {
				owner.insert((_Value&&)value, pos);
			}

			INLINE void dump() {
				owner.dump(pos);
			}
		};

	#elif MODE(IteratorMode, Pointer)

		template<int _step, class _Value, class _Ref, class _Ptr, class _Owner, bool _deref = false>
		struct __iterator
		{
			template<class>
			friend class _vector;

			template<class>
			friend class _refvector;

			using difference_type = ptrdiff_t;
			using value_type = _Value;
			using reference = _Ref;
			using pointer = _Ptr;
			using iterator_category = std::bidirectional_iterator_tag;

			_Owner& owner;
			_Ptr ptr;


			__iterator(_Owner& owner) noexcept:
				owner{owner},
				ptr{owner.data_} {
			}

			__iterator(_Owner& owner, size_t pos) noexcept:
				owner{owner},
				ptr{owner.data_ + pos} {
			}

			__iterator(const __iterator& other) noexcept:
				owner{other.owner},
				ptr{other.ptr} {
			}

			__iterator(__iterator&& other) noexcept:
				owner{other.owner},
				ptr{other.ptr} {
			}

			FORCEINLINE __iterator& operator++() noexcept {
				ptr += _step;
				return *this;
			}


			FORCEINLINE __iterator& operator--() noexcept {
				ptr -= _step;
				return *this;
			}


			INLINE __iterator operator++(int) noexcept {
				__iterator copy{*this};
				ptr += _step;
				return copy;
			}

			INLINE __iterator operator--(int) noexcept {
				__iterator copy{*this};
				ptr -= _step;
				return copy;
			}

			FORCEINLINE __iterator operator+(int i) noexcept {
				return __iterator(owner, ptr + i);
			}

			FORCEINLINE __iterator operator-(int i) noexcept {
				return __iterator(owner, ptr - i);
			}

			FORCEINLINE __iterator& operator+=(int i) noexcept {
				ptr += i;
				return *this;
			}

			FORCEINLINE __iterator& operator-=(int i) noexcept {
				ptr -= i;
				return *this;
			}

			FORCEINLINE __iterator operator+(size_t i) noexcept {
				return __iterator(owner, ptr + i);
			}

			FORCEINLINE __iterator operator-(size_t i) noexcept {
				return __iterator(owner, ptr - i);
			}

			FORCEINLINE __iterator& operator+=(size_t i) noexcept {
				ptr += i; return *this;
			}

			FORCEINLINE __iterator& operator-=(size_t i) noexcept {
				ptr -= i; return *this;
			}

			FORCEINLINE _Ref operator*() const {
				if constexpr (_deref)
					return (_Ref)(**ptr);
				else
					return (_Ref)(*ptr);
			}

			FORCEINLINE bool operator==(const __iterator& other) const noexcept {
				return ptr == other.ptr;
			}

			FORCEINLINE bool operator!=(const __iterator& other) const noexcept {
				return ptr != other.ptr;
			}

			FORCEINLINE bool operator<(const __iterator& other) const noexcept {
				return ptr < other.ptr;
			}

			FORCEINLINE bool operator>(const __iterator& other) const noexcept {
				return ptr > other.ptr;
			}

			FORCEINLINE bool operator<=(const __iterator& other) const noexcept {
				return ptr <= other.ptr;
			}

			FORCEINLINE bool operator>=(const __iterator& other) const noexcept {
				return ptr >= other.ptr;
			}

			FORCEINLINE __iterator& operator=(const __iterator& other) noexcept {
				_trivcopy(this, &other);
				return *this;
			}

			FORCEINLINE __iterator& operator=(__iterator&& other) noexcept {
				_trivcopy(this, &other);
				return *this;
			}

			/*FORCEINLINE __iterator& operator=(size_t ptr) noexcept {
			this->ptr = ptr;
			return *this;
			}*/

			FORCEINLINE explicit operator bool() const noexcept {
				return ptr < owner.pcend();
			}

			FORCEINLINE bool operator !() const noexcept {
				return ptr >= owner.pcend();
			}

			FORCEINLINE auto operator->() const {
				return ptr;
			}

			/*template<class _MPtr>
			FORCEINLINE auto operator->*(_MPtr mptr) {
				return [=](auto&&... args) {
					return ((_Ptr)x::ptr(ptr)->*mptr)(std::forward<decltype(args)>(args)...);
				};
			}*/

			/*FORCEINLINE _Ptr ptr() const noexcept {
			return ptr;
			}*/

			FORCEINLINE void reset() noexcept {
				ptr = owner.data_;
			}

			INLINE void swap(__iterator& other) noexcept {
				x::swap(*this, other);
			}

			FORCEINLINE _Value&& move() const {
				static_assert(!std::is_const_v<_Value>);
				return (_Value&&)(*ptr);
			}

			/*INLINE void erase() {
			owner.erase(ptr);
			}

			INLINE void erase(size_t n) {
			owner.erase(ptr, ptr + n - 1);
			}

			INLINE void insert(_Value const& value) {
			owner.insert(value, ptr);
			}

			INLINE void insert(_Value&& value) {
			owner.insert((_Type&&)value, ptr);
			}*/
		};
	#endif
#endif
	template<class _Type>
	class _vector
	{
	protected:
		template<int, class, class, class, class, bool>
		friend class __iterator;

		template<class _Type>
		friend class _vector_backwards;

		template<class _T>
		struct _CountDim {
			static constexpr size_t value = 0;
		};

		template<class _T>
		struct _CountDim<_vector<_T>> {
			static constexpr size_t value = 1 + _CountDim<_T>::value;
		};

		///////////////////////////////////////////////////////////////////////////////

		template<class _Type>
		struct _AtomicType
		{
			using type = _Type;
		};

		template<class _Type>
		struct _AtomicType<_vector<_Type>>
		{
			using type = typename _AtomicType<_Type>::type;
		};

		template<class _Type>
		using atomic_t = typename _AtomicType<_Type>::type;

		///////////////////////////////////////////////////////////////////////////////

		static constexpr bool IS_POINTER_ = std::is_pointer<_Type>::value;
		static constexpr bool IS_POD_ = std::is_pod<_Type>::value;
		static constexpr bool IS_POD_BYTE_ = IS_POD_ && sizeof(_Type) == 1;
		static constexpr bool IS_SMALL_ = sizeof(_Type) <= 4;
		static constexpr bool IS_SMALL_POD_ = IS_POD_ && IS_SMALL_;

		using _TypeConst = std::conditional_t<IS_SMALL_POD_, _Type, _Type const&>;

		///////////////////////////////////////////////////////////////////////////////

		static constexpr size_t DIM_ = _CountDim<_vector<_Type>>::value;
		static constexpr size_t ELEMENT_SIZE_ = sizeof(_Type);
		static constexpr size_t DEFAULT_ALLOC_ = 10;
		static constexpr size_t MIN_ALLOC_ = 1;
		static constexpr size_t EXTEND_MULTIPLIER_ = 2;
		static constexpr size_t MAX_SIZE = std::numeric_limits<size_t>::max();

		///////////////////////////////////////////////////////////////////////////////

	//XVECTOR_FIELD_ACCESS:
	protected:
		size_t reserved_;
		size_t size_;
		_Type* data_;

	#if XVECTOR_LOCK_ENABLED
		_MUTEX_TYPE _MUTEX_NAME;
	#endif

	private:
		///////////////////////////////////////////////////////////////////////////////////////////////

		FORCEINLINE void __declspec(SPEC)reallocate_(size_t newsize) {
			if constexpr (XVECTOR_USE_REALLOC)
				data_ = reinterpret_cast<_Type*>(::realloc(data_, newsize * sizeof(_Type)));
			else {
				_Type* newdata = reinterpret_cast<_Type*>(::malloc(newsize * sizeof(_Type)));
				::memcpy(newdata, data_, size_ * sizeof(_Type));
				::free(data_);
				data_ = newdata;
			}
			reserved_ = newsize;
		}

		FORCEINLINE void __declspec(SPEC) dump_reallocate_(size_t newsize) {
			::free(data_);
			if constexpr (XVECTOR_USE_CALLOC) {
				data_ = reinterpret_cast<_Type*>(::calloc(newsize, sizeof(_Type)));
			} else {
				data_ = reinterpret_cast<_Type*>(::malloc(newsize * sizeof(_Type)));
			}
			reserved_ = newsize;
		}

		FORCEINLINE static __declspec(SPEC) _Type* allocate_(size_t size) {
			if constexpr (XVECTOR_USE_CALLOC) {
				return reinterpret_cast<_Type*>(::calloc(size, sizeof(_Type)));
			} else {
				return reinterpret_cast<_Type*>(::malloc(size * sizeof(_Type)));
			}
		}

		FORCEINLINE static __declspec(SPEC) _Type* zero_allocate_(size_t size) {
			return reinterpret_cast<_Type*>(::calloc(size, sizeof(_Type)));
		}

		FORCEINLINE void __declspec(SPEC) deallocate_() {
			::free(data_);
		}

		FORCEINLINE static __declspec(SPEC) void deallocate_(void* data) {
			::free(data);
		}


		INLINE void __declspec(SPEC) destruct_all_() {
			if constexpr (!std::is_trivially_destructible_v<_Type>) {
				_foreach(e)
					_destruct(e);
			}
		}

		INLINE void __declspec(SPEC) destruct_from_(_Type* begin) {
			if constexpr (!std::is_trivially_destructible_v<_Type>) {
				_foreach_from(e, begin)
					_destruct(e);
			}
		}

		/*INLINE void destruct_from_(_Type* begin, size_t size) {
		if constexpr (!std::is_trivially_destructible_v<_Type>)
		_for_range(e, begin, begin + size)
		_destruct(e);
		}*/

		INLINE void __declspec(SPEC) destruct_range_(_Type* begin, _Type* end) {
			if constexpr (!std::is_trivially_destructible_v<_Type>) {
				_for_range(e, begin, end)
					_destruct(e);
			}
		}


		INLINE static void copy_(_Type* dest, _Type const* src, size_t size) {
			if constexpr (std::is_trivially_copy_constructible_v<_Type>)
				::memcpy(dest, src, size * sizeof(_Type));
			else {
				for (_Type* end = dest + size; dest < end; ++dest, ++src)
					_construct(dest, *src);
			}
		}


		INLINE static void move_(_Type* dest, _Type* src, size_t size) {
			if constexpr (std::is_trivially_move_constructible_v<_Type>)
				::memcpy(dest, src, size * sizeof(_Type));
			else {
				for (_Type* end = dest + size; dest < end; ++dest, ++src)
					_construct(dest, (_Type&&)*src);
			}
		}


		template<class _Elem>
		INLINE static __declspec(SPEC) void copy_initializer_list_(_Type* dest, _Elem const* ilsrc, _Elem const* ilend) {
			if constexpr (std::is_same_v<_Type, _Elem> && std::is_trivially_move_constructible_v<_Type>) {
				::memcpy(dest, ilsrc, (ilend - ilsrc) * sizeof(_Type));
			} else if constexpr (XVECTOR_MOVE_FROM_INITIALIZER_LIST) {
				for (; ilsrc < ilend; ++dest, ++ilsrc)
					_construct(dest, const_cast<_Elem&&> (*ilsrc));
			} else {
				for (; ilsrc < ilend; ++dest, ++ilsrc)
					_construct(dest, *ilsrc);
			}
		}


		static FORCEINLINE constexpr size_t extended_capacity_(size_t capacity) noexcept {
			return capacity * EXTEND_MULTIPLIER_ + _DEFAULT_MIN_SIZE;
		}

		////////////////////////////////////////////////////////////////////////////

	public:
		template<class>
		friend class _vector;

		////////////////////////////////////////////////////////////////////////////

		using element_type = _Type;
		using atomic_type = typename _AtomicType<_Type>::type;
		using this_type = _vector<_Type>;

		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = _Type;
		using pointer = _Type * ;
		using reference = _Type & ;

		////////////////////////////////////////////////////////////////////////////

	#if XVECTOR_ENABLE_ITERATORS
	protected:
		template<int _step>
		using _iterator = __iterator<_step, _Type, _Type&, _Type*, _vector<_Type>>;

		template<int _step>
		using _const_iterator = __iterator<_step, _Type const, _Type const&, _Type const*, _vector<_Type> const>;

		template<int _step>
		using _move_iterator = __iterator<_step, _Type, _Type&&, _Type*, _vector<_Type>>;
	
	public:	
		using iterator = _iterator<1>;
		using reverse_iterator = _iterator<-1>;
		using const_iterator = _const_iterator<1>;
		using reverse_const_iterator = _const_iterator<-1>;
		using move_iterator = _move_iterator<1>;
		using reverse_move_iterator = _move_iterator<-1>;
	
		////////////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Gets iterator pointing to the first element.
		/// </summary>
		/// <returns>iterator with position 0</returns>
		template<int _step = 1>
		FORCEINLINE _iterator<_step> begin() & noexcept {
			return _iterator<_step>(*this, 0);
		}


		/// <summary>
		/// Gets const iterator to the first element when called on vector const reference.
		/// </summary>
		/// <returns>const iterator with position 0</returns>
		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> begin() const & {
			return _const_iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> begin() && noexcept {
			return _move_iterator<_step>(*this, 0);
		}


		/// <summary>
		/// Gets iterator pointing to the element 1 place beyond the last.
		/// </summary>
		/// <returns>iterator with position equal to size</returns>
		template<int _step = 1>
		FORCEINLINE _iterator<_step> end() & noexcept {
			return  _iterator<_step>(*this, size_);
		}


		/// <summary>
		/// Gets const iterator pointing to the element 1 place beyond the last 
		/// when called on vector const reference.
		/// </summary>
		/// <returns>const iterator with position equal to size</returns>
		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> end() const & noexcept {
			return  _const_iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> end() && noexcept {
			return  _move_iterator<_step>(*this, size_);
		}


		/// <summary>
		/// Gets const_iterator pointing to the first element.
		/// </summary>
		/// <returns>iterator with position 0</returns>
		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cbegin() const noexcept {
			return  _const_iterator<_step>(*this, 0);
		}


		/// <summary>
		/// Gets const_iterator pointing to the element 1 place beyond the last.
		/// </summary>
		/// <returns>iterator with position equal to size</returns>
		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cend() const noexcept {
			return  _const_iterator<_step>(*this, size_);
		}


		/// <summary>
		/// Gets const_iterator pointing to the first element.
		/// </summary>
		/// <returns>iterator with position 0</returns>
		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mbegin() noexcept {
			return _move_iterator<_step>(*this, 0);
		}


		/// <summary>
		/// Gets const_iterator pointing to the element 1 place beyond the last.
		/// </summary>
		/// <returns>iterator with position equal to size</returns>
		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mend() {
			return _move_iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _iterator<_step> iter(size_t i = 0) & noexcept {
			return _iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> iter(size_t i = 0) const & noexcept {
			return _const_iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> iter(size_t i = 0) && noexcept {
			return _move_iterator<_step>(*this, i);
		}

	#else
	public:
		using iterator = _Type * ;
		using const_iterator = _Type const*;
		using move_iterator = _Type * ;


		FORCEINLINE _Type* begin() & noexcept {
			return data_;
		}


		FORCEINLINE _Type const* begin() const {
			return _const_iterator<_step>(*this, 0);
		}


		FORCEINLINE _Type* end() & noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type const* end() const & noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type const* cbegin() const noexcept {
			return data_;
		}


		FORCEINLINE _Type const* cend() const noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type* mbegin() noexcept {
			return data_;
		}


		FORCEINLINE _Type* mend() {
			return data_ + size_;
		}


		FORCEINLINE _iterator<_step> iter(size_t i = 0) & noexcept {
			return _iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> iter(size_t i = 0) const & noexcept {
			return _const_iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> iter(size_t i = 0) && noexcept {
			return _move_iterator<_step>(*this, i);
		}

	#endif		

		/// <summary>
		/// Gets pointer to the element 1 place beyond the last.
		/// </summary>
		/// <returns>Pointer equal to data + size</returns>
		FORCEINLINE _Type* pbegin() noexcept {
			return data_;
		}


		FORCEINLINE _Type const* pcbegin() const noexcept {
			return data_;
		}


		FORCEINLINE _Type const* pbegin() const noexcept {
			return data_;
		}


		FORCEINLINE _Type* pend() noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type const* pcend() const noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type const* pend() const noexcept {
			return data_ + size_;
		}


		FORCEINLINE _Type* pback() noexcept {
			return data_ + size_ - 1;
		}


		FORCEINLINE _Type const* pcback() const noexcept {
			return data_ + size_ - 1;
		}


		FORCEINLINE _Type const* pback() const noexcept {
			return data_ + size_ - 1;
		}

		
		FORCEINLINE _Type* ppenult() noexcept {
			return data_ + size_ - 2;
		}


		FORCEINLINE _Type const* pcpenult() const noexcept {
			return data_ + size_ - 2;
		}


		FORCEINLINE _Type const* ppenult() const noexcept {
			return data_ + size_ - 2;
		}


		FORCEINLINE _Type* psecond() noexcept {
			return data_ + 1;
		}


		FORCEINLINE _Type const* pcsecond() const noexcept {
			return data_ + 1;
		}


		FORCEINLINE _Type const* psecond() const noexcept {
			return data_ + 1;
		}


		FORCEINLINE _vector_backwards<_Type>& backwards() & noexcept {
			return reinterpret_cast<_vector_backwards<_Type>&>(*this);
		}


		FORCEINLINE _vector_backwards<_Type> const& backwards() const & noexcept {
			return reinterpret_cast<_vector_backwards<_Type> const&>(*this);
		}


		FORCEINLINE _vector_backwards<_Type>&& backwards() && noexcept {
			return reinterpret_cast<_vector_backwards<_Type>&&>(*this);
		}


		////////////////////////////////////////////////////////////////////////////

	public:
		/// <summary>
		/// Constructs an empty vector.
		/// </summary>
		/// <remarks>
		/// The capacity of allocated memory is set to default allocation size which can be set using function
		/// set_default_alloc or viewed by calling default_alloc(). The size is set to 0, so no elements 
		/// are accessible.
		/// </remarks>
		constexpr _vector() noexcept:
			reserved_(0),
			size_(0),
			data_(nullptr) {
		}


		/// <summary>
		/// Constructs an empty vector allocating memory of given capacity.
		/// </summary>
		/// <remarks>
		/// If \a size argument was 0, memory of size 1 is automatically allocated. The size is set to 0, 
		/// so no elements are accessible.
		/// </remarks>
		/// <param name="capacity">the capacity of allocated memory</param>
		explicit _vector(size_t capacity) {
			reserved_ = capacity;
			size_ = 0;
			if (reserved_ > 0)
				data_ = allocate_(reserved_);
			else
				data_ = nullptr;
		}


		explicit _vector(size_t capacity, size_t size) {
			reserved_ = capacity;
			if (reserved_ > 0) {
				if (size > capacity)
					size_ = capacity;
				else
					size_ = size;
				data_ = allocate_(reserved_);
			} else {
				size_ = 0;
				data_ = nullptr;
			}
		}


		/*_vector(_Type const& elem, size_t size) {
		reserved_ = size;
		size_ = 0;
		if (reserved_ > 0) {
		data_ = allocate_(reserved_);
		initialize(elem);
		}
		else
		data_ = nullptr;
		}


		_vector(_Type const& elem, size_t size, size_t capacity) {
		reserved_ = capacity;
		size_ = 0;
		if (reserved_ > 0) {
		data_ = allocate_(reserved_);
		initialize(elem, size);
		}
		else
		data_ = nullptr;

		#if _DEBUG_CTOR == 1
		std::cout << "req size fill ctor\n";
		#endif
		}*/


		/// <summary>
		/// Constructs a vector copying elements from given array_data of known size. 
		/// </summary>
		/// <remarks>
		/// Memory of capacity equal to given \a size is allocated. 
		/// This constructor assumes that the size of memory block is known and does not
		/// provide any security in case of invalid value or inaccessibility of the memory.
		/// If the \a arr pointer is nullptr or size = 0, memory of default size is allocated. 
		/// </remarks>
		/// <param name="arr">array_data to copy from</param>
		/// <param name="size">the size of array</param>
		explicit _vector(_Type const* arr, size_t size) {
			if (arr == nullptr) {
				reserved_ = 0;
				size_ = 0;
				data_ = nullptr;
			} else {
				reserved_ = size;
				size_ = size;
				data_ = allocate_(reserved_);
				copy_(data_, arr, size_);
			}
		}


		explicit _vector(std::nullptr_t data, size_t size) {
			reserved_ = 0;
			size_ = 0;
			data_ = nullptr;
		}


		/// <summary>
		/// Constructs a vector copying elements from given static array_data of known size. 
		/// </summary>
		/// <remarks>
		/// This operation is safer than constructing a vector from dynamic array_data. 
		/// Memory of capacity equal to \a _size is allocated.
		/// </remarks>
		/// <param name="_size">deduced size of static array_data</param>
		/// <param name="arr">array_data to copy from</param>
		template<size_t _size>
		_vector(const _Type(&arr)[_size]) {
			reserved_ = _size;
			size_ = _size;
			data_ = allocate_(_size);
			copy_(data_, arr, _size);
		}


		template<size_t _size>
		_vector(_Type(&&arr)[_size]) {
			reserved_ = _size;
			size_ = _size;
			data_ = allocate_(_size);
			move_(data_, arr, _size);
		}


		/// <summary>
		/// Constructs a vector initializing explicitly given elements from initializer_list.
		/// </summary>
		/// <remarks>
		/// All elements fro the list are accessible after the constructor. If the list was empty, memory
		/// of default size is allocated.
		/// </remarks>
		/// <param name="list"></param>
		template<class _Elem>
		_vector(std::initializer_list<_Elem> elements) {
			reserved_ = elements.size();
			if (reserved_ > 0) {
				size_ = reserved_;
				data_ = allocate_(reserved_);
				copy_initializer_list_(data_, elements.begin(), elements.end());
			} else {
				size_ = 0;
				data_ = nullptr;
			}
		}

		//necessary when passing {...} to intializer list
		_vector(std::initializer_list<_Type> elements) {
			reserved_ = elements.size();
			if (reserved_ > 0) {
				size_ = reserved_;
				data_ = allocate_(reserved_);
				copy_initializer_list_(data_, elements.begin(), elements.end());
			} else {
				size_ = 0;
				data_ = nullptr;
			}
		}


		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <remarks>
		/// Copies data of the argument vector to the constructed one.
		/// If the argument vector is empty, memory of default capacity is allocated.
		/// </remarks>
		/// <param name="other">vector to be copied from</param>
		_vector(_vector<_Type> const& other) {
			if (other.size_ > 0) {
				reserved_ = other.size_;
				size_ = reserved_;
				data_ = allocate_(reserved_);
				copy_(data_, other.data_, size_);
			} else {
				reserved_ = 0;
				size_ = 0;
				data_ = nullptr;
			}
		}


		_vector(_refvector<_Type> const& other) {
			reserved_ = other.size_;
			if (reserved_ > 0) {
				size_ = reserved_;
				data_ = allocate_(reserved_);
				_Type* dest = data_;
				_Type* end = data_ + size_;
				_Type const** src = other.data_;
				for (; dest < end; ++dest, ++src) 
					_construct(dest, **src);
			} else {
				size_ = 0;
				data_ = nullptr;
			}
		}

		//? pointless / invalid ?
		/*_vector(_refvector<_Type> && other) {
		reserved_ = other.size_;
		if (reserved_ > 0) {
		size_ = reserved_;
		data_ = allocate_(reserved_);
		_Type* dest = data_;
		_Type* end = data_ + size_;
		_Type const** src = other.data_;
		for (; dest < end; ++dest, ++src) {
		if constexpr (std::is_trivially_move_constructible_v<_Type> &&
		std::is_trivially_move_assignable_v<_Type>)
		*dest = (_Type&&)(**src);
		else
		new (dest) _Type((_Type&&)(**src));
		}
		}
		else {
		size_ = 0;
		data_ = nullptr;
		}
		}*/



		/*template<class _Other, class _Func>
		_vector(std::initializer_list<_Other> other, _Func&& func):
		reserved_(other.size()),
		size_(reserved_),
		data_(allocate_(reserved_))
		{
		_Other const* begin = other.begin();
		for (size_t i = 0; i < size_; ++i)
		data_[i] = func(begin[i]);
		}*/


		explicit _vector(_vector<_Type> const& other, size_t capacity) {
			if (other.size_ > 0) {
				reserved_ = x::max(other.reserved_, capacity);
				size_ = other.size_;
				data_ = allocate_(reserved_);
				copy_(data_, other.data_, size_);
			} else {
				reserved_ = capacity;
				size_ = 0;
				data_ = allocate_(reserved_);
			}
		}


		explicit _vector(_vector<_Type> && other, size_t capacity) {
			size_ = other.size_;
			data_ = other.data_;
			other.data_ = nullptr;
			if (other.reserved_ < capacity)
				reallocate_(capacity);
			else
				reserved_ = other.reserved_;
		}


		/*template<class _Other, class _Func>
		explicit _vector(_vector<_Other> const& other, _Func&& func) {
			reserved_ = other.size_;
			if (reserved_ > 0) {
				size_ = reserved_;
				data_ = allocate_(reserved_);
				_pair_foreach(*this, dest, other, src) {
					if constexpr (std::is_trivially_destructible_v<_Type> && std::is_trivially_move_constructible_v<_Type>)
						_trivcopy(dest, &func((_Other&&)*src));
					else
						new (dest) _Type(func((_Other&&)*src));
				}
			} else {
				size_ = 0;
				data_ = nullptr;
			}
		}


		template<class _Other, class _Func>
		explicit _vector(_vector<_Other> && other, _Func&& func) {
			if constexpr (std::is_same_v<_Other, _Type>) {
				reserved_ = other.reserved_;
				size_ = other.size_;
				data_ = other.data_;
				other.data_ = nullptr;
				_foreach(e) {
					if constexpr (std::is_trivially_destructible_v<_Type> && std::is_trivially_move_constructible_v<_Type>)
						_trivcopy(e, &func((_Other&&)*e));
					else
						new (e) _Type(func((_Other&&)*e));
				}
			} else {
				reserved_ = other.size_;
				if (reserved_ > 0) {
					size_ = reserved_;
					data_ = allocate_(reserved_);
					_pair_foreach(*this, dest, other, src) {
						if constexpr (std::is_trivially_destructible_v<_Type> &&
							std::is_trivially_move_constructible_v<_Type>)
							_trivcopy(dest, &func((_Other&&)*src));
						else
							new (dest) _Type(func((_Other&&)*src));
					}
				} else {
					size_ = 0;
					data_ = nullptr;
				}
			}
		}*/

		////? begin, size ?
		//explicit _vector(_vector<_Type> const& other, size_t begin, size_t end) {
		//	if (begin <= end) {
		//		if (end < other.size_) {
		//			reserved_ = end - begin + 1;
		//			size_ = reserved_;
		//			data_ = allocate_(reserved_);
		//			copy_(data_, other.data_ + begin, size_);
		//		} else if (begin < other.size_) {
		//			reserved_ = other.size_ - begin;
		//			size_ = reserved_;
		//			data_ = allocate_(reserved_);
		//			copy_(data_, other.data_ + begin, size_);
		//		} else {
		//			reserved_ = 0;
		//			size_ = 0;
		//			data_ = nullptr;
		//		}
		//	} else {
		//		reserved_ = 0;
		//		size_ = 0;
		//		data_ = nullptr;
		//	}
		//}


		////? begin, size ?
		//explicit _vector(_vector<_Type>&& other, size_t begin, size_t end) {
		//	reserved_ = other.reserved_;
		//	data_ = other.data_;
		//	other.data_ = nullptr;
		//	if (begin <= end) {
		//		if (end < other.size_) {
		//			size_ = end - begin + 1;
		//			_destruct_range(data_ + end + 1, data_ + other.size_);
		//			if (begin != 0) {
		//				_destruct_range(data_, data_ + begin);
		//				::memcpy(data_, data_ + begin, size_ * sizeof(_Type));
		//			}
		//		} else if (begin < other.size_) {
		//			size_ = other.size_ - begin;
		//			data_ = other.data_;
		//			if (begin != 0) {
		//				_destruct_range(data_, data_ + begin);
		//				::memcpy(data_, data_ + begin, size_ * sizeof(_Type));
		//			}
		//		} else
		//			size_ = 0;
		//	} else
		//		size_ = 0;
		//}


		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <remarks>
		/// Fields are initialized to the other vector's values. The argument vector is made
		/// permanently unusable. This constructor does not copy any element, just sets the handled data
		/// and parameters. It will be called if <code>move()</code> method is called on vector passed
		/// as argument or a rvalue reference was passed to the constructor. Also due to what standard says
		/// this constructor will be used when vector is returned from function so one should not bother
		/// about unnecessary copying of returned data because it will not happen.
		/// </remarks>
		/// <param name="other">the vector to be moved</param>
		_vector(_vector<_Type>&& other) noexcept {
			reserved_ = other.reserved_;
			size_ = other.size_;
			data_ = other.data_;
			other.data_ = nullptr;
			if constexpr (XVECTOR_ZERO_SIZE_ON_MOVE) {
				other.reserved_ = 0;
				other.size_ = 0;
			}
		}


		_vector(_vector<_Type> const&& other) = delete;


		/// <summary>
		/// Constructs a vector copying data from an instance of std::vector.
		/// </summary>
		/// <remarks>
		/// Constructed vector will contain non-trivial copy of all elements from the other.
		/// If the argument vector is empty, memory of default size is allocated.
		/// </remarks>
		/// <param name="vec">the std::vector to copy data from</param>
		template<class _Alloc>
		_vector(std::vector<_Type, _Alloc> const& vec) {
			reserved_ = vec.size();
			size_ = reserved_;
			data_ = allocate_(reserved_);		
			copy_(data_, vec.data(), size_);
		}


	#if _MOVE_STD_VECTOR
		template<class _Alloc>
		_vector(std::vector<_Type, _Alloc>&& vec) {
			using StdAllocTypes = std::_Vector_alloc<std::_Vec_base_types<int, std::allocator<int>>>;
			using StdVectorData = std::_Compressed_pair<typename StdAllocTypes::_Alty, std::_Vector_val<typename StdAllocTypes::_Val_types>>;
			uint8_t vecdata[sizeof(std::vector<_Type, _Alloc>)];
			new (vecdata) std::vector<_Type, _Alloc>((std::vector<_Type, _Alloc>&&)vec);
			auto& pval = reinterpret_cast<StdVectorData*>(vecdata)->_Get_second();
			data_ = pval._Myfirst;
			reserved_ = pval._Myend - data_;
			size_ = pval._Mylast - data_;
		}
	#endif

		INLINE explicit  _vector(const_iterator const& begin, const_iterator const& end):
			_vector(begin.owner, begin.pos, end.pos) {
		}

		INLINE explicit _vector(const_iterator const& begin, size_t size):
			_vector(begin.owner, begin.pos, begin.pos + size - 1) {
		}

		explicit _vector(move_iterator const& begin, move_iterator const& end) {
			if (begin < end && end.pos <= end.owner.size_) {
				reserved_ = end.pos - begin.pos;
				size_ = reserved_;
				data_ = allocate_(reserved_);
				move_(data_, begin.ptr(), size_);
			} else {
				reserved_ = 0;
				size_ = 0;
				data_ = nullptr;
			}
		}

		explicit _vector(move_iterator const& begin, size_t size) {
			if (begin && size > 0) {
				reserved_ = size;
				size_ = reserved_;
				data_ = allocate_(reserved_);
				move_(data_, begin.ptr(), size_);
			} else {
				reserved_ = 0;
				size_ = 0;
				data_ = nullptr;
			}
		}

		explicit _vector(_Type const* begin, _Type const* end) {
			if (begin < end && begin != nullptr) {
				reserved_ = end - begin;
				size_ = reserved_;
				data_ = allocate_(reserved_);
				copy_(data_, begin, size_);
			} else {
				reserved_ = 0;
				size_ = 0;
				data_ = nullptr;
			}
		}


		///////////////////////////////////////////////////////////////////////////////////////////////

	#if XVECTOR_LOCK_ENABLED
		FORCEINLINE void __declspec(SPEC)lock() {
			lock_.lock();
		}

		FORCEINLINE bool __declspec(SPEC)try_lock() {
			return lock_.try_lock();
		}

		FORCEINLINE void __declspec(SPEC)unlock() {
			lock_.unlock();
		}

		FORCEINLINE bool __declspec(SPEC)is_locked() const {
			return lock_.is_locked();
		}
	#endif

		///////////////////////////////////////////////////////////////////////////////////////////////


		/// <summary>
		/// Returns number representing nesting of vector which is grater by 1 if the type parameter is
		/// also a vector. E.g. <code> vector&ltvector&ltvector&ltint&gt&gt&gt </code> will be of dimension 3.
		/// </summary>
		/// <returns>The number of dimensions</returns>
		static constexpr size_t dim() noexcept {
			return DIM_;
		}


		/// <summary>
		/// Returns pointer to currently allocated and handled data. It should not be used 
		/// to modify the vector's data in any way, only for iteration or informational purposes.
		/// One must be aware that the pointer may be invalid after some modifications of the vector
		/// due to memory reallocation.
		/// </summary>
		/// <returns>the pointer to allocated data</returns>
		FORCEINLINE _Type const* data() const noexcept {
			return data_;
		}


		FORCEINLINE _Type* mutable_data() noexcept {
			return data_;
		}


		static constexpr size_t max_size() noexcept {
			return std::numeric_limits<size_t>::max();
		}


		_Type* extract_data() noexcept {
			_Type* prev = data_;
			reserved_ = 0;
			data_ = nullptr;
			size_ = 0;
			return prev;
		}


		/// <summary>
		/// Gets pointer to so far and handled data and allocates new memory of the previous size.
		/// The resulting pointer can be safely used for any modifications and will no longer be
		/// used by the caller vector.
		/// </summary>
		/// <returns>the pointer to previous data</returns>
		_Type* extract_data(size_t newSize) & {
			_Type* prev = data_;
			reserved_ = newSize;
			if (newSize > 0)
				data_ = allocate_(newSize);
			else
				data_ = nullptr;
			size_ = 0;
			return prev;
		}


		FORCEINLINE _Type* extract_data(size_t newSize) && {
			return extract_data();
		}


		/// <summary>
		/// Forgets the currently handled data setting it to nullptr and making the vector unusable.
		/// </summary>
		/// <returns>
		/// This function can be used when a vector was used to handle adopted data. At the end of life of 
		/// vector the data can be discarded and then the destructor will not try to deallocate the data, 
		/// which would cause a runtime error if it was deallocated externally. 
		/// </returns>
		void discard_data() noexcept {
			data_ = nullptr;
			size_ = 0;
			reserved_ = 0;
		}

		void dealloc() {
			_destruct_all();
			deallocate_();
		}

	/*protected:
		FORCEINLINE void dealloc_moved_() {
			::free(data_);
			data_ = nullptr;
		}*/

	public:
		/*FORCEINLINE _vector<_Type>& forward() & {
		return *this;
		}

		FORCEINLINE _vector<_Type> const& forward() const & {
		return *this;
		}

		FORCEINLINE _vector<_Type>&& forward() && noexcept {
		return _rvthis;
		}*/

		/// <summary>
		/// Deallocates current memory and sets the given pointer as its data. 
		/// The pointer passed as argument should not be used later outside the caller vector.
		/// </summary>
		/// <param name="data">the new memory block to handle</param>
		/// <param name="size">the size of given memory block</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& adopt(_Type* data, size_t size) & {
			if (data_ != nullptr) {
				_destruct_all();
				deallocate_();
			}
			reserved_ = size;
			size_ = size;
			data_ = data;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& adopt(_Type* data, size_t size) && {
			return _rv(adopt(data, size));
		}


	private:
		static void copy_from_(_Type* dest, _Type const* src, size_t size) {
			if constexpr (std::is_trivially_copy_constructible_v<_Type> && std::is_trivially_destructible_v<_Type>)
				::memcpy(dest, src, size * sizeof(_Type));
			else {
				for (_Type* e = dest, *end = dest + size; e < end; ++e, ++src) {
					_destruct(e);
					_construct(e, *src);
				}
			}
		}

		static void move_from_(_Type* dest, _Type* src, size_t size) {
			if constexpr (std::is_trivially_copy_constructible_v<_Type> && std::is_trivially_destructible_v<_Type>)
				::memcpy(dest, src, size * sizeof(_Type));
			else {
				for (_Type* e = dest, *end = dest + size; e < end; ++e, ++src) {
					_destruct(e);
					_construct(e, (_Type&&)*src);
				}
			}
		}


	public:
		INLINE _vector<_Type>& copy_from(_Type const* data, size_t size) & {
			copy_from_(data_, data, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_Type const* data, size_t size) && {
			copy_from_(data_, data, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(size_t pos, _Type const* data, size_t size) & {
			copy_from_(data_ + pos, data, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _Type const* data, size_t size) && {
			copy_from_(data_ + pos, data, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(x::_vector<_Type> const& other) & {
			copy_from_(data_, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type> const& other) && {
			copy_from_(data_, other.data_, other.size_);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(_vector<_Type>&& other) & {
			move_from_(data_, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type>&& other) && {
			move_from_(data_, other.data_, other.size_);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type> const& other) & {
			copy_from_(data_ + pos, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type> const& other) && {
			copy_from_(data_ + pos, other.data_, other.size_);
			return _rvthis;
		}

		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type>&& other) & {
			move_from_(data_ + pos, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type>&& other) && {
			move_from_(data_ + pos, other.data_, other.size_);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(_vector<_Type> const& other, size_t size) & {
			copy_from_(data_, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type> const& other, size_t size) && {
			copy_from_(data_, other.data_, size);
			return _rvthis;
		}

		INLINE _vector<_Type>& copy_from(_vector<_Type>&& other, size_t size) & {
			move_from_(data_, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type>&& other, size_t size) && {
			move_from_(data_, other.data_, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(_vector<_Type> const& other, size_t size, size_t offset) & {
			copy_from_(data_, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type> const& other, size_t size, size_t offset) && {
			copy_from_(data_, other.data_ + offset, size);
			return _rvthis;
		}

		INLINE _vector<_Type>& copy_from(_vector<_Type>&& other, size_t size, size_t offset) & {
			move_from_(data_, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(_vector<_Type>&& other, size_t size, size_t offset) && {
			move_from_(data_, other.data_ + offset, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type> const& other, size_t size) & {
			copy_from_(data_ + pos, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type> const& other, size_t size) && {
			copy_from_(data_ + pos, other.data_, size);
			return _rvthis;
		}

		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type>&& other, size_t size) & {
			move_from_(data_ + pos, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type>&& other, size_t size) && {
			move_from_(data_ + pos, other.data_, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type> const& other, size_t size, size_t offset) & {
			copy_from_(data_ + pos, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type> const& other, size_t size, size_t offset) && {
			copy_from_(data_ + pos, other.data_ + offset, size);
			return _rvthis;
		}

		INLINE _vector<_Type>& copy_from(size_t pos, _vector<_Type>&& other, size_t size, size_t offset) & {
			move_from_(data_ + pos, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& copy_from(size_t pos, _vector<_Type>&& other, size_t size, size_t offset) && {
			move_from_(data_ + pos, other.data_ + offset, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(_Type* data, size_t size) & {
			move_from_(data_, data, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(_Type* data, size_t size) && {
			move_from_(data_, data, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(size_t pos, _Type* data, size_t size) & {
			move_from_(data_ + pos, data, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(size_t pos, _Type* data, size_t size) && {
			move_from_(data_ + pos, data, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(_vector<_Type>&& other) & {
			move_from_(data_, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(_vector<_Type>&& other) && {
			move_from_(data_, other.data_, other.size_);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(size_t pos, _vector<_Type>&& other) & {
			move_from_(data_ + pos, other.data_, other.size_);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(size_t pos, _vector<_Type>&& other) && {
			move_from_(data_ + pos, other.data_, other.size_);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(_vector<_Type>&& other, size_t size) & {
			move_from_(data_, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(_vector<_Type>&& other, size_t size) && {
			move_from_(data_, other.data_, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(_vector<_Type>&& other, size_t size, size_t offset) & {
			move_from_(data_, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(_vector<_Type>&& other, size_t size, size_t offset) && {
			move_from_(data_, other.data_ + offset, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(size_t pos, _vector<_Type>&& other, size_t size) & {
			move_from_(data_ + pos, other.data_, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(size_t pos, _vector<_Type>&& other, size_t size) && {
			move_from_(data_ + pos, other.data_, size);
			return _rvthis;
		}


		INLINE _vector<_Type>& move_from(size_t pos, _vector<_Type>&& other, size_t size, size_t offset) & {
			move_from_(data_ + pos, other.data_ + offset, size);
			return *this;
		}

		INLINE _vector<_Type>&& move_from(size_t pos, _vector<_Type>&& other, size_t size, size_t offset) && {
			move_from_(data_ + pos, other.data_ + offset, size);
			return _rvthis;
		}


		FORCEINLINE _vector<_Type> const& copy_to(_Type* dest) const & {
			copy_(dest, data_, size_);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& copy_to(_Type* dest) && {
			copy_(dest, data_, size_);
			return _rvthis;
		}

		FORCEINLINE _vector<_Type>& move_to(_Type* dest) & {
			move_(dest, data_, size_);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& move_to(_Type* dest) && {
			move_(dest, data_, size_);
			return _rvthis;
		}

		/// <summary>
		/// Gets current size of the vector, that means amount of accessible elements.
		/// </summary>
		/// <returns>the current vector size</returns>
		template<unsigned _depth = 1>
		INLINE size_t size() const noexcept {
			if constexpr (_depth == 1)
				return size_;
			else {
				size_t result = 0;
				_foreach(e)
					result += e->size<_depth - 1>();
				return result;
			}
		}


		/// <summary>
		/// Equivalent to calling size() - 1. Gets the last valid and accessible position of the
		/// vector that can be safely used as argument to operator[].
		/// </summary>
		/// <returns>the last accessible position</returns>
		FORCEINLINE size_t lastpos() const noexcept {
			return size_ - 1;
		}


		/// <summary>
		/// Returns the current total number of elements for which memory is allocated.
		/// </summary>
		/// <returns>the current memory capacity</returns>
		template<unsigned _depth = 1>
		INLINE size_t capacity() const noexcept {
			if constexpr (_depth == 1)
				return reserved_;
			else {
				size_t result = 0;
				_foreach(e)
					result += e->capacity<_depth - 1>();
				return result;
			}
		}


		/// <summary>
		/// Equivalent of capacity() * sizeof(_Type). Gets the amount of memory currently 
		/// allocated by the vector in bytes.
		/// </summary>
		/// <returns>the __int8 size of allocated memory</returns>
		template<unsigned _depth = 1>
		FORCEINLINE size_t memory() const noexcept {
			if constexpr (_depth == 1)
				return reserved_ * sizeof(_Type);
			else {
				size_t result = 0;
				_foreach(e)
					result += e->memory<_depth - 1>();
				return result;
			}
		}


		template<unsigned _depth = 1>
		FORCEINLINE size_t unused() const noexcept {
			if constexpr (_depth == 1)
				return reserved_ - size_;
			else {
				size_t result = 0;
				_foreach(e)
					result += e->unused<_depth - 1>();
				return result;
			}
		}


		template<unsigned _depth = 1>
		FORCEINLINE size_t unused_memory() const noexcept {
			if constexpr (_depth == 1)
				return (reserved_ - size_) * sizeof(_Type);
			else {
				size_t result = 0;
				_foreach(e)
					result += e->unused_memory<_depth - 1>();
				return result;
			}
		}


		/// <summary>
		/// Checks whether vector is empty.
		/// </summary>
		/// <remarks>
		/// Vector is considered empty if it does not contain any accessible elements nonetheless 
		/// it can have allocated, handled memory.
		/// </remarks>
		/// <returns>true if vector is empty, otherwise false</returns>
		template<unsigned _depth = 1>
		FORCEINLINE bool empty() const noexcept {
			if constexpr (_depth == 1)
				return size_ == 0;
			else {
				if (size_ == 0)
					return true;
				_foreach(e)
					if (!e->empty<_depth - 1>())
						return false;
				return true;
			}
		}


		template<unsigned _depth = 1>
		bool valid() const noexcept {
			if constexpr (_depth == 1)
				return ((data_ == nullptr) == (reserved_ == 0)) && reserved_ >= size_;
			//return data_ != nullptr;
			else {
				if (((data_ == nullptr) == (reserved_ == 0)) && reserved_ >= size_) {
					_foreach(v)
						if (!v->valid<_depth - 1>())
							return false;
					return true;
				} else
					return false;
			}
		}


		/// <summary>
		/// Gets the current capacity of memory that will be defaultly allocated e.g.
		/// by constructors and some functions that clear, reduce the size of vector 
		/// or reallocate memory in every case when the new desired memory capacity is not specified.
		/// This value is static and so is the same for all vectors of the same.
		/// </summary>
		/// <returns>the current default vector capacity</returns>
		/// <see cref="set_default_alloc"/>
		//FORCEINLINE static size_t default_alloc() noexcept {
		//	return defaultAlloc_;
		//}


		/// <summary>
		/// Sets the current capacity of memory that will be defaultly allocated e.g.
		/// by constructors and some functions that clear, reduce the size of vector 
		/// or reallocate memory in every case when the new desired memory capacity is not specified.
		/// This value is static and so is the same for all vectors of the same.
		/// </summary>
		/// <param name="defSize">the new default vector capacity, DEFAULT: global default capacity = 10</param>
		/// <see cref="default_alloc"/>
		/*FORCEINLINE static void set_default_alloc(size_t defSize = DEFAULT_ALLOC_) noexcept {
		defaultAlloc_ = defSize;
		}*/


		/// <summary>
		/// Gets current value of allocation multiplier, a factor by which the current capacity will be 
		/// multiplied if a memory reallocation is needed.
		/// This value is static and so is the same for all vectors of the same.
		/// </summary>
		/// <returns>the current reallocation capacity multiplier</returns>
		/// <see cref="set_extend_multiplier"/>
		static constexpr size_t extend_multiplier() noexcept {
			return size_t(2);
		}


		/// <summary>
		/// Checks whether the vector contains any accessible element.
		/// </summary>
		/// <returns>true if the vector contains any accessible elements, otherwise false</returns>
		FORCEINLINE explicit operator bool() const noexcept {
			return size_ > 0;
			//return data_ != nullptr && size_ > 0;
		}


		FORCEINLINE bool operator!() const noexcept {
			return size_ == 0;
		}


		FORCEINLINE _vector<_Type>&& move() const noexcept {
			return const_cast<_vector<_Type>&&>(*this);
		}

		FORCEINLINE _vector<_Type>&& rv() const noexcept {
			return const_cast<_vector<_Type>&&>(*this);
		}

		/// <summary>
		/// Gets reference to the element at specified position.
		/// This function does not validate the position, only tries to access an element of the data array_data.
		/// For safe access to an element use at().
		/// </summary>
		/// <param name="pos">poition of the element to get</param>
		/// <returns>the element at given position</returns>
		/// <see cref="at"/>
		FORCEINLINE _Type& operator[](size_t pos) & {
			return data_[pos];
		}

		FORCEINLINE _Type const& operator[](size_t pos) const & {
			return data_[pos];
		}

		FORCEINLINE _Type&& operator[](size_t pos) && {
			return (_Type&&)data_[pos];
		}


		_vector<_Type> operator[](_vector<size_t> const& pos) const & {
			_vector<_Type> result(pos.size_);
			result.enable();
			_pair_foreach(result, r, pos, p)
				_construct(r, data_[*p]);
			/*for (size_t i = 0; i < pos.size_; ++i)
			_construct(result.data_ + i, data_[pos.data_[i]]);*/
			return result;
		}

		_vector<_Type> operator[](_vector<size_t> const& pos) && {
			_vector<_Type> result(pos.size_);
			result.enable();
			_pair_foreach(result, r, pos, p)
				_construct(r, (_Type&&)data_[*p]);
			return result;
		}

		/*template<size_t _size, size_t... _i>
		FORCEINLINE void put_(_refvector<_Type>& result, size_t(&pos)[_size], seq<_i...> const&) {
		x::va::expand{(result.data_[_i] = &data_[pos[_i]])...};
		}

		template<size_t _size>
		_refvector<_Type> operator[](size_t(&&pos)[_size]) {
		_refvector<_Type> result(_size);
		result.size_ = _size;
		put_(result, pos, seq_v<_size>);
		}*/

		_vector<_Type> operator[](std::initializer_list<size_t> pos) const & {
			_vector<_Type> result(pos.size());
			result.enable();
			_Type const* p = pos.begin();
			for (size_t i = 0; i < result.size_; ++i, ++p)
				_construct(result.data_ + i, data_[*p]);
			return result;
		}

		_vector<_Type> operator[](std::initializer_list<size_t> pos) && {
			_vector<_Type> result(pos.size());
			result.enable();
			_Type const* p = pos.begin();
			for (size_t i = 0; i < result.size_; ++i, ++p)
				_construct(result.data_ + i, (_Type&&)data_[*p]);
			return result;
		}


		/// <summary>
		/// Creates a copy of the caller vector and appends the right-hand operand, whose elements
		/// are copied to the resulting vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns>copied vector with appended copied right-hand opperand vector</returns>
		/// <see cref="operator+="/>
		/// <see cref="append"/>
		_vector<_Type> operator+(const _vector<_Type>& other) const & {
			_vector<_Type> result(*this, size_ + other.size_);
			result.enable();
			copy_(result.data_ + size_, other.data_, other.size_);
			return result;
		}


		FORCEINLINE _vector<_Type>&& operator+(const _vector<_Type>& other) && {
			return _rv(append(other));
		}


		_vector<_Type> operator+(_vector<_Type>&& other) const & {
			_vector<_Type> result(size_ + other.size_);
			result.size_ = result.reserved_;
			copy_(result.data_, data_, size_);
			::memcpy(result.data_ + size_, other.data_, other.size_ * sizeof(_Type));
			result.deallocate_();
			result.data_ = nullptr;
			return result;
		}


		FORCEINLINE _vector<_Type>&& operator+(_vector<_Type>&& other) && {
			return _rv(append((_vector<_Type>&&)other));
		}


		FORCEINLINE _vector<_Type>& operator+=(_vector<_Type> const& other) & {
			return append(other);
		}


		FORCEINLINE _vector<_Type>&& operator+=(_vector<_Type> const& other) && {
			return _rv(append(other));
		}


		FORCEINLINE _vector<_Type>& operator+=(_vector<_Type>&& other) & {
			return append((_vector<_Type>&&)other);
		}


		FORCEINLINE _vector<_Type>&& operator+=(_vector<_Type>&& other) && {
			return _rv(append((_vector<_Type>&&)other));
		}


		template<class... _Arg>
		auto operator()(_Arg&&... args) {
			using Res = std::invoke_result_t<_Type, _Arg...>;
			if constexpr (std::is_void_v<Res>) {
				_foreach(e)
					(*e)((_Arg&&)args...);
				return;
			} else {
				_vector<Res> result(size_);
				result.size_ = result.reserved_;
				_pair_foreach(*this, e, result, r)
					_construct_t(Res, r, (*e)((_Arg&&)args...));
				return result;
			}
		}


		/// <summary>
		/// Forces the use of memcmp to compare the vector to given for equality of the date.
		/// </summary>
		/// <remarks>
		/// It returns false without checking memory if the sizes are different.
		/// </remarks>
		/// <param name="other">the vector to be compared to</param>
		/// <returns>true if the vectors' memory is equal, otherwise false</returns>
		int memcmp(const _vector<_Type>& other) const {
			return ::memcmp(data_, other.data_, size_ * sizeof(_Type));
		}


		///////////////////////////////////////////////////////////////////////////////

	protected:
		bool equal_to_(const _vector<_Type>& other) const {
			if constexpr (std::is_pod_v<_Type>)
				return size_ == other.size_ && this->memcmp(other) == 0;
			else {
				if (size_ != other.size_)
					return false;
				_pair_foreach(*this, e, other, o)
					if (!(*e == *o))
						return false;
				return true;
			}
		}


		int compare_(_vector<_Type> const& other) const {
			if constexpr (std::is_pod_v<_Type>) {
				int sizeDiff = (int)size_ - (int)other.size_;
				if (sizeDiff == 0)
					return ::memcmp(data_, other.data_, x::min(size_, other.size_) * sizeof(_Type));
				else if (sizeDiff < 0) {
					int diff = ::memcmp(data_, other.data_, size_ * sizeof(_Type));
					return diff != 0 ? diff : -1;
				} else {
					int diff = ::memcmp(data_, other.data_, other.size_ * sizeof(_Type));
					return diff != 0 ? diff : 1;
				}
			} else {
				size_t max = x::min(size_, other.size_);
				for (size_t i = 0; i < max; ++i) {
					auto diff = data_[i] - other.data_[i];
					if (diff == 0)
						continue;
					if (diff < 0)
						return -1;
					else
						return 1;
				}
				return (int)size_ - (int)other.size_;
			}
		}


	public:
		/// <summary>
		/// Uses operator== to compare each element. If the size of given vector is different than
		/// the size of the caller, this function automatically returns false.
		/// For trivial types this function does the same as memcmp.
		/// </summary>
		/// <param name="other">the vector to be compared to</param>
		/// <returns>true if each element is equal, otherwise false</returns>
		FORCEINLINE bool equal_to(_vector<_Type> const& other) const {
			return equal_to_(other);
		}

		/// <summary>
		/// Uses operator== to compare each element. If the size of given vector is different than
		/// the size of the caller, this function automatically returns false.
		/// </summary>
		/// <typeparam name="_Func">deduced type of the comparator</typeparam>
		/// <param name="other">the vector to be compared to</param>
		/// <param name="comparator">object or function comparing two elements</param>
		/// <returns>true if each element is equal, otherwise false</returns>
		template<class _Func>
		bool equal_to(_vector<_Type> const& other, _Func&& comparator) const {
			if (size_ != other.size_)
				return false;
			for (size_t i = 0; i<size_; ++i) {
				if (!comparator(data_[i], other.data_[i]))
					return false;
			}
			return true;
		}

		///////////////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Compares the vector to another for equality of all elements.
		/// </summary>
		/// <remarks>
		/// Equivalent to <code>equal_to(other)</code>. If the size of given vector is different than
		/// the size of the caller, this function automatically returns false.
		/// </remarks>
		/// <param name="other">the vector to be compared to</param>
		/// <returns>true if the vectors' memory is equal, otherwise false</returns>
		/// <see cref="equal_to"/>
		FORCEINLINE bool operator==(_vector<_Type> const& other) const {
			return equal_to_(other);
		}


		INLINE bool operator==(_Type const& value) const {
			return size_ == 1 && data_[0] == value;
		}


		/// <summary>
		/// Compares the vector to another for non-equality of any elements. 
		/// </summary>
		/// <remarks>
		/// Equivalent to <code>! equal_to(other)</code>. If the size of given vector is different than
		/// the size of the caller, this function automatically returns false.
		/// </remarks>
		/// <param name="other">the vector to be compared to</param>
		/// <returns>true if the vectors' memory is not equal, otherwise false</returns>
		FORCEINLINE bool operator!=(_vector<_Type> const& other) const {
			return !equal_to(other);
		}


		FORCEINLINE bool operator!=(_Type const& value) const {
			return !operator==(value);
		}


		FORCEINLINE bool operator < (_vector<_Type> const& other) const {
			return compare_(other) < 0;
		}

		FORCEINLINE bool operator <= (_vector<_Type> const& other) const {
			return compare_(other) <= 0;
		}

		FORCEINLINE bool operator > (_vector<_Type> const& other) const {
			return compare_(other) > 0;
		}

		FORCEINLINE bool operator >= (_vector<_Type> const& other) const {
			return compare_(other) >= 0;
		}


		/// <summary>
		/// Gets reference to the element at specified position wrapped in x::result object.
		/// If the position is greater than the maximum accessible, the function returns
		/// x::result of invalid state.
		/// </summary>
		/// <param name="pos">poition of the element to get</param>
		/// <returns>the element at given position</returns>
		/// <see cref="operator[]"/>
		/// <see cref="last"/>
		/// <see cref="first"/>
		opt<_Type&> at(size_t i) {
			if (i < size_)
				return data_[i];
			return opt<_Type&>::INVALID;
		}


		opt<_Type const&> at(size_t i) const {
			if (i < size_)
				return data_[i];
			return opt<_Type const&>::INVALID;
		}

		_Type& at(size_t i, _Type& def) {
			if (i < size_)
				return data_[i];
			return def;
		}

		_Type const& at(size_t i, _Type const& def) const {
			if (i < size_)
				return data_[i];
			return def;
		}


		template<class _DataType>
		FORCEINLINE _DataType& get(size_t i) {
			return reinterpret_cast<_DataType*>(data_)[i];
		}

		template<class _DataType>
		FORCEINLINE _DataType const& get(size_t i) const {
			return reinterpret_cast<_DataType const*>(data_)[i];
		}

		FORCEINLINE uint8_t& byte(size_t i) {
			return reinterpret_cast<uint8_t*>(data_)[i];
		}

		FORCEINLINE uint8_t byte(size_t i) const {
			return reinterpret_cast<uint8_t const*>(data_)[i];
		}


		bool __declspec(noinline) bit(size_t i) const {
		#if XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
			_asm {
				mov ebx, [ecx]this_type.data_
				mov edx, i
				mov ecx, edx
				and ecx, 7
				mov eax, 1
				shl eax, cl
				shr edx, 3
				xor ecx, ecx
				mov cl, byte ptr[ebx + edx]
				and eax, ecx
				cmp eax, 0
				je	_RET_
				mov eax, 1
				_RET_:
			}
		#else
			return (reinterpret_cast<uint8_t const*>(data_)[i / 8] & (1 << (i % 8))) != 0;
		#endif
		}


		void __declspec(noinline _SPEC) set_bit(size_t i, bool value) const {
		#if XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
			_asm {
				mov ebx, [ecx]this_type.data_
				mov edx, i
				mov ecx, edx
				and ecx, 7
				mov eax, 1
				shl eax, cl
				shr edx, 3
				cmp value, 0
				je	_SET_0_
				_SET_1_ :
				or  byte ptr[ebx + edx], al
				jmp _RET_
				_SET_0_ :
				not eax
				and byte ptr[ebx + edx], al
				_RET_ :
			}
		#else
			if (value)
				reinterpret_cast<uint8_t const*>(data_)[i / 8] |= (1 << (i % 8));
			else
				reinterpret_cast<uint8_t const*>(data_)[i / 8] &= ~(1 << (i % 8));
		#endif
		}


		void __declspec(noinline _SPEC) set_bit(size_t i) const {
		#if XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
			_asm {
				mov ebx, [ecx]this_type.data_
				mov edx, i
				mov ecx, edx
				and ecx, 7
				mov eax, 1
				shl eax, cl
				shr edx, 3
				or  byte ptr[ebx + edx], al
			}
		#else
			reinterpret_cast<uint8_t const*>(data_)[i / 8] |= (1 << (i % 8));
		#endif
		}


		void __declspec(noinline _SPEC) clear_bit(size_t i) const {
		#if XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
			_asm {
				mov ebx, [ecx]this_type.data_
				mov edx, i
				mov ecx, edx
				and ecx, 7
				mov eax, 1
				shl eax, cl
				shr edx, 3
				not eax
				and byte ptr[ebx + edx], al
			}
		#else
			reinterpret_cast<uint8_t const*>(data_)[i / 8] &= ~(1 << (i % 8));
		#endif
		}


		void __declspec(noinline _SPEC) toggle_bit(size_t i) const {
		#if XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
			_asm {
				mov ebx, [ecx]this_type.data_
				mov edx, i
				mov ecx, edx
				and ecx, 7
				mov eax, 1
				shl eax, cl
				shr edx, 3
				xor byte ptr[ebx + edx], al
			}
		#else
			reinterpret_cast<uint8_t const*>(data_)[i / 8] ^= (1 << (i % 8));
		#endif
		}


		size_t bitcount(bool bitval) const {
			size_t count = 0;
			uint8_t const* bcdata = bitval ? x::bitcount::ONES : x::bitcount::ZEROS;
			for (uint8_t const* b = reinterpret_cast<uint8_t const*>(data_), *end = b + size_ * sizeof(_Type); b < end; ++b)
				count += bcdata[*b];
			return count;
		}


		/// <summary>
		/// Gets reference to the first element wrapped in x::result object.
		/// If the size of vector is 0, the function returns x::result of invalid state.
		/// </summary>
		/// <returns>the first element</returns>
		/// <see cref="at"/>
		/// <see cref="operator[]"/>
		/// <see cref="last"/>
		opt<_Type&> first() {
			if (size_ > 0)
				return data_[0];
			return opt<_Type&>::INVALID;
		}

		opt<_Type const&> first() const {
			if (size_ > 0)
				return data_[0];
			return opt<_Type const&>::INVALID;
		}

		_Type& first(_Type& def) {
			if (size_ > 0)
				return data_[0];
			return def;
		}

		_Type const& first(_Type const& def) const {
			if (size_ > 0)
				return data_[0];
			return def;
		}

		/// <summary>
		/// Gets reference to the last element wrapped in x::result object.
		/// If the size of vector is 0, the function returns x::result of invalid state.
		/// </summary>
		/// <returns>the last element</returns>
		/// <see cref="at"/>
		/// <see cref="operator[]"/>
		/// <see cref="first"/>
		opt<_Type&> last() {
			if (size_ > 0)
				return data_[size_ - 1];
			return opt<_Type&>::INVALID;
		}

		opt<_Type const&> last() const {
			if (size_ > 0)
				return data_[size_ - 1];
			return opt<_Type const&>::INVALID;
		}

		_Type& last(_Type& def) {
			if (size_ > 0)
				return data_[size_ - 1];
			return def;
		}

		_Type const& last(_Type const& def) const {
			if (size_ > 0)
				return data_[size_ - 1];
			return def;
		}

		/// <summary>
		/// Swaps the data pointer and size parameters with other vector. This operation is fast and
		/// does not copy any allocated data.
		/// </summary>
		/// <param name="other">the vector to swapped with</param>
		_vector<_Type>& swap(_vector<_Type>& other) noexcept {
			x::swap(*this, other);
			return *this;
		}

		_vector<_Type>& swap(_vector<_Type>&& other) noexcept {
			this->~_vector();
			_trivcopy(this, )
			return _rvthis;
		}

		/// <summary>
		/// Swaps elements at given positions. This operation does not perform any deep copying,
		/// only raw __int8 form of the elements are copied. No constructor or assignment operator is called.
		/// </summary>
		/// <param name="pos1">position of the first element fo be swapped</param>
		/// <param name="pos2">position of the second element fo be swapped</param>
		/// <returns>reference to the caller</returns>//swaps two elements
		FORCEINLINE _vector<_Type>& swap(size_t pos1, size_t pos2) & {
			x::swap(data_[pos1], data_[pos2]);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& swap(size_t pos1, size_t pos2) && {
			x::swap(data_[pos1], data_[pos2]);
			return _rvthis;
		}


		/// <summary>
		/// Constructs a new vector containing copied elements of the caller vector beginning from 
		/// the first specified position and ending at the second position inclusively.
		/// If the vector is empty or \a begin is greater than \a end the resulting vector will be empty.
		/// </summary>
		/// <param name="begin">beginning of range</param>
		/// <param name="end">end of range</param>
		/// <returns>new vector with elements from given range</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type> subset(size_t begin, size_t end) const & {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (begin >= size_ || end < begin)
					return _vector<_Type>();
				if (end >= size_)
					end = size_ - 1;
			}
			size_t subsetSize = end - begin + 1;
			_vector<_Type> sub(subsetSize);
			sub.size_ = sub.reserved_;
			copy_(sub.data_, data_ + begin, sub.size_);
			return sub;
		}

		template<mode_t _mode = _DefaultMode>
		_vector<_Type>&& subset(size_t begin, size_t end) && {
			_assert_mode(Default, NoArgCheck, Naked);
			return _rvthis.cut<_mode>(begin, end);
		}


		/// <summary>
		/// Constructs a new vector containing copied elements of the caller vector beginning from 
		/// the specified position and ending at the last element.
		/// If the vector is empty or \a begin is greater than the last position 
		/// the resulting vector will be empty
		/// </summary>
		/// <param name="begin">beginning of range</param>
		/// <returns>new vector with elements from given range</returns>
		/// <see cref="subset"/>
		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type> subset(size_t begin) const & {
			_assert_mode(Default, NoArgCheck, Naked);
			return subset<NoArgCheck>(begin, size_ - 1);
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& subset(size_t begin) && {
			_assert_mode(Default, NoArgCheck, Naked);
			return _rvthis.cut<_mode>(begin);
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type> const& subset_view(size_t begin, size_t end) const {
			_assert_mode(Default, Naked, NoIndexCheck);
			_vector<_Type>& view = *reinterpret_cast<_vector<_Type>*>(_VectorTemp::view_.data);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (begin >= size_ || end < begin) {
					view.discard_data();
					return view;
				}
				if (end >= size_)
					end = size_ - 1;
			}
			view.size_ = end - begin + 1;
			view.reserved_ = view.size_;
			view.data_ = data_ + begin;
			return view;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type> const& subset_view(size_t begin) const {
			_assert_mode(Default, Naked, NoSizeCheck);
			_vector<_Type>& view = *reinterpret_cast<_vector<_Type>*>(_VectorTemp::view_.data);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (begin >= size_) {
					view.discard_data();
					return view;
				}
			}
			view.size_ = size_ - begin;
			view.reserved_ = view.size_;
			view.data_ = data_ + begin;
			return view;
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type> subvector(size_t begin, size_t size) const & {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (begin >= size_)
					return _vector<_Type>();
			}
			_vector<_Type> sub(size);
			if constexpr (!_mode_set(NoArgCheck))
				sub_size_ = size;
			else
				sub.size_ = x::min(size, size_ - begin);
			copy_(sub.data_, data_ + begin, sub.size_);
			return sub;
		}

		template<mode_t _mode = _DefaultMode>
		_vector<_Type>&& subvector(size_t begin, size_t size) && {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (_mode_set(NoArgCheck))
				return _rvthis.cut<_mode>(begin, begin + size - 1);
			else
				return _rvthis.cut<_mode>(begin, x::min(begin + size - 1, size_ - 1));
		}



		/*template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type> subvector(size_t begin) const & {
		_assert_mode(Default, NoArgCheck, Naked);
		if constexpr (!_mode_set(NoArgCheck)) {
		if (begin >= size_)
		return _vector<_Type>();
		}
		_vector<_Type> sub(size_ - begin);
		if constexpr (!_mode_set(NoArgCheck))
		sub_size_ = size;
		else
		sub.size_ = x::min(size, size_ - begin);
		copy_(sub.data_, data_ + begin, sub.size_);
		return sub;
		}*/


		/*template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& subvector(size_t begin) && {
		_assert_mode(Default, NoArgCheck, Naked);
		return _rvthis.cut<_mode>(begin);
		}*/


		template<mode_t _mode = _DefaultMode>
		_vector<_Type> const& subvector_view(size_t begin, size_t size) const {
			_assert_mode(Default, Naked, NoSizeCheck);
			_vector<_Type>& view = *reinterpret_cast<_vector<_Type>*>(_VectorTemp::view_.data);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (begin >= size_ || end < begin) {
					view.discard_data();
					return view;
				}
				if (begin + size > size_)
					view.size_ = size_ - begin;
				else
					view.size_ = size;
			} else
				view.size_ = size;

			view.reserved_ = view.size_;
			view.data_ = data_ + begin;
			return view;
		}


		/*	template<mode_t _mode = _DefaultMode>
		_vector<_Type> const& subvector_view(size_t begin) const {
		_assert_mode(Default, Naked, NoSizeCheck);
		_vector<_Type>& view = *reinterpret_cast<_vector<_Type>*>(_VectorTemp::view_.data);
		if constexpr (!_mode_set(NoIndexCheck)) {
		if (begin >= size_) {
		view.discard_data();
		return view;
		}
		}
		view.size_ = size_ - begin;
		view.reserved_ = view.size_;
		view.data_ = data_ + begin;
		return view;
		}*/



		/*template<mode_t _mode = _DefaultMode>
		_vector<_Type> const& subset_view(size_t begin, size_t end) const {
		_assert_mode(Default, Naked, NoIndexCheck, NoSizeCheck);
		struct ViewClearer {
		_vector<_Type>& view;
		~ViewClearer() {
		view.discard_data();
		}
		};
		static thread_local _vector<_Type> view_;
		static thread_local ViewClearer viewClearer_(view_);

		_vector<_Type>& view = view_;
		if constexpr (!_mode_set(NoSizeCheck)) {
		if (size_ == 0) {
		view.discard_data();
		return view;
		}
		}
		if constexpr (!_mode_set(NoIndexCheck)) {
		if (end >= size_)
		end = size_ - 1;
		if (end < begin) {
		view.discard_data();
		return view;
		}
		}
		view.reserved_ = reserved_;
		view.size_ = end - begin + 1;
		view.data_ = data_ + begin;
		return view;
		}*/

		/*_vector<_Type> const& subset_view(size_t begin, size_t end) const {
		struct ViewClearer {
		_vector<_Type>& view;
		~ViewClearer() {
		view.discard_data();
		}
		};
		static thread_local _vector<_Type> view_(NO_ALLOC);
		static thread_local ViewClearer viewClearer_{view_};

		_vector<_Type>& view = view_;
		if (size_ > 0 && end >= begin) {
		view.reserved_ = reserved_;
		view.size_ = end - begin + 1;
		view.data_ = data_ + begin;
		}
		else {
		view.discard_data();
		}
		return view;
		}*/

		/*template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type> const&& subset_view(size_t begin, size_t end) const && {
		return _rv(subset_view<_mode>(begin, end));
		}*/

		/*template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type> const&& subset_view(size_t begin) const && {
		return _rv(subset_view<_mode>(begin, size_ - 1));
		}*/

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& mutable_subset_view(size_t begin, size_t end) {
			_assert_mode(Default, NoArgCheck, Naked);
			return const_cast<_vector<_Type&>>(subset_view<_mode>(begin, end));
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& mutable_subset_view(size_t begin) {
			_assert_mode(Default, NoArgCheck, Naked);
			return const_cast<_vector<_Type&>>(subset_view<_mode>(begin));
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& mutable_subvector_view(size_t begin, size_t size) {
			_assert_mode(Default, NoArgCheck, Naked);
			return const_cast<_vector<_Type&>>(subvector_view<_mode>(begin, size));
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& mutable_subvector_view(size_t begin) {
			_assert_mode(Default, NoArgCheck, Naked);
			return const_cast<_vector<_Type&>>(subvector_view<_mode>(begin));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type> uniform_select(size_t step) const & {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (step <= 1)
					return *this;
				else if (step >= size_) {
					_vector<_Type> result(1);
					_construct(result.data_, *data_);
					result.size_ = 1;
					return result;
				}
			}
			_vector<_Type> result(size_ / step + 1);
			_Type* r = result.data_;
			_const_step_foreach(e, step)
				_construct(r++, *e);
			result.size_ = r - result.data_;
			return result;
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>&& uniform_select(size_t step) && {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (step <= 1)
					return _rvthis;
				else if (step >= size_) {
					if constexpr (!std::is_trivially_destructible_v<_Type>)
						_destruct_from(data_ + 1);
					size_ = 1;
					return _rvthis;
				}
			}
			_Type* d = data_ + 1;
			if constexpr (std::is_trivially_destructible_v<_Type>) {
				_step_foreach_o(s, step, step)
					_trivcopy(d++, s);
			} else {
				_Type* next = data_ + step;
				/*for (_Type* s = data_, *end = data_ + size_; ;) {
				if (next >= end) {
				for (_Type* e = s + 1; e < end; ++e)
				_destruct(e);
				break;
				}
				else {
				for (_Type* e = s + 1; e < next; ++e)
				_destruct(e);
				_trivcopy(d++, next);
				s = next;
				next += step;
				}
				}*/

				_foreach_o(s, 1) {
					if (s == next) {
						next += step;
						_trivcopy(d++, s);
					} else
						_destruct(s);
				}
			}
			size_ = d - data_;
			return _rvthis;
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type> uniform_select(size_t step, size_t offset) const & {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (offset >= size_)
					return _vector<_Type>();
				if (step <= 1)
					return subset<NoArgCheck>(offset);
				else if (step >= size_ - offset) {
					_vector<_Type> result(1);
					_construct(result.data_, data_[offset]);
					result.size_ = 1;
					return result;
				}
			}
			_vector<_Type> result((size_ - offset) / step + 1);
			_Type* r = result.data_;
			_const_step_foreach_o(e, offset, step)
				_construct(r++, *e);
			result.size_ = r - result.data_;
			return result;
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>&& uniform_select(size_t step, size_t offset) && {
			_assert_mode(Default, NoArgCheck, Naked);
			_Type* begin;
			if constexpr (!_mode_set(NoArgCheck)) {
				if (offset >= size_)
					return _rvthis;
				begin = data_ + offset;
				if (step <= 1)
					return _rvthis.subset<NoArgCheck>(offset);
				else if (step >= size_ - offset) {
					_destruct_range(data_, begin);
					_destruct_from(begin + 1);
					_trivcopy(data_, begin);
					size_ = 1;
					return _rvthis;
				}
			} else
				begin = data_ + offset;

			_destruct_range(data_, data_ + offset);

			_trivcopy(data_, begin);
			_Type* d = data_ + 1;
			_Type* next = begin + step;
			_foreach_from(s, begin + 1) {
				if (s == next) {
					next += step;
					_trivcopy(d++, s);
				} else
					_destruct(s);
			}
			size_ = d - data_;
			return _rvthis;
		}


		FORCEINLINE _vector<_Type> odd() const & {
			return uniform_select(2, 1);
		}


		FORCEINLINE _vector<_Type>&& odd() && {
			return _rvthis.uniform_select(2, 1);
		}


		FORCEINLINE _vector<_Type> even() const & {
			return uniform_select(2);
		}


		FORCEINLINE _vector<_Type>&& even() && {
			return _rvthis.uniform_select(2);
		}


		/*INLINE _vector<_Type>* dynamic() const & {
		return new _vector<_Type>(*this);
		}

		INLINE _vector<_Type>* dynamic() && {
		return new _vector<_Type>(_rvthis);
		}*/


		/// <summary>
		/// Removes every element beyond given range. If \a newBegin is greater or equal to \a newEnd, 
		/// the vector is cleared. If \a newEnd is greater or equal to the size of vector, 
		/// it is trimmed to the last accessible position.
		/// </summary>
		/// <param name="newBegin">position of te first element in the resulting vector</param>
		/// <param name="newEnd">position of te last element in the resulting vector</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& cut(size_t begin, size_t end) & {
			_assert_mode(Default, NoArgCheck, Naked);
			if constexpr (!_mode_set(NoArgCheck)) {
				if (begin >= size_ || end < begin) {
					size_ = 0;
					return *this;
				}
				if (end >= size_)
					end = size_ - 1;
			}
			_destruct_range(data_, data_ + begin);
			_destruct_range(data_ + end + 1, data_ + size_);
			size_ = end - begin + 1;
			::memcpy(data_, data_ + begin, size_ * sizeof(_Type));
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& cut(size_t begin, size_t end) && {
			_assert_mode(Default, NoArgCheck, Naked);
			return _rv(cut<_mode>(begin, end));
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& cut(size_t begin) & {
			_assert_mode(Default, NoArgCheck, Naked);
			return cut<_mode>(begin, size_ - 1);
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& cut(size_t begin) && {
			_assert_mode(Default, NoArgCheck, Naked);
			return _rv(cut<_mode>(begin, size_ - 1));
		}


		/// <summary>
		/// Removes every element in given range inclusively. 
		/// If \a p2 is greater than \a p1, the function does nothing. If \a p2 is greater or equal to 
		/// the size of vector, it is trimmed to the last accessible position.
		/// </summary>
		/// <param name="p1">position of te first element to be removed</param>
		/// <param name="p2">position of te last element to be removed</param>
		/// <returns>reference to the caller</returns>
		FORCEINLINE _vector<_Type>& erase(size_t begin, size_t end) & {
			if (size_ && (end > begin)) {
				_destruct_range(data_ + begin, data_ + end + 1);
				::memcpy(data_ + begin, data_ + end + 1, (size_ - end - 1) * sizeof(_Type));
				size_ -= (end - begin + 1);
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& erase(size_t begin, size_t end) && {
			return _rv(erase(begin, end));
		}

		/// <summary>
		/// Removes one specified element. If the element's position is greater than the last accessible
		/// position, the function does nothing.
		/// </summary>
		/// <param name="pos">position of the element to be removed</param>
		/// <returns>reference to the caller</returns>
		FORCEINLINE _vector<_Type>& erase(size_t pos) & {
			if (pos < size_) {
				_destruct(data_ + pos);
				::memcpy(data_ + pos, data_ + pos + 1, (size_ - pos - 1) * sizeof(_Type));
				--size_;
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& erase(size_t pos) && {
			return _rv(erase(pos));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& erase(std::initializer_list<size_t> pos) & {
			_assert_mode(Default, AssumeSorted, NoSizeCheck, Naked);
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (pos.size() == 0)
					return *this;
				if (size_ == 0)
					return *this;
			}
			size_t const* pp = pos.begin();
			size_t const* ppe = pos.end() - 1;
			size_t nrem = 0;
			for (; pp < ppe; ++pp) {
				size_t p = *pp;
				_Type* remptr = data_ + p - nrem;
				_destruct(remptr);
				::memcpy(remptr, remptr + 1, (pp[1] - p + 1) * sizeof(_Type));
				++nrem;
			}
			size_t p = *pp;
			_Type* remptr = data_ + p - nrem;
			_destruct(remptr);
			::memcpy(remptr, remptr + 1, size_ - p);
			size_ -= pos.size();
			return *this;
		}

		//sygnatura

		//#define _GEN_REFQ(_name) \
			//	FORCEINLINE _vector<_Type>& _name & { \
	//		_name##_(pos); \
	//		return *this; \
	//	} \
	//	FORCEINLINE _vector<_Type>&& _name && { \
	//		_name##_(pos); \
	//		return _rvthis; \
	//	}

//	_GEN_REFQ(erase(size_t pos));

		FORCEINLINE _vector<_Type>& zero() & {
			::memset(data_, 0, size_ * sizeof(_Type));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& zero() && {
			::memset(data_, 0, size_ * sizeof(_Type));
			return _rvthis;
		}


		FORCEINLINE _vector<_Type>& zero(size_t offset) & {
			::memset(data_ + offset, 0, (size_ - offset) * sizeof(_Type));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& zero(size_t offset) && {
			::memset(data_ + offset, 0, (size_ - offset) * sizeof(_Type));
			return _rvthis;
		}


		FORCEINLINE _vector<_Type>& zero(size_t offset, size_t size) & {
			::memset(data_ + offset, 0, size * sizeof(_Type));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& zero(size_t offset, size_t size) && {
			::memset(data_ + offset, 0, size * sizeof(_Type));
			return _rvthis;
		}


		_vector<_Type>& memset(uint8_t byteval) & {
			::memset(data_, (int)byteval, reserved_ * sizeof(_Type));
			return *this;
		}

		_vector<_Type>&& memset(uint8_t byteval) && {
			::memset(data_, (int)byteval, reserved_ * sizeof(_Type));
			return _rvthis;
		}


		_vector<_Type>& fill_assign(_TypeConst value) & {
			_foreach(e)
				*e = value;
		}

		FORCEINLINE _vector<_Type>&& fill_assign(_TypeConst value) && {
			return _rv(fill_assign(value));
		}


		/*FORCEINLINE _vector<_Type>& default_initialize() & {
		::memset(data_ + offset, 0, size * sizeof(_Type));
		return *this;
		}

		FORCEINLINE _vector<_Type>&& default_initialize() && {
		::memset(data_ + offset, 0, size * sizeof(_Type));
		return _rvthis;
		}*/


		template<class... _Arg>
		_vector<_Type>& fill_construct(_Arg&&... args) {
			_foreach(e)
				_reconstruct(e, (_Arg&&)args...);
			return *this;
		}


		template<class _Func, class... _Arg>
		_vector<_Type>& fill_execute(_Func&& func, _Arg&&... args) {
			_foreach(e)
				_reconstruct(e, func((_Arg&&)args...));
			return *this;
		}


		template<class _Func, class... _Arg>
		_vector<_Type>& fill_execute(size_t size, _Func&& func, _Arg&&... args) {
			if (size > reserved_) {
				_destruct_all();
				dump_reallocate_(size);
				_foreach(e)
					_construct(e, func((_Arg&&)args...));
			} else {
				size_ = size;
				_foreach(e)
					_reconstruct(e, func((_Arg&&)args...));
				_destruct_range(data_ + size_, data_ + reserved_);
			}
			return *this;
		}


		/// <summary>
		/// Uses already allocated memory to fill it with copies of the same element.
		/// The size of vector is not changed.
		/// </summary>
		/// <param name="elem">an element to be filled with</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& fill(_TypeConst value) & {
			if constexpr (std::is_trivially_default_constructible_v<_Type> && sizeof(_Type) == 1)
				::memset(data_, value, size_);
			else
				_foreach(e)
				_reconstruct(e, value);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& fill(_TypeConst value) && {
			return _rv(fill(value));
		}

		/// <summary>
		/// Fills the vector with copies of the same element. Allocates new memory 
		/// of given size if needed or uses the existing memory if it is enough.
		/// The size of vector is set to given.
		/// </summary>
		/// <param name="elem">an element to be filled with</param>
		/// <param name="size">new size of the vector</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& fill(_TypeConst value, size_t size) & {
			if (size > reserved_) {
				_destruct_all();
				dump_reallocate_(size);
				size_ = reserved_;
				if constexpr (std::is_trivially_default_constructible_v<_Type> && sizeof(_Type) == 1) {
					::memset(data_, value, size_);
				} else {
					_foreach(e)
						_construct(e, value);
				}
			} else {
				if constexpr (std::is_trivially_default_constructible_v<_Type> && sizeof(_Type) == 1) {
					size_ = size;
					::memset(data_, value, size_);
				} else if constexpr (std::is_trivially_destructible_v<_Type>) {
					size_ = size;
					_foreach(e)
						_construct(e, value);
				} else {
					if (size > size_) {
						_foreach(e)
							_reconstruct(e, value);
						_foreach_from_s(e, data_ + size_, size)
							_construct(e);
					} else {
						_foreach_from(e, data_ + size)
							_destruct(e);
						size_ = size;
						_foreach(e)
							_reconstruct(e, value);
					}
				}
			}
			return *this;
		}


		FORCEINLINE _vector<_Type>&& fill(_TypeConst value, size_t size) && {
			return _rv(fill(value, size));
		}


		/*_vector<_Type>& fill(_TypeConst value, size_t begin, size_t size) & {
		size_t maxsize = size_ - begin;
		if (size > maxsize)
		size = maxsize;
		if constexpr (std::is_trivially_default_constructible_v<_Type> && sizeof(_Type) == 1) {
		::memset(data_ + begin, value, size);
		}
		else {
		_Type* pend = data_ + end;
		_for_range(e, data_ + begin, pend);
		_construct(e, value);
		}
		return *this;
		}


		FORCEINLINE _vector<_Type>&& fill(_TypeConst value, size_t begin, size_t end) && {
		return _rv(fill(value, begin, end));
		}*/


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& initialize() & {
			if constexpr (_mode_set(AssumeEmpty)) {
				if constexpr (std::is_trivially_default_constructible_v<_Type> || DIM_ >= 2) {
					::memset(data_, 0, reserved_ * sizeof(_Type));
				} else {
					_foreach_reserved(e)
						_construct(e);
				}
			} else {
				if constexpr (std::is_trivially_default_constructible_v<_Type> || DIM_ >= 2) {
					::memset(data_ + size_, 0, (reserved_ - size_) * sizeof(_Type));
				} else if constexpr (std::is_default_constructible_v<_Type>) {
					_foreach_uninit(e)
						_construct(e);
				}
			}
			size_ = reserved_;
			return *this;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE	_vector<_Type>&& initialize() && {
			return _rv(initialize<_mode>());
		}


		_vector<_Type>& initialize(_TypeConst value) & {
			_foreach_uninit(e)
				_construct(e, value);
			size_ = reserved_;
			return *this;
		}


		FORCEINLINE _vector<_Type>&& initialize(_TypeConst value) && {
			return _rv(initialize(value));
		}


		_vector<_Type>& initialize(_TypeConst value, size_t maxsize) & {
			if (maxsize > reserved_)
				maxsize = reserved_;
			_foreach_from_s(e, data_ + size_, maxsize)
				_construct(e, value);
			size_ = maxsize;
			return *this;
		}

		FORCEINLINE	_vector<_Type>&& initialize(_TypeConst value, size_t maxsize) && {
			return _rv(initialize(value, maxsize));
		}

		template<class... _Arg>
		_vector<_Type>& initialize_construct(_Arg&&... args) & {
			_foreach_uninit(e)
				_construct(e, (_Arg&&)args...);
			size_ = reserved_;
			return *this;
		}


		template<class... _Arg>
		FORCEINLINE _vector<_Type>&& initialize_construct(_Arg&&... args) && {
			return _rv(initialize_construct((_Arg&&)args...));
		}


		_vector<_Type> replicate(size_t n) const & {
			size_t resSize = size_ * n;
			_vector<_Type> result(resSize, resSize);
			_step_foreach_v(r, result, size_)
				copy_(r, data_, size_);
			return result;
		}

		_vector<_Type>&& replicate(size_t n) && {
			size_t newsize = size_ * n;
			reserve(newsize);
			_step_foreach_os(r, size_, size_, reserved_)
				copy_(r, data_, size_);
			size_ = reserved_;
			return _rvthis;
		}

		/*private:
		size_t split_size_(size_t pos) {
		size_t rightSize = size_ > pos ? size_ - pos : 0;
		size_ -= rightSize;
		return rightSize;
		}*/

		std::pair<_vector<_Type>&, _vector<_Type>> split(size_t pos) & {
			size_t rightSize = size_ > pos ? size_ - pos : 0;
			size_ -= rightSize;
			std::pair<_vector<_Type>&, _vector<_Type>> result{*this, _vector<_Type>(rightSize, rightSize)};
			::memcpy(result.second.data_, data_ + pos, rightSize * sizeof(_Type));
			return result;
		}

		std::pair<_vector<_Type>&&, _vector<_Type>> split(size_t pos) && {
			size_t rightSize = size_ > pos ? size_ - pos : 0;
			size_ -= rightSize;
			std::pair<_vector<_Type>&&, _vector<_Type>> result{_rvthis, _vector<_Type>(rightSize, rightSize)};
			::memcpy(result.second.data_, data_ + pos, rightSize * sizeof(_Type));
			return result;
		}

		//TODO _vector<_Type>& split(size_t pos, _vector<_Type>& v1, _vector<_Type>& v2)

	protected:
		FORCEINLINE void clear_resize_(size_t newSize) {
			clear_reserve_(newSize);
			size_ = newSize;
		}


		void zero_reserve_(size_t capacity) {
		#if _RESERVE_CHECK_NULLPTR
			if (data_ == nullptr) {
				data_ = zero_allocate_(capacity);
				reserved_ = capacity;
			} else {
				_destruct_all();
				if (reserved_ < capacity) {
					deallocate_(data_);
					data_ = zero_allocate_(capacity);
					reserved_ = capacity;
				}
			}
		#else
			_destruct_all();
			if (reserved_ < capacity) {
				deallocate_(data_);
				data_ = zero_allocate_(capacity);
				reserved_ = capacity;
			}
		#endif
		}


		FORCEINLINE void zero_resize_(size_t newSize) {
			zero_reserve_(newSize);
			size_ = newSize;
		}


		void clear_reserve_(size_t capacity) {
		#if _RESERVE_CHECK_NULLPTR
			if (data_ == nullptr) {
				data_ = allocate_(capacity);
				reserved_ = capacity;
			} else {
				_destruct_all();
				if (reserved_ < capacity) {
					deallocate_(data_);
					data_ = allocate_(capacity);
					reserved_ = capacity;
				}
				//	reallocate_(capacity);
			}
		#else
			_destruct_all();
			if (reserved_ < capacity) {
				deallocate_(data_);
				data_ = allocate_(capacity);
				reserved_ = capacity;
			}
		#endif
		}


		//MEMBER_TEST(has_addeq_op_, operator+=);
		//MEMBER_TEST(has_add_op_, operator+);

		template<unsigned _depth>
		using nested_type_t = x::nested_type_t<_vector<_Type>, _depth>;


	public:
		template<unsigned _depth = 1>
		auto sum() const {
			if constexpr (_depth == 0)
				return *this;
			else if constexpr (_depth == 1) {
				_Type result = _Type();
				_const_foreach(e)
					result += *e;
				return result;
			} else {
				nested_type_t<_depth> result = nested_type_t<_depth>();
				_const_foreach(e)
					result += e->sum<_depth - 1>();
				return result;
			}
		}


		template<unsigned _depth = 1, class _Accum>
		FORCEINLINE _Type accumulate(_Accum&& accum) const {
			return accumulate<_depth>(_Type(), (_Accum&&)accum);
		}


		template<unsigned _depth = 1, class _Accum>
		_Type accumulate(_TypeConst base, _Accum&& accum) const {
			if constexpr (_depth == 0)
				return *this;
			else if constexpr (_depth == 1) {
				_Type result = base;
				_const_foreach(e)
					accum(result, *e);
				return result;
			} else {
				nested_type_t<_depth> result = base;
				_const_foreach(e)
					accum(result, e->accumulate<_depth - 1>(base, (_Accum&&)accum));
				return result;
			}
		}


		//TODO extend invoke on references etc...
		template<unsigned _depth = 1, class _Func, class... _Arg, class _Res = std::invoke_result_t<_Func, nested_type_t<_depth>>>
		FORCEINLINE _Res sum_compute(_Func&& func, _Arg&&... args) const {
			return sum_compute<_depth>(_Res(), (_Func&&)func, (_Arg&&)args...);
		}


		template<unsigned _depth = 1, class _Func, class... _Arg, class _Res = std::invoke_result_t<_Func, nested_type_t<_depth>>>
		_Res sum_compute(_Res&& base, _Func&& func, _Arg&&... args) const {
			if constexpr (_depth == 0)
				return func(*this);
			else if constexpr (_depth == 1) {
				_Res result = (_Res&&)base;
				_const_foreach(e)
					result += func(*e, (_Arg&&)args...);
				return result;
			} else {
				nested_type_t<_depth> result = base;
				_const_foreach(e)
					result += func(e->sum_compute<_depth - 1>((_Res&&)base, (_Func&&)func, (_Arg&&)args...));
				return result;
			}
		}


		template<unsigned _depth = 1, class _Func, class _Accum, class... _Arg, class _Res = std::invoke_result_t<_Func, nested_type_t<_depth>>>
		FORCEINLINE _Res accumulate_compute(_Accum&& accum, _Func&& func, _Arg&&... args) const {
			return accumulate_compute<_depth>(_Res(), (_Accum&)accum, (_Func&&)func, (_Arg&&)args...);
		}


		template<unsigned _depth = 1, class _Func, class _Accum, class... _Arg, class _Res = std::invoke_result_t<_Func, nested_type_t<_depth>>>
		_Res accumulate_compute(_Res&& base, _Accum&& accum, _Func&& func, _Arg&&... args) const {
			if constexpr (_depth == 0)
				return func(*this);
			else if constexpr (_depth == 1) {
				_Res result = (_Res&&)base;
				_const_foreach(e)
					accum(result, func(*e, (_Arg&&)args...));
				return result;
			} else {
				nested_type_t<_depth> result = base;
				_const_foreach(e)
					accum(result, func(e->accumulate_compute<_depth - 1>((_Res&&)base, (_Accum&&)accum, (_Func&&)func, (_Arg&&)args...)));
				return result;
			}
		}


		template<class _Res = _Type>
		_Res average() const {
			return (_Res)sum() / size_;
		}


		template<class _Res = _Type, class _Func>
		_Res average(_Func&& func) const {
			return (_Res)sum_compute((_Func&&)func) / size_;
		}

		/// <summary>
		/// Generates the vector's content basing on a given function calculated over a range of
		/// iterable values. The function will be executed on every value from \a begin to
		/// value \a end with delta \a d and the results of execution will become the vector's data.
		/// If there is more memory needed it will be allocated.
		/// If the \a _Iter type has no += operator, this function template will fail to compile.
		/// </summary>
		/// <typeparam name="_Func">deduced type of function, lambda of functor object</typeparam>
		/// <typeparam name="_Iter">type used for iteration over range</typeparam>
		/// <param name="func">function to be executed over range</param>
		/// <param name="begin">the beginning of generation range</param>
		/// <param name="end">the end of generation range</param>
		/// <param name="d">delta in iteration</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode, class _Func, class _Iter>
		_vector<_Type>& generate(_Func&& func, _Iter begin, _Iter end, _Iter d) & {
			_destruct_all();
			//? what about flaot...
			reallocate_(size_t(abs((end - begin) / d)) + 1);  
			size_ = reserved_;
			_Iter x = begin;
			_foreach(e) {
				_construct(e, func(x));
				x += d;
			}
			return *this;
		}

		template<class _Func, class _Iter>
		_vector<_Type>&& generate(_Func&& func, _Iter begin, _Iter end, _Iter d) && {
			return _rv(generate((_Func&&)func, begin, end, d));
		}

		/// <summary>
		/// Generates the vector's content basing on a given function calculated over a range of
		/// iterable values. The function will be executed on every value from \a begin with delta \a d 
		/// and the results of execution will become the vector's data of the current size, so
		/// the first element becomes <code>begin</code> and the last becomes <code>begin + d*size()</code>.
		/// No more memory is allocated. If a numeric limit of the \a _Iter type is exceeded,
		/// the behaviour is undefined. If the \a _Iter type has no += operator, this function template 
		/// will fail to compile.
		/// </summary>
		/// <typeparam name="_Func">deduced type of function, lambda of functor object</typeparam>
		/// <typeparam name="_Iter">type used for iteration over range</typeparam>
		/// <param name="func">function to be executed over range</param>
		/// <param name="begin">the beginning of generation range</param>
		/// <param name="d">delta in iteration</param>
		/// <returns>reference to the caller</returns>
		template<class _Func, class _Iter>
		_vector<_Type>& generate(_Func&& func, _Iter begin, _Iter d) & {
			_Iter x = begin;
			_foreach(e) {
				_reconstruct(e, func(x));
				x += d;
			}
			return *this;
		}

		template<class _Func, class _Iter>
		_vector<_Type>&& generate(_Func&& func, _Iter begin, _Iter d) && {
			return _rv(generate((_Func&&)func, begin, d));
		}


		template<class _Func, class _Arg>
		_vector<_Type>& generate(_Func&& func, _vector<_Arg> const& args) & {
			clear_resize_(args.size_);
			_pair_foreach(*this, e, args, a)
				_construct(e, func(*a));
			return *this;
		}

		template<class _Func, class _Arg>
		FORCEINLINE _vector<_Type>&& generate(_Func&& func, _vector<_Arg> const& args) && {
			return _rv(generate((_Func&&)func, args));
		}

	private:
		template<mode_t _mode = _DefaultMode, class _First, class... _Rest>
		_vector<_Type>& uniform_generate_impl_(iterative_range<atomic_type> const& range, _First first, _Rest... sizes) {
			static_assert(sizeof...(_Rest) == DIM_ - 2);
			if constexpr (_mode_set(NoSizeCheck))
				size_ = first;
			else
				zero_resize_(first);
			_foreach(v)
				v->uniform_generate_impl_<_mode>(range, sizes...);
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		void uniform_generate_impl_(iterative_range<atomic_type> const& range) {
			if constexpr (!_mode_set(NoSizeCheck))
				clear_resize_(x::ct::abs((range.to - range.from) / range.step) + 1);
			else
				size_ = x::ct::abs((range.to - range.from) / range.step) + 1;
			_Type x = range.from;
			_foreach(e) {
				_construct(e, x);
				x += range.step;
			}
		}

	public:
		template<mode_t _mode = _DefaultMode, class... _Size>
		FORCEINLINE _vector<_Type>& uniform_generate(iterative_range<atomic_type> const& range, _Size... sizes) {
			uniform_generate_impl_<_mode>(range, sizes...);
			return *this;
		}

		/*template<mode_t _mode = _DefaultMode>
		_vector<_Type>& uniform_generate(_TypeConst from, _TypeConst to, _TypeConst d) & {
			if constexpr (!_mode_set(NoSizeCheck)) {
				size_ = x::ct::abs((to - from) / d) + 1;
				clear_reserve_(size_);
			}
			_Type x = from;
			_foreach(e) {
				_construct(e, x);
				x += d;
			}
			return *this;
		}*/

		/*template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& uniform_generate(_TypeConst from, _TypeConst to, _TypeConst d) && {
			return _rv(generate<_mode>(from, to, d));
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& uniform_generate(_TypeConst from, _TypeConst to) & {
			return generate<_mode>(from, to, _Type(1));
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& uniform_generate(_TypeConst from, _TypeConst to) && {
			return _rv(generate<_mode>(from, to, 1));
		}*/


		template<class _Iter>
		_vector<_Type>& uniform_fill(_Iter begin, _Iter step) & {
			_foreach(e) {
				_destruct(e);
				_construct(e, begin);
				begin += step;
			}
			return *this;
		}

		template<class _Iter>
		FORCEINLINE _vector<_Type>&& uniform_fill(_Iter begin, _Iter step) && {
			return _rv(uniform_fill(begin, step));
		}


		template<class _Iter>
		_vector<_Type>& uniform_fill(_Iter begin) & {
			_foreach(e) {
				_destruct(e);
				_construct(e, begin);
				++begin;
			}
			return *this;
		}


		template<class _Iter>
		FORCEINLINE _vector<_Type>&& uniform_fill(_Iter begin) && {
			return _rv(uniform_fill(begin));
		}


		template<class _Iter = _Type>
		FORCEINLINE _vector<_Type>& uniform_fill() & {
			if constexpr (std::is_trivially_destructible_v<_Type> && std::is_trivially_copy_assignable_v<_Type>) {
				for (_Iter i = 0; i < (_Iter)size_; ++i)
					data_[i] = i;
			} else {
				for (_Iter i = 0; i < (_Iter)size_; ++i) {
					_destruct(data_ + i);
					_construct(data_ + i, i);
				}
			}
			return *this;
		}

		template<class _Iter = _Type>
		FORCEINLINE _vector<_Type>&& uniform_fill() && {
			return _rv(uniform_fill());
		}


		template<class _Func>
		_vector<_Type>& reconstruct(_Func&& func) & {
			if constexpr (std::is_trivially_destructible_v<_Type>) {
				_foreach(e)
					_construct(e, func(*e));
			} else {
				uint8_t temp[sizeof(_Type)];
				_foreach(e) {
					_construct(&temp, func(*e));
					_destruct(e);
					_trivcopy(e, temp);
				}
			}
			return *this;
		}


		template<class _Func>
		FORCEINLINE _vector<_Type>&& reconstruct(_Func&& func) && {
			return _rv(reconstruct((_Func&&)func));
		}



	private:
		template<class _Func>
		FORCEINLINE _Type* init_generate_sequence_(_Func&& func) {
			return data_;
		}

		template<class _Func, class _Arg0>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0) {
			_construct(data_, func(arg0));
			return data_ + 1;
		}

		template<class _Func, class _Arg0, class _Arg1>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0, _Arg1&& arg1) {
			_Type* e = data_;
			_construct(e, func(arg0, arg1));
			if (size_ > 1) {
				//{ if constexpr (std::is_trivially_copyable_v<_Type>) { *(++e) = _Type(func(arg1, data_[0])); } else { new (++e) _Type(func(arg1, data_[0])); } }
				_construct(++e, func(arg1, data_[0]));
			} else
				return ++e;
			return ++e;
		}

		template<class _Func, class _Arg0, class _Arg1, class _Arg2>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0, _Arg1&& arg1, _Arg2&& arg2) {
			_Type* e = data_;
			_construct(e, func(arg0, arg1, arg2));
			if (size_ > 1) {
				_construct(++e, func(arg1, arg2, data_[0]));
			} else
				return ++e;
			if (size_ > 2) {
				_construct(++e, func(arg2, data_[0], data_[1]));
			} else
				return ++e;
			return ++e;
		}


		template<class _Func, class _Arg0, class _Arg1, class _Arg2, class _Arg3>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0, _Arg1&& arg1, _Arg2&& arg2, _Arg3&& arg3) {
			_Type* e = data_;
			_construct(e, func(arg0, arg1, arg2, arg3));
			if (size_ > 1) {
				_construct(++e, func(arg1, arg2, arg3, data_[0]));
			} else
				return ++e;
			if (size_ > 2) {
				_construct(++e, func(arg2, arg3, data_[0], data_[1]));
			} else
				return ++e;
			if (size_ > 3) {
				_construct(++e, func(arg3, data_[0], data_[1], data_[2]));
			} else
				return ++e;
			return ++e;
		}


		template<class _Func, class _Arg0, class _Arg1, class _Arg2, class _Arg3, class _Arg4>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0, _Arg1&& arg1, _Arg2&& arg2, _Arg3&& arg3, _Arg4&& arg4) {
			_Type* e = data_;
			_construct(e, func(arg0, arg1, arg2, arg3, arg4));
			if (size_ > 1) {
				_construct(++e, func(arg1, arg2, arg3, arg4, data_[0]));
			} else
				return ++e;
			if (size_ > 2) {
				_construct(++e, func(arg2, arg3, arg4, data_[0], data_[1]));
			} else
				return ++e;
			if (size_ > 3) {
				_construct(++e, func(arg3, arg4, data_[0], data_[1], data_[2]));
			} else
				return ++e;
			if (size_ > 4) {
				_construct(++e, func(arg4, data_[0], data_[1], data_[2], data_[3]));
			} else
				return ++e;
			return ++e;
		}


		template<class _Func, class _Arg0, class _Arg1, class _Arg2, class _Arg3, class _Arg4, class _Arg5>
		_Type* init_generate_sequence_(_Func&& func, _Arg0&& arg0, _Arg1&& arg1, _Arg2&& arg2, _Arg3&& arg3, _Arg4&& arg4, _Arg5&& arg5) {
			_Type* e = data_;
			_construct(e, func(arg0, arg1, arg2, arg3, arg4, arg5));
			if (size_ > 1) {
				_construct(++e, func(arg1, arg2, arg3, arg4, arg5, data_[0]));
			} else
				return ++e;
			if (size_ > 2) {
				_construct(++e, func(arg2, arg3, arg4, arg5, data_[0], data_[1]));
			} else
				return ++e;
			if (size_ > 3) {
				_construct(++e, func(arg3, arg4, arg5, data_[0], data_[1], data_[2]));
			} else
				return ++e;
			if (size_ > 4) {
				_construct(++e, func(arg4, arg5, data_[0], data_[1], data_[2], data_[3]));
			} else
				return ++e;
			if (size_ > 5) {
				_construct(++e, func(arg5, data_[0], data_[1], data_[2], data_[3], data_[4]));
			} else
				return ++e;
			return ++e;
		}


		template<size_t _argnum, class _Func>
		FORCEINLINE void generate_sequence_elem_(_Type* ptr, _Func&& func) {
			if constexpr (_argnum == 0) {
				_construct(ptr, func());
			} else if constexpr (_argnum == 1) {
				_construct(ptr, func(ptr[-1]));
			} else if constexpr (_argnum == 2) {
				_construct(ptr, func(ptr[-1], ptr[-2]));
			} else if constexpr (_argnum == 3) {
				_construct(ptr, func(ptr[-1], ptr[-2], ptr[-3]));
			} else if constexpr (_argnum == 4) {
				_construct(ptr, func(ptr[-1], ptr[-2], ptr[-3], ptr[-4]));
			} else if constexpr (_argnum == 5) {
				_construct(ptr, func(ptr[-1], ptr[-2], ptr[-3], ptr[-4], ptr[-5]));
			} else if constexpr (_argnum == 6) {
				_construct(ptr, func(ptr[-1], ptr[-2], ptr[-3], ptr[-4], ptr[-5], ptr[-6]));
			} else {
				static_assert(false, "The maximum number of arguments for the sequence generating function is 6.");
			}
		}

	public:
		template<class _Func, class... _Arg>
		_vector<_Type>& generate_sequence(_Func&& func, size_t size, _Arg&&... initialArgs) {
			if (size == 0) {
				clear();
				return *this;
			}
			clear_resize_(size);
			_Type* e = init_generate_sequence_(func, (_Arg&&)initialArgs...);
			_foreach_from_i(e)
				generate_sequence_elem_<sizeof...(_Arg)>(e, func);
			return *this;
		}


		/// <summary>
		/// Equivalent to subset(0, n-1). Creates a vector containing \a n first elements of the caller
		/// vector. If the vector is empty, empty vector is returned. If \a n is greater than
		/// the size of the vector, a full copy is returned.
		/// </summary>
		/// <param name="n">number of elements to copy from the beginning of vector</param>
		/// <returns>vector containing \a n first elements</returns>
		FORCEINLINE _vector<_Type> const& front(size_t n) const {
			return subset_view(0, n - 1);
		}


		FORCEINLINE _Type& front() & {
			return data_[0];
		}


		FORCEINLINE _Type const& front() const & {
			return data_[0];
		}


		FORCEINLINE _Type&& front() && {
			return (_Type&&)data_[0];
		}


		/// <summary>
		/// Equivalent to subset(size() - n). Creates a vector containing \a n last elements of the caller
		/// vector. If the vector is empty, empty vector is returned. If \a n is greater than
		/// the size of the vector, a full copy is returned.
		/// </summary>
		/// <param name="n">number of elements to copy from the end of vector</param>
		/// <returns>vector containing \a n last elements</returns>
		FORCEINLINE _vector<_Type> const& back(size_t n) const {
			return subset_view(size_ - n, size_ - 1);
		}

		FORCEINLINE _Type& back() & {
			return data_[size_ - 1];
		}


		FORCEINLINE _Type const& back() const & {
			return data_[size_ - 1];
		}


		FORCEINLINE _Type&& back() && {
			return (_Type&&)data_[size_ - 1];
		}


		FORCEINLINE _Type& penult() & {
			return data_[size_ - 2];
		}


		FORCEINLINE _Type const& penult() const & {
			return data_[size_ - 2];
		}


		FORCEINLINE _Type&& penult() && {
			return (_Type&&)data_[size_ - 2];
		}


		FORCEINLINE _Type& second() & {
			return data_[1];
		}


		FORCEINLINE _Type const& second() const & {
			return data_[1];
		}


		FORCEINLINE _Type&& second() && {
			return (_Type&&)data_[1];
		}


		_vector_nd_t<size_t, DIM_ - 1> sizes() const {
			if constexpr (DIM_ == 1)
				return size_;
			else {
				_vector_nd_t<size_t, DIM_ - 1> result(size_);
				result.size_ = result.reserved_;
				if constexpr (DIM_ == 2) {
					_pair_foreach(*this, v, result, r)
						*r = v->size_;
				} else {
					using V = _vector_nd_t<size_t, DIM_ - 2>;
					_pair_foreach(*this, v, result, r)
						_construct_t(V, r, v->sizes());
				}
				return result;
			}
		}


		//! internal error
		/*_vector_nd_t<size_t, DIM_ - 1> sizes() const {
		if constexpr (DIM_ == 1)
		return size_;
		else {
		_vector_nd_t<size_t, DIM_ - 1> result(size_);
		result.size_ = result.reserved_;
		if constexpr (DIM_ == 2) {
		_pair_foreach(*this, v, result, r)
		*r = v->size_;
		} else if (DIM_ > 2) {
		_pair_foreach(*this, v, result, r)
		_construct_t(_vector_nd_t<size_t, DIM_ - 1>, r, v->sizes());
		}
		return result;
		}
		}*/


		/// <summary>
		/// The assignment operator. Copies data of right-hand side vector to the left-hand side.
		/// </summary>
		/// <remarks>
		/// If the right-hand side vector is empty, the vector is cleared, no memory is copied nor deallocated.
		/// </remarks>
		/// <param name="other">the vector to be copied</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& operator=(_vector<_Type> const& other) & {
			if (other.size_ > 0) {
				clear_resize_(other.size_);
				copy_(data_, other.data_, size_);
				return *this;
			} else {
				return clear();
			}
		}

		FORCEINLINE _vector<_Type>&& operator=(_vector<_Type> const& other) && {
			return _rv(operator=(other));
		}


		/// <summary>
		/// The move assignment operator. Moves data of right-hand side vector to the left-hand side.
		/// </summary>
		/// <remarks>
		/// Deallocates current memory and sets handled data and parameters of vector to the moved one's.
		/// The moved vector is made permanently unusable.
		/// </remarks>
		/// <param name="other">the moved vector</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& operator=(_vector<_Type> && other) & {
			if (other.reserved_ > 0) {
				//? check unnecessary?
				//if (data_) {
					_destruct_all();
					deallocate_();
				//}
				reserved_ = other.reserved_;
				size_ = other.size_;
				data_ = other.data_;
				other.data_ = nullptr;
			} else {
				_destruct_all();
				size_ = 0;
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& operator=(_vector<_Type>&& other) && {
			return _rv(operator=(other.move()));
		}



		/// <summary>
		/// The assignment operator setting vector to containing one given element.
		/// </summary>
		/// <remarks>
		/// Deallocates current memory and allocates memory of capacity = 1. The given value
		/// becomes the only element.
		/// </remarks>
		/// <param name="value">element to be set</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& operator=(_Type const& value) & {
			clear_resize_(1);
			_construct(data_, value);
			return *this;
		}

		_vector<_Type>&& operator=(_Type const& value) && {
			clear_resize_(1);
			_construct(data_, value);
			return _rvthis;
		}

		_vector<_Type>& operator=(_Type&& value) & {
			clear_resize_(1);
			_construct(data_, (_Type&&)value);
			return *this;
		}

		_vector<_Type>&& operator=(_Type&& value) && {
			clear_resize_(1);
			_construct(data_, (_Type&&)value);
			return _rvthis;
		}


		template<class _Elem>
		_vector<_Type>& operator=(std::initializer_list<_Elem> elements) & {
			clear_resize_(elements.size());
			copy_initializer_list_(data_, elements.begin(), elements.end());
			return *this;
		}

		template<class _Elem>
		FORCEINLINE _vector<_Type>&& operator=(std::initializer_list<_Elem> elements) && {
			return _rv(operator=(elements));
		}


		_vector<_Type>& operator=(std::initializer_list<_Type> elements) & {
			clear_resize_(elements.size());
			copy_initializer_list_(data_, elements.begin(), elements.end());
			return *this;
		}

		FORCEINLINE _vector<_Type>&& operator=(std::initializer_list<_Type> elements) && {
			return _rv(operator=(elements));
		}


		template<mode_t _mode = _DefaultMode>
		_Type* mempush() {
			_assert_mode(Default, Naked, NoSizeCheck);
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_)
					extend();
			}
			return data_ + size_++;
		}


		/// <summary>
		/// Appends a copy of given object at the end of vector.
		/// </summary>
		/// <param name="newElem">element to be added at the end</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_back(_Type const& elem) & {
			_assert_mode(Default, Naked, NoSizeCheck);
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_)
					extend();
			}
			_construct(data_ + size_++, elem);
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& push_back(_Type const& elem) && {
			return _rv(push_back<_mode>(elem));
		}

		/// <summary>
		/// Appends moved object at the end of vector.
		/// </summary>
		/// <param name="newElem">element to be added at the end</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_back(_Type && elem) & {
			_assert_mode(Default, Naked, NoSizeCheck);
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_)
					extend();
			}
			_construct(data_ + size_++, (_Type&&)elem);
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& push_back(_Type && elem) && {
			return _rv(push_back<_mode>((_Type&&)elem));
		}

		/// <summary>
		/// Appends a default constructed object at the end of vector.
		/// </summary>
		/// <returns>reference to the caller</returns>		
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_back() & {
			_assert_mode(Default, Naked, NoSizeCheck);
			if constexpr (!_mode_set(NoSizeCheck))
				if (size_ >= reserved_)
					extend();
			_construct(data_ + size_);
			++size_;
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& push_back() && {
			return _rv(push_back<_mode>());
		}

		/// <summary>
		/// Appends a copy of given object at the beginning of vector.
		/// </summary>
		/// <param name="newElem">element to be added at the beginning</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_front(_Type const& value) & {
			if constexpr(!_mode_set(NoSizeCheck)) {
				if (size_ == reserved_) {
					reserved_ = extended_capacity_(reserved_);
					_Type* newdata = allocate_(reserved_);
					::memcpy(newdata + 1, data_, size_ * sizeof(_Type));
					_construct(newdata, value);
					deallocate_(data_);
					data_ = newdata;
				} else {
					::memmove(data_ + 1, data_, size_ * sizeof(_Type));
					_construct(data_, value);
				}
			} else {
				::memmove(data_ + 1, data_, size_ * sizeof(_Type));
				_construct(data_, value);
			}
			++size_;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& push_front(_Type const& value) && {
			return _rv(push_front(value));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_front(_Type&& value) & {
			if constexpr(!_mode_set(NoSizeCheck)) {
				if (size_ == reserved_) {
					reserved_ = extended_capacity_(reserved_);
					_Type* newdata = allocate_(reserved_);
					::memcpy(newdata + 1, data_, size_ * sizeof(_Type));
					_construct(newdata, (_Type&&)value);
					deallocate_(data_);
					data_ = newdata;
				} else {
					::memmove(data_ + 1, data_, size_ * sizeof(_Type));
					_construct(data_, (_Type&&)value);
				}
			} else {
				::memmove(data_ + 1, data_, size_ * sizeof(_Type));
				_construct(data_, (_Type&&)value);
			}
			++size_;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& push_front(_Type&& value) && {
			return _rv(push_front(value));
		}


		/// <summary>
		/// Appends a default constructed object at the beginning of vector.
		/// </summary>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& push_front() & {
			if constexpr(!_mode_set(NoSizeCheck)) {
				if (size_ == reserved_) {
					reserved_ = extended_capacity_(reserved_);
					_Type* newdata = allocate_(reserved_);
					::memcpy(newdata + 1, data_, size_ * sizeof(_Type));
					_construct(newdata);
					deallocate_(data_);
					data_ = newdata;
				} else {
					::memmove(data_ + 1, data_, size_ * sizeof(_Type));
					_construct(data_);
				}
			} else {
				::memmove(data_ + 1, data_, size_ * sizeof(_Type));
				_construct(data_);
			}
			++size_;
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& push_front() && {
			return _rv(push_front());
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& set(size_t i, _Type const& value) {
			_assert_mode(Default, Naked, NoIndexCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (i > size_) {
					if (i > reserved_)
						reallocate_(i + 1);
					_construct(data_ + i, value);
					size_ = i + 1;
				} else
					_reconstruct(data_ + i, value);
			} else if constexpr (mode_Set(NoIndexCheck)) {
				_reconstruct(data_ + i, value);
			}
			return *this;
		}


		template<mode_t _mode = _DefaultMode, class... _Arg>
		_vector<_Type>& construct_back(_Arg&&... args) {
			_assert_mode(Default, Naked);
			if constexpr (_mode == Default) {
				if (size_ >= reserved_)
					extend();
			}
			_construct(data_ + size_++, (_Arg&&)args...);
			return *this;
		}


		template<class... _Arg>
		FORCEINLINE _vector<_Type>& construct_front(_Arg&&... args) {
			return construct(0, (_Arg&&)args...);
		}


		template<class... _Arg>
		_vector<_Type>& construct(size_t pos, _Arg&&... args) {
			if (pos > size_)
				pos = size_;
			if (size_ >= reserved_) {
				reserved_ = extended_capacity_(reserved_);
				_Type* newData = allocate_(reserved_);
				::memcpy(newData + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
				_construct(newData + pos, (_Arg&&)args...);
				::memcpy(newData, data_, pos * sizeof(_Type));
				delete[] reinterpret_cast<__int8*>(data_);
				data_ = newData;
			} else {
				::memcpy(data_ + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
				_construct(data_ + pos, (_Arg&&)args...);
			}
			++size_;
			return *this;
		}

		/// <summary>
		/// Inserts copy of given element at the position \a pos, moving all following elements 
		/// one place forward. If the specified position is greater than size of vector, the 
		/// element is appended at the end of vector so the behavior of function becomas equal 
		/// to push_back. The size of vector is incremented by 1.
		/// </summary>
		/// <param name="newElem">the element to be inserted to vector</param>
		/// <param name="pos">the position to insert new element</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& insert(const _Type& elem, size_t pos) & {
			_assert_mode(Default, Naked, NoIndexCheck, NoSizeCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (pos > size_)
					return push_back(elem);
			}
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_) {
					reserved_ = extended_capacity_(reserved_);
					_Type* newData = allocate_(reserved_);
					::memcpy(newData + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
					_construct(newData + pos, elem);
					::memcpy(newData, data_, pos * sizeof(_Type));
					delete[] reinterpret_cast<__int8*>(data_);
					data_ = newData;
				} else {
					::memcpy(data_ + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
					_construct(data_ + pos, elem);
				}
			} else {
				::memcpy(data_ + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
				_construct(data_ + pos, elem);
			}
			++size_;
			return *this;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& insert(const _Type& elem, size_t pos) && {
			_assert_mode(Default, Naked, NoIndexCheck, NoSizeCheck);
			return _rv(insert<_mode>(elem, pos));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& insert(_Type&& elem, size_t pos) & {
			_assert_mode(Default, Naked, NoIndexCheck, NoSizeCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (pos >= size_)
					return push_back((_Type&&)elem);
			}
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_) {
					reserved_ = extended_capacity_(reserved_);
					_Type* newData = allocate_(reserved_);
					::memcpy(newData + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
					_construct(newData + pos, (_Type&&)elem);
					::memcpy(newData, data_, pos * sizeof(_Type));
					deallocate_();
					data_ = newData;
				} else {
					::memcpy(data_ + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
					_construct(data_ + pos, (_Type&&)elem);
				}
			} else if constexpr (_mode_set(NoSizeCheck)) {
				::memcpy(data_ + pos + 1, data_ + pos, (size_ - pos) * sizeof(_Type));
				_construct(data_ + pos, (_Type&&)elem);
			}
			++size_;
			return *this;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& insert(_Type&& elem, size_t pos) && {
			_assert_mode(Default, Naked, NoIndexCheck, NoSizeCheck);
			return _rv(insert<_mode>((_Type&&)elem, pos));
		}

		/// <summary>
		/// Inserts copy of given vector at the position \a pos, moving all following elements 
		/// forward number of places equal to \a other's size. If the specified position is greater 
		/// than size of vector, the \a other vector is appended at the end of vector so the behavior 
		/// of function becomas equal to append. The size of vector is incremented by the size of \a other.
		/// </summary>
		/// <param name="other">the vector to be inserted</param>
		/// <param name="pos">the position to insert vector's content</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& insert(_vector<_Type> const& other, size_t pos) & {
			if (pos >= size_)
				return append(other);
			if (reserved_ < size_ + other.size_) {
				reserved_ = size_ + other.size_;
				_Type* newData = allocate_(reserved_);
				::memcpy(newData + pos + other.size_, data_ + pos, (size_ - pos) * sizeof(_Type));
				copy_(newData + pos, other.data_, other.size_);
				::memcpy(newData, data_, pos * sizeof(_Type));
				deallocate_();
				data_ = newData;
			} else {
				::memcpy(data_ + pos + other.size_, data_ + pos, (size_ - pos) * sizeof(_Type));
				copy_(data_ + pos, other.data_, other.size_);
			}
			size_ += other.size_;
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& insert(_vector<_Type> const& other, size_t pos) && {
			return _rv(insert<_mode>(other, pos));
		}

		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& insert(_vector<_Type>&& other, size_t pos) & {
			if (pos >= size_)
				return append(other.move());
			size_t newSize = size_ + other.size_;
			if (reserved_ < newSize) {
				reserved_ = newSize;
				_Type* newData = allocate_(reserved_);
				::memcpy(newData + pos + other.size_, data_ + pos, (size_ - pos) * sizeof(_Type));
				::memcpy(newData + pos, other.data_, other.size_ * sizeof(_Type));
				::memcpy(newData, data_, pos * sizeof(_Type));
				deallocate_();
				data_ = newData;
			} else {
				::memcpy(data_ + pos + other.size_, data_ + pos, (size_ - pos) * sizeof(_Type));
				::memcpy(data_ + pos, other.data_, other.size_ * sizeof(_Type));
			}
			other.deallocate_();
			other.data_ = nullptr;
			size_ += other.size_;
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& insert(_vector<_Type>&& other, size_t pos) && {
			return _rv(insert<_mode>(other.move(), pos));
		}


	protected:
		template<class _Pred>
		size_t dump_remove_(_Pred&& pred, size_t max) {
			size_t nrem = 0;
			for (_Type* e = data_, end = data_ + size_; e < end; ) {
				if (pred(*e)) {
					_destruct(e);
					_trivcopy(e, data_ + --size_);
					if (++nrem == max) break;
				} else
					++e;
			}
			return 0;
		}

		/*_vector<_Type>& remove(_Type const& value) {
		_Type* a = data_;
		_Type* b;
		_Type* end = data_ + size_;
		while (a < end) {
		if (*a == value) {
		_destruct(a);
		b = a + 1;
		goto _CONTINUE_REMOVE_;
		}
		++a;
		}
		return *this;
		_CONTINUE_REMOVE_:
		while (b < end) {
		if (*b == value) {
		_destruct(b);
		++b;
		}
		else {
		_trivcopy(a, b);
		++a, ++b;
		}
		}
		size_ -= (b-a);
		return *this;
		}*/


		//===========LAST===================
		/*template<mode_t _mode = _DefaultMode, class _Verifier>
		size_t remove_(_Verifier&& verify, size_t max) {
		_assert_mode(Default, AllowReorder);
		if constexpr (_mode_set(AllowReorder)) {
		return dump_remove_((_Verifier&&)verify, max);
		}
		int i = -1;
		int lastp = -1;
		size_t nrem = 0;
		int diff;
		while (++i < size_) {
		if (verify(data_[i])) {
		_destruct(data_[i]);
		diff = i - nrem;
		if (diff > lastp) {
		::memcpy(data_ + lastp,
		data_ + lastp + nrem,
		sizeof(_Type)*(diff - lastp));
		lastp = diff;
		}
		if (++nrem == max) break;
		}
		}
		if (size_ - lastp - nrem) {
		::memcpy(data_ + lastp,
		data_ + lastp + nrem,
		sizeof(_Type)*(size_ - lastp - nrem));
		}
		size_ -= nrem;
		return nrem;
		}*/


		/*template<class _Verifier>
		int remove_(unsigned max) {
		int i = -1, lastp = -1, nrem = 0;
		while (++i < size_) {
		if (_Verifier::verify(data_[i])) {
		_destruct(data_[i]);

		if (i > lastp + nrem) {
		::memcpy(data_ + lastp,
		data_ + lastp + nrem,
		sizeof(_Type)*(i - lastp - nrem));
		lastp = i - nrem;
		}
		if (++nrem == max) break;
		}
		}
		if (size_ - lastp - nrem) {
		::memcpy(data_ + lastp,
		data_ + lastp + nrem,
		sizeof(_Type)*(size_ - lastp - nrem));
		}
		size_ -= nrem;
		return nrem;
		}*/



	public:
		template<unsigned _depth = 1, class _Value = _Type>
		INLINE _vector<_Type>& remove(_Value const& value) & {
			_validate_depth;
			return remove_if<_depth>([&value](_Type const& e) { return e == value; });
		}

		template<unsigned _depth = 1, class _Value = _Type>
		INLINE _vector<_Type>&& remove(_Value const& value) && {
			_validate_depth;
			return _rv(remove_if<_depth>([&value](_Type const& e) { return e == value; }));
		}


		template<unsigned _depth = 1, class _Pred, class... _Arg>
		_vector<_Type>& remove_if(_Pred&& pred, _Arg&&... args) & {
			_validate_depth;
			if constexpr (_depth == 1) {
				_Type* a = data_;
				_Type* b;
				_Type* end = pend();
				while (a < end) {
					if (pred(*a, (_Arg&&)args...)) {
						_destruct(a);
						b = a + 1;
						goto _CONTINUE_REMOVE_;
					}
					++a;
				}
				return *this;
			_CONTINUE_REMOVE_:
				while (b < end) {
					if (pred(*b, (_Arg&&)args...)) {
						_destruct(b);
						++b;
					} else {
						_trivcopy(a, b);
						++a, ++b;
					}
				}
				size_ -= (b - a);
				return *this;
			} else {
				_foreach(v)
					v->remove_if<_depth - 1>(pred, (_Arg&&)args...);
				return *this;
			}
		}

		template<unsigned _depth = 1, class _Pred, class... _Arg>
		FORCEINLINE _vector<_Type>&& remove_if(_Pred&& pred, _Arg&&... args) && {
			return _rv(remove_if<_depth>(pred, (_Arg&&)args...));
		}

		template<unsigned _depth = 1, class _Member, class _T>
		INLINE _vector<_Type>& remove_by(_Member(_T::*member), _Member const& value) & {
			return remove_if<_depth>([member, &value](_Type const& e) { return (e.*member) == value; });
		}

		template<unsigned _depth = 1, class _Member, class _T>
		FORCEINLINE _vector<_Type>&& remove_by(_Member(_T::*member), _Member const& value) && {
			return _rv(remove_by<_depth>(member, value));
		}


		template<mode_t _mode = _DefaultMode, size_t _optStaticSize = 0>
		_vector<_Type>& remove_all(_vector<_Type> const& values, _TypeConst min, _TypeConst max) & {
			_assert_mode(Default, NoIndexCheck, NoDynamic);
			if constexpr (!_mode_set(NoDynamic)) {
				bool* removeMap = new bool[max - min + 1]{false};
				for (size_t i = 0; i < values.size_; ++i)
					removeMap[values.data_[i] - min] = true;
				remove_all<_mode & ~NoDynamic>(removeMap, min, max);
				delete[] removeMap;
				return *this;
			} else {
				bool removeMap[_optStaticSize]{false};
				for (size_t i = 0; i < values.size_; ++i)
					removeMap[values.data_[i] - min] = true;
				remove_all<_mode & ~NoDynamic>(removeMap, min, max);
				return *this;
			}
		}


		template<mode_t _mode = _DefaultMode, size_t _optStaticSize = 0>
		_vector<_Type>&& remove_all(_vector<_Type> const& values, _TypeConst min, _TypeConst max) && {
			_assert_mode(Default, NoIndexCheck, NoDynamic);
			return _rv(remove_all<_mode, _optStaticSize>(values, min, max));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& remove_all(bool const* removeMap, _TypeConst min, _TypeConst max) & {
			_assert_mode(Default, NoIndexCheck);
			_foreach(e) {
				if constexpr (!_mode_set(NoIndexCheck)) {
					if (beyond(*e, min, max))
						continue;
				}
				if (removeMap[*e - min]) {
					_destruct(e);
					_trivcopy(e, data_ + --size_);
				}
			}
			return *this;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& remove_all(bool const* removeMap, _TypeConst min, _TypeConst max) && {
			_assert_mode(Default, NoIndexCheck);
			return _rv(remove_all(removeMap, min, max));
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& remove_all(size_t const* removeMap, _TypeConst min, _TypeConst max) & {
			_assert_mode(Default, NoIndexCheck);
			_foreach(e) {
				if constexpr (!_mode_set(NoIndexCheck)) {
					if (beyond(*e, min, max))
						continue;
				}
				if (removeMap[*e - min]--) {
					_destruct(e);
					_trivcopy(e, data_ + --size_);
				}
			}
			return *this;
		}


		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& remove_all(size_t const* removeMap, _TypeConst min, _TypeConst max) && {
			_assert_mode(Default, NoIndexCheck);
			return _rv(remove_all<_mode>(removeMap, min, max));
		}


		/// <summary>
		/// Copies every occurence of the element for which the specified function returns true into a new
		/// instance of vector.
		/// </summary>
		/// <remarks>
		/// The amount of copied elements can be limited by specifying \a max. 
		/// The maximum number of elements to be copied set to 0 is equivalent to no limit, which is default.
		/// </remarks>
		/// <typeparam name="_Func">deduced type of function</typeparam>
		/// <param name="func">function deciding about copying of elements</param>
		/// <param name="max">maximum number of occurences to be copied, DEFAULT: 0 (no limit)</param>
		/// <returns>vector containing copied elements</returns>
		template<class _Func, class... _Arg>
		_vector<_Type> copy_if(_Func&& func, _Arg&&... args) const {
			_vector<_Type> result(size_);
			_Type* r = result.data_;
			_const_foreach(e) {
				if (func(*e, (_Arg&&)args...)) {
					_construct(r, *e);
					++r;
				}
			}
			result.size_ = r - result.data_;
			return result;
		}


		template<class _Member, class _T = _Type>
		_vector<_Type> copy_by(_Member(_T::*member), std::remove_const_t<_Member> const& value) const {
			_vector<_Type> result(size_);
			_Type* r = result.data_;
			_const_foreach(e) {
				if constexpr (std::is_pointer_v<_Type>) {
					if ((*e)->*member == value) {
						_construct(r, *e);
						++r;
					}
				} else {
					if (e->*member == value) {
						_construct(r, *e);
						++r;
					}
				}
			}
			result.size_ = r - result.data_;
			return result;
		}

		using ptr_t = std::conditional_t<std::is_pointer_v<_Type> && std::is_class_v<std::remove_pointer_t<_Type>>, _Type, _Type*>;
		using const_ptr_t = std::conditional_t<std::is_pointer_v<_Type> && std::is_class_v<std::remove_pointer_t<_Type>>, std::add_const_t<std::remove_pointer_t<_Type>>*, std::add_const_t<_Type>*>;


		template<class _Member, class... _Arg, class _T>
		_vector<_Type> copy_by(_Member(_T::*member)(_Arg...) const, std::remove_const_t<_Member> const& value, _Arg&&... args) const {
			_vector<_Type> result(size_);
			_Type* r = result.data_;
			if constexpr (std::is_same_v<_T, _Type>) {
				_const_foreach(e) {
					if ((e->*member)((_Arg&&)args...)) {
						_construct(r, *e);
						++r;
					}
				}
			} else if constexpr (std::is_same_v<_T, std::remove_pointer_t<_Type>>) {
				_const_foreach(e) {
					if (((*e)->*member)((_Arg&&)args...) == value) {
						_construct(r, *e);
						++r;
					}
				}
			} else {
				_const_foreach(v)
					result.push_back(v->copy_by(member, value, (_Arg&&)args...));
			}

			result.size_ = r - result.data_;
			return result;
		}


		template<class _Member, class... _Arg, class _T = _Type>
		FORCEINLINE _vector<_Type> copy_by(_Member(_T::*member)(_Arg...), std::remove_const_t<_Member> const& value, _Arg&&... args) {
			return copy_by(reinterpret_cast<_Member(_T::*)(_Arg...) const>(member), value, (_Arg&&)args...);
		}


		template<class _Pred, class... _Arg>
		_vector<_Type> extract_if(_Pred&& pred, _Arg&&... args) & {
			_Type* a = data_;
			_Type* b;
			_Type* end = pend();
			_vector<_Type> result(size_);
			_Type* r = result.data_;
			while (a < end) {
				if (pred(*a, (_Arg&&)args...)) {
					_trivcopy(r++, a);
					b = a + 1;
					goto _CONTINUE_REMOVE_;
				}
				++a;
			}
			return _vector<_Type>();
		_CONTINUE_REMOVE_:
			while (b < end) {
				if (pred(*b, (_Arg&&)args...))
					_trivcopy(r++, b++);
				else
					_trivcopy(a++, b++);
			}
			result.size_ = (b - a);
			size_ -= result.size_;
			return result.shrink();
		}

		template<class _Pred, class... _Arg>
		FORCEINLINE _vector<_Type>&& extract_if(_Pred&& pred, _Arg&&... args) && {
			return _rv(_rvthis.remove_if(x::pred::not(pred), (_Arg&&)args...));
		}


		template<class _Member, class _T>
		INLINE _vector<_Type> extract_by(_Member(_T::*member), _Member const& value) & {
			return extract_if([member, &value](_Type const& e) {
				return (e.*member) == value;
			});
		}

		template<class _Member, class _T>
		INLINE _vector<_Type>&& extract_by(_Member(_T::*member), _Member const& value) && {
			return remove_if([member, &value](_Type const& e) {
				return !((e.*member) == value);
			}).move();
		}


		template<class _Member, class _Func, class _T>
		_vector<_Member> extract_member_if(_Member(_T::*member), _Func&& func, size_t expected) const {
			_vector<_Member> extracted(expected);
			_foreach(e) {
				_Member const& mr = e->*member;
				if (func(mr))
					extracted.push_back(mr);
			}
			return extracted;
		}

		template<class _Member, class _Func, class _T>
		FORCEINLINE _vector<_Member> extract_member_if(_Member(_T::*member), _Func&& func) const {
			return extract_member_if(member, (_Func&&)func, size_ / 2 + 1);
		}


		template<class _Member, class _T>
		_vector<_Member> extract_member(_Member(_T::*member)) const {
			_vector<_Member> result(size_, size_);
			_pair_foreach(*this, e, result, r)
				_construct_t(_Member, r, e->*member);
			return result;
		}


		template<class _Member, class _T>
		_vector<_Member> extract_member(_Member(_T::*member), _Member const& newvalue) const {
			_vector<_Member> result(size_, size_);
			_pair_foreach(*this, e, result, r) {
				_trivcopy_t(_Member, r, e);
				_construct_t(_Member, e, newvalue);
			}
			return result;
		}


		/// <summary>
		/// Erases specified element fast, swapping it with the current last element.
		/// The size of vector is decreased by 1 and value of the element that has been 
		/// thrown is not destructed and remains at position of 1 place beyond the last and can be 
		/// accessed e.g. by the reference returned by function or <code>*vec.pend()</code> but 
		/// it is volatile and any vector transormation changing its size, reallocation memory, etc. 
		/// makes potential access to this element very unsafe or impossible. 
		/// The order of contained elements is not preserved. If specified position
		/// is greater than or equal to size of vector, the function returns result of invalid state.
		/// </summary>
		/// <param name="which">position of element to be thrown</param>
		/// <returns>reference to the throwed element</returns>
		/*_Type& throw_back(size_t i) & {
			x::swap(data_[i], data_[--size_]);
			return data_[size_];
		}

		_Type&& throw_back(size_t i) && {
			x::swap(data_[i], data_[--size_]);
			return (_Type&&)data_[size_];
		}*/

		_vector<_Type>& throw_back(size_t i) & {
			x::swap(data_[i], data_[size_ - 1]);
			return *this;
		}

		_vector<_Type>&& throw_back(size_t i) && {
			x::swap(data_[i], data_[size_ - 1]);
			return _rvthis;
		}


		/// <summary>
		/// Erases specified element fast by writing value of the last element.
		/// The size of vector is decreased by 1.
		/// If the given position is not accessible, this function does nothing.
		/// </summary>
		/// <param name="which">position of element to be removed</param>
		/// <returns>reference to the caller</returns>		
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& dump(size_t i) & {
			_assert_mode(Default, Naked, NoIndexCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (i >= size_)
					return *this;
			}
			_destruct(data_ + i);
			_trivcopy(data_ + i, data_ + (--size_));
			return *this;
		}

		template<mode_t _mode>
		FORCEINLINE _vector<_Type>&& dump(size_t i) && {
			return _rv(dump<_mode>(i));
		}


		/// <summary>
		/// Removes the first element from vector. If the vector is empty, this function does nothing.
		/// </summary>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& pop_front() & {
			if (size_ > 0) {
				_destruct(data_);
				if (--size_ > 0)
					::memcpy(data_, data_ + 1, size_ * sizeof(_Type));
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& pop_front() && {
			return _rv(pop_front());
		}

		/// <summary>
		/// Removes the last element from vector. If the vector is empty, this function does nothing.
		/// </summary>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& pop_back() & {
			if (size_ > 0)
				_destruct(data_ + (--size_));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& pop_back() && {
			return _rv(pop_back());
		}

		_vector<_Type>& pop_back(size_t n) & {
			n = x::min(n, size_);
			_Type* end = data_ + size_;
			size_ -= n;
			_destruct_range(data_ + size_, end);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& pop_back(size_t n) && {
			return _rv(pop_back(n));
		}

		_vector<_Type>& order(size_t i1, size_t i2) & {
			if (data_[i1] > data_[i2])
				x::swap(data_[i1], data_[i2]);
			return *this;
		}

		_vector<_Type>&& order(size_t i1, size_t i2) && {
			if (data_[i1] > data_[i2])
				x::swap(data_[i1], data_[i2]);
			return _rvthis;
		}

	protected:
	#if MODE(QuicksortPivot, Random)
		#if defined _M_X86
			#define _QUICKSORT_PIVOT(_pivot) _pivot = (_Type*)(random32(size_t(r1 + 1), size_t(r2), sizeof(_Type))); x::swapp(_pivot, r2)
		#elif defined _M_X64
			#define _QUICKSORT_PIVOT(_pivot) _pivot = (_Type*)(random64(size_t(r1 + 1), size_t(r2), sizeof(_Type))); x::swapp(_pivot, r2)
		#endif
	#elif MODE(QuicksortPivot, Split)
		#define _QUICKSORT_PIVOT(_pivot) _pivot = (r2 + r1) / 2; x::swapp(_pivot, r2)
	#elif MODE(QuicksortPivot, First)
		#define _QUICKSORT_PIVOT(_pivot) _pivot = r1; x::swapp(_pivot, r2)
	#elif MODE(QuicksortPivot, Last)
		#define _QUICKSORT_PIVOT(_pivot) _pivot = r2
	#endif


		template<size_t _lowlim = 18>
		static void quicksort_(_Type* r1, _Type* r2) {
			if (r2 - r1 > _lowlim) {
				_Type* pivot;
				_QUICKSORT_PIVOT(pivot);
				_Type* last = r2;
				
				for (_Type* e = r1; e < last; ++e) {
					if (*r2 < *e) {
						--last;
						while (e < last && *r2 < *last)
							--last;
						x::swapp(e, last);
					}
				}
				x::swapp(last, r2);
				if (r1 < last - 1) quicksort_<_lowlim>(r1, last - 1);
				if (last + 1 < r2) quicksort_<_lowlim>(last + 1, r2);
			} else {
				uint8_t temp[sizeof(_Type)];
				for (_Type* e = r1 + 1; e <= r2; ++e) {
					_trivcopy(reinterpret_cast<_Type*>(temp), e);
					_Type* o = e - 1;
					while (o >= r1 && *reinterpret_cast<_Type const*>(temp) < *o) {
						_trivcopy(o + 1, o);
						--o;
					}
					_trivcopy(o + 1, reinterpret_cast<_Type const*>(temp));
				}
			}
		}


		template<class _Func>
		void quicksort_(int r1, int r2, _Func&& comparator) {
			int last = r1;
			size_t pivot = random32(uint32_t(r1 + 1), uint32_t(r2));
			_Type& e2 = data_[r2];
			x::swap(data_[pivot], e2);
			for (_Type* e = data_ + r1, *end = data_ + r2; e <= end; ++e) {
				if (comparator(*e < e2)) {
					x::swap(*e, data_[last]);
					++last;
				}
			}
			x::swap(data_[last], e2);
			if (r1 < last - 1) quicksort_(r1, last - 1);
			if (last + 1 < r2) quicksort_(last + 1, r2);
		}


		void boolsort_asc_() {
			size_t ntrue = 0;
			_foreach(e)
				if (*e)
					++ntrue;
			size_t lsize = size_ - ntrue;
			memset(data_, 0, lsize);
			memset(data_ + lsize, 1, ntrue);
		}

		void boolsort_desc_() {
			size_t ntrue = 0;
			_foreach(e)
				if (*e)
					++ntrue;
			memset(data_, 0, ntrue);
			memset(data_ + ntrue, 1, size_ - ntrue);
		}

	public:
		_vector<_Type>& sort() & {
			if constexpr (std::is_same_v<_Type, bool>) {
				boolsort_asc_();
			} else {
				if (size_ > 1) {
					if constexpr (MODE(DefaultSortAlgorithm, Quicksort)) {
						quicksort();
					} else if constexpr (MODE(DefaultSortAlgorithm, Mergesort)) {
						mergesort();
					} else {
						static_assert(false, "Invalid value of DefaultSortAlgorithm");
					}
				}
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& sort() && {
			return _rv(sort());
		}

		_vector<_Type>& quicksort() & {
			if (size_ > 1)
				_quicksort(data_, data_ + size_ - 1);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& quicksort() && {
			return _rv(quicksort());
		}

		/// <summary>
		/// Uses quick sort on the specified range. The elements are sorted in order from the lowest
		/// to the highest by using operator &lt on pairs of them.
		/// If \a begin position &gt= \a end, this function does nothing.
		/// If \a end &gt= size of vector, the size of vector - 1 is used as the end of sort range.
		/// This function is fast but does not provide any security, so such issues as stack overflow
		/// can occur if the data is too large.
		/// </summary>
		/// <param name="begin">the beginning of sort range</param>
		/// <param name="end">the end of sort range</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& sort(size_t begin, size_t end) & {
			_assert_mode(Default, Naked, NoIndexCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (begin >= end) return *this;
				if (end >= size_) (int&)end = (int)size_ - 1;
			}
			quicksort_((int)begin, (int)end);
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& sort(size_t begin, size_t end) && {
			_assert_mode(Default, Naked, NoIndexCheck);
			return _rv(sort<_mode>(begin, end));
		}

		template<class _Func>
		INLINE _vector<_Type>& sort(_Func&& comparator) & {
			if (size_ > 1)
				quicksort_(0, (int)size_ - 1, comparator);
			return *this;
		}

		template<class _Func>
		FORCEINLINE _vector<_Type>&& sort(_Func&& comparator) && {
			return _rv(sort(std::forward<_Func>(comparator)));
		}


		template<mode_t _mode = _DefaultMode, class _Func>
		_vector<_Type>& sort(size_t begin, size_t end, _Func&& comparator) & {
			_assert_mode(Default, Naked, NoIndexCheck);
			if constexpr (!_mode_set(NoIndexCheck)) {
				if (begin >= end) return;
				if (end >= size_) (int&)end = (int)size_ - 1;
			}
			quicksort_((int)begin, (int)end, comparator);
			return *this;
		}

		template<mode_t _mode = _DefaultMode, class _Func>
		FORCEINLINE _vector<_Type>&& sort(size_t begin, size_t end, _Func&& comparator) && {
			_assert_mode(Default, Naked, NoIndexCheck);
			return _rv(sort<_mode>(begin, end, std::forward<_Func>(comparator)));
		}

		_vector<_Type>& countsort(_TypeConst min, _TypeConst max, size_t* countMap) & {
			for (size_t i = 0; i < size_; ++i) {
				++countMap[(size_t)data_[i] - (size_t)min];
			}
			_Type elem = min;
			for (size_t i = 0, k = 0; k < size_; ++i, ++elem) {
				size_t count = countMap[i];
				for (size_t c = 0; c < count; ++c)
					data_[k++] = elem;
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& countsort(_TypeConst min, _TypeConst max, size_t* countMap) && {
			return _rv(countsort(min, max, countMap));
		}

		_vector<_Type>& countsort(_TypeConst min, _TypeConst max) & {
			size_t* countMap = new size_t[max - min + 1]();
			countsort(min, max, countMap);
			delete[] countMap;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& countsort(_TypeConst min, _TypeConst max) && {
			return _rv(countsort(min, max));
		}

		FORCEINLINE _vector<_Type>& countsort(_TypeConst max) & {
			return countsort(0, max);
		}

		FORCEINLINE _vector<_Type>&& countsort(_TypeConst max) && {
			return _rv(countsort(0, max));
		}

	protected:
		static void mergesort_(_Type* begin, _Type* end, _Type* buffer) {
			if (end - begin == 1) {
				if (*end < *begin)
					x::swapp(begin, end);
				return;
			}
			_Type* mid = (_Type*)((((size_t)begin + (size_t)end) >> 1) & (size_t)0xFFFF'FFFF'FFFF'FFFC);
			if (mid - begin > 1)
				mergesort_(begin, mid, buffer);
			if (end - mid > 1)
				mergesort_(mid, end, buffer);
			_Type* el = begin;
			_Type* er = mid;
			_Type* eb = buffer;
		BEGIN:
			if (*el < *er) {
				_trivcopy(eb++, el++);
				if (el >= mid)
					goto COPY_BUFFER;
			}
			else {
				_trivcopy(eb++, er++);
				if (er >= end) {
					size_t size = (uint8_t*)el - (uint8_t*)begin;
					memcpy((uint8_t*)end - size, el, size);
					goto COPY_BUFFER;
				}
			}
			goto BEGIN;
		COPY_BUFFER:
			memcpy(begin, buffer, (uint8_t*)eb - (uint8_t*)buffer);
		}

	public:
		_vector<_Type>& mergesort(_Type* buffer) {
			if (size_ >= 2)
				mergesort_(data_, data_ + size_, buffer);
			return *this;
		}

		_vector<_Type>& mergesort() {
			if (size_ >= 2) {
				_vector<uint8_t>& buffer = _VectorTemp::buffer_;
				buffer.reserve(size_ * sizeof(_Type));
				mergesort_(data_, data_ + size_, reinterpret_cast<_Type*>(buffer.data_));
			}
			return *this;
		}

		_vector<_Type>& internal_mergesort() {
			if (size_ >= 2) {
				reserve(size_ + size_ / 2 + _INNER_MERGESORT_MIN_RESERVE);
				mergesort_(data_, data_ + size_, data_ + size_);
			}
			return *this;
		}

		/// <summary>
		/// Checks whether vector is sorted in ascending order
		/// </summary>
		/// <returns>true if vector is sorted, otherwise false</returns>
		FORCEINLINE bool is_sorted() const {
			return is_sorted_ascending();
		}

		bool is_sorted_ascending() const {
			if constexpr (std::is_same_v<_Type, bool>) {
				bool* ptrue = reinterpret_cast<bool*>(::memchr(data_, int(true), size_));
				return ptrue == nullptr || ::memchr(ptrue, int(false), data_ + size_ - ptrue) == nullptr;
			} else {
				for (size_t i = 1; i < size_; ++i) {
					if (data_[i] < data_[i - 1])
						return false;
				}
				return true;
			}
		}

		bool is_sorted_descending() const {
			if constexpr (std::is_same_v<_Type, bool>) {
				bool* pfalse = reinterpret_cast<bool*>(::memchr(data_, int(false), size_));
				return pfalse == nullptr || ::memchr(pfalse, int(true), data_ + size_ - pfalse) == nullptr;
			} else {
				for (size_t i = 1; i < size_; ++i) {
					if (data_[i - 1] < data_[i])
						return false;
				}
				return true;
			}
		}


		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& insert_sorted(_TypeConst value) & {
			if constexpr (std::is_same_v<_Type, bool>) {
				if (value)
					push_back(value);
				else
					push_front(value);
			} else {
				size_t i = 0;
				while (i < size_ && data_[i] < value)
					++i;
				insert<_mode | NoIndexCheck>(value, i);
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& insert_sorted(_TypeConst value) && {
			return _rv(insert_sorted(value));
		}

		_vector<_Type>& insert_sorted(_Type&& value) & {
			size_t i = 0;
			for (; i < size_ && data_[i] < value; ++i) {}
			insert((_Type&&)value, i);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& insert_sorted(_Type&& value) && {
			return _rv(insert_sorted((_Type&&)value));
		}

	protected:
		FORCEINLINE void insert_unique_sorted_bool_(bool value) {
			if (size_ > 1)
				return *this;
			else if (size_ == 1) {
				if (value) {
					if (data_[0])
						return *this;
					else {
						if (reserved_ < 2)
							data_ = dump_reallocate_(2);
						data_[0] = false;
						data_[1] = true;
						size_ = 2;
					}
				} else {
					if (data_[0]) {
						if (reserved_ < 2)
							data_ = dump_reallocate_(2);
						data_[0] = false;
						data_[1] = true;
						size_ = 2;
					} else
						return *this;
				}
			} else {
				if (reserved_ < 2)
					data_ = dump_reallocate_(2);
				data_[0] = value;
				size_ = 1;
			}
		}

	public:
		_vector<_Type>& insert_unique_sorted(_TypeConst value) {
			if constexpr (std::is_same_v<_Type, bool>) {				
				insert_unique_sorted_bool_(value);
			} else {
				_Type* e = data_;
				_Type* end = data_ + size_;
				while (e < end) {
					if constexpr (x::is_less_or_equal_comparable_v<_Type, _Type>) {
						if (value <= *e)
							break;
					} else {
						if (!(*e < value))
							break;
					}
					++e;
				}
				if (*e == value)
					return *this;
				if (size_ >= reserved_) {
					size_t pos = e - data_;
					reserved_ = extended_capacity_(reserved_);
					_Type* newdata = allocate_(reserved_);
					_Type* dest = newdata + pos;
					::memcpy(newdata, data_, pos * sizeof(_Type));
					::memcpy(dest + 1, e, (end - e) * sizeof(_Type));
					_construct(dest, value);
					deallocate_(data_);
					data_ = newdata;
					++size_;
				} else {
					::memmove(e + 1, e, (size_ - pos) * sizeof(_Type));
					_construct(e, value);
					++size_;
				}
			}
			return *this;
		}


		_vector<_Type>& inser_unique(_TypeConst value) & {
			if (!contains(value))
				push_back(value);
			return *this;
		}

		_vector<_Type>& inser_unique(_TypeConst value) && {
			if (!contains(value))
				push_back(value);
			return *this;
		}


		_vector<_Type>& inser_unique(_Type&& value) & {
			if (!contains(value))
				push_back((_Type&&)value);
			return *this;
		}

		_vector<_Type>& inser_unique(_Type&& value) && {
			if (!contains(value))
				push_back((_Type&&)value);
			return *this;
		}
		

		/// <summary>
		/// Sets elements currently contained in vector in x::random order. 
		/// If \a swapEach is enabled, every element will be placed somewhere else, otherwise
		/// there is some probability for each element of not being moved.
		/// </summary>
		/// <param name="swapEach">flag denoting that every element will change place, DEFAULT: disabled</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& shuffle() & {
			for (size_t i = size_ - 1; i > 0; --i)
				x::swapp(data_ + i, data_ + random32(i));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& shuffle() && {
			return _rv(shuffle());
		}

		_vector<_Type>& shuffle(size_t n) & {
			repeat(n)
				x::swapp(data_ + random32(size_), data_ + random32(size_));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& shuffle(size_t n) && {
			return _rv(shuffle(n));
		}

		/// <summary>
		/// Gets randomly selected element from specified position range.
		/// </summary>
		/// <param name="begin">the beginning of range</param>
		/// <param name="end">the end of range</param>
		/// <returns>reference to randomly picked element</returns>
		_Type& random(size_t begin, size_t end) & {
			return data_[random32(begin, end)];
		}

		_Type const& random(size_t begin, size_t end) const & {
			return data_[random32(begin, end)];
		}

		_Type && random(size_t begin, size_t end) && {
			return (_Type&&)data_[random32(begin, end)];
		}


		/// <summary>
		/// Gets randomly selected element from the whole vector.
		/// Equivalent to <code> random(0, size() - 1) </code>.
		/// </summary>
		/// <returns>reference to randomly picked element</returns>
		_Type& random() & {
			return data_[random32(size_)];
		}

		_Type const& random() const & {
			return data_[random32(size_)];
		}

		_Type&& random() && {
			return (_Type&&)data_[random32(size_)];
		}


		_vector<_Type> random_subset(size_t size) const & {
			_vector<size_t>& indexes = _VectorTemp::indexes_;
			indexes.resize(size_);
			size_t end = size_;
			size_t* idxdata = indexes.data_;
			for (size_t i = 0; i < size_; ++i) 
				idxdata[i] = i;
			_vector<_Type> result(size, size);
			_foreach_v(r, result) {
				size_t i = random32(end);
				_construct(r, data_[idxdata[i]]);
				idxdata[i] = idxdata[--end];
			}
			return result;
		}

		//_vector<_Type> random_subset(size_t size) const & {
		//	if (isize_ < size_) {
		//		size_t newsize = size_;
		//		//::free(is_);
		//		//is_ = (size_t*)::malloc(newsize * sizeof(size_t));
		//		is_ = (size_t*)::realloc(is_, newsize * sizeof(size_t));
		//		isize_ = newsize;
		//	}
		//	for (size_t i = 0; i < size_; ++i)
		//		is_[i] = i;			
		//	size_t end = size_;
		//	_vector<_Type> result(size);
		//	result.size_ = size;
		//	_foreach_v(e, result) {
		//		size_t i = random32(end);
		//		_trivcopy(e, data_ + is_[i]);
		//		is_[i] = is_[--end];
		//	}
		//	return result;
		//}


		//_vector<_Type>&& random_subset(size_t size) && {
		//	if (size == 0)
		//		return _rvthis.clear();
		//	//shuffle();
		//	for (size_t i = size - 1; i < size; --i) 
		//		x::swapp(data_ + i, data_ + i + random32(size_ - i));
		//	_destruct_from(data_ + size);
		//	size_ = size;
		//	return _rvthis;
		//}

		//TODO optimize randomize for fundamentals
		_vector<_Type>& fill_randomize(_TypeConst bound) & {
			_foreach(e)
				_reconstruct(e, x::random<_Type>(bound));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& fill_randomize(_TypeConst bound) && {
			return _rv(fill_randomize(bound));
		}

		/// <summary>
		/// Fills vector with randomly generated elements from specified range.
		/// If there is no implementation of x::x::random specialization on the type contained in vector,
		/// the function will fail to compile. By default, all fundamental types are possible to
		/// be randomized.
		/// </summary>
		/// <param name="r1">the beginning of randomization range</param>
		/// <param name="r2">the end of randomization range</param>
		/// <returns>reference to the caller</returns>
		/*_vector<_Type>& fill_randomize(_TypeConst r1, _TypeConst r2) & {
			_foreach(e)
				_reconstruct(e, x::random<_Type>(r1, r2));
			return *this;
		}*/

		_vector<_Type>& fill_randomize(range<_Type> const& range) & {
			_foreach(e)
				_reconstruct(e, x::random<_Type>(r1, r2));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& fill_randomize(range<_Type> const& range) && {
			return _rv(fill_randomize(range));
		}


		/// <summary>
		/// Reallocates the memory to given \a size and fills vector with randomly generated elements 
		/// from specified range. If there is no implementation of x::x::random specialization on the 
		/// type contained in vector, the function will fail to compile. 
		/// By default, all fundamental types are possible to be randomized.
		/// </summary>
		/// <param name="r1">the beginning of randomization range</param>
		/// <param name="r2">the end of randomization range</param>
		/// <param name="size">new size of the vector</param>
		/// <returns>reference to the caller</returns>
		/*_vector<_Type>& randomize(_TypeConst r1, _TypeConst r2, size_t size) & {
		clear_resize_(size);
		return randomize(r1, r2);
		}*/


		template<class _FirstSize, class... _Size>
		_vector<_Type>& randomize(range<atomic_type> const& range, _FirstSize first, _Size... sizes) & {
			static_assert(sizeof...(_Size) + 1 == DIM_);
			clear_resize_(first);
			if constexpr (DIM_ == 1) {
				_foreach(e)
					_construct(e, x::random<_Type>(range.begin, range.end));
			} else {
				zero();
				_foreach(v)
					v->randomize(range, sizes...);
			}
			return *this;
		}

		template<class _FirstSize, class... _Size>
		FORCEINLINE _vector<_Type>&& randomize(range<atomic_type> const& range, _FirstSize first, _Size... sizes) && {
			return _rv(randomize(range, first, sizes...));
		}


		//void randomize_impl_(range<atomic_type> const& range, size_t const* s) {
		//	clear_resize_(*s);
		//	if constexpr (DIM_ == 1) {
		//		_foreach(e)
		//			_construct(e, x::random<_Type>(range.begin, range.end));
		//	} else {
		//		++s;
		//		zero(); //TODO unnecessary?
		//		_foreach(v)
		//			v->randomize(range, s);
		//	}
		//}

		//FORCEINLINE _vector<_Type>& randomize(range<atomic_type> const& range, std::initializer_list<size_t> sizes) & {
		//	randomize_impl_(range, sizes.begin());
		//	return *this;
		//}


		_vector<_Type>& randomize_exact(_vector<_Type> const& set) & {
			size_t setsize = set.size_;
			for (size_t i = 0; i < size_; ++i)
				_reconstruct(data_ + i, set.data_[random32(setsize)]);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& randomize_exact(_vector<_Type> const& set) && {
			return _rv(randomize_exact(set));
		}


		template<class _FirstSize, class... _Size>
		_vector<_Type>& randomize_exact(_vector<_Type> const& set, _FirstSize first, _Size... sizes) & {
			clear_resize_(first);
			if constexpr (DIM_ == 1) {
				_foreach(e)
					_construct(e, set.random());
			} else {
				zero();
				_foreach(v)
					v->randomize_exact(set, sizes...);
			}
			return *this;
		}

		template<class _FirstSize, class... _Size>
		FORCEINLINE _vector<_Type>&& randomize_exact(_vector<_Type> const& set, _FirstSize first, _Size... sizes) && {
			return _rv(randomize_exact(set, first, sizes...));
		}


		_vector<_Type>& randomize_exact(std::initializer_list<_Type> set) & {
			size_t setsize = set.size();
			_Type const* setdata = set.begin();
			for (size_t i = 0; i < size_; ++i)
				_reconstruct(data_ + i, setdata[random32(setsize)]);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& randomize_exact(std::initializer_list<_Type> set) && {
			return _rv(randomize_exact(set));
		}
		

		_vector<_Type>& randomize_exact(std::initializer_list<_Type> set, size_t size) & {
			clear_resize_(size);
			return randomize_exact(set);
		}

		FORCEINLINE _vector<_Type>&& randomize_exact(std::initializer_list<_Type> set, size_t size) && {
			return _rv(randomize_exact(set, size));
		}


		/*FORCEINLINE _vector<_Type>&& randomize(_TypeConst n) && {
			return _rv(randomize(n));
		}

		FORCEINLINE _vector<_Type>&& randomize(_TypeConst r1, _TypeConst r2) && {
			return _rv(randomize(r1, r2));
		}

		FORCEINLINE _vector<_Type>&& randomize(_TypeConst r1, _TypeConst r2, size_t size) && {
			clear_resize_(size);
			return _rv(randomize(r1, r2));
		}*/


		/// <summary>
		/// Jitters each element from the current value by randomized factor from range.
		/// </summary>
		/// <remarks>
		///
		/// Multiplies every element by a randomized factor in range from 1.0 +\a r1 to 1.0 +\a r2.
		/// If \a r1 &gt \a r2, this function does nothing.
		/// </remarks>
		/// <param name="r1">minimum of the jitter range</param>
		/// 
		/// <param name="r2">maximum of the jitter range</param>
		/// <returns>reference to the caller</returns>
		template<class _Real>
		_vector<_Type>& jitter(_Real r1, _Real r2) & {
			if (r1 > r2) return *this;
			for (size_t i = 0; i < size_; ++i)
				data_[i] *= x::random<_Real>(r1, r2);
			return *this;
		}

		template<class _Real>
		FORCEINLINE _vector<_Type>&& jitter(_Real r1, _Real r2) && {
			return _rv(jitter(r1, r2));
		}

		/// <summary>
		/// Jitters each element from the current value by randomized factor from range.
		/// </summary>
		/// <remarks>
		/// Multiplies every element by a randomized factor in range from 1.0 -\a r to 1.0 +\a r.
		/// If \a r1 &gt \a r2, this function does nothing.
		/// Equivalent to <code>jitter(-r, r)</code>.
		/// </remarks>
		/// </summary>
		/// <param name="r">radius of the jitter range</param>
		/// <returns>reference to the caller</returns>
		template<class _Real>
		FORCEINLINE _vector<_Type>& jitter(_Real r) & {
			return jitter(-r, r);
		}


		template<class _Real>
		FORCEINLINE _vector<_Type>&& jitter(_Real r) && {
			return _rv(jitter(-r, r));
		}

		/// <summary>
		/// Deallocates currently unused memory beyond the minimum required to store accessible elements.
		/// </summary>
		/// <remarks>
		/// Its usage is to manually control the amount of memory used by vector and prevent from 
		/// keeping unused memory e.g. when the vector is known to change size rarely or never,
		/// since functions changing the size or capacity of vector allocate new memory if needed
		/// but do not deallocate excessive memory.
		/// All elements currently contained in vector are preserved and the size does not change.
		/// </remarks>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& shrink() & {
			reallocate_(size_);
			return *this;
		}

		_vector<_Type>&& shrink() && {
			reallocate_(size_);
			return _rvthis;
		}

		_vector<_Type>& shrink(size_t capacity) & {
			reallocate_(x::max(size_, capacity));
			return *this;
		}

		_vector<_Type>&& shrink(size_t capacity) && {
			reallocate_(x::max(size_, capacity));
			return _rvthis;
		}

		/// <summary>
		/// Allocates desired amount of memory if the current capacity of vector is not sufficient.
		/// </summary>
		/// <remarks>
		/// If \a capacity is lower than capacity of currently allocated memory, this function does nothing.
		/// Its usage is to manually control amount of memory handled by the vector for 
		/// optimization purposes, e.g. if there are some operations to be performed on vector
		/// known to increase vector's size. Similar functionality can be achieved by passing 
		/// desired size of vector to constructor but it does not allow to do it on the flow.
		/// </remarks>
		/*/// <example>
		/// <code>x::vector&ltBase*&gt vec;
		/// vec.reserve(200);
		/// for (int i=0; i&lt200; ++i) {
		///		vec.push_back(new Derived{x::random32&ltint&gt(0, i)});
		/// }</code>
		/// </example>*/
		/// <param name="capacity">the desired capacity of vector</param>
		/// <returns>reference to the caller</returns>


		_vector<_Type>& reserve(size_t capacity) & {
			if (capacity > reserved_)
				reallocate_(capacity);
			return *this;
		}

		_vector<_Type>&& reserve(size_t capacity) && {
			if (capacity > reserved_)
				reallocate_(capacity);
			return _rvthis;
		}

		template<class... _Size>
		_vector<_Type>& reserve(size_t capacity, _Size... capacities) & {
			if (capacity > reserved_)
				reallocate_(capacity);
			if (size_ == 0) {
				size_ = reserved_;
				_foreach(v) {
					_construct(v);
					v->reserve(capacities...);
				}
			} else {
				_foreach(v)
					v->reserve(capacities...);
				_foreach_from_s(v, data_ + size_, reserved_) {
					_construct(v);
					v->reserve(capacities...);
				}
				size_ = reserved_;
			}
			return *this;
		}

		template<class... _Size>
		FORCEINLINE _vector<_Type>&& reserve(size_t capacity, _Size... capacities) && {
			return _rv(reserve(capacity, capacities...));
		}


		_vector<_Type>& resize(size_t size) & {
			if (size > reserved_)
				reallocate_(size);
			size_ = size;
			return *this;
		}

		_vector<_Type>&& resize(size_t size) && {
			if (size > reserved_)
				reallocate_(size);
			size_ = size;
			return _rvthis;
		}


		template<class... _Size>
		_vector<_Type>& resize(size_t size, _Size... sizes) & {
			if (size > reserved_)
				reallocate_(size);
			if (size_ == 0) {
				size_ = reserved_;
				_foreach(v) {
					_construct(v);
					v->resize(sizes...);
				}
			} else {
				_foreach(v)
					v->resize(sizes...);
				_foreach_from_s(v, data_ + size_, reserved_) {
					_construct(v);
					v->resize(sizes...);
				}
				size_ = reserved_;
			}
			return *this;
		}

		template<class... _Size>
		FORCEINLINE _vector<_Type>&& resize(size_t size, _Size... sizes) && {
			return _rv(resize(size, sizes...));
		}

	private:
		_vector<_Type>& dump_resize_(size_t size) & {
			if (size > reserved_)
				dump_reallocate_(size);
			size_ = size;
			return *this;
		}

		_vector<_Type>&& dump_resize_(size_t size) && {
			if (size > reserved_)
				dump_reallocate_(size);
			size_ = size;
			return _rvthis;
		}

	public:
		/// <summary>
		/// Forces the size to be set to given value.
		/// </summary>
		/// <remarks>
		/// If given size is greater than current capacity it is set to the value of capacity.
		/// </remarks>
		/// <param name="size">the value of vector's size</param>
		/// <returns>reference to the caller</returns>
		INLINE _vector<_Type>& enable(size_t size) & noexcept {
			size_ = x::min(size, reserved_);
			return *this;
		}

		INLINE _vector<_Type>&& enable(size_t size) && noexcept {
			size_ = x::min(size, reserved_);
			return _rvthis;
		}

		/// <summary>
		/// Forces the current maximum value of size, that is equal to capacity.
		/// </summary>
		/// <returns>reference to the caller</returns>
		template<unsigned _depth = 1>
		FORCEINLINE _vector<_Type>& enable() & {
			if constexpr (_depth == 1)
				size_ = reserved_;
			else {
				_foreach(v)
					v->enable<_depth - 1>();
				initialize();
			}
			return *this;
		}


		template<unsigned _depth = 1>
		FORCEINLINE _vector<_Type>&& enable() && {
			if constexpr (_depth == 1)
				size_ = reserved_;
			else
				return _rv(enable());
		}

		/// <summary>
		/// Allocates additional amount of memory.
		/// </summary>
		/// <remarks>
		/// Equivalent to <code>reserve(reserved() + \a capacity) </code>. Asserts that the memory 
		/// will be added, contrary to reserve which will do nothing if the specified capacity does
		/// not extend the current vector's capacity.
		/// </remarks>
		/// <see cref="reserve"/>
		/// <param name="capacity"></param>
		/// <returns></returns>
		INLINE _vector<_Type>& extend(size_t capacity) & {
			reallocate_(reserved_ + capacity);
			return *this;
		}

		INLINE _vector<_Type>&& extend(size_t capacity) && {
			reallocate_(reserved_ + capacity);
			return _rvthis;
		}

		_vector<_Type>& extend() & {
			reallocate_(extended_capacity_(reserved_));
			return *this;
		}

		_vector<_Type>&& extend() && {
			reallocate_(extended_capacity_(reserved_));
			return _rvthis;
		}


		/// <summary>
		/// Copies content of \a other vector and appends it at the end.
		/// </summary>
		/// <param name="other">vector to be appended</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		_vector<_Type>& append(_vector<_Type> const& other) & {
			_OPT_LOCK;
			if (reserved_ < size_ + other.size_)
				reallocate_(size_ + other.size_);
			copy_(data_ + size_, other.data_, other.size_);
			size_ += other.size_;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(_vector<_Type> const& other) && {
			return _rv(append(other));
		}

		_vector<_Type>& append(_vector<_Type> const& other, size_t n) & {
			if (n == 0)
				return *this;
			size_t othsize = other.size_;
			if (othsize == 0)
				return *this;
			size_t newsize = size_ + othsize * n;
			if (reserved_ < newsize)
				reallocate_(newsize);
			_Type* end = data_ + size_;
			for (size_t i = 0; i < n; ++i, end += othsize)
				copy_(end, other.data_, othsize);
			size_ = newsize;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(_vector<_Type> const& other, size_t n) && {
			return _rv(append(other, n));
		}


		_vector<_Type>& append(_vector<_Type>&& other) & {
			reserve(size_ + other.size_);
			::memcpy(data_ + size_, other.data_, other.size_ * sizeof(_Type));
			other.deallocate_();
			other.data_ = nullptr;
			size_ += other.size_;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(_vector<_Type>&& other) && {
			return _rv(append(other.move()));
		}


		_vector<_Type>& append(_vector<_Type>&& other, size_t n) & {
			if (n == 0)
				return *this;
			size_t othsize = other.size_;
			if (othsize == 0)
				return *this;
			size_t newsize = size_ + othsize * n;
			if (reserved_ < newsize)
				reallocate_(newsize);
			_Type* end = data_ + size_;
			for (size_t i = 1; i < n; ++i, end += othsize)
				copy_(end, other.data_, othsize);
			::memcpy(end, other.data_, other.size_ * sizeof(_Type));
			other.deallocate_();
			other.data_ = nullptr;
			size_ = newsize;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(_vector<_Type>&& other, size_t n) && {
			return _rv(append(other.move(), n));
		}

		_vector<_Type>& append(std::initializer_list<_Type> elements) & {
			size_t newsize = size_ + elements.size();
			if (reserved_ < newsize)
				reallocate_(newsize);
			copy_initializer_list_(data_ + size_, elements.begin(), elements.end());
			size_ = newsize;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(std::initializer_list<_Type> elements) && {
			return _rv(append(elements));
		}

		/*template<size_t _size, size_t... _i>
		void expand_append_(_Type(&&arr)[_size], seq<_i...> const&) {
		va::expand((new (data_ + size_ + _i) _Type((_Type&&)arr[_i]))...);
		}

		template<size_t _size>
		_vector<_Type>& append(_Type(&&arr)[_size]) {
		size_t newsize = size_ + _size;
		if (reserved_ < newsize)
		reallocate_(newsize);
		expand_append_(arr, seq_v<_size>);
		size_ = newsize;
		return *this;
		}*/


		_vector<_Type>& append(std::initializer_list<_Type> elements, size_t n) & {
			if (n == 0)
				return *this;
			size_t ilsize = elements.size();
			if (ilsize == 0)
				return *this;
			size_t newsize = size_ + ilsize * n;
			if (reserved_ < newsize)
				reallocate_(newsize);
			_Type* src = const_cast<_Type*>(elements.begin());
			_Type* end = data_ + size_;
			for (size_t i = 1; i < n; ++i, end += ilsize)
				copy_(end, src, ilsize);
			copy_initializer_list_(end, src, elements.end());
			size_ = newsize;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& append(std::initializer_list<_Type> other, size_t n) && {
			return _rv(append(other, n));
		}

		/// <summary>
		/// Copies content of \a other vector and pepends it at the beginning.
		/// </summary>
		/// <param name="other">vector to be prepended</param>
		/// <returns>reference to the caller</returns>
		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& prepend(const _vector<_Type>& other) & {
			if (other.size_ == 0)
				return *this;
			size_t newsize = size_ + other.size_;
			if (newsize > reserved_) {
				_Type* newdata = allocate_(newsize);
				copy_(newdata, other.data_, other.size_);
				::memcpy(newdata + other.size_, data_, size_ * sizeof(_Type));
				deallocate_(data_);
				data_ = newdata;
				reserved_ = newsize;
			} else {
				::memmove(data_ + other.size_, data_, size_ * sizeof(_Type));
				copy_(data_, other.data_, other.size_);
			}
			size_ = newsize;
			return *this;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& prepend(const _vector<_Type>& other) && {
			return _rv(prepend(other));
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>& prepend(_vector<_Type>&& other) & {
			if (other.size_ == 0)
				return *this;
			size_t newsize = size_ + other.size_;
			if (newsize > reserved_) {
				_Type* newdata = allocate_(newsize);
				::memcpy(newdata, other.data_, other.size_ * sizeof(_Type));
				::memcpy(newdata + other.size_, data_, size_ * sizeof(_Type));
				deallocate_(data_);
				data_ = newdata;
				reserved_ = newsize;
			} else {
				::memcpy(data_, other.data_, other.size_ * sizeof(_Type));
				::memmove(data_ + other.size_, data_, size_ * sizeof(_Type));
			}
			other.deallocate_();
			other.data_ = nullptr;
			size_ = newsize;
			return _rvthis;
		}

		template<mode_t _mode = _DefaultMode>
		FORCEINLINE _vector<_Type>&& prepend(_vector<_Type>&& other) && {
			return _rvthis.insert(other.move(), 0);
		}

		//moves content forward and
		//inserts new elements on the beginning
		/*_vector<_Type>& prepend(std::initializer_list<_Type> other)
		{
		if (reserved_<size_ + other.size())
		reallocate_(size_ + other.size());
		::memcpy(data_ + other.size(), data_, size_ * sizeof(_Type));
		int k = 0;
		for (class std::initializer_list<_Type>::iterator i = other.begin();
		i != other.end(); ++i, ++k) {
		data_[k] = _Type(*i);
		}
		size_ += other.size();
		return *this;
		}*/

		/// <summary>
		/// Counts number of occurences of given element in vector.
		/// </summary>
		/// <remarks>
		/// If the contained type has no overloaded operator ==, this function will fail to compile.
		/// </remarks>
		/// <param name="elem">value to be counted</param>
		/// <returns>number of occurences of counted value</returns>
		template<unsigned _depth = 1, class _Value = _Type>
		NODISCARD
		size_t count(_Value const& elem) const {
			_validate_depth;
			size_t n = 0;
			if constexpr (_depth == 1) {
				_const_foreach(e)
					if (*e == elem)
						++n;
			} else {
				_const_foreach(v)
					n += v->count<_depth - 1>(elem);
			}
			return n;
		}


		/// <summary>
		/// Counts number of elements fulfilling given \a condition.
		/// </summary>
		/// <remarks>
		/// The \a condition must be a delegate that takes contained type as argument and returns bool or
		/// type convertible to bool, otherwise this function will fail to compile.
		/// </remarks>
		/// <typeparam name="_Func">deducet type of function</typeparam>
		/// <param name="condition">the condition to be checked over elements</param>
		/// <returns>number of elements fulfilling condition</returns>
		/*template<unsigned _depth = 1, class _Pred>
		size_t count_if(_Pred&& pred) const {
			size_t n = 0;
			_validate_depth;
			if constexpr (_depth == 1) {
				_const_foreach(e)
					if (pred(*e))
						++n;
			} else {
				_const_foreach(v)
					n += v->count_if<_depth - 1>((_Pred&&)pred);
			}
			return n;
		}*/

	private:
		template<class _Func, class _Type>
		static constexpr bool is_sub_invocable = std::is_invocable_v<_Func, _Type>;

		template<class _Func, class _Type>
		static constexpr bool is_sub_invocable<_Func, _vector<_Type>> = std::is_invocable_v<_Func, _vector<_Type>> || is_sub_invocable<_Func, _Type>;


		template<class _Func, class _Type>
		static constexpr bool is_sub_invocable_c = std::is_invocable_v<_Func, _Type const>;

		template<class _Func, class _Type>
		static constexpr bool is_sub_invocable_c<_Func, _vector<_Type>> = is_sub_invocable_c<_Func, _Type> || std::is_invocable_v<_Func, _vector<_Type> const>;


		template<class _Ret, class _Func, class _Type>
		static constexpr bool is_sub_invocable_r = std::is_invocable_v<_Ret, _Func, _Type>;

		template<class _Ret, class _Func, class _Type>
		static constexpr bool is_sub_invocable_r<_Ret, _Func, _vector<_Type>> = std::is_invocable_v<_Func, _vector<_Type>> || is_sub_invocable_r<_Ret, _Func, _Type>;


		template<class _Ret, class _Func, class _Type>
		static constexpr bool is_sub_invocable_r_c = std::is_invocable_r_v<_Ret, _Func, _Type const>;

		template<class _Ret, class _Func, class _Type>
		static constexpr bool is_sub_invocable_r_c<_Ret, _Func, _vector<_Type>> = std::is_invocable_v<_Ret, _Func, _vector<_Type> const> || is_sub_invocable_r_c<_Ret, _Func, _Type>;


	public:
		template<class _Pred>
		NODISCARD
		std::enable_if_t<!is_sub_invocable_c<_Pred, _Type>,
		size_t> count_if(_Pred&& pred) {
			size_t n = 0;
			if constexpr (std::is_invocable_v<_Pred, _Type>) {
				_foreach(e)
					if (pred(*e))
						++n;
			} else {
				_foreach(v)
					n += v->count_if((_Pred&&)pred);
			}
			return n;
		}

		template<class _Pred>
		NODISCARD
		std::enable_if_t<is_sub_invocable_c<_Pred, _Type>,
		size_t> count_if(_Pred&& pred) const {
			size_t n = 0;
			if constexpr (std::is_invocable_v<_Pred, _Type const>) {
				_const_foreach(e)
					if (pred(*e))
						++n;
			} else {
				_const_foreach(v)
					n += v->count_if((_Pred&&)pred);
			}
			return n;
		}


		template<class _Member, class _T>
		NODISCARD
		size_t count_by(_Member(_T::*member), std::remove_const_t<_Member> const& value) const {
			size_t n = 0;
			if constexpr (std::is_same_v<_T, _Type>) {
				_const_foreach(e)
					if ((e->*member) == value)
						++n;
			} else if constexpr (std::is_same_v<_T, std::remove_pointer_t<_Type>>) {
				_const_foreach(e)
					if (((*e)->*member) == value)
						++n;
			} else {
				_const_foreach(v)
					n += v->count_by(member, value);
			}
			return n;
		}

		/*template<class _T = _Type>
		FORCEINLINE size_t count_by(bool(_T::*member)) const {
			return count_by(member, true);
		}

		template<class _T = _Type>
		FORCEINLINE size_t count_by(bool const(_T::*member)) const {
			return count_by(reinterpret_cast<bool(_T::*)>(member), true);
		}*/


		template<class _Member, class _T, class... _Arg>
		NODISCARD
		size_t count_by(_Member(_T::*member)(_Arg...) const, std::remove_const_t<_Member> const& value, _Arg&&... args) const {
			size_t n = 0;
			if constexpr (std::is_same_v<_T, _Type>) {
				_const_foreach(e)
					if ((e->*member)((_Arg&&)args...) == value)
						++n;
			} else if constexpr (std::is_same_v<_T, std::remove_pointer_t<_Type>>) {
				_const_foreach(e)
					if (((*e)->*member)((_Arg&&)args...) == value)
						++n;
			} else {
				_const_foreach(v)
					n += v->count_by(member, value, (_Arg&&)args...);
			}
			return n;
		}

		template<class _Member, class _T, class... _Arg>
		NODISCARD
		FORCEINLINE size_t count_by(_Member(_T::*member)(_Arg...), std::remove_const_t<_Member> const& value, _Arg&&... args) {
			return count_by(reinterpret_cast<_Member(_T::*)(_Arg...) const>(member), value, (_Arg&&)args...);
		}

		/*template<class _T, class... _Arg>
		FORCEINLINE size_t count_by(bool(_T::*member)(_Arg...), _Arg&&... args) const {
			return count_by(member, true, (_Arg&&)args...);
		}
*/

		/// <summary>
		/// Finds first occurence of given element.
		/// </summary>
		/// <remarks>
		/// The resulting reference is wrapped in result object and if the element was not found,
		/// result of invalid state is returned.
		/// If the contained type has no overloaded operator ==, this function will fail to compile.
		/// </remarks>
		/// <param name="elem">element to be found</param>
		/// <returns>reference to found element</returns>
		NODISCARD 
		FORCEINLINE iterator find(_TypeConst elem) & {
			return {*this, pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE const_iterator find(_TypeConst elem) const & {
			return {*this, pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE move_iterator find(_TypeConst elem) && {
			return {*this, pos_of(elem)};
		}


		NODISCARD
		_Type& find(_TypeConst elem, _Type& def) & {
			_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type const& find(_TypeConst elem, _Type const& def) const & {
			_const_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type& find(_TypeConst elem, _Type& def) && {
			_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type&& find(_TypeConst elem, _Type&& def) && {
			_foreach(e)
				if (*e == elem)
					return (_Type&&)*e;
			return (_Type&&)def;
		}


		NODISCARD
		FORCEINLINE iterator find_first(_TypeConst elem) & {
			return {*this, pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE const_iterator find_first(_TypeConst elem) const & {
			return {*this, pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE move_iterator find_first(_TypeConst elem) && {
			return {*this, pos_of(elem)};
		}


		NODISCARD
		FORCEINLINE _Type& find_first(_TypeConst elem, _Type& def) & {
			return find(elem, def);
		}

		NODISCARD
		FORCEINLINE _Type const& find_first(_TypeConst elem, _Type const& def) const & {
			return find(elem, def);
		}

		NODISCARD
		FORCEINLINE _Type& find_first(_TypeConst elem, _Type& def) && {
			return find(elem, def);
		}

		NODISCARD
		FORCEINLINE _Type&& find_first(_TypeConst elem, _Type&& def) && {
			return (_Type&&)find(elem, (_Type&&)def);
		}


		NODISCARD
		FORCEINLINE iterator find_last(_TypeConst elem) & {
			return {*this, last_pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE const_iterator find_last(_TypeConst elem) const & {
			return {*this, last_pos_of(elem)};
		}

		NODISCARD
		FORCEINLINE move_iterator find_last(_TypeConst elem) && {
			return {*this, last_pos_of(elem)};
		}


		NODISCARD
		_Type& find_last(_TypeConst elem, _Type& def) & {
			_reverse_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type const& find_last(_TypeConst elem, _Type const& def) const & {
			_const_reverse_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type& find_last(_TypeConst elem, _Type& def) && {
			_reverse_foreach(e)
				if (*e == elem)
					return *e;
			return def;
		}

		NODISCARD
		_Type&& find_last(_TypeConst elem, _Type&& def) && {
			_reverse_foreach(e)
				if (*e == elem)
					return (_Type&&)*e;
			return (_Type&&)def;
		}


		NODISCARD
		bool owner_of(_Type const& elem) const {
			return (&elem >= data_) && (&elem < data_ + size_);
		}


		NODISCARD
		bool owner_of(_Type const* elem) const {
			return (elem >= data_) && (elem < data_ + size_);
		}


		NODISCARD
		bool owner_of(iterator const& i) const {
			return &i.owner == this;
		}


		NODISCARD
		bool owner_of(const_iterator const& i) const {
			return &i.owner == this;
		}


		NODISCARD
		bool owner_of(move_iterator const& i) const {
			return &i.owner == this;
		}


		NODISCARD
		bool contains(_TypeConst value) const {
			_const_foreach(e)
				if (*e == value)
					return true;
			return false;
		}


		NODISCARD
		FORCEINLINE bool contains(_TypeConst value, size_t n) const {
			return count(value) == n;
		}


		template<class _Func, class... _Arg>
		_refvector<_Type> const& filter(_Func&& pred, _Arg&&... args) {
			_refvector<_Type>& filtered = _VectorTemp::instance_.reinterpret<_Type>();
			filtered.clear();
			filtered.reserve(size_);
			_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					filtered.push_back<NoSizeCheck>(e);
			return filtered;
		}


		/// <summary>
		/// Finds first occurence of given element and gets its position in vector.
		/// </summary>
		/// <remarks>
		/// The resulting position is wrapped in result object and if the element was not found,
		/// result of invalid state is returned.
		/// If the contained type has no overloaded operator ==, this function will fail to compile.
		/// </remarks>
		/// <param name="elem">element to be found</param>
		/// <returns>position of found element</returns>
		NODISCARD
		size_t pos_of(_TypeConst elem, size_t def) const {
			_const_foreach(e)
				if (*e == elem)
					return e - data_;
			return def;
		}


		NODISCARD
		FORCEINLINE size_t pos_of(_TypeConst elem) const {
			return pos_of(elem, (size_t)-1);
		}


		NODISCARD
		size_t last_pos_of(_TypeConst elem, size_t def) const {
			_const_reverse_foreach(e)
				if (*e == elem)
					return e - data_;
			return def;
		}


		NODISCARD
		FORCEINLINE size_t last_pos_of(_TypeConst elem) const {
			return pos_of(elem, (size_t)-1);
		}


		//TODO maybe use _VectorTemp for result ?
		_vector<size_t> all_pos_of(_TypeConst value) const {
			_vector<size_t> result;
			_foreach(e)
				if (*e == value)
					result.push_back(e - data_);
			return result;
		}

		/*size_t pos_of(_TypeConst elem, size_t def = std::numeric_limits<size_t>::max()) const {
		_foreach(e)
		if (*e == elem)
		return e - data_;
		return def;
		}*/

		template<class _Pred, class... _Arg>
		FORCEINLINE size_t pos_of_true(_Pred&& pred, _Arg&&... args) const {
			pos_of_true((_Pred&&)pred, (size_t)-1, (_Arg&&)args...);
		}


		template<class _Pred, class... _Arg>
		size_t pos_of_true(_Pred&& pred, size_t def, _Arg&&... args) const {
			_const_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					return e - data_;
			return def;
		}


		template<class _Pred, class... _Arg>
		FORCEINLINE size_t last_pos_of_true(_Pred&& pred, _Arg&&... args) const {
			last_pos_of_true((_Pred&&)pred, (size_t)-1, (_Arg&&)args...);
		}


		template<class _Pred, class... _Arg>
		size_t last_pos_of_true(_Pred&& pred, size_t def, _Arg&&... args) const {
			_const_reverse_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					return e - data_;
			return def;
		}


		template<class _Pred>
		_vector<size_t> all_pos_of_true(_Pred&& pred) const {
			_vector<size_t> result;
			_foreach(e)
				if (pred(*e))
					result.push_back(e - data_);
			return result;
		}


		/// <summary>
		/// Searches the vector for element for which specified condition is fulfilled.
		/// </summary>
		/// <remarks>
		/// The condition can be any delegate which result is or can be converted to bool.
		/// If the vector is empty or no matching element was found, this function
		/// returns result of invalid state.
		/// </remarks>
		/// <typeparam name="_Func">deduced type of condition function</typeparam>
		/// <param name="condition">the condition to be checked</param>
		/// <returns>element fulfilling the condition</returns>
		template<class _Pred, class... _Arg>
		iterator find_by(_Pred&& pred, _Arg&&... args) & {
			_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					return iterator(*this, e - data_);
			return end();
		}

		template<class _Pred, class... _Arg>
		const_iterator find_by(_Pred&& pred, _Arg&&... args) const & {
			_const_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					return const_iterator(*this, e - data_);
			return cend();
		}

		template<class _Pred, class... _Arg>
		move_iterator find_by(_Pred&& pred, _Arg&&... args) && {
			_const_foreach(e)
				if (pred(*e, (_Arg&&)args...))
					return move_iterator(*this, e - data_);
			return mend();
		}



		/// <summary>
		/// Searches the vector for element for which specified member has some value.
		/// </summary>
		/// <remarks>
		/// If the vector is empty or no matching element was found, this function
		/// returns result of invalid state.
		/// </remarks>
		/// <typeparam name="_Member">the type of checked member</typeparam>
		/// <param name="member">member field to be checked</param>
		/// <param name="value">the searched member value</param>
		/// <returns>element fulfilling the condition</returns>
		//TODO 
		template<class _Member, class _T>
		iterator find_by(_Member(_T::*member), _Member const& value) {
			_foreach(e)
				if (e->*member == value)
					return iterator(*this, e-data_);
			return end();
		}


		/// <summary>
		/// Searches the vector for element for which specified member function returns some value.
		/// </summary>
		/// <remarks>
		/// If the vector is empty or no matching element was found, this function
		/// returns result of invalid state.
		/// </remarks>
		/// <typeparam name="_Ret">the return type of checked member function</typeparam>
		/// <param name="member">member field to be checked</param>
		/// <param name="value">the searched member value</param>
		/// <returns>element fulfilling the condition</returns>
		template<class _Ret, class _T, class... _Arg>
		iterator find_by(_Ret(_T::*member)(_Arg...), _Ret const& value, _Arg&&... args) {
			_foreach(e)
				if ((e->*member)((_Arg&&)args...) == value)
					return iterator(*this, e-data_);
			return end();
		}


		/// <summary>
		/// Replaces each occurence of specified value with other value.
		/// </summary>
		/// <remarks>
		/// Maximum of replacements can be specified by setting \a max. Maximum set to 0 means 
		/// there is no limit of replacements, which is default.
		/// </remarks>
		/// <param name="what">element to be replaced</param>
		/// <param name="value">element to be placed instead of found elements</param>
		/// <param name="max">maximum number of replacements, DEFAULT: 0 (unlimited replacements)</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& replace(const _Type& what, const _Type& value, unsigned max = 0) & {
			size_t nrep = 0;
			for (size_t i = 0; i < size_; ++i) {
				if (data_[i] == what) {
					_reconstruct(data_ + i, value);
					if (++nrep == max) return *this;
				}
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& replace(const _Type& what, const _Type& value, unsigned max = 0) && {
			return _rv(replace(what, value, max));
		}


	private:
		static void reverse_(_Type* data, size_t size) {
			_Type* e1 = data;
			_Type* e2 = data + size - 1;
			while (e1 < e2) {
				x::swap(*e1, *e2);
				++e1;
				--e2;
			}
		}


	public:
		/// <summary>
		/// Sets elements of vector in the reverse order.
		/// </summary>
		/// <returns>reference to the caller</returns>
		FORCEINLINE _vector<_Type>& reverse() & {
			reverse_(data_, size_);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& reverse() && {
			return _rv(reverse());
		}

	private:
		template<class _Container>
		void reorder_impl_(_Container&& order) {
			_Type* newdata = allocate_(size_);
			_Type* e = newdata;
			for (auto i : order)
				_trivcopy(e++, data_ + i);
			deallocate_(data_);
			data_ = newdata;
			reserved_ = size_;
		}

	public:
		template<class _Container>
		FORCEINLINE _vector<_Type>&& reorder(_Container&& order) & {
			reorder_impl_(std::forward<_Container>(order));
			return *this;
		}

		template<class _Container>
		FORCEINLINE _vector<_Type>&& reorder(_Container&& order) && {
			reorder_impl_(std::forward<_Container>(order));
			return _rvthis;
		}

		_vector<_Type>& reorder(std::initializer_list<size_t> order) & {
			reorder_impl_(order);
			return *this;
		}

		_vector<_Type>&& reorder(std::initializer_list<size_t> order) && {
			reorder_impl_(order);
			return _rvthis;
		}

		/// <summary>
		/// Moves elments by \a n places, making elements that go beyond the vector appear on
		/// the beginning.
		/// </summary>
		/// <remarks>
		/// If \a n is positive, elements will be moved towards higher position, if negative:
		///	towards 0. \a n can be any number, if it exceeds the size of vector, the vector will
		/// be shifted by the remainder from division of \a n by size.
		/// </remarks>
		/// <param name="n">number of places to shift the vector</param>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& shift(int n) & {
			if (n %= (int)size_) {
				if (n < 0)
					n += size_;
				_Type* newData = allocate_(reserved_);
				::memcpy(newData, data_ + size_ - n, n * sizeof(_Type));
				::memcpy(newData + n, data_, (size_ - n) * sizeof(_Type));
				deallocate_();
				data_ = newData;
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& shift(int n) && {
			return _rv(shift(n));
		}

		_vector<_Type>& shift_left() & {
			if (size_ < 2)
				return *this;
			if (reserved_ > size_) {
				assign(data_ + size_, data_);
				::memcpy(data_, data_ + 1, size_ * sizeof(_Type));
			} else {
				__int8 elem[sizeof(_Type)];
				assign(reinterpret_cast<_Type*>(elem), data_);
				::memcpy(data_, data_ + 1, (size_ - 1) * sizeof(_Type));
				assign(data_ + size_ - 1, reinterpret_cast<_Type*>(elem));
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& shift_left() && {
			return _rv(shift_left());
		}


		_vector<_Type>& shift_right() & {
			if (size_ < 2)
				return *this;
			__int8 elem[sizeof(_Type)];
			assign(reinterpret_cast<_Type*>(elem), data_ + size_ - 1);
			::memmove(data_ + 1, data_, (size_ - 1) * sizeof(_Type));
			assign(data_, reinterpret_cast<_Type*>(elem));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& shift_right() && {
			return _rv(shift_right());
		}


		/*_vector<_Type>& pivot(size_t pos) & {
		if (size_ <= 1)
		return *this;
		if (pos >= size_)
		reverse_(data_, size_);
		else {
		if (pos == 0)
		reverse_(data_ + 1, size_ - 1);
		else if (pos == size_ - 1)
		reverse_(data_, size_ - 1);
		else {
		reverse_(data_, pos);
		reverse_(data_ + pos + 1, size_ - pos - 1);
		}
		}
		return *this;
		}*/

		_vector<_Type>& pivot(size_t pos) & {
			if (size_ <= 1)
				return *this;
			if (pos >= size_)
				reverse_(data_, size_);
			else {
				size_t t = size_ - pos - 1;
				reverse_(data_, t);
				reverse_(data_ + t, pos + 1);
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& pivot(size_t pos) && {
			return _rv(pivot(pos));
		}


		/// <summary>
		/// Erases element of given position from vector and returns its value. 
		/// </summary>
		/// <remarks>
		/// If the position &gt= size of vector, result of invalid state will be returned.
		/// </remarks>
		/// <param name="pos">position of the element to be taken</param>
		/// <returns>the taken element</returns>
		opt<_Type> take(size_t pos) {
			if (pos < size_) {
				_Type elem = data_[pos];
				erase(pos);
				return elem;
			}
			return opt<_Type>::INVALID;
		}


		FORCEINLINE _Type&& take() {
			return (_Type&&)data_[--size_];
		}


		/// <summary>
		/// Searches the vector for occurences of repeated elements and removes the repetitions.
		/// </summary>
		/// <remarks>
		/// After calling this function the vector will contain element of every value that occured
		/// beforehand once. All repetitions are removed, the objects are destructed properly. 
		/// The order of elements can change significantly.
		/// </remarks>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& unify() & {
			for (size_t i = 0; i < size_; ++i) {
				for (size_t k = i + 1; k < size_; ) {
					if (data_[i] == data_[k])
						dump(k);
					else
						++k;
				}
			}
			return *this;
		}

		FORCEINLINE _vector<_Type>&& unify() && {
			return _rv(unify());
		}

		_vector<_Type>& unify(_TypeConst min, _TypeConst max) & {
			bool* foundMap = new bool[max - min + 1]{false};
			unify(min, max, foundMap, false);
			delete[] foundMap;
			return *this;
		}

		FORCEINLINE _vector<_Type>&& unify(_TypeConst min, _TypeConst max) && {
			return _rv(unify(min, max));
		}

		_vector<_Type>& unify(_TypeConst min, _TypeConst max, bool* foundMap, bool zeroMap = false) & {
			size_t range = max - min + 1;
			if (zeroMap)
				::memset(foundMap, 0, range);
			size_t last = 0;
			for (size_t i = 0; i < size_; ++i) {
				_Type elem = data_[i];
				if (bool& b = foundMap[elem - min]; !b) {
					b = true;
					data_[last++] = elem;
				}
			}
			size_ = last;
			return *this;
		}

		_vector<_Type>&& unify(_TypeConst min, _TypeConst max, bool* foundMap, bool zeroMap = false) && {
			return _rv(unify(min, max, foundMap, zeroMap));
		}

		FORCEINLINE _vector<_Type>& unify(_TypeConst max) & {
			return unify(0, max);
		}

		FORCEINLINE _vector<_Type>&& unify(_TypeConst max) && {
			return _rv(unify(0, max));
		}


		FORCEINLINE _vector<_Type>& unify(_TypeConst max, bool* foundMap, bool zeroMap = false) & {
			return unify(0, max, foundMap, zeroMap);
		}

		FORCEINLINE _vector<_Type>&& unify(_TypeConst max, bool* foundMap, bool zeroMap = false) && {
			return _rv(unify(0, max, foundMap, zeroMap));
		}


		/*_vector<_Type> unique() const & {
		_vector<_Type> result(size_ / 2 + 1);
		for (size_t i = 0; i < size_; ++i) {
		for (size_t k = i + 1; k < size_; ++k) {
		if (data_[i] == data_[k])
		goto _END_INNER_;
		}
		result.push_back(data_[i]);
		_END_INNER_:;
		}
		return result;
		}


		FORCEINLINE _vector<_Type>&& unique() && {
		return _rv(unify());
		}*/


		template<template<class...> class _Res = x::tuple, class... _Other>
		_vector<_Res<_Type, _Other...>> bind(_vector<_Other> const& ... other) const & {
			size_t resSize = x::va::min(size_, other.size_...);
			_vector<_Res<_Type, _Other...>> result(resSize);
			for (size_t i = 0; i < resSize; ++i)
				new (result.data_ + i) _Res<_Type, _Other...>{data_[i], other.data_[i]...};
			result.size_ = resSize;
			return result;
		}

		//template<template<class...> class _Res = x::two, class... _Other>
		//_vector<_Res<_Type, _Other...>> && bind(_vector<_Other> const& ... other) && {
		//	size_t resSize = x::va::min(other.size_...);
		//	_vector<_Res<_Type, _Other...>> && res = reinterpret<_Res<_Type, _Other...>>();
		//	
		//	reserved_ = resSize;
		//	//_vector<_Res<_Type, _Other...>> bindRes(resSize, resSize);
		//	for (size_t i = 0; i < resSize; ++i)
		//		_construct_t(_Res<_Type, _Other...>, bindRes.data_ + i, {data_[i], other.data_[i]...});
		//	return bindRes;
		//}

	private:
		template<class _OutLeft, class _OutRight, class _Left, class _Right, class _Cmp, class... _Arg>
		static _vector<_Type> sorted_merge_impl_(_Left&& left, _Right&& right, _Cmp&& cmp, _Arg&&... args) {
			_vector<_Type> result(left.size_ + right.size_);
			result.size_ = result.reserved_;
			_Type const* l = left.data_;
			_Type const* r = right.data_;
			_foreach_v(d, result) {
				if (cmp(*l, *r, (_Arg&&)args...))
					_construct(d, (_OutLeft)*l++);
				else
					_construct(d, (_OutRight)*r++);
			}
			return result;
		}


		template<class _OutLeft, class _OutRight, class _Left, class _Right, class _Cmp, class... _Arg>
		static void sorted_merge_impl_(_Left&& left, _Right&& right, _vector<_Type>& dest, _Cmp&& cmp, _Arg&&... args) {
			dest.clear_resize_(left.size_ + right.size_);
			_Type const* l = left.data_;
			_Type const* r = right.data_;
			_foreach_v(d, dest) {
				if (cmp(*l, *r, (_Arg&&)args...))
					_construct(d, (_OutLeft)*l++);
				else
					_construct(d, (_OutRight)*r++);
			}
		}


		template<class _OutLeft, class _OutRight, class _Left, class _Right, class _Cmp, class... _Arg>
		static void sorted_self_merge_impl_(_Left&& left, _Right&& right, _Cmp&& cmp, _Arg&&... args) {
			left.reserve(left.size_ + right.size_);
			_Type* l = left.pback();
			_Type const* r = right.pcback();
			_Type const* ldata = left.data_;
			_Type const* rdata = right.data_;
			_Type const* lback = left.data_ + left.reserved_ - 1;
			for (; l >= ldata && r >= rdata) {
				if (cmp(*l, *r, (_Arg&&)args...)) {
					_trivcopy(lback, l);
					--l;
				}
				else {
					_trivcopy(lback, r);
					--r;
				}
				--lback;
			}
			left.enable();
		}

	public:
		template<class _Cmp, class... _Arg>
		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type> const& other, _Cmp&& cmp, _Arg&&... args) const & {
			return sorted_merge_impl_<_Type const&, _Type const&>(
				*this, other, (_Cmp&&)cmp, (_Arg&&)args...);
		}

		template<class _Cmp, class... _Arg>
		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type> const& other, _Cmp&& cmp, _Arg&&... args) && {
			return sorted_merge_impl_<_Type&&, _Type const&>(
				_rvthis, other, (_Cmp&&)cmp, (_Arg&&)args...);
		}

		template<class _Cmp, class... _Arg>
		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type>&& other, _Cmp&& cmp, _Arg&&... args) const & {
			return sorted_merge_impl_<_Type const&, _Type&&>(
				*this, _rv(other), (_Cmp&&)cmp, (_Arg&&)args...);
		}

		template<class _Cmp, class... _Arg>
		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type>&& other, _Cmp&& cmp, _Arg&&... args) && {
			return sorted_merge_impl_<_Type&&, _Type&&>(
				_rvthis, _rv(other), (_Cmp&&)cmp, (_Arg&&)args...);
		}


		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type> const& other) const & {
			return sorted_merge_impl_<_Type const&, _Type const&>(
				*this, other, [](auto&& e1, auto&& e2) {return e1 < e2; });
		}

		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type> const& other) && {
			return sorted_merge_impl_<_Type&&, _Type const&>(
				_rvthis, other, [](auto&& e1, auto&& e2) {return e1 < e2; });
		}

		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type>&& other) const & {
			return sorted_merge_impl_<_Type const&, _Type&&>(
				*this, _rv(other), [](auto&& e1, auto&& e2) {return e1 < e2; });
		}

		FORCEINLINE _vector<_Type> sorted_merge(_vector<_Type>&& other) && {
			return sorted_merge_impl_<_Type&&, _Type&&>(
				_rvthis, _rv(other), [](auto&& e1, auto&& e2) {return e1 < e2; });
		}







		void merge_sort_impl_(_Type* buffer, size_t begin, size_t end) {
			size_t partsize = end - begin + 1;
			size_t split = (begin + end) / 2;
			if (begin < split)
				merge_sort_impl_(buffer, begin, split);
			if (split + 1 < end)
				merge_sort_impl_(buffer, split + 1, end);

			_Type const* e1 = data_ + begin;
			_Type const* e2 = data_ + split + 1;
			_Type const* end1 = e2;
			_Type const* end2 = data_ + end;
			_Type* b = buffer;
			while (e1 <= end1 && e2 <= end2) {
				if (*e1 < *e2) {
					_trivcopy(b, e1++);
					++e1;
				} else {
					_trivcopy(b, e2);
					++e2;
				}
				++b;
			}
			if (e1 < end1)
				::memcpy(b, e1, (end1 - e1 + 1) * sizeof(_Type));
			else if (e2 < end2)
				::memcpy(b, e2, (end2 - e2 + 1) * sizeof(_Type));
			::memcpy(data_ + begin, buffer, partsize * sizeof(_Type));
			pretty_println();
		}


		_vector<_Type>& merge_sort() {
			_Type* buffer = allocate_(size_);
			merge_sort_impl_(buffer, 0, size_ - 1);
			deallocate_(buffer);
			return *this;
		}


		/*	_vector<_Type>& merge(_vector<_Type>& other) {
		size_t newsize = size_ + other.size_;
		reserve(newsize);
		_Type* end = data_ + size_;
		size_ = newsize;
		_Type* e = data_;
		_Type* o = other.data_;
		_Type const* t = nullptr;
		while (e < end) {
		if (*e < *o)
		++e;
		else {
		x::swapp(e++, o);
		pretty_println();
		other.pretty_println();
		cout << "\n";
		if (*)
		if (o[1] < *o) {
		t = other.data_;
		++o;
		}
		}
		}
		end = data_ + size_;
		if (t != nullptr) {
		while (e < end) {
		if (*t < *o)
		_trivcopy(e++, t++);
		else
		_trivcopy(e++, o++);
		pretty_println();
		other.pretty_println();
		cout << "\n";
		}
		}

		return *this;
		}*/


	protected:
		template<size_t _dim = DIM_>
		enable_if<_dim >= 2,
			void> atomic_copy_to_(_vector<atomic_type>& other) const {
			for (size_t i = 0; i < size_; ++i)
				data_[i].atomic_copy_to_(other);
		}

		template<size_t _dim = DIM_>
		FORCEINLINE enable_if<_dim == 1,
			void> atomic_copy_to_(_vector<atomic_type>& other) const {
			other.append(*this);
		}


	public:
		template<size_t _dim = DIM_>
		enable_if<_dim >= 2,
			_vector<atomic_type>> flatten() const & {
			if (size_ > 0) {
				_vector<atomic_type> result(size_ * 2 + 1);
				atomic_copy_to_(result);
				return result;
			} else
				return _vector<atomic_type>(1);
		}

		template<size_t _dim = DIM_>
		FORCEINLINE enable_if<_dim == 1,
			_vector<atomic_type> const&> flatten() const & noexcept {
			return *this;
		}

		template<size_t _dim = DIM_>
		FORCEINLINE enable_if<_dim == 1,
			_vector<atomic_type>&> flatten() & noexcept {
			return *this;
		}

		template<size_t _dim = DIM_>
		FORCEINLINE enable_if<_dim == 1,
			_vector<atomic_type>&&> flatten() && noexcept {
			return _rvthis;
		}


		//template<template<class, class> _Temp>
		//using make_variadic_t = typename make_variadic<_Temp>::type;

		//template<template<class,class> class _Res, class _Other>
		//_vector<_Res<_Type, _Other>> bind(_vector<_Other> const& other) const
		//{
		//	return reinterpret_cast<_vector<_Res<_Type, _Other>>&&>(bind<typename make_variadic<_Res>::type>(other));
		//	/*size_t resSize = x::va::min(other.size_...);
		//	_vector<_Res<_Type, _Other>> bindRes(resSize, resSize);
		//	for (size_t i = 0; i < resSize; ++i)
		//		_construct_t(_Res<_Type, _Other>, bindRes.data_ + i, {data_[i], other.data_[i]});
		//	return bindRes;*/
		//}



		/// <summary>
		/// Passes vector's elements to ostream iteratively.
		/// </summary>
		/// <remarks>
		/// Each element is by default separated with space. New line character is printed after
		/// passing all elements. If the contained type cannot be passed to ostream with operator&lt&lt,
		/// this function will fail to compile.
		/// </remarks>
		/// <param name="os">the ostream to print elements</param>
		/// <param name="vec">the vector to be printed</param>
		/// <returns>reference to the left-hand side ostream</returns>
		template<class _Elem, class _Traits>
		friend std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& os, _vector<_Type> const& vec) {
			vec.write_impl_(os);
			return os;
		}


		//TODO moving _Type&& and from _vector<_Type>&&
		friend _vector<_Type>& operator>>(_vector<_Type>& vec, _Type& obj) {
			obj = vec.back();
			return vec.pop_back();
		}


		friend _vector<_Type>& operator<<(_vector<_Type>& vec, _Type& obj) {
			return vec.push_back(obj);
		}


		friend _vector<_Type>& operator >> (_vector<_Type>& v1, _vector<_Type>& v2) {
			_trivcopy(v2.data_ + v2.size_ - 1, v1.back());
			--v1.size_;
			return v1;
		}

		friend _vector<_Type>& operator << (_vector<_Type>& v1, _vector<_Type>& v2) {
			_trivcopy(v1.data_ + v1.size_ - 1, v2.back());
			--v2.size_;
			return v1;
		}

		/// <summary>
		/// Reads one input from the input stream and pushes it back as new element.
		/// </summary>
		/// <remarks>
		/// If the contained type has no overloaded operator>> or is not fundamental type, this function
		/// will fail to compile.
		/// </remarks>
		/// <param name="is">the input stream</param>
		/// <param name="vec">the vector to add element from input</param>
		/// <returns>reference to the caller</returns>
		template<class _Elem, class _Traits>
		friend std::basic_istream<_Elem, _Traits>& operator >> (std::basic_istream<_Elem, _Traits>& is, _vector<_Type> &vec) {
			if (vec.size_ >= vec.reserved_)
				vec.extend();
			is >> vec.data_[vec.size_++];
			return is;
		}


		//? is.eof() probably incorrect - to check
		//template<class _Elem, class _Traits>
		//_vector<_Type>& read(size_t begin, size_t end, std::basic_istream<_Elem, _Traits>& is) {
		//	for (size_t i = begin; i <= end && !is.eof(); ++i)
		//		is >> data_[i];
		//	return *this;
		//}


		template<class _Elem, class _Traits>
		_vector<_Type>& read(std::basic_istream<_Elem, _Traits>& is) & {
			while (is.good()) {
				if (size_ >= reserved_)
					extend();
				_construct(data_ + size_);
				is >> data_[size_];
				/*if (is.fail()) {
					_destruct(data_ + size_);
					break;
				}*/
				++size_;
			}
			return *this;
			/*if (size_ >= reserved_)
				extend();
			_construct(data_ + size_);
			while (is >> data_[size_]) {
				++size_;
				if (size_ >= reserved_)
					extend();
				_construct(data_ + size_);
			}
			_destruct(data_ + size_);
			return *this;*/
		}

		template<class _Elem, class _Traits>
		FORCEINLINE _vector<_Type>&& read(std::basic_istream<_Elem, _Traits>& is) && {
			return _rv(read(is));
		}


		template<class _Char = char>
		FORCEINLINE _vector<_Type>& read(char const* filename) & {
			return read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename));
		}


		template<class _Char = char>
		FORCEINLINE _vector<_Type>&& read(char const* filename) && {
			return _rv(read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename)));
		}


		template<class _Char = char>
		_vector<_Type>& read(std::string const& filename) & {
			return read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename));
		}


		template<class _Char = char>
		_vector<_Type>&& read(std::string const& filename) && {
			return _rv(read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename)));
		}


		/// <summary>
		/// Reads a number of elements iteratively asking for input from specified istream.
		/// </summary>
		/// <remarks>
		/// The size of vector is set to \a newSize and this amount of elements are read.
		/// If the contained type has no overloaded operator>> or is not fundamental type, this function
		/// will fail to compile. The purpose of this function is e.g. to conveniently initialize 
		/// vector of strings or any other text dependent types, to load a number of strings from 
		/// input at once, etc.
		/// </remarks>
		/// <param name="is">the input stream</param>
		/// <param name="newSize">the desired number of elements to be read</param>
		/// <returns>reference to the caller</returns>
		/// <see cref="read_until"/>
		template<class _Char, class _Traits>
		_vector<_Type>& read(std::basic_istream<_Char, _Traits>& is, size_t size) & {
			clear_resize_(size);
			_foreach(e) {
				_construct(e);
				if (!(is >> *e)) {
					_destruct(e);
					size_ = e - data_;
					return *this;
				}
			}
			return *this;
		}

		template<class _Char, class _Traits>
		FORCEINLINE _vector<_Type>&& read(std::basic_istream<_Char, _Traits>& is, size_t size) && {
			return _rv(read(is, size));
		}


		template<class _Char = char>
		_vector<_Type>& read(char const* filename, size_t size) & {
			return read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename), size);
		}

		template<class _Char = char>
		FORCEINLINE _vector<_Type>&& read(char const* filename, size_t size) && {
			return _rv(read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename), size));
		}

		template<class _Char = char>
		_vector<_Type>& read(std::string const& filename, size_t size) & {
			return read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename), size);
		}

		template<class _Char = char>
		FORCEINLINE _vector<_Type>&& read(std::string const& filename, size_t size) && {
			return _rv(read(std::basic_ifstream<_Char, std::char_traits<_Char>>(filename), size));
		}


		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& read_member(std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			_foreach(e) {
				if (!(is >> ... >> (e->*member)))
					break;
			}
			return *this;
		}

		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& read_member(size_t offset, std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			_foreach_o(e, offset) {
				if (!(is >> ... >> (e->*member)))
					break;
			}
			return *this;
		}

		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& read_member(size_t offset, size_t size, std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			if (offset + size > size_)
				size = size_ - offset;
			_foreach_from_s(e, offset, size) {
				if (!(is >> ... >> (e->*member)))
					break;
			}
			return *this;
		}


		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& binary_read_member(std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			_foreach(e) {
				if (!(is.read(reinterpret_cast<char*>(&(e->*member)), sizeof(decltype(e->*member))) && ...))
					break;
			}
			return *this;
		}

		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& binary_read_member(size_t offset, std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			_foreach_o(e, offset) {
				if (!(is.read(reinterpret_cast<char*>(&(e->*member)), sizeof(decltype(e->*member))) && ...))
					break;
			}
			return *this;
		}

		template<class _Char, class _Traits, class... _Member, class _T>
		_vector<_Type>& binary_read_member(size_t offset, size_t size, std::basic_istream<_Char, _Traits>& is, _Member(_T::*...member)) {
			if (offset + size > size_)
				size = size_ - offset;
			_foreach_from_s(e, offset, size) {
				if (!(is.read(reinterpret_cast<char*>(&(e->*member)), sizeof(decltype(e->*member))) && ...))
					break;
			}
			return *this;
		}


		/*template<class _Char, class _Traits, class _Member, class _T = _Type>
		std::enable_if_t<std::is_class_v<_T>,
			_vector<_Type>&> read_member(std::basic_istream<_Char, _Traits>& is, _Member(_T::*member), size_t offset, size_t size = MAX_SIZE) {
			if (offset >= size_)
				return *this;
			if (offset + size > size_)
				size = size_ - offset;
			_foreach_from_s(e, offset, size) {
				if (!(is >> (e->*member)))
					break;
			}
			return *this;
		}*/


		/*template<class _Char, class _Traits, class _Member, class _T = _Type>
		std::enable_if_t<std::is_class_v<_T>,
		_vector<_Type>&> read_member(std::basic_istream<_Char, _Traits>& is, _Member(_T::*member)) {
			_foreach(e) {
				if (!(is >> (e->*member)))
					break;
			}
			return *this;
		}


		template<class _Char, class _Traits, class _Member, class _T = _Type>
		std::enable_if_t<std::is_class_v<_T>,
			_vector<_Type>&> read_member(std::basic_istream<_Char, _Traits>& is, _Member(_T::*member), size_t offset, size_t size = MAX_SIZE) {
			if (offset >= size_)
				return *this;
			if (offset + size > size_)
				size = size_ - offset;
			_foreach_from_s(e, offset, size) {
				if (!(is >> (e->*member)))
					break;
			}
			return *this;
		}*/


		/// <summary>
		/// Reads elements iteratively asking for input from specified istream until the read element
		/// is equal to given \a end value.
		/// </summary>
		/// <remarks>
		/// The size of vector is set to the amount of elements read.
		/// If the contained type has no overloaded operator>> or is not fundamental type, this function
		/// will fail to compile.
		/// </remarks>
		/// <param name="is">the input stream</param>
		/// <param name="end">a value that terminates reading to vector</param>
		/// <returns>reference to the caller</returns>
		/// <see cref="read_fully"/>
		_vector<_Type>& read_until_value(std::istream& is, _Type const& end) & {
			_Type elem;
			if (!is.eof())
				is >> elem;
			while (!(elem == end) && !is.eof()) {
				push_back(elem);
				is >> elem;
			}
			return *this;
		}


		_vector<_Type>& read_until_value(std::istream& is, _Type const& end, size_t expected) & {
			reserve(expected);
			return read_until(is, end);
		}


		FORCEINLINE _vector<_Type>&& read_until_value(std::istream& is, _Type const& end) && {
			return _rv(read_until_value(is, end));
		}


		FORCEINLINE _vector<_Type>&& read_until_value(std::istream& is, _Type const& end, size_t expected) && {
			return _rv(read_until_value(is, end, expected));
		}


		template<class _Pred>
		_vector<_Type>& read_until(std::istream& is, _Pred&& pred) & {
			_Type elem;
			if (is.eof())
				is >> elem;
			while (!(*pred)(elem) && !is.eof()) {
				push_back(elem);
				is >> elem;
			}
			return *this;
		}


		template<class _Pred>
		_vector<_Type>& read_until(std::istream& is, _Pred&& pred, size_t expected) & {
			reserve(expected);
			return read_until(is, (_Pred&&)pred);
		}


		template<class _Pred>
		FORCEINLINE _vector<_Type>&& read_until(std::istream& is, _Pred&& pred) && {
			return _rv(read_until(is, (_Pred&&)pred));
		}


		template<class _Pred>
		FORCEINLINE _vector<_Type>&& read_until(std::istream& is, _Pred&& pred, size_t expected) && {
			return _rv(read_until(is, (_Pred&&)pred, expected));
		}

	private:
		template<class _Func, size_t... _i>
		FORCEINLINE auto expand_pass_(_Func&& func, seq<_i...> const&) {
			return func(data_[_i]...);
		}

	public:
		template<class _Func>
		auto pass(_Func&& func) {
			return expand_pass_(func, seq_v<argnum_v<_Func>>);
		}


		/// <summary>
		/// Iterates through vector and calls a function on every element.
		/// </summary>
		/// <remarks>
		/// The function to be called can be any delegate that takes object of contained type,
		/// reference or type convertible to contained type as argument.
		/// The resulting type of function can be any, but the results are not preserved anywhere
		/// and are not checked so it is suggested to use this function with delegates returning void.
		/// See function compute for receiving results from multiple function calls on elements.
		/// </remarks>
		/// <typeparam name="_Func">deduced type of function</typeparam>
		/// <param name="func">function to be called on elements</param>
		/// <returns>reference to the caller</returns>
		template<class _Func, class... _Arg>
		_vector<_Type>& execute(_Func&& func, _Arg&&... args) & {
			_foreach(e)
				func(*e, (_Arg&&)args...);
			return *this;
		}

		template<class _Func, class... _Arg>
		_vector<_Type> const& execute(_Func&& func, _Arg&&... args) const & {
			_const_foreach(e)
				func(*e, (_Arg&&)args...);
			return *this;
		}

		template<class _Func, class... _Arg>
		_vector<_Type>&& execute(_Func&& func, _Arg&&... args) && {
			_foreach(e)
				func((_Type&&)*e, (_Arg&&)args...);
			return _rvthis;
		}


		template<class _Ret, class _T, class... _Arg>
		_vector<_Type>& call(_Ret(_T::*member)(_Arg...), _Arg&&... args) {
			if constexpr (std::is_pointer_v<_Type>) {
				_foreach(e)
					(void)((*e)->*member)((_Arg&&)args...);
			} else {
				_foreach(e)
					(void)(e->*member)((_Arg&&)args...);
			}
			return *this;
		}

		template<class _Ret, class _T, class... _Arg>
		_vector<_Type> const& call(_Ret(_T::*member)(_Arg...) const, _Arg&&... args) const {
			if constexpr (std::is_pointer_v<_Type>) {
				_const_foreach(e)
					(void)((*e)->*member)((_Arg&&)args...);
			} else {
				_const_foreach(e)
					(void)(e->*member)((_Arg&&)args...);
			}
			return *this;
		}

	protected:
		template<class _Func, size_t... _i>
		FORCEINLINE auto apply_on_data_(_Func&& func, size_t pos, seq<_i...>&) const {
			return func(data_[pos + _i]...);
		}

	public:
		template<class... _Func>
		auto compute(_Func&&... func) const {
			using Res = std::conditional_t<sizeof...(_Func) >= 2,
					tuple<std::result_of_t<_Func(_Type)>...>,
					std::result_of_t<first_t<_Func...>(_Type)>>;
					_vector<Res> result(size_);
			_pair_foreach(*this, s, result, d)
				_construct_t(Res, d, func(*s)...);
			result.size_ = size_;
			return result;
		}


		template<class _Size0, class... _Size>
		_vector_nd_t<_Type, sizeof...(_Size) + 2> reshape(_Size0 size0, _Size... sizes) const & {
			return reshape(sizes...).reshape(size0);
			/*using sub_vector = _vector_nd_t<_Type, _dim - 1>;
			if (size_ == 0)
			return sub_vector();
			auto subSize = size0 * (sizes * ...);
			_vector_nd_t<_Type, _dim> result(size_ / subSize + 1);
			size_t p = size0;
			size_t i = 0;
			for (; p <= size_; p += size0, ++i) {
			_vector<_Type>* vptr = result.data_ + i;
			new (vptr) sub_vector(subset_view(p-size0, p-1).reshape(;
			copy_(vptr->data_, data_ + p - size, size);
			}
			if (p > size_) {
			size_t lastSize = size_ - (p - size);
			_vector<_Type>* vptr = result.data_ + i;
			new (vptr) _vector<_Type>(Enable(lastSize));
			copy_(vptr->data_, data_ + p - size, lastSize);
			}
			result.size_ = i + 1;
			return result;*/
		}

		template<class _Size0, class... _Size>
		_vector_nd_t<_Type, sizeof...(_Size) + 2> reshape(_Size0 size0, _Size... sizes) && {
			return move().reshape(sizes...).reshape(size0);
		}


		//TODO: reshape(0)
		template<class _Size>
		_vector_nd_t<_Type, 2> reshape(_Size dim) const & {
			if ((size_t)dim >= size_)
				return _vector_nd_t<_Type, 2>{*this};
			_vector_nd_t<_Type, 2> result(size_ / (size_t)dim + 1);
			_Type const* e = data_;
			_Type const* elast = data_ + size_ - (size_t)dim;
			_vector<_Type>* vptr = result.data_;
			for (; e <= elast; e += (size_t)dim, ++vptr) {
				_construct_t(_vector<_Type>, vptr, dim);
				vptr->size_ = (size_t)dim;
				copy_(vptr->data_, e, (size_t)dim);
			}
			size_t lastSize = data_ + size_ - e;
			if (lastSize > 0) {
				_construct_t(_vector<_Type>, vptr, lastSize);
				vptr->size_ = lastSize;
				copy_(vptr->data_, e, lastSize);
				result.size_ = result.reserved_;
			} else
				result.size_ = result.reserved_ - 1;
			return result;
		}


		template<class _Size>
		_vector_nd_t<_Type, 2> reshape(_Size dim) && {
			if ((size_t)dim >= size_)
				return _vector_nd_t<_Type, 2>{*this};
			_vector_nd_t<_Type, 2> result(size_ / (size_t)dim + 1);
			_Type* e = data_;
			_Type* elast = data_ + size_ - (size_t)dim;
			_vector<_Type>* vptr = result.data_;
			for (; e <= elast; e += (size_t)dim, ++vptr) {
				_construct_t(_vector<_Type>, vptr, dim);
				vptr->size_ = (size_t)dim;
				::memcpy(vptr->data_, e, (size_t)dim * sizeof(_Type));
				//move_(vptr->data_, e, dim);
			}
			size_t lastSize = data_ + size_ - e;
			if (lastSize > 0) {
				_construct_t(_vector<_Type>, vptr, lastSize);
				vptr->size_ = lastSize;
				::memcpy(vptr->data_, e, lastSize * sizeof(_Type));
				//move_(vptr->data_, e, lastSize);
				result.size_ = result.reserved_;
			} else
				result.size_ = result.reserved_ - 1;
			size_ = 0;
			return result;
		}


		template<class... _Var>
		_vector<_Type>& unpack(_Var&... vars) & {
			_Type const* e = data_;
			x::va::expand{(vars = *e++)...};
			return *this;
		}

		template<class... _Var>
		_vector<_Type> const& unpack(_Var&... vars) const & {
			_Type const* e = data_;
			x::va::expand{(vars = *e++)...};
			return *this;
		}

		template<class... _Var>
		_vector<_Type>&& unpack(_Var&... vars) && {
			_Type* e = data_;
			x::va::expand{(vars = (_Type&&)*e++)...};
			return _rvthis;
			//_destruct_from(e);
			//size_ = 0;
		}


		/*template<class _Size, size_t _dim = 2>
		_vector_nd_t<_Type, _dim> reshape(_Size size) const {
		if (size_ == 0)
		return _vector_nd_t<_Type, _dim>();
		_vector_nd_t<_Type, _dim> result(size_ / size + 1);
		size_t p = size;
		size_t i = 0;
		for (; p <= size_; p += size, ++i) {
		_vector<_Type>* vptr = result.data_ + i;
		_construct_t(_vector<_Type>, vptr, size);
		vptr->enable();
		copy_(vptr->data_, data_ + p - size, size);
		}
		if (p > size_) {
		size_t lastSize = size_ - (p - size);
		_vector<_Type>* vptr = result.data_ + i;
		_construct_t(_vector<_Type>, vptr, lastSize);
		vptr->enable();
		copy_(vptr->data_, data_ + p - size, lastSize);
		}
		result.size_ = i + 1;
		return result;
		}*/


		template<class _Dst>
		_vector<_Dst> map(_Dst const* table) const {
			_vector<_Dst> result(size_);
			for (size_t i = 0; i<size_; ++i)
				result.data_[i] = table[(size_t)data_[i]];
			return result;
		}


		template<class _Member, class _Dst, class _T>
		_vector<_Dst> map(_Member(_T::*member), _Dst const* table) const {
			_vector<_Dst> result(size_);
			for (size_t i = 0; i<size_; ++i)
				result.data_[i] = table[(size_t)(data_[i].*member)];
			return result;
		}


		template<class _Member, class _Dst, class _T>
		_vector<_Dst> map(_Member(_T::*method)(), _Dst const* table) const {
			_vector<_Dst> result(size_);
			for (size_t i = 0; i<size_; ++i)
				result.data_[i] = table[(size_t)(data_[i].*method)()];
			return result;
		}


		template<class... _Pred>
		bool for_all(_Pred&&... predicates) const {
			_foreach(e)
				if (!(predicates(*e) && ...))
					return false;
			return true;
		}


		template<class... _Pred>
		bool for_any(_Pred&&... predicates) const {
			_foreach(e)
				if ((predicates(*e) && ...))
					return true;
			return false;
		}


		bool all_equal(_TypeConst value) const {
			_const_foreach(e)
				if (!(*e == value))
					return false;
			return true;
		}

		bool all_equal() const {
			if (size_ == 0)
				return true;
			_const_foreach_from(e, data_ + 1)
				if (!(*e == *data_))
					return false;
			return true;
		}


		/// <summary>
		/// Checks whether a condition is fulfilled for every element.
		/// </summary>
		/// Tests every element by execting a function on it. This function assumes that the ergument
		/// function returns a value that is bool or is convertible to bool.
		/// If the vector is empty, this function always returns true. 
		/// <param name="condition">the condition function to be checked</param>
		/// <returns>true if condition is fulfilled for every element, otherwise false</returns>
		template<class _Func, class _Ret>
		bool all_equal(_Func&& func, _Ret&& result) const {
			_foreach(e)
				if (!(func(*e) == result))
					return false;
			return true;
		}


		bool any_equal(_TypeConst value) const {
			_const_foreach(e)
				if (*e == value)
					return true;
			return false;
		}


		/// <summary>
		/// Checks whether a condition is fulfilled for any element.
		/// </summary>
		/// Tests every element by execting a function on it. This function assumes that the ergument
		/// function returns a value that is bool or is convertible to bool.
		/// If the vector is empty, this function always returns false. 
		/// <param name="condition">the condition function to be checked</param>
		/// <returns>true if condition is fulfilled for any element, otherwise false</returns>
		template<class _Func, class _Ret>
		bool any_equal(_Func&& condition, _Ret&& result) const {
			_const_foreach(e)
				if (condition(*e) == result)
					return true;
			return false;
		}


		_Type min() const {
			_Type const* pmin = data_;
			_const_foreach_from(e, data_ + 1)
				if (*e < *pmin)
					pmin = e;
			return *pmin;
		}

		_Type max() const {
			_Type const* pmax = data_;
			_const_foreach_from(e, data_ + 1)
				if (*e > *pmax)
					pmax = e;
			return *pmax;
		}

		template<class _Func>
		auto min(_Func&& func) const {
			_Type const* pmin = data_;
			auto min = func(*pmin);
			_const_foreach_from(e, data_ + 1) {
				auto res = func(*e);
				if (res < min) {
					pmin = e;
					min = res;
				}
			}
			return *pmin;
		}

		template<class _Func>
		auto max(_Func&& func) const {
			_Type const* pmax = data_;
			auto max = func(*pmax);
			_const_foreach_from(e, data_ + 1) {
				auto res = func(*e);
				if (res > max) {
					pmax = e;
					max = res;
				}
			}
			return *pmax;
		}


		auto extremes() const {
			struct Extremes {
				_Type min;
				_Type max;
			};
			_Type const* pmax = data_;
			_Type const* pmin = data_;
			_const_foreach_from(e, data_ + 1) {
				if (*e > *pmax)
					pmax = e;
				else if (*e < *pmin)
					pmin = e;
			}
			return Extremes{*pmin, *pmax};
		}

		template<class _Func>
		auto extremes(_Func&& func) const {
			struct Extremes {
				_Type min;
				_Type max;
			};
			_Type const* pmax = data_;
			_Type const* pmin = data_;
			auto max = func(*pmax);
			auto min = func(*pmin);
			_const_foreach_from(e, data_ + 1) {
				auto res = func(*e);
				if (res > max) {
					pmax = e;
					max = res;
				} else if (res < min) {
					pmin = e;
					min = res;
				}
			}
			return Extremes{*pmin, *pmax};
		}


		/// <summary>
		/// Clears all content with no memory deallocation.
		/// </summary>
		/// <remarks>
		/// This function just forgets the content stored in vector, making it empty, but the memory
		/// already allocated remains for future usage. If the contained type is class, the elements
		/// re destructed properly by a call to destructor. It is useful when one wants to use the vector
		/// further and add new elements after clearing. For explicit control of memory deallocation,
		/// see no-argument fucntion erase().
		/// </remarks>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& clear() & {
			_destruct_all();
			size_ = 0;
			return *this;
		}

		_vector<_Type>&& clear() && {
			_destruct_all();
			size_ = 0;
			return _rvthis;
		}

		/// <summary>
		/// Clears all content and allocates new block of memory of default size. 
		/// </summary>
		/// <remarks>
		/// This function just destructs the content stored in vector, making it empty, 
		/// deallocates the current memory and allocates new block of default size. If the contained 
		/// type is class, the elements are destructed properly by a call to destructor. 
		/// It is useful when one wants to use the vector further but the number of elements will
		/// be reduced. For clearing vector with no memory deallocation, see clear().
		/// </remarks>
		/// <returns>reference to the caller</returns>
		_vector<_Type>& erase() {
			if (data_ != nullptr) {
				_destruct_all();
				deallocate_();
			}
			reserved_ = 0;
			size_ = 0;
			data_ = nullptr;
			return *this;
		}


		/// <summary>
		/// Converts every element to type specified as template argument and puts them into new instance
		/// of vector containing these converted elements.
		/// </summary>
		/// <remarks>
		/// If contained type of caller vector is also vector of some type (if value of dim() &gt= 2), 
		/// this function will convert every vector element calling this function. The result will be 
		/// then a vector of vectors of type contained in contained vector. This behavior will proceed 
		/// recursively until the vector elements contain any type different than another nested vector template.
		/// The template argument type \a _To must have constructor that takes the mostly nested type as argument
		/// or the contained type has to be convertible to \a _To type, otherwise this function will fail to compile. 
		/// The caller vector is not modified.
		/// </remarks>
		/// <typeparam name="_To">the type to convert elements to</typeparam>
		/// <returns>new instance of vector of contained elements</returns>
		/// <see cref="dim"/>
		template<class _To>
		enable_if<std::is_convertible<_Type, _To>::value,
			_vector_nd_t<_To, DIM_>> convert_to() const {
			_vector_nd_t<_To, DIM_> converted(size_, size_);
			if constexpr (DIM_ == 1) {
				_pair_foreach(*this, e, converted, r)
					_construct_t(_To, r, _To(*e));
			} else {
				_pair_foreach(*this, v, converted, r)
					if constexpr (std::is_trivially_copyable_v<_vector_nd_t<_To, DIM_ - 1>>) *(r) = _vector_nd_t<_To, DIM_ - 1>(v->convert_to<_To>()); else new (r) _vector_nd_t<_To, DIM_ - 1>(v->convert_to<_To>());
				//_construct_t(_vector_nd_t<_To, DIM_ - 1>, r, v->convert_to<_To>());
			}
			converted.size_ = size_;
			return converted;
		}


		template<class _Dst>
		FORCEINLINE _vector<_Dst>& reinterpret() & {
			return *reinterpret_cast<_vector<_Dst>*>(this);
		}

		template<class _Dst>
		FORCEINLINE _vector<_Dst> const& reinterpret() const & {
			return *reinterpret_cast<_vector<_Dst> const*>(this);
		}

		template<class _Dst>
		FORCEINLINE _vector<_Dst> && reinterpret() && {
			return reinterpret_cast<_vector<_Dst>&&>(*this);
		}


		template<class _T = _Type>
		enable_if<std::is_pointer_v<_T>, 
		_vector<_Type>&> call_delete() & {
			_foreach(e)
				delete *e;
			return *this;
		}

		template<class _T = _Type>
		FORCEINLINE enable_if<std::is_pointer_v<_T>,
		_vector<_Type>&&> call_delete() && {
			return _rv(call_delete());
		}


		template<class _T = _Type>
		enable_if<std::is_pointer_v<_T>,
		_vector<_Type>&> call_array_delete() & {
			_foreach(e)
				delete[] *e;
			return *this;
		}

		template<class _T = _Type>
		FORCEINLINE enable_if<std::is_pointer_v<_T>,
		_vector<_Type>&&> call_array_delete() && {
			return _rv(call_array_delete());
		}


		FORCEINLINE std::string bitstr() const {
			return x::bitstr(data_, size_ * sizeof(_Type));
		}


		FORCEINLINE void bitstr(char* str) const {
			x::bitstr(str, data_, size_ * sizeof(_Type));
		}
			   	

		template<class _Elem, class _Traits, class _Sep, class... _SepR>
		void write(std::basic_ostream<_Elem, _Traits>& os, _Sep && separator, _SepR &&... separators) const {
			if constexpr (DIM_ == 1) {
				static_assert(sizeof...(separators) == 0);
				if (size_ == 0)
					return;
				os << data_[0];
				_const_foreach_from(e, data_ + 1)
					os << (_Sep&&)separator << *e;
			} else {
				if (size_ == 0)
					return;
				data_[0].write(os, (_SepR&&)separators...);
				_const_foreach_from(e, data_ + 1) {
					os << (_Sep&&)separator;
					e->write(os, (_SepR&&)separators...);
				}
			}
		}


		template<class _Elem, class _Traits>
		void write(std::basic_ostream<_Elem, _Traits>& os) const {
			_const_foreach(e)
				os << *e;
		}


		FORCEINLINE void write(std::string const& filename) const {
			write(std::ofstream(filename));
		}


		template<class _Elem, class _Traits, class... _Sep>
		FORCEINLINE void write(std::basic_ostream<_Elem, _Traits>& os, _Sep&&... separators) const {
			write(os, (_Sep&&)separators...);
		}


		template<class... _Sep>
		FORCEINLINE void write(std::string const& filename, _Sep &&... separators) const {
			write(std::ofstream(filename), (_Sep&&)separators...);
		}


		template<class _Out, class _Elem, class _Traits, class _Sep, class... _SepR>
		void write_as(std::basic_ostream<_Elem, _Traits>& os, _Sep && separator, _SepR &&... separators) const {
			if constexpr (DIM_ == 1) {
				static_assert(sizeof...(separators) == 0);
				if (size_ == 0)
					return;
				os << static_cast<_Out>(data_[0]);
				_const_foreach_from(e, data_ + 1)
					os << (_Sep&&)separator << static_cast<_Out>(*e);
			} else {
				if (size_ == 0)
					return;
				data_[0].write_as<_Out>(os, (_SepR&&)separators...);
				_const_foreach_from(e, data_ + 1) {
					os << (_Sep&&)separator;
					e->write_as<_Out>(os, (_SepR&&)separators...);
				}
			}
		}


		template<class _Out, class _Elem, class _Traits>
		void write_as(std::basic_ostream<_Elem, _Traits>& os) const {
			_const_foreach(e)
				os << static_cast<_Out>(*e);
		}


		template<class _Out>
		FORCEINLINE void write_as(std::string const& filename) const {
			write_as<_Out>(std::ofstream(filename));
		}


		template<class _Out, class _Elem, class _Traits, class... _Sep>
		FORCEINLINE void write_as(std::basic_ostream<_Elem, _Traits>& os, _Sep&&... separators) const {
			write_as<_Out>(os, (_Sep&&)separators...);
		}


		template<class _Out, class... _Sep>
		FORCEINLINE void write_as(std::string const& filename, _Sep &&... separators) const {
			write_as<_Out>(std::ofstream(filename), (_Sep&&)separators...);
		}


		template<class _Elem, class _Traits>
		FORCEINLINE void writeln(std::basic_ostream<_Elem, _Traits>& os) const {
			write(os);
			os << std::endl;
		}


		FORCEINLINE void writeln(std::string const& filename) const {
			write(std::ofstream(filename));
		}


		template<class _Elem, class _Traits, class... _Sep>
		FORCEINLINE void writeln(std::basic_ostream<_Elem, _Traits>& os, _Sep&&... separators) const {
			writeln(os, (_Sep&&)separators...);
			os << std::endl;
		}


		template<class... _Sep>
		FORCEINLINE void writeln(std::string const& filename, _Sep &&... separators) const {
			writeln(std::ofstream(filename), (_Sep&&)separators...);
		}


		template<class _Out, class _Elem, class _Traits>
		FORCEINLINE void writeln_as(std::basic_ostream<_Elem, _Traits>& os) const {
			write_as<_Out>(os);
			os << std::endl;
		}


		template<class _Out>
		FORCEINLINE void writeln_as(std::string const& filename) const {
			writeln_as<_Out>(std::ofstream(filename));
		}


		template<class _Out, class _Elem, class _Traits, class... _Sep>
		FORCEINLINE void writeln_as(std::basic_ostream<_Elem, _Traits>& os, _Sep&&... separators) const {
			write_as<_Out>(os, (_Sep&&)separators...);
			os << std::endl;
		}


		template<class _Out, class... _Sep>
		FORCEINLINE void writeln_as(std::string const& filename, _Sep &&... separators) const {
			writels_as<_Out>(std::ofstream(filename), (_Sep&&)separators...);
		}

	
		template<class _Elem, class _Traits, class _Header, class _Footer, class _Delim>
		void pretty_write(std::basic_ostream<_Elem, _Traits>& os, _Header&& header, _Footer&& footer, _Delim&& delim) const {
			os << header;
			if constexpr (DIM_ == 1) {
				write(os, (_Delim&&)delim);
			} else if (size_ > 0) {
				data_[0].pretty_write(os, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
				_foreach_from(v, data_ + 1) {
					os << (_Delim&&)delim;
					v->pretty_write(os, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
				}
			}
			os << footer;
		}

		template<class _Elem, class _Traits>
		FORCEINLINE void pretty_write(std::basic_ostream<_Elem, _Traits>& os) const {
			pretty_write(os, "{ ", " }", ", ");
		}


		template<class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_write(std::string const& filename, _Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write(std::ofstream(filename), (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
		}


		FORCEINLINE void pretty_write(std::string const& filename) const {
			pretty_write(std::ofstream(filename), "{ ", " }", ", ");
		}


		template<class _Out, class _Elem, class _Traits, class _Header, class _Footer, class _Delim>
		void pretty_write_as(std::basic_ostream<_Elem, _Traits>& os, _Header&& header, _Footer&& footer, _Delim&& delim) const {
			os << header;
			if constexpr (DIM_ == 1) {
				write_as<_Out>(os, (_Delim&&)delim);
			} else if (size_ > 0) {
				data_[0].pretty_write_as<_Out>(os, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
				_foreach_from(v, data_ + 1) {
					os << (_Delim&&)delim;
					v->pretty_write_as<_Out>(os, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
				}
			}
			os << footer;
		}

		template<class _Out, class _Elem, class _Traits>
		FORCEINLINE void pretty_write_as(std::basic_ostream<_Elem, _Traits>& os) const {
			pretty_write_as<_Out>(os, "{ ", " }", ", ");
		}


		template<class _Out, class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_write_as(std::string const& filename, _Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write_as<_Out>(std::ofstream(filename), (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
		}

		template<class _Out>
		FORCEINLINE void pretty_write_as(std::string const& filename) const {
			pretty_write_as<_Out>(std::ofstream(filename), "{ ", " }", ", ");
		}


		template<class... _Sep>
		FORCEINLINE void print(_Sep&&... separators) const {
			write(std::cout, (_Sep&&)separators...);
		}


		template<class... _Sep>
		FORCEINLINE void println(_Sep&&... separators) const {
			write(std::cout, (_Sep&&)separators...);
			std::cout << std::endl;
		}


		FORCEINLINE void pretty_print() const {
			pretty_write(std::cout);
		}


		template<class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_print(_Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write(std::cout, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
		}


		FORCEINLINE void pretty_println() const {
			pretty_write(std::cout);
			std::cout << std::endl;
		}


		template<class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_println(_Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write(std::cout, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
			std::cout << std::endl;
		}


		template<class _Out, class... _Sep>
		FORCEINLINE void print_as(_Sep&&... separators) const {
			write_as<_Out>(std::cout, (_Sep&&)separators...);
		}


		template<class _Out, class... _Sep>
		FORCEINLINE void println_as(_Sep&&... separators) const {
			writeln_as<_Out>(std::cout, (_Sep&&)separators...);
		}


		template<class _Out>
		FORCEINLINE void pretty_print_as() const {
			pretty_write_as<_Out>(std::cout);
		}


		template<class _Out, class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_print_as(_Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write_as<_Out>(std::cout, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
		}


		template<class _Out>
		FORCEINLINE void pretty_println_as() const {
			pretty_write_as<_Out>(std::cout);
			std::cout << std::endl;
		}


		template<class _Out, class _Header, class _Footer, class _Delim>
		FORCEINLINE void pretty_println_as(_Header&& header, _Footer&& footer, _Delim&& delim) const {
			pretty_write_as<_Out>(std::cout, (_Header&&)header, (_Footer&&)footer, (_Delim&&)delim);
			std::cout << std::endl;
		}

	protected:
		void binary_write_impl_(std::ostream& os) const {
			os.write(reinterpret_cast<char const*>(data_), size_ * sizeof(_Type));
		}

		void binary_write_impl_(std::ostream& os, size_t begin, size_t size) const {
			os.write(reinterpret_cast<char const*>(data_ + begin), size * sizeof(_Type));
		}

		INLINE void binary_write_impl_(void* buffer) const {
			::memcpy(buffer, data_, size_ * sizeof(_Type));
		}

		INLINE void binary_write_impl_(void* buffer, size_t begin, size_t size) const {
			::memcpy(buffer, data_ + begin, size * sizeof(_Type));
		}

	public:
		FORCEINLINE _vector<_Type>& binary_write(void* buffer) & {
			binary_write_impl_(buffer);
			return *this;
		}

		FORCEINLINE _vector<_Type> const& binary_write(void* buffer) const & {
			binary_write_impl_(buffer);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& binary_write(void* buffer) && {
			binary_write_impl_(buffer);
			return _rvthis;
		}

		FORCEINLINE _vector<_Type>& binary_write(size_t begin, size_t size, void* buffer) & {
			binary_write_impl_(buffer, begin, size);
			return *this;
		}

		FORCEINLINE _vector<_Type> const& binary_write(size_t begin, size_t size, void* buffer) const & {
			binary_write_impl_(buffer, begin, size);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& binary_write(size_t begin, size_t size, void* buffer) && {
			binary_write_impl_(buffer, begin, size);
			return _rvthis;
		}

		FORCEINLINE _vector<_Type>& binary_write(std::ostream& os) & {
			binary_write_impl_(os);
			return *this;
		}

		FORCEINLINE _vector<_Type> const& binary_write(std::ostream& os) const & {
			binary_write_impl_(os);
			return *this;
		}

		FORCEINLINE _vector<_Type>&& binary_write(std::ostream& os) && {
			binary_write_impl_(os);
			return _rvthis;
		}

		FORCEINLINE _vector<_Type>& binary_write(size_t begin, size_t size, std::ostream& os) & {
			binary_write_impl_(os, begin, size);
			return *this;
		}

		FORCEINLINE _vector<_Type> const& binary_write(size_t begin, size_t size, std::ostream& os) const & {
			binary_write_impl_(os, begin, size);
			return *this;
		}

		FORCEINLINE _vector<_Type> const& binary_write(size_t begin, size_t size, std::ostream& os) && {
			binary_write_impl_(os, begin, size);
			return _rvthis;
		}



		/*_vector<_Type>& read(std::istream& fs)
		{
		fs.seekg(std::ios::beg);
		std::streampos fsize = 0;
		fsize = fs.tellg();
		fs.seekg(0, std::ios::end);
		fsize = fs.tellg() - fsize;
		fs.seekg(std::ios::beg);

		clear_resize_(fsize / sizeof(_Type));
		fs.read(reinterpret_cast<char*>(data_), size_ * sizeof(_Type));
		return *this;
		}*/


		/*_vector<_Type>& binary_read(std::istream& is) & {
			clear();
			size_t nread = 0;
			char* begin = reinterpret_cast<char*>(data_);
			char* end = reinterpret_cast<char*>(data_ + reserved_);
			size_t sumread = 0;
			while (is.read(begin, end - begin), nread = is.gcount()) {
				sumread += nread;
				begin += nread;
				if (begin >= end) {
					extend();
					begin = reinterpret_cast<char*>(data_) + sumread;
					end = reinterpret_cast<char*>(data_ + reserved_);
				}
			}
			size_ = sumread / sizeof(_Type);
			return *this;
		}*/

		_vector<_Type>& binary_read(std::istream& is) & {
			clear();
			size_t bytes = 0;
			char* pdata = reinterpret_cast<char*>(data_);
			is.read(pdata, reserved_*sizeof(_Type));
			bytes += is.gcount();
			while (bytes == reserved_*sizeof(_Type)) {
				size_ = reserved_;
				extend();
				is.read(reinterpret_cast<char*>(data_ + size_), (reserved_ - size_)*sizeof(_Type));
				bytes += is.gcount();
			}
			size_ = bytes / sizeof(_Type);
			return *this;
		}

		FORCEINLINE _vector<_Type>& binary_read(std::istream& is) && {
			return _rv(binary_read(is));
		}

		_vector<_Type>& binary_read(std::istream& is, size_t fsize) & {
			clear_resize_(fsize/sizeof(_Type) + 1);
			is.read(reinterpret_cast<char*>(data_), size_ * sizeof(_Type));
			return *this;
		}

		FORCEINLINE _vector<_Type>&& binary_read(std::istream& is, size_t fsize) && {
			return _rv(binary_read(is, fsize));
		}

		/// <summary>
		/// Destructs the object.
		/// </summary> 
		/// Destructs all elements and deallocates the memory. Should not be called explicitly.<remarks>
		/// </remarks>
		~_vector() {
			if (data_ != nullptr) {
				_destruct_all();
				deallocate_();
				data_ = nullptr;
			}
		#if _DEBUG_CTOR
			std::cout << "~_vector\n";
		#endif
		}
	};


	///////////////////////////////////////////////////////////////////////////////


	template<class _Type>
	class _vector_backwards: public _vector<_Type>
	{
		using _vector<_Type>::begin;
		using _vector<_Type>::end;
		using _vector<_Type>::cbegin;
		using _vector<_Type>::cend;
		using _vector<_Type>::mbegin;
		using _vector<_Type>::mend;
		using _vector<_Type>::backwards;

		template<int _step>
		using _iterator = typename _vector<_Type>::_iterator<-_step>;

		template<int _step>
		using _const_iterator = typename _vector<_Type>::_const_iterator<-_step>;

		template<int _step>
		using _move_iterator = typename _vector<_Type>::_move_iterator<-_step>;

	public:
		using element_type = _Type;
		using atomic_type = typename _vector<_Type>::atomic_type;
		using this_type = _vector<_Type>;

		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = _Type;
		using pointer = _Type * ;
		using reference = _Type & ;

		using iterator = typename _vector<_Type>::reverse_iterator;
		using reverse_iterator = typename _vector<_Type>::iterator;
		using const_iterator = typename _vector<_Type>::reverse_const_iterator;
		using reverse_const_iterator = typename _vector<_Type>::const_iterator;
		using move_iterator = typename _vector<_Type>::reverse_move_iterator;
		using reverse_move_iterator = typename _vector<_Type>::move_iterator;

		///////////////////////////////////////////////////////////////////////////////

		template<int _step = 1>
		FORCEINLINE _iterator<_step> begin() & {
			return _iterator<_step>(*this, size_ - 1);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> begin() const & {
			return _const_iterator<_step>(*this, size_ - 1);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> begin() && {
			return _move_iterator<_step>(*this, size_ - 1);
		}


		template<int _step = 1>
		FORCEINLINE _iterator<_step> end() & {
			return  _iterator<_step>(*this, size_t(-1));
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> end() const & {
			return  _const_iterator<_step>(*this, size_t(-1));
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> end() && {
			return  _move_iterator<_step>(*this, size_t(-1));
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cbegin() const {
			return  _const_iterator<_step>(*this, size_ - 1);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cend() const {
			return  _const_iterator<_step>(*this, size_t(-1));
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mbegin() {
			return _move_iterator<_step>(*this, size_ - 1);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mend() {
			return _move_iterator<_step>(*this, size_t(-1));
		}


		FORCEINLINE _vector<_Type>& backwards() & {
			return reinterpret_cast<_vector<_Type>&>(*this);
		}


		FORCEINLINE _vector<_Type> const& backwards() const & {
			return reinterpret_cast<_vector<_Type> const&>(*this);
		}


		FORCEINLINE _vector<_Type>&& backwards() && {
			return reinterpret_cast<_vector<_Type>&&>(*this);
		}
	};



	template<class _Type>
	class _refvector
	{
		template<class>
		friend class _vector;

		template<int, class, class, class, class, bool>
		friend class __iterator;

		size_t reserved_;
		size_t size_;
		_Type** data_;

		FORCEINLINE void realloc_(size_t newsize) {
			data_ = reinterpret_cast<_Type**>(::realloc(data_, sizeof(_Type*) * newsize));
			reserved_ = newsize;
		}

		FORCEINLINE static _Type** alloc_(size_t size) {
			return reinterpret_cast<_Type**>(::malloc(size * sizeof(_Type*)));
		}

		FORCEINLINE void dealloc_() {
			::free(data_);
		}

	public:
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = _Type;
		using pointer = _Type * ;
		using reference = _Type & ;

	private:
		template<int _step>
		using _iterator = __iterator<_step, _Type*, _Type&, _Type*, _refvector<_Type>, true>;

		template<int _step>
		using _const_iterator = __iterator<_step, _Type const*, _Type const&, _Type const*, _refvector<_Type> const, true>;

		template<int _step>
		using _move_iterator = __iterator<_step, _Type*, _Type&&, _Type*, _refvector<_Type>, true>;

	public:
		using iterator = _iterator<1>;
		using reverse_iterator = _iterator<-1>;
		using const_iterator = _const_iterator<1>;
		using reverse_const_iterator = _const_iterator<-1>;
		using move_iterator = _move_iterator<1>;
		using reverse_move_iterator = _move_iterator<-1>;

		_refvector():
			reserved_(0),
			size_(0),
			data_(nullptr) {
		}

		_refvector(size_t size):
			reserved_(size),
			size_(size),
			data_(alloc_(size)) {
		}

		_refvector(_refvector<_Type> const& other):
			reserved_(other.size_),
			size_(other.size_),
			data_(alloc_(size)) {
			::memcpy(data_, other.data_, size_ * sizeof(_Type*));
		}

		_refvector(_refvector<_Type>&& other):
			reserved_(other.reserved_),
			size_(other.size_),
			data_(other.data_) {
			other.data_ = nullptr;
		}

		FORCEINLINE ~_refvector() {
			dealloc_();
		}

		FORCEINLINE size_t size() const noexcept {
			return size_;
		}


		FORCEINLINE size_t lastpos() const noexcept {
			return size_ - 1;
		}


		FORCEINLINE size_t capacity() const noexcept {
			return reserved_;
		}


		FORCEINLINE size_t memory() const noexcept {
			return reserved_ * sizeof(_Type*);
		}


		FORCEINLINE size_t unused() const noexcept {
			return reserved_ - size_;
		}


		FORCEINLINE bool empty() const noexcept {
			return size_ == 0;
		}


		FORCEINLINE explicit operator bool() const noexcept {
			return size_ > 0;
		}


		FORCEINLINE bool operator!() const noexcept {
			return size_ == 0;
		}


		template<mode_t _mode = _DefaultMode>
		void push_back(_Type& value) {
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_)
					realloc_(reserved_ * 2 + 1);
			}
			data_[size_++] = &value;
		}

		template<mode_t _mode = _DefaultMode>
		void push_back(_Type* ptr) {
			if constexpr (!_mode_set(NoSizeCheck)) {
				if (size_ >= reserved_)
					realloc_(reserved_ * 2 + 1);
			}
			data_[size_++] = ptr;
		}


		void clear() {
			size_ = 0;
		}


		FORCEINLINE _Type& operator[](size_t i) & {
			return *data_[i];
		}

		FORCEINLINE _Type const& operator[](size_t i) const & {
			return *data_[i];
		}

		FORCEINLINE _Type&& operator[](size_t i) && {
			return (_Type&&)(*data_[i]);
		}



		template<int _step = 1>
		FORCEINLINE _iterator<_step> begin() & noexcept {
			return _iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> begin() const & {
			return _const_iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> begin() && noexcept {
			return _move_iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _iterator<_step> end() & noexcept {
			return  _iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> end() const & noexcept {
			return  _const_iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> end() && noexcept {
			return  _move_iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cbegin() const noexcept {
			return  _const_iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> cend() const noexcept {
			return  _const_iterator<_step>(*this, size_);
		}

		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mbegin() noexcept {
			return _move_iterator<_step>(*this, 0);
		}


		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> mend() {
			return _move_iterator<_step>(*this, size_);
		}


		template<int _step = 1>
		FORCEINLINE _iterator<_step> iter(size_t i = 0) & noexcept {
			return _iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _const_iterator<_step> iter(size_t i = 0) const & noexcept {
			return _const_iterator<_step>(*this, i);
		}

		template<int _step = 1>
		FORCEINLINE _move_iterator<_step> iter(size_t i = 0) && noexcept {
			return _move_iterator<_step>(*this, i);
		}


		void reserve(size_t capacity) {
			if (capacity > reserved_)
				realloc_(capacity);
		}

		void resize(size_t size) {
			if (size > reserved_)
				realloc_(size);
			size_ = size;
		}

		template<class _Out>
		FORCEINLINE _refvector<_Out>& reinterpret() & {
			return reinterpret_cast<_refvector<_Out>&>(*this);
		}

		template<class _Out>
		FORCEINLINE _refvector<_Out> const& reinterpret() const & {
			return reinterpret_cast<_refvector<_Out> const&>(*this);
		}

		template<class _Out>
		FORCEINLINE _refvector<_Out>&& reinterpret() && {
			return reinterpret_cast<_refvector<_Out>&&>(*this);
		}

		friend std::ostream& operator << (std::ostream& os, _refvector<_Type> const& a) {
			for (size_t i = 0; i < a.size_; ++i)
				os << *a.data_[i] << ' ';
			return os;
		}
	};

	class _VectorTemp {
		template<class>
		friend class _vector;

		template<class>
		friend class _refvector;

		struct View {
			uint8_t data[sizeof(_vector<void*>)];

			View():
				data{0} {
			}

			~View() {
				reinterpret_cast<_vector<void*>*>(data)->discard_data();
			}
		};

		inline static OPT_THREAD_LOCAL _vector<size_t> indexes_ = {};
		inline static OPT_THREAD_LOCAL _refvector<void*> refvectorData_ = {};
		inline static OPT_THREAD_LOCAL View view_ = {};
		inline static OPT_THREAD_LOCAL _vector<uint8_t> buffer_ = {};
		/*inline static OPT_THREAD_LOCAL void* buffer =
			_INITIAL_STATIC_BUFFER_SIZE > 0 ?
			::malloc(_INITIAL_STATIC_BUFFER_SIZE) :
			nullptr;*/
	};


	namespace pred
	{
		inline const auto empty = [](auto&& c) { return c.empty(); };
		inline const auto is_sorted = [](auto&& c) { return c.is_sorted(); };
		inline const auto owner_of = [](auto&& c, auto&&... v) { return c.owner_of(v...); };
		inline const auto contains = [](auto&& c, auto&&... v) { return c.contains(v...); };
		inline const auto for_all = [](auto&& c, auto&&... p) { return c.for_all(p...); };
		inline const auto for_any = [](auto&& c, auto&&... p) { return c.for_any(p...); };
		inline const auto all_equal = [](auto&& c, auto&&... a) { return c.all_equal(a...); };
		inline const auto any_equal = [](auto&& c, auto&&... a) { return c.any_equal(a...); };
	}

} // namespace x

///////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning(pop)

///////////////////////////////////////////////////////////////////////////////////////////////

#undef XVECTOR_DEBUG
#undef XVECTOR_EXTENSION_MODE
#undef XVECTOR_ITERATOR_MODE
#undef XVECTOR_THREAD_SAFE
#undef XVECTOR_USE_THREAD_LOCAL
#undef XVECTOR_LOCK_ENABLED
#undef XVECTOR_USE_REALLOC
#undef XVECTOR_NO_INLINE
#undef XVECTOR_OPTIMIZE_CONSTRUCT_FOR_TRIVIALLY_COPYABLE
#undef XVECTOR_ALLOW_AGGREGATE_CONSTRUCT
#undef XVECTOR_MOVE_FROM_INITIALIZER_LIST
#undef XVECTOR_DEFAULT_ALLOCATION_MODE
#undef XVECTOR_FIELD_ACCESS
#undef XVECTOR_ALLOW_MSVC_INLINE_ASSEMBLER
#undef XVECTOR_DEFAULT_METHOD_MODE
#undef XVECTOR_ENABLE_EXCEPTIONS
#undef XVECTOR_FORCEINLINE_DESTRUCT
#undef XVECTOR_PREALLOC_POLICY

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _RESERVE_CHECK_NULLPTR
#undef _MOVE_STD_VECTOR

///////////////////////////////////////////////////////////////////////////////////////////////

#undef ExtensionMode_Constant
#undef ExtensionMode_Local
#undef ExtensionMode_Static
#undef ExtensionMode_Custom
#undef IteratorMode_Index
#undef IteratorMode_Pointer
#undef FieldAccess_private
#undef FieldAccess_protected
#undef FieldAccess_public
#undef PreallocPolicyMode_None
#undef PreallocPolicyMode_Reasonable
#undef PreallocPolicyMode_Generous
#undef PreallocPolicyMode_Custom

///////////////////////////////////////////////////////////////////////////////////////////////

#undef MODE
#undef MODE_NOT
#undef MODE_ONE_OF
#undef MODE_NONE_OF

///////////////////////////////////////////////////////////////////////////////////////////////

#undef ExtensionMode
#undef IteratorMode
#undef FieldAccessMode
#undef PreallocPolicyMode

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _MUTEX_NAME
#undef _MUTEX_TYPE
#undef _LOCK_TYPE

#undef _LOCK_MODE_SET
#undef _OPT_LOCK
#undef OPT_THREAD_LOCAL

#undef INLINE
#undef FORCEINLINE

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _destruct_all
#undef _destruct_from
#undef _destruct_range

#undef _DefaultMode
	   
///////////////////////////////////////////////////////////////////////////////////////////////

#undef SPEC
#undef _SPEC

///////////////////////////////////////////////////////////////////////////////////////////////

#undef enable_if
#undef enable_if_

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _mode
#undef _mode_set
#undef _assert_mode

#undef _validate_depth

#undef _foreach
#undef _foreach_o
#undef _foreach_v
#undef _step_foreach
#undef _const_step_foreach
#undef _step_foreach_v
#undef _const_step_foreach_v
#undef _step_foreach_o
#undef _const_step_foreach_o
#undef _step_foreach_os
#undef _const_step_foreach_os
#undef _reverse_foreach
#undef _const_reverse_foreach
#undef _const_foreach
#undef _const_foreach_o
#undef _foreach_from
#undef _const_foreach_from
#undef _foreach_from_s
#undef _const_foreach_from_s
#undef _foreach_from_i
#undef _const_foreach_from_i
#undef _for_range
#undef _const_for_range
#undef _foreach_uninit
#undef _const_foreach_uninit
#undef _foreach_reserved
#undef _const_foreach_reserved
#undef _pair_foreach

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _construct_t
#undef _construct

///////////////////////////////////////////////////////////////////////////////////////////////

#undef _destruct_t
#undef _destruct
#undef _reconstruct_t
#undef _reconstruct
#undef _trivcopy
#undef _trivcopy_t

#undef _rvthis
#undef _rv
#undef _rv_t

#undef _enable_if

///////////////////////////////////////////////////////////////////////////////////////////////

#endif //_X_VECTOR_H_