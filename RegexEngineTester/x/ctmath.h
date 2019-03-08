#ifndef CT_ALGORITHM_H
#define CT_ALGORITHM_H

#include "more_type_traits.h"
#include <cstdint>

#pragma region CTMATH_MACROS
#define POW2(_val) ((_val)*(_val))
#define POW3(_val) ((_val)*(_val)*(_val))
#define MEAN(_val1, _val2) (((_val1) + (_val2))/2.0)


#pragma endregion


template<uint32_t _n, uint32_t _p>
struct ct_pow
{
	static constexpr uint32_t value = _n * ct_pow<_n, _p - 1>::value;
};

template<uint32_t _n>
struct ct_pow<_n, 0>
{
	static constexpr uint32_t value = 1;
};

///////////////////////////////////////////////////////////////////////////////

namespace x
{
	namespace ct
	{
		template<typename T>
		constexpr T pow(T val, unsigned p)
		{
			return p == 0 ? 1 : val * pow(val, p-1);
		}


		//////////////////////////////////////////////////////////////////////////////

		constexpr unsigned long long fact(unsigned value)
		{
			return value == 0 ? 1 : value*fact(value-1);
		}

		//////////////////////////////////////////////////////////////////////////////

		template<typename _First, typename... _Rest>
		constexpr auto sum(_First first, _Rest... rest)
		{
			return first + sum(rest...);
		}

		constexpr auto sum()
		{
			return 0;
		}

		template<typename _First, typename... _Rest>
		constexpr auto sum_first(unsigned n, _First first, _Rest... rest)
		{
			return n > 0 ? first + sum_first(n - 1, rest...) : 0;
		}

		constexpr auto sum_first(unsigned n)
		{
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////////

		template<typename T, typename... R>
		constexpr auto product(T first, R... rest)
		{
			return first * product(rest...);
		}

		constexpr auto product()
		{
			return 1;
		}

		//////////////////////////////////////////////////////////////////////////////

		template<unsigned rangePow, typename T>
		struct _CtSqrt
		{
			static constexpr T _sqrt(T x, T xlo, T xhi)
			{
				return (double)(POW2(MEAN(xlo, xhi)))/(double)(x) < 1.0-x::ct::pow(0.1,rangePow) ?
					_sqrt(x, MEAN(xlo, xhi), xhi) : (
					(double)(POW2(MEAN(xlo, xhi)))/(double)(x) > 1.0+x::ct::pow(0.1, rangePow) ?
						_sqrt(x, xlo, MEAN(xlo, xhi)) :
						MEAN(xlo, xhi));
			}
		};

		template<unsigned rangePow = 9, typename T>
		inline constexpr T sqrt(T value)
		{
			return _CtSqrt<rangePow,T>::_sqrt(value, 0, value);
		}

		//////////////////////////////////////////////////////////////////////////////

		template<unsigned rangePow, typename T>
		struct _CtCbrt
		{
			static constexpr T _cbrt(T x, T xlo, T xhi)
			{
				return (double)(POW3(MEAN(xlo, xhi)))/(double)(x) < 1.0-x::ct::pow(0.1, rangePow) ?
					_cbrt(x, MEAN(xlo, xhi), xhi) : (
					(double)(POW3(MEAN(xlo, xhi)))/(double)(x) > 1.0+x::ct::pow(0.1, rangePow) ?
						_cbrt(x, xlo, MEAN(xlo, xhi)) :
						MEAN(xlo, xhi));
			}
		};

		template<unsigned rangePow = 9, typename T>
		inline constexpr T cbrt(T value)
		{
			return _CtCbrt<rangePow, T>::_cbrt(value, 0, value);
		}

		//////////////////////////////////////////////////////////////////////////////

		template<typename T>
		inline constexpr T abs(T value)
		{
			return value < T(0) ? -value : value;
		}

		//////////////////////////////////////////////////////////////////////////////

		template<typename T>
		inline constexpr T sgn(T value)
		{
			return (value > T(0)) - (value < T(0));
		}

		template<typename T>
		inline constexpr T val(T _val)
		{
			return _val;
		}
	}
}

#undef POW2
#undef POW3
#undef MEAN

#endif
