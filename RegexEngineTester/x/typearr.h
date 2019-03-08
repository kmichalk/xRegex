#ifndef TYPEARR_H
#define TYPEARR_H

#include "more_type_traits.h"

namespace x
{
	template<typename... _Type>
	struct TypeArray
	{
		constexpr TypeArray()
		{
		}

		template<typename _Get>
		static constexpr size_t num_of = x::find_type<_Get>::in<_Type...>::value;

		template<size_t _n>
		using get = x::select_t<_n, _Type...>;
	};
}
#endif //TYPEARR_H
