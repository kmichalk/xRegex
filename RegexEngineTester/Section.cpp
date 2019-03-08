#include "stdafx.h"
#include "Section.h"


x::Buffer<x::Section> x::Section::_buffer(SECTION_STACK_SIZE);

///////////////////////////////////////////////////////////////////////////////////////////////

void x::Section::_applyQuantifiers() {
	if (looped)
		end->cloneTransitions(begin, begin->next);
	if (optional) {
		if (end->accepting)
			begin->accepting = true;
		begin->cloneTransitions(end);
	}
	if (sub != nullptr)
		sub->applyQuantifiers();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::Section::applyQuantifiers() {
	//do apply quantifiers
	_applyQuantifiers();
	Section* s = next;
	//iterate through subsections and do the same
	while (s != nullptr) {
		s->_applyQuantifiers();
		s = s->next;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::Section::addSubsection(Section * section) {
	section->parent = this;
	section->next = sub;
	sub = section;
}

///////////////////////////////////////////////////////////////////////////////////////////////

char x::Section::quantifierSymbol() const {
	return looped ? (optional ? '*' : '+') : (optional ? '?' : ' ');
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::_print(Section * s, unsigned depth) const {
	repeat(depth)
		printf("  ");

	if (s->begin == nullptr)
		printf("%i: (null) - ", s->id);
	else
		printf("%i: %i - ", s->id, s->begin->id);

	if (s->end == nullptr)
		printf("(null) %c\n", s->quantifierSymbol());
	else
		printf("%i %c\n", s->end->id, s->quantifierSymbol());

	if (s->sub != nullptr)
		_print(s->sub, depth + 1);
	Section* c = s->next;
	while (c != nullptr) {
		_print(c, depth);
		c = c->next;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::SectionStack::SectionStack():
	_root(nullptr),
	_top(nullptr),
	_lastId(0) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::init(NFA::Node* begin) {
	_root = Section::_buffer.next();
	_root->id = _lastId++;
	_root->begin = begin;
	_top = _root;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::push() {
	Section* s = Section::_buffer.next();
	s->id = _lastId++;
	_top->addSubsection(s);
	_top = s;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::push(NFA::Node * begin) {
	Section* s = Section::_buffer.next();
	s->id = _lastId++;
	s->begin = begin;
	_top->addSubsection(s);
	_top = s;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Section* x::SectionStack::push(NFA::Node * begin, NFA::Node * end) {
	Section* s = Section::_buffer.next();
	s->id = _lastId++;
	s->begin = begin;
	s->end = end;
	_top->addSubsection(s);
	return _top = s;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Section* x::SectionStack::put(NFA::Node * begin, NFA::Node * end) {
	Section* s = Section::_buffer.next();
	s->id = _lastId++;
	s->begin = begin;
	s->end = end;
	_top->addSubsection(s);
	return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::Section * x::SectionStack::clone(Section * s, NFA::Node * entry) {
	//calculate the length of sections data stored in buffer since section s
	Section* bufend = Section::_buffer.end();
	size_t sectoffset = size_t(bufend - s);
	//calculate the number of nodes added since section s
	size_t nodeoffset = size_t(entry->id - s->begin->id);
	//reserve data on buffer of the same capacity
	Section* cloned = Section::_buffer.reserve(bufend - s);
	//set the iterating pointers
	Section* dest = cloned;
	Section* src = s;

	//clone the first section
	dest->id = _lastId++;
	dest->begin = src->begin + nodeoffset;
	dest->end = src->end + nodeoffset;
	dest->looped = src->looped;
	dest->optional = src->optional;
	//add the new section to the parent of cloned section
	src->parent->addSubsection(dest);
	++src;

	//iterate and clone the rest sections
	while (src < bufend) {
		++dest;
		dest->id = _lastId++;
		dest->begin = src->begin + nodeoffset;
		dest->end = src->end + nodeoffset;
		dest->looped = src->looped;
		dest->optional = src->optional;
		//add the new section on the same level as the cloned section
		(dest - (src - src->parent))->addSubsection(dest);
		++src;
	}
	return cloned;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::clear() {
	Section::_buffer.clear();
	Section::_buffer.zero();
	_root = nullptr;
	_top = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::SectionStack::print() const {
	if (_root != nullptr)
		_print(_root, 0);
	printf("\n");
}
