#include <stdio.h>

#include "node_set.hpp"

/* PRIVATE FUNCTIONS -- DECLARATIONS */

void build_node_metasets_aux(nodemetaset_t node_metasets[], uint n_nodes,
                            uint index);


/* BUILD ALL THE NODESETS OF EACH SIZE */

void build_node_metasets(nodemetaset_t node_metasets[], uint n_nodes)
{
  // launch recursion with the correct value
  build_node_metasets_aux(node_metasets, n_nodes, 0);
}


/* DEBUG INFORMATION */

void print_nodes(nodeset_t const* nodeset)
{
  printf("\t{ ");
  for(nodeset_it i = nodeset->begin(); i != nodeset->end(); i++)
    printf("%d ", (*i));
  printf("}\n");
}

void print_node_sets(nodemetaset_t const* node_metaset)
{
  for(nodemetaset_it i = node_metaset->begin(); i != node_metaset->end(); i++)
    print_nodes(&(*i));
}

void print_node_metasets(nodemetaset_t node_metasets[], uint n_nodes)
{
  for(uint size = 0; size < n_nodes; size++)
  {
    nodemetaset_t* node_metaset = &node_metasets[size];
    printf("%d set(s) of size %d :\n", (int)node_metaset->size(), size+1);
    print_node_sets(node_metaset);
  }
}

/* PRIVATE FUNCTIONS -- DEFINITIONS */

void build_node_metasets_aux(nodemetaset_t node_metasets[], uint n_nodes,
                            uint index)
{
  // since it is pointless to consider sets of size 0, index 0 is used for sets
  // of size 1 and so on.
  uint size = index + 1;

  // base case -- stop after reaching the full size
  if(size > n_nodes)
    return;

  // bootstrap -- unitary sets must be built by hand
  else if(size == 1)
  {
    // size 1 is initialised with a unitary set for each node identifier
    for(uint node_i = 0; node_i < n_nodes; node_i++)
    {
      nodeset_t new_set;
      new_set.insert(node_i);
      node_metasets[index].insert(new_set);
    }
  }

  // recursion -- will out each size based on previous sizes
  else
  {
    nodemetaset_t& previous = node_metasets[index-1];

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
          node_metasets[index].insert(new_set);
      }
    }
  }

  // move on to the next size - remember that we incremented size at the start:
  // it will be incremented again at the beginning of the next step !
  build_node_metasets_aux(node_metasets, n_nodes, index+1);
}
