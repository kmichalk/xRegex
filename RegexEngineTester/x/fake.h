#ifndef _FAKE_H_
#define _FAKE_H_

#include "more_type_traits.h"
////#include "__int8.h"

namespace x
{
	template<typename _Type>
	class FakeType
	{
		static constexpr size_t size_ = sizeof(_Type);

		__int8 fakeData_[size_];

	public:
		inline FakeType() noexcept
		{
		}

		FakeType(FakeType<_Type> const&) = delete;

		FakeType(FakeType<_Type>&&) = delete;

		__forceinline FakeType<_Type>& operator=(FakeType<_Type> const& other) = default;
		/*{
			memcpy(fakeData_, other.fakeData_, size_);
		}*/

		~FakeType()
		{
		}

		template<typename _To>
		inline operator _To*() const noexcept
		{
			return reinterpret_cast<_To*>(fakeData_);
		}
	};

	/*template<typename _Type>
	using FakeType = __int8[sizeof(_Type)];*/

	/*template<typename _Type>
	__forceinline _Type* fake() noexcept
	{
		return reinterpret_cast<_Type*>(new FakeType<_Type>);
	}

	template<typename _Type>
	__forceinline _Type* fake(size_t size) noexcept
	{
		return reinterpret_cast<_Type*>(new FakeType<_Type>[size]);
	}*/


	///////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Class recursively expanding to specified size.
	/// </summary>
	/// <typeparam name="_size"> - desired size of generated type</typeparam>
	/// <typeparam name="_Fake"> - type, size of which _size parameter will be multiplied
	/// by default: __int8</typeparam>
	template<class _Type>
	struct fake
	{
	//#define _FORWARD_VALUE std::conditional_t<std::is_rvalue_reference_v<decltype(value)>, _Value&&, _Value const&>
	//#define _SET_DATA(_value) new (data) std::remove_reference_t<_Value>((_FORWARD_VALUE)value)

		__int8 data[sizeof(_Type)];

		//fake() { }

		/*template<class _Value>
		fake(_Value&& value) {
			_SET_DATA(value);
		}

		template<class _Value>
		__forceinline void operator = (_Value&& value) {
			_SET_DATA(value);
		}*/

	//#undef _FORWARD_VALUE
	//#undef _SET_DATA
	};
	/*template<size_t _size, class _Fake = __int8>
	class fake
	{
		std::conditional_t<_size == sizeof(_Fake), _Fake, fake<_size - sizeof(_Fake), _Fake>> data_;
	};*/

	template<class _Type>
	struct alignas(_Type) fake_ptr
	{
		__int8 data[sizeof(_Type)];

		fake_ptr() = default;

		template<class _Value>
		__forceinline fake_ptr(_Value&& value) {
			new (data) std::remove_reference_t<_Value>(std::forward<_Value>(value));
		}

		template<class _Value>
		__forceinline fake_ptr& operator=(_Value&& value) {
			new (data) std::remove_reference_t<_Value>(std::forward<_Value>(value));
		}

		__forceinline _Type* operator->() noexcept {
			return reinterpret_cast<_Type*>(data);
		}

		__forceinline _Type const* operator->() const noexcept {
			return reinterpret_cast<_Type const*>(data);
		}

		__forceinline _Type& operator*() noexcept {
			return *reinterpret_cast<_Type*>(data);
		}

		__forceinline _Type const& operator*() const noexcept {
			return *reinterpret_cast<_Type const*>(data);
		}
	};


	template<class _Type>
	using make_trivial = std::conditional_t<std::is_pod_v<_Type>, _Type, fake<_Type>>;
}

#endif //_FAKE_H_
