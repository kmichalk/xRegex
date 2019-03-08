#ifndef _LOOPS_H_
#define _LOOPS_H_


//#define _ITER_VAR_NAME(_n) __i##_n
#define _ITER_VAR_NAME(_n) __i
#define _RESOLVE_VAR_NAME(_name) __if_not_exists(_name##0) { _name##0 } __if_exists(_name##0) { __if_not_exists(_name##1) { _name##1 } __if_exists(_name##1) { __if_not_exists(_name##2) { _name##2 } __if_exists(_name##2) { _name##3 } } } 

/// <summary>
/// Simplified version of for loop.
/// Repeats underlying code \a _n times.
/// </summary>
/// <param name="_n"> - number of iterations</param>
#define repeat(_n) for (decltype(_n) _ITER_VAR_NAME = 0; _ITER_VAR_NAME < _n; ++_ITER_VAR_NAME)


/// <summary>
/// Simplified iterator for loop, only valid when used with objects
/// from x namespace since they are using non-standard, optimized iteration syntax. 
/// </summary>
/// <param name="_i"> - name of the iterator</param>
/// <param name="_cnt"> - name of the container</param>
/// <example><code>x::vector<int> iv{1,2,3};
/// foreach(i, iv) ++*i;</code></example>
#define foreach(_i, _cnt) for (auto _i{_cnt.begin()}; _i; ++_i)


/// <summary>
/// Simplified const_iterator for loop, only valid when used with objects
/// from x namespace since they are using non-standard, optimized iteration syntax. 
/// </summary>
/// <param name="_i"> - name of the const_iterator</param>
/// <param name="_cnt"> - name of the container</param>
/// <example><code>int sum(x::vector<int> const& iv) {
///		int result = 0;
///		const_foreach(i, iv) result += *i;
///		return result;
/// }</code></example>
#define const_foreach(_i, _cnt) for (auto _i{_cnt.cbegin()}; _i; ++_i)

#define ptr_foreach(_i, _data, _size) for (auto _i = _data, __end_##_i = _i + _size; _i < __end_##_i; ++_i)


//
///// <summary>
///// Expands to infinite loop <code>while (true)</code>.
///// </summary>
//#define loop while(true)

//
///// <summary>
///// While loop with negated condition resulting in loop executing until
///// given condition is fulfilled.
///// </summary>
///// <param name="">any statement to be checked</param>
//#define until(...) while(! (__VA_ARGS__))
//#define booliter(_iterName) for (int _iterName=0;_iterName<2;++_iterName)

//
//#define booliter(_iterName, _CODE) \
//	{\
//		static constexpr bool _iterName = false;\
//		_CODE\
//	}{\
//		static constexpr bool _iterName = false;\
//		_CODE\
//	}
//
//#define __iter_2(_iterName, _to) for (auto _iterName = 0; _iterName < _to; ++_iterName)
//#define __iter_3(_iterName, _from, _to) for (auto _iterName{_from}; _iterName <= _to; ++_iterName) 
//
//#define iter(...) SEPARATE(CAT(__iter_, NARGS(__VA_ARGS__)), (__VA_ARGS__))


#endif //_LOOPS_H_