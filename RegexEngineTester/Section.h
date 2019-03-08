#pragma once

#include "NFA.h"
#include "Buffer.h"

#pragma pack(push)
#pragma pack(1)

namespace x
{
	//represents a section found in regex e.g. when ( ) are encountered
	//has tree structure
	struct Section
	{
		friend class SectionStack;
	private:
		//buffer containing preallocated memory for creating new Section objects
		static Buffer<Section> _buffer;
		//process the quantifiers recursively on sections
		void _applyQuantifiers();
	public:
		//parent of the section node in tree
		Section* parent;
		//sections on the same level are aligned in a single-linked list so
		//this is a pointer to the next section on the same level
		Section* next;
		//pointer to list with subsections
		Section* sub;
		//NFA begin node
		NFA::Node* begin;
		//NFA end node
		NFA::Node* end;
		//the order number
		id_t id;
		//flag set in case of quantifiers * and +
		bool looped;
		//flag set in case of quantifiers * and ?
		bool optional;

		Section() = default;
		Section(NFA::Node* begin);
		Section(NFA::Node* begin, NFA::Node* end);
		//process the quantifiers recursively on sections
		void applyQuantifiers();
		//insert section in the list on the level below
		void addSubsection(Section* section);
		//generate the symbol of quantifier basing on looped and optional flags
		char quantifierSymbol() const;
		//the distance between NFA nodes 
		unsigned length() const;
	};

	//stack of sections that keep important information when building section tree
	class SectionStack
	{
		//the root section
		Section* _root;
		//the last handled section (top of stack)
		Section* _top;
		//ptr to section that can be remembered and restored by store/restore methods
		Section* _stored;
		//id of the last added section
		id_t _lastId;
		void _print(Section* s, unsigned depth) const;
	public:
		SectionStack();
		//init the stack with new section beginning at node
		void init(NFA::Node* begin);
		//clear the stack
		void clear();
		//insert section on current level and set as top
		void push();
		//insert section on current level and set as top, beginning with node
		void push(NFA::Node* begin);
		//insert section on current level and set as top, set begin and end nodes
		Section* push(NFA::Node* begin, NFA::Node* end);
		//insert section on current level, not increment the stack, set begin and end nodes
		Section* put(NFA::Node* begin, NFA::Node* end);
		//go up to parent in tree
		void pop();
		//end top section with node
		void end(NFA::Node* end);
		//end top section with node and set as accepting, used on the ned of parsing
		void finish(NFA::Node* end);
		//get the top section
		Section* top() const;
		//get the root section
		Section* root() const;
		//get the last added section
		Section* last() const;
		//clone specified section basing on a node to be the begin of new section
		Section* clone(Section* s, NFA::Node* entry);
		//get number of sections
		size_t count() const;
		//remember topsection
		void store();
		//restore stored section as top
		void restore();
		//print the stack to stdout
		void print() const;
	};
}

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Section::Section(NFA::Node * begin):
	begin(begin) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Section::Section(NFA::Node * begin, NFA::Node * end):
	begin(begin),
	end(end) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline unsigned x::Section::length() const {
	return end->id - begin->id;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::SectionStack::pop() {
	_top = _top->parent;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline void x::SectionStack::end(NFA::Node * end) {
//	_top->end = end;
//	_top = _top->parent;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::SectionStack::finish(NFA::Node* end) {
	_top->end = end;
	end->accepting = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Section * x::SectionStack::top() const {
	return _top;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Section * x::SectionStack::root() const {
	return _root;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::Section * x::SectionStack::last() const {
	return _top->sub;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::SectionStack::store() {
	_stored = _top;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::SectionStack::restore() {
	_top = _stored;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline size_t x::SectionStack::count() const {
	return _lastId;
}
