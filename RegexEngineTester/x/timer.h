//#pragma once
#ifndef _X_TIMER_H_
#define _X_TIMER_H_

#include <chrono>
#include "more_type_traits.h"

namespace x
{
	template<class _Unit = std::chrono::microseconds, class _Measure = double>
	class timer
	{
		static constexpr _Measure _RATIO = _Measure(_Unit::duration::period::num) / _Measure(_Unit::duration::period::den);
		std::chrono::time_point<std::chrono::system_clock> _from;
		std::chrono::time_point<std::chrono::system_clock> _to;
		_Measure _time;

	public:
		timer():
			_time(0)
		{
		}

		timer(timer&&) = delete;
		~timer() = default;
		timer& operator=(timer const&) = delete;
		timer& operator=(timer&&) = delete;

		static unsigned long long int epoch() {
			return std::chrono::duration_cast<_Unit>(
				std::chrono::system_clock::now().time_since_epoch()).count();
		}

		void reset() {
			_from = std::chrono::system_clock::now();
		}

		_Measure get() {
			_to = std::chrono::system_clock::now();
			return _time = _Measure(std::chrono::duration_cast<_Unit>(_to.time_since_epoch() - _from.time_since_epoch()).count()) * _RATIO;
		}

		_Measure tic() {
			get();
			_from = _to;
			return _time;
		}

		__forceinline _Measure time() const {
			return _time;
		}

		/*template<class _Func, class... _Arg>
		_Measure measure(_Func&& func, _Arg&&... args) {
			reset();
			func(args...);
			return get();
		}*/

		/*template<class _U>
		inline friend std::ostream& operator<<(std::ostream &os, timer<_U> const& t) {
			return os << t._time;
		}*/
	};
}
#endif //_X_TIMER_H_