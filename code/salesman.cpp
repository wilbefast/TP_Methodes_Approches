uint salesman(matrix_t* distances, uint n_nodes)
{
  // the optimal round-trip distance
  uint result = UINT_MAX;

  // this structure maps a node-set/end-node pair to the shortest cost for
  // starting at 0, traversing the set ending at the specified destination
  costmap_t C;

  // this structure contains all the node-sets of each size
  nodemetaset_t node_metasets[n_nodes];
  // FIXME -- IT IS UNSAFE TO ALLOCATE ARRAYS IN THIS MANNER as the compiler
	// won't know how big this statically allocated array is at compile time!
  build_node_metasets(node_metasets, n_nodes);

  // the shortest path from the start (0) any other node (1 .. n_nodes-1)
  // is always the birds' flight distance given by the distances matrix
  nodeset_t start_s;
    start_s.insert(0);
  for (uint end_i = 1; end_i < n_nodes; end_i++)
  {
    itinerary_t start_end(start_s, end_i);
    C[start_end] = distances->t[0][end_i];
  }

  // for sets of more than one node, things become a little more complicated
  for(uint set_size = 1; set_size < n_nodes-1; set_size++)
  {
    // get the set of all nodes-sets of the current size
    nodemetaset_t& mset = node_metasets[set_size];

    // for each set of the given set size
    for(nodemetaset_it set_it = mset.begin(); set_it != mset.end(); set_it++)
    {
      nodeset_t set = (*set_it);

      // we already know the length of the optimal circuit within 'set' (S), now
      // we need to extend it by choosing a leaving node 'n' and a new end node
      // 'e' and then back to the start node 's' to complete a larger circuit.
      //    ___
      //   /   s----------.
      //  |  S  |         :
      //  |     n---------e
      //   \___/
      //
      // for our purposes though we'll not consider the distance from 'e' to 's'
      // as this would prevent us from building on the result later.

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

          // the 'to_n' itinerary may not have been mapped yet, in which case
          // we'll need to create it
          if(set_minus_n.size() == 1)
            C[to_n] = distances->t[*(set_minus_n.begin())][n];

          // dump results to memory : we'll continue building on it later
          bool exists = (C.find(to_e) == C.end());
          uint new_distance = C[to_n] + distances->t[n][e];
          C[to_e] = (exists) ? new_distance : min(C[to_e], new_distance);

          // unless of course this is the final iteration, in which case we can
          // begin to figure out what the result is based on all our hard work.
          // This is as simple as connecting the path back to the start node.
          if(set_size == n_nodes-2)
            result = min(result, C[to_e] + distances->t[e][0]);
        }
      }
    }

  }

  // return result
  return result;
}

