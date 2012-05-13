#ifndef NODE_SET_HPP_INCLUDED
#define NODE_SET_HPP_INCLUDED

#include <map>
#include <set>

#include "types.h"

// type definitions

// set of node identifiers
typedef std::set<uint> nodeset_t;
typedef nodeset_t::iterator nodeset_it;
// set of node sets
typedef std::set<nodeset_t> nodemetaset_t;
typedef nodemetaset_t::iterator nodemetaset_it;
// node set with a destination to arrive at when others are visited
typedef std::pair<nodeset_t, uint> itinerary_t;
// iternaries mapped to the shortest distance to traverse it entirely
typedef std::map<itinerary_t, uint> costmap_t;
typedef costmap_t::iterator costmap_it;

// debug information
void print_nodes(nodeset_t const* nodeset);
void print_node_sets(nodemetaset_t const* node_metaset);
void print_node_metasets(nodemetaset_t node_metasets[], uint n_nodes);


// build all the nodesets of each size
void build_node_metasets(nodemetaset_t node_metasets[], uint n_nodes);

#endif // NODE_SET_HPP_INCLUDED
