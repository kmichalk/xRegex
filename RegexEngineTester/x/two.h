#ifndef _TWO_H_
#define _TWO_H_

#include "more_type_traits.h"
#include <iostream>

namespace x
{
	template<typename T1, typename T2 = T1>
	struct two
	{
		T1 a;
		T2 b;

		two() = default;

		constexpr two(T1 const& a, T2 const& b):
			a(a), b(b)
		{
		}

		two(two const& other) = default;
		two(two&& other) = default;

		bool operator==(two const& other) const
		{
			return a == other.a && b == other.b;
		}

		friend std::ostream& operator<<(std::ostream& os, two<T1, T2> const& t)
		{
			return os << t.a << ' ' << t.b;
		}
	};
}
#endif //_TWO_H_
