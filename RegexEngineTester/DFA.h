#pragma once

#include "static_prop.h"

namespace x {
	//the representation of dfa. used by regex objectas a final representation of parsed regex
	class DFA
	{
		friend class NFA;
		friend class RegexParser;
	public:
		//a state in the dfa
		class Node
		{
			//pool for preallocating and reusing nodes
			static x::pool<Node> _pool;
		public:
			//transitions on every symbol from alphabet
			Node* transitions[CHAR_RANGE];
			//the order id
			id_t id;
			//indicates if state is accepting
			bool accepting;

			//overloaded new and delete operators that allocate memory on pool rather than dynamically
			static void* operator new (size_t size);
			static void* operator new (size_t size, void* dest) noexcept;
			static void operator delete (void* ptr);

			Node() = default;
			Node(id_t id, bool accepting = false);

			void display() const;
			void clear();

			__forceinline void connect(char ch, Node* n) {
				transitions[(uint8_t)ch] = n;
			}
		};

	private:
		x::vector<Node*> _nodes;

		DFA() = default;
		DFA(size_t size);
		DFA(x::vector<Node*>&& _nodes);

	public:
		DFA(DFA const& other) = delete;
		DFA(DFA&& other);
		~DFA();

		void display() const;
		size_t memory() const;
		Node* operator[](id_t i);
		Node const* operator[](id_t i) const;
		void connect(id_t src, id_t dest, char ch);
		//the entry state of dfa. it is always node of id 0
		Node const* entry() const;
		size_t size() const;
		bool empty() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::DFA::Node* x::DFA::operator[](id_t i) {
	return _nodes[(size_t)i];
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::DFA::Node const* x::DFA::operator[](id_t i) const {
	return _nodes[(size_t)i];
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline size_t x::DFA::size() const {
	return _nodes.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline bool x::DFA::empty() const {
	return _nodes.size() == 1 && _nodes[0]->accepting;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::DFA::Node const * x::DFA::entry() const {
	return _nodes.front();
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::DFA::Node::clear() {
	::memset(this, 0, sizeof(Node));
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void* x::DFA::Node::operator new (size_t size) {
	return reinterpret_cast<Node*>(_pool.alloc());
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void* x::DFA::Node::operator new (size_t size, void* dest) noexcept {
	return dest;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::DFA::Node::operator delete (void* ptr) {
	_pool.dealloc(reinterpret_cast<Node*>(ptr));
}

