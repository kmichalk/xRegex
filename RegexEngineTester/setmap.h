#pragma once

#include "static_prop.h"
#include "Buffer.h"

namespace x
{
	//the map of sets of states
	class SetMap
	{
		//an added set
		struct Set {
			//the pointer to array of ids in set
			id_t const* data;
			//size of the array
			size_t size;
			//id of the set
			id_t id = INVALID_ID;
		};

		//a container of sets
		//each container is assigned to one id number, being the smallest in set
		//this speeds up the resolution of sets, narrowing the range of compared sets
		struct SetContainer {
			Set* data;
			size_t size;
		};

		static Buffer<Set> _buffer;
		SetContainer _data[MAX_NODES];

	public:
		__forceinline SetMap() = default;
		//get an id assigned to a set of state ids.
		id_t& resolve(id_t const* ids, size_t size);
		void clear();
	};
}
