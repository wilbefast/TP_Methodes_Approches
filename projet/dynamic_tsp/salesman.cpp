#include <stdlib.h>

#include <map>
#include <set>

#include "salesman.hpp"

using namespace std;

// set of node identifiers
typedef set<uint> nodeset_t;
typedef nodeset_t::iterator nodeset_it;
// set of node sets
typedef set<nodeset_t*> nodemetaset_t;
typedef nodemetaset_t::iterator nodemetaset_it;
// node set with a destination to arrive at when others are visited
typedef pair<nodeset_t*, uint> itinerary_t;
// iternaries mapped to the shortest distance to traverse it entirely
typedef map<itinerary_t*, uint> costmap_t;
typedef costmap_t::iterator costmap_it;


// the solver itself
uint salesman(matrix_t* distances, uint n_nodes)
{
  // the optimal round-trip distance
  uint result = 0;

  // this structure maps a node-set/end-node pair to the shortest cost for
  // traversing the set ending at the specified destination
  costmap_t C;

  // for shortest path from the start (0) any other node (1 .. n_nodes-1)
  // is always the birds' flight distance given by the distances matrix
  for (uint end_i = 1; end_i < n_nodes; end_i++)
  {
    nodeset_t* start_end = new nodeset_t();
      start_end->insert(0);
      start_end->insert(end_i);

    itinerary_t* birds_flight = new itinerary_t(start_end, end_i);
    C[birds_flight] = distances->t[0][end_i];
  }

  // for each set size above two (birds' flight distances)
  for(uint set_size = 3; set_size < n_nodes; set_size++)
  {
    // build a set of all nodes sets of this size
    /*NodeSetList* node_sets;
    NodeSet::allSets(set_size); /// REMEMBER TO FREE THIS

    // for each set of the given set size
    for(nodeset_it i = node_sets->begin(); i != node_sets->end(); i++)
    {
      NodeSet* set = (*i);
    }*/
  }

  // free the cost-map
  for(costmap_it cm_i = C.begin(); cm_i != C.end(); cm_i++)
  {
    // free each set of node sets
    itinerary_t* i = (*cm_i).first;
    nodeset_t* ns = i->first;
    ns->clear();
    delete ns;
    delete i;

  }

  // return result
  return result;
}

/*uint salesman(matrix_t* distances, uint n_nodes)
{
  ShortestPaths paths;

  // for shortest path from the start (0) any other node (1 .. n_nodes-1)
  // is always the birds' flight distance given by the distances matrix
  for (uint end_i = 1; end_i < n_nodes; end_i++)
  {
    NodeSet* set = new NodeSet(); /// REMEMBER TO FREE THIS
      set->add(0);
      set->add(end_i);
    paths.setDistance(set, distances->t[0][end_i]);
  }

  // for each set size
  for(uint set_size = 3; set_size < n_nodes; set_size++)
  {
    // build a set of all nodes sets of this size
    NodeSetList* node_sets;
    NodeSet::allSets(set_size); /// REMEMBER TO FREE THIS

    // for each set of the given set size
    for(NodeSetListIt i = node_sets->begin(); i != node_sets->end(); i++)
    {
      NodeSet* set = (*i);
    }
  }
  // return the optimal distance
  return 0; /// FIXME

}*/
