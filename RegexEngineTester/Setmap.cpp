#include "stdafx.h"
#include "setmap.h"


x::Buffer<x::SetMap::Set> x::SetMap::_buffer = (SET_BUFFER_SIZE);

///////////////////////////////////////////////////////////////////////////////////////////////

id_t & x::SetMap::resolve(id_t const * ids, size_t size) {
	//get the subset of mapped ids that contain smallest id
	SetContainer& sets = _data[*ids];
	Set* ps;
	//if there is no data allocated per this container, allocate
	if (sets.data == nullptr) {
		sets.data = _buffer.reserve(SETS_PER_CONTAINER);
		//new set will be added to the new container
		ps = sets.data;
	} else {
		//iterathe through sets and find matching set
		Set* psend = sets.data + sets.size;
		for (ps = sets.data; ps < psend; ++ps)
			if (ps->size == size && memcmp(ps->data, ids, size * sizeof(id_t)) == 0)
				//found matching set
				return ps->id;
	}
	//inset the set into contained and return
	*ps = {ids, size};
	++sets.size;
	return ps->id;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SetMap::clear() {
	_buffer.clear();
	::memset(_data, 0, sizeof(_data));
}