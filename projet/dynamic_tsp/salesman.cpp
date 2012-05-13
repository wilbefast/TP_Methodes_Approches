#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "salesman.hpp"
#include "node_set.hpp"

using namespace std;

/* TRAVELLING SALESMAN PROBLEM SOLVER */

uint salesman(matrix_t* distances, uint n_nodes)
{
  // the optimal round-trip distance
  uint result = 0;

  // this structure maps a node-set/end-node pair to the shortest cost for
  // starting at 0, traversing the set ending at the specified destination
  costmap_t C;

  // this structure contains all the node-sets of each size
  nodemetaset_t node_metasets[n_nodes];
  build_node_metasets(node_metasets, n_nodes);
  print_node_metasets(node_metasets, n_nodes);

  // for shortest path from the start (0) any other node (1 .. n_nodes-1)
  // is always the birds' flight distance given by the distances matrix
  nodeset_t start_s;
    start_s.insert(0);
  for (uint end_i = 1; end_i < n_nodes; end_i++)
  {
    itinerary_t start_end(start_s, end_i);
    C[start_end] = distances->t[0][end_i];

    // NB - pointers saved in C so it can be freed at the end
  }

  // for sets of more than one node, things become a little more complicated
  for(uint set_size = 1; set_size < n_nodes; set_size++)
  {
    // get the set of all nodes-sets of the current size
    nodemetaset_t& mset = node_metasets[set_size];

    // for each set of the given set size
    for(nodemetaset_it set_it = mset.begin(); set_it != mset.end(); set_it++)
    {
      nodeset_t set = (*set_it);
      print_nodes(&set);

      // we already know the length of the optimal circuit within 'set' (S), now
      // we need to extend it by choosing a leaving node 'n' and a new end node
      // 'e' and then back to the start node 's' to complete a larger circuit.
      //    ___
      //   /   s----------.
      //  |  S  |         :
      //  |     n---------e
      //   \___/


      // first we choose 'n' from amongst the starting set
      for(nodeset_it n_it = set.begin(); n_it != set.end(); n_it++)
      {
        uint n = (*n_it);
        // make sure that 'n' is not 's'
        if(n == 0)
          continue;

        // next we choose 'e' from amongst those nodes not in 'set'
        for(uint e = 1; e < n_nodes; e++)
        {
          // make sure that 'e' is not already in 'set'
          nodeset_it search = set.find(e);
          if(search != set.end())
            continue;

          // create a copy of the original set minus n
          nodeset_t set_minus_n(set);
          set_minus_n.erase(n);

          // the new circuit is the best circuit ending with 'n' plus the
          // distance from 'n' to 'e', plus the best distance from 'e' to the
          // start again.
          itinerary_t to_n(set_minus_n, n),
                      to_e(set, e);

          C[to_e] = C[to_n] + distances->t[n][e] + distances->t[e][0];




          printf("we'll add %d from %d\n", e, n);
        }
      }

    }
  }

  // free the cost-map's contents
  /*for(costmap_it cm_i = C.begin(); cm_i != C.end(); cm_i++)
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

/*
      for(nodeset_it node_it = set.begin(); node_it != set.end(); node_it++)
        for(nodeset_it node_it = set.begin(); node_it != set.end(); node_it++)
      {
        //uint m =
        // calculate the min cost to travel between all the nodes of the set,
        // finishing at the end node
        uint min_distance = UINT_MAX;
      }
*/

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
