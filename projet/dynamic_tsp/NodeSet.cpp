#include "NodeSet.hpp"

/* FUNCTIONS */

NodeSetList* NodeSet::allSets(uint size, uint n_nodes)
{
  // recursion base case : return the empty list
  if(size == 0)
    return new NodeSetList();

  // recursive step
  NodeSetList* result = allSets(size-1, n_nodes);
  for(uint node_i = 0; node_i < n_nodes; node_i++)
  {

    NodeSet* set = new NodeSet();
    set->add(node_i);
  }
}

/* CREATION, DESTRUCTION */

NodeSet::NodeSet()
{
}

/* MODIFICATION */

void NodeSet::add(uint node_i)
{

}
