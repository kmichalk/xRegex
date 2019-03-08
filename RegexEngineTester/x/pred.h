#ifndef _X_PRED_H_
#define _X_PRED_H_

namespace x::pred
{
	inline const auto less = [](auto&& a, auto&& b) constexpr { return a < b; };
	inline const auto less_equal = [](auto&& a, auto&& b) constexpr { return a <= b; };
	inline const auto greater = [](auto&& a, auto&& b) constexpr { return a > b; };
	inline const auto greater_equal = [](auto&& a, auto&& b) constexpr { return a >= b; };
	inline const auto equal = [](auto&& a, auto&& b) constexpr { return a == b; };
	inline const auto not_equal = [](auto&& a, auto&& b) constexpr { return a != b; };
	inline const auto between = [](auto&& a, auto&& r1, auto&& r2) constexpr { return a >= r1 && a <= r2; };
	inline const auto not_between = [](auto&& a, auto&& r1, auto&& r2) constexpr { return a < r1 || a > r2; };
	inline const auto one_of = [](auto&& a, auto&&... bs) constexpr { return ((a == bs) || ...); };
	inline const auto none_of = [](auto&& a, auto&&... bs) constexpr { return ((a != bs) && ...); };
	inline const auto is_nullptr = [](auto p) constexpr { return p == nullptr; };
	inline const auto is_zero = [](auto p) constexpr { return p == 0; };

	inline const auto and = [](auto&& f, auto&& g) constexpr { return [&](auto&&... a) constexpr { return f(a...) && g(a...); }; };

	template<class _Func, class... _Arg>
	__forceinline auto bind(_Func&& f, _Arg&&... a) {
		return [&](auto&&... _a) {
			return f(a..., _a...);
		};
	}

	template<class _Func, class... _Arg>
	__forceinline auto bindl(_Func&& f, _Arg&&... a) {
		return [&](auto&&... _a) {
			return f(a..., _a...);
		};
	}

	template<class _Func, class... _Arg>
	__forceinline auto bindr(_Func&& f, _Arg&&... a) {
		return [&](auto&&... _a) {
			return f(_a..., a...);
		};
	}

	template<class _Func>
	__forceinline auto not(_Func&& f) noexcept {
		return [&f](auto&&... a) {
			return !f(a...);
		};
	}


}

#endif //_X_PRED_H_
