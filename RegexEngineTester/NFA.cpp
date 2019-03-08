#include "stdafx.h"
#include "NFA.h"

//ENABLE_STACK_DISPLAY;
//ENABLE_DEBUG;
//ENABLE_BYTE_DISPLAY;


x::NFA::NFA(size_t reserveNodes):
	_nodes(reserveNodes),
	_mergeData{0},
	_idMap(),
	_lastNode(nullptr),
	_lastID(INVALID_ID) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::_mergeNode(Node & node, Node & destNode) {
	//for all symbols of transitions of a node
	for (char ch : node.symbols) {
		//for all ids a symbol transits to
		for (id_t id : node.transitions[(uint8_t)ch]) {
			//if there was no connection, connect and mark
			bool& transitions = _mergeData[id][(uint8_t)ch];
			if (!transitions) {
				destNode.connect(id, ch);
				transitions = true;
			}
		}
	}
	//a node is accepting when any of coponent nodes is accepting
	if (node.accepting)
		destNode.accepting = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::_mergeNodesByIDs(x::array<id_t, MAX_CHAR_CONNECTIONS> const & mergedIDs, id_t destID) {
	_clearMergeData();
	Node& destNode = _nodes[destID];
	//for all nodes from a set merge transitions to a destNode
	for (id_t compositeID : mergedIDs) {
		_mergeNode(_nodes[compositeID], destNode);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::addNode() {
	//create a node in the container and connect the nodes as list
	_nodes.construct_back(++_lastID);
	Node* n = _nodes.pback();
	n->next = nullptr;
	n->prev = _lastNode;
	_lastNode->next = n;
	_lastNode = n;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::initNode() {
	_nodes.construct_back(++_lastID);
	Node* n = &_nodes.back();
	n->prev = nullptr;
	n->next = nullptr;
	_lastNode = n;
}

///////////////////////////////////////////////////////////////////////////////////////////////

id_t x::NFA::_resolveIDFor(x::array<id_t, MAX_CHAR_CONNECTIONS> const & charConnection) {
	id_t& resolvedID = _idMap.resolve(charConnection.data(), charConnection.size());
	if (resolvedID == INVALID_ID) {
		//if there is no id assigned to a set, create new node and assign next id
		addNode();
		resolvedID = _lastID;
		_mergeNodesByIDs(charConnection, resolvedID);
	}
	return resolvedID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::reserve(size_t n) {
	_nodes.reserve(n);
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::DFA x::NFA::toDFA() {
	if (_nodes.empty())
		return {};
	//for all nodes, also until no more are created
	for (auto inode = _nodes.begin(); inode; ++inode) {
		auto& node = *inode;
		node.dfaNode->accepting = node.accepting;
		//for all symbols that a node has transitions on
		for (char ch : node.symbols) {
			auto& charConnection = node.transitions[(uint8_t)ch];
			//if it is a set of nodes, resolve id; connect
			if (charConnection.size() >= 2) {
				id_t resolvedID = _resolveIDFor(charConnection);
				node.dfaNode->connect(ch, _nodes[resolvedID].dfaNode);
			} else {
				node.dfaNode->connect(ch, _nodes[charConnection.front()].dfaNode);
			}
		}
	}
	//extract all dfa nodes from NFA as a container and put into dfa
	return DFA(_nodes.extract_member(&Node::dfaNode));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::clear() {
	_nodes.clear();
	_idMap.clear();
	_lastID = INVALID_ID;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::debug() const {
	//for (const Node& node : _nodes)
		
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::display() const {
	for (Node const& node : _nodes) {
		std::cout << node.id << (node.accepting ? "  *\n" : "  \n");
		for (char ch : node.symbols) {
			std::cout << '\t' << ch << ":  " << node.transitions[(uint8_t)ch] << '\n';
		}
	}
	std::cout << "\n\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////


x::NFA::Node::Node(id_t id, bool accepting):
	id(id),
	accepting(false),
	prev(nullptr),
	next(nullptr),
	dfaNode(new DFA::Node(id)) {
	::memset(transitions, 0, sizeof(transitions));
	::memset(&symbols, 0, sizeof(symbols));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::connect(id_t id, char ch) {
	auto& charCons = transitions[(uint8_t)ch];
	//if there was no connection on that symbol, add symbol to symbols list; 
	//insert the node id keeping sorted order
	if (charCons.empty()) {
		symbols.push_back(ch);
		charCons.push_back(id);
	} else
		charCons.insert_unique_sorted(id);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::connect(x::array<id_t, MAX_CHAR_CONNECTIONS> const & ids, char ch) {
	for (id_t id : ids)
		connect(id, ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::connect(id_t id, x::array<char, MAX_CONNECTIONS> const & chs) {
	for (char ch : chs)
		connect(id, ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::connect(id_t id, char const * chs) {
	while (*chs != '\0') {
		connect(id, *chs);
		++chs;
	}
}

void x::NFA::Node::connect(id_t id, bool const * symbolMap) {
	for (size_t i = 0; i < ASCII_RANGE; ++i) {
		if (symbolMap[i])
			connect(id, (char)i);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::cloneTransitions(Node const* other) {
	if (this == other)
		return;
	//for all symbols of other node
	for (char const* pc = other->symbols.data(), *pcend = pc + other->symbols.size(); pc < pcend; ++pc) {
		auto& charCons = other->transitions[(uint8_t)*pc];
		//make the same transitions
		for (id_t const* pid = charCons.data(), *pidend = pid + charCons.size(); pid < pidend; ++pid)
			connect(*pid, *pc);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void x::NFA::Node::cloneTransitions(Node const * other, Node const * dest) {
	if (this == other)
		return;
	id_t destid = dest->id;
	//for all symbols of other node
	for (char const* pc = other->symbols.data(), *pcend = pc + other->symbols.size(); pc < pcend; ++pc) {
		auto& t = other->transitions[(uint8_t)*pc];
		//make connection if transition directs to a dest node
		for (id_t const* pid = t.data(), *pidend = pid + t.size(); pid < pidend; ++pid) {
			if (*pid == destid) {
				connect(destid, *pc);
				break;
			}
		}
	}
}

void x::NFA::Node::initDFANode() {
	dfaNode = new DFA::Node(id, accepting);
}
