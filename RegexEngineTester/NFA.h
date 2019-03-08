#pragma once

#include "DFA.h"
#include "setmap.h"

#pragma pack(push)
#pragma pack(1)

namespace x
{
	//object representing NFA. built in parsing the regex
	class NFA
	{
	public:
		//a single state of NFA
		struct Node
		{
			//the order number
			id_t id;
			bool accepting;
			//previously created node
			Node* prev;
			//next created node
			Node* next;
			DFA::Node* dfaNode;
			//the transition table, sets of achiveable states for each symbol
			x::array<id_t, MAX_CHAR_CONNECTIONS> transitions[CHAR_RANGE];
			//all symbols the state has transitions on
			x::array<char, MAX_CONNECTIONS> symbols;

			Node(id_t id, bool accepting = false);
			Node(Node const&) = delete;
			Node(Node&&) = delete;
			Node& operator=(Node const&) = delete;
			Node& operator=(Node&&) = delete;

			//connect to state on symbol
			void connect(id_t id, char ch);
			//connect to states using data of other state
			void connect(x::array<id_t, MAX_CHAR_CONNECTIONS> const& ids, char ch);
			//connect to state on multiple symbols using data of other state
			void connect(id_t id, x::array<char, MAX_CONNECTIONS> const& chs);
			//connect to state on symbols
			void connect(id_t id, char const* chs);
			void connect(id_t id, bool const* symbolMap);
			//clone all transitions from other node
			void cloneTransitions(Node const* other);
			//clone all transitions from other node that lead to dest node
			void cloneTransitions(Node const* other, Node const* dest);
			void initDFANode();
		};

	private:
		//all the nodes
		x::vector<Node> _nodes;
		//data for merging nodes, bool values: if a node already has transition on symbol
		bool _mergeData[MAX_NODES][CHAR_RANGE];
		//the states sets map for resolving new ids
		x::SetMap _idMap;
		Node* _lastNode;
		//id of last added node
		id_t _lastID;

		//use the set map and resolve new state id
		id_t _resolveIDFor(x::array<id_t, MAX_CHAR_CONNECTIONS> const& charConnection);
		//merge the transitions of node into destNode
		void _mergeNode(Node& node, Node& destNode);
		//perform the merge
		void _mergeNodesByIDs(x::array<id_t, MAX_CHAR_CONNECTIONS> const& charConnection, id_t destID);
		void _clearMergeData();

	public:
		NFA(size_t reserveNodes = MAX_NODES);
		NFA(NFA const&) = delete;
		NFA(NFA&&) = delete;
		NFA& operator=(NFA const&) = delete;
		NFA& operator=(NFA&&) = delete;

		//get node of id
		Node* operator[](id_t i);
		//get node of id
		Node const* operator[](id_t i) const;
		//reserve memory for n ndoes
		void reserve(size_t n);
		void addNode();
		void initNode();
		NFA::Node* lastNode();
		//convert to dfa
		DFA toDFA();
		void clear();
		void debug() const;
		void display() const;
	};
}

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::NFA::Node * x::NFA::lastNode() {
	return _lastNode;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void x::NFA::_clearMergeData() {
	::memset(_mergeData, 0, _nodes.size()*CHAR_RANGE);
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::NFA::Node * x::NFA::operator[](id_t i) {
	return &_nodes[i];
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline x::NFA::Node const* x::NFA::operator[](id_t i) const {
	return &_nodes[i];
}
