#pragma once

//global constants used by parser and automatons

//the number of symbols taken into consideration (128 = all ASCII)
static constexpr size_t CHAR_RANGE = 128;
//number of symbols in ASCII
static constexpr size_t ASCII_RANGE = 128;
//max NFA nodes
static constexpr size_t MAX_NODES = 512;
//max DFA nodes
static constexpr size_t MAX_DFA_NODES = 1024;
//max connections for a node
static constexpr size_t MAX_CONNECTIONS = CHAR_RANGE;
//max connections on a simgle symbol
static constexpr size_t MAX_CHAR_CONNECTIONS = 8;
//prealocated memory for NFA
static constexpr size_t DEFAULT_RESERVE_NODES = MAX_NODES;
//default memory for  connections of a node
static constexpr size_t CONNECTIONS_PER_NODE = CHAR_RANGE;
//maximum sections stack size
static constexpr size_t SECTION_STACK_SIZE = 64;
//set containers in set map
static constexpr size_t MAX_SET_CONTAINERS = 64;
//possible sets in set container
static constexpr size_t SETS_PER_CONTAINER = 64;
//preallocated memory for symbol sets
static constexpr size_t SET_BUFFER_SIZE = MAX_SET_CONTAINERS * SETS_PER_CONTAINER;
//default expected matches in regex search
static constexpr size_t DEFAULT_EXPECTED_SEARCH_RESULTS = 16;

//the id type is the smallest unsigned int that can contain all possible values, based on MAX_NODES constant
using id_t = x::smallest_type<MAX_NODES>;
static constexpr id_t INVALID_ID = -1;
