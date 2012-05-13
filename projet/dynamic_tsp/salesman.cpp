#include <stdlib.h>
#include <stdio.h>

#include <map>
#include <set>

#include "salesman.hpp"

using namespace std;

/* TYPES DEFINITIONS */

// set of node identifiers
typedef set<uint> nodeset_t;
typedef nodeset_t::iterator nodeset_it;
// set of node sets
typedef set<nodeset_t> nodemetaset_t;
typedef nodemetaset_t::iterator nodemetaset_it;
// node set with a destination to arrive at when others are visited
typedef pair<nodeset_t*, uint> itinerary_t;
// iternaries mapped to the shortest distance to traverse it entirely
typedef map<itinerary_t*, uint> costmap_t;
typedef costmap_t::iterator costmap_it;

/* PRIVATE FUNCTIONS */

void print_nodesets(nodemetaset_t nodesets[], uint n_nodes)
{
  for(uint size = 0; size < n_nodes; size++)
  {
    nodemetaset_t& nodemset = nodesets[size];
    printf("%d sets %d in size :\n", (int)nodemset.size(), size+1);
    for(nodemetaset_it i = nodemset.begin(); i != nodemset.end(); i++)
    {
      printf("\t{ ");
      for(nodeset_it j = (*i).begin(); j != (*i).end(); j++)
        printf("%d ", (*j));
      printf("}\n");
    }
  }
}

void build_nodesets_aux(nodemetaset_t nodesets[], uint n_nodes, uint index)
{
  // since it is pointless to consider sets of size 0, index 0 is used for sets
  // of size 1 and so on.
  uint size = index + 1;

  // base case
  if(size > n_nodes)
    return;

  // bootstrap
  else if(size == 1)
  {
    // size 1 is initialised with a unitary set for each node identifie
    for(uint node_i = 0; node_i < n_nodes; node_i++)
    {
      nodeset_t new_set;
      new_set.insert(node_i);
      nodesets[index].insert(new_set);
    }
  }

  // recursion
  else
  {
    nodemetaset_t& previous = nodesets[index-1];

    // we'll be adding each node identifier to what already exists
    for(uint node_i = 0; node_i < n_nodes; node_i++)
    {
      // for each set of sets that is 1 smaller than the one we're currently
      // trying to build
      for(nodemetaset_it nms_i = previous.begin(); nms_i != previous.end();
                                                  nms_i++)
      {
        // copy each set and add a different identifier to the copy each time
        nodeset_t new_set((*nms_i));
        new_set.insert(node_i);

        // add the result to the node-set set we're currently building, but only
        // if the size is correct, that is we didn't add something that was
        // already there
        if(new_set.size() == size)
          nodesets[index].insert(new_set);
      }
    }
  }

  // move on to the next size - remember that we incremented size at the start:
  // it will be incremented again at the beginning of the next step !
  build_nodesets_aux(nodesets, n_nodes, index+1);
}

void build_nodesets(nodemetaset_t nodesets[], uint n_nodes)
{
  // launch recursion with the correct value
  build_nodesets_aux(nodesets, n_nodes, 0);
}


/* TRAVELLING SALESMAN PROBLEM SOLVER */

uint salesman(matrix_t* distances, uint n_nodes)
{
  // the optimal round-trip distance
  uint result = 0;

  // this structure maps a node-set/end-node pair to the shortest cost for
  // starting at 0, traversing the set ending at the specified destination
  costmap_t C;

  // this structure contains all the node-sets of each size
  nodemetaset_t nodemetasets[n_nodes];
  build_nodesets(nodemetasets, n_nodes);
  print_nodesets(nodemetasets, n_nodes);

  // for shortest path from the start (0) any other node (1 .. n_nodes-1)
  // is always the birds' flight distance given by the distances matrix
  /*nodeset_t start_s;
    start_s.insert(0);
  for (uint end_i = 1; end_i < n_nodes; end_i++)
  {
    itinerary_t* start_end = new itinerary_t(&start_s, end_i);
    C[start_end] = distances->t[0][end_i];

    // NB - pointers saved in C so it can be freed at the end
  }

  // for sets of more than one node, things become a little more complicated
  for(uint set_size = 2; set_size < n_nodes; set_size++)
  {
    // get a set of all nodes-sets of this size
    nodemetaset_t& mset = nodesets[set_size];

    // for each set of the given set size
    for(nodemetaset_it set_i = mset.begin(); set_i != mset.end(); set_i++)
    {
      nodeset_t set = (*set_i);
      for(nodeset_it node_i = set.begin(); node_i != set.end(); node_i++)
        ;
    }
  }

  // free the cost-map's contents
  for(costmap_it cm_i = C.begin(); cm_i != C.end(); cm_i++)
  {
    itinerary_t* i = (*cm_i).first;
    nodeset_t* ns = i->first;
    // clear and delete the node set
    ns->clear();
    delete ns;
    // also destroy the node-set/end-node pair
    delete i;
  }*/

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
