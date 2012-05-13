#ifndef NODESET_HPP_INCLUDED
#define NODESET_HPP_INCLUDED

#include <list>

#include "types.h"

// forward declaration
class NodeSet;
// containers
typedef std::list<NodeSet*> NodeSetList;
typedef NodeSetList::iterator NodeSetListIt;

class NodeSet
{
  /* FUNCTIONS */
public:
  static NodeSetList* allSets(uint size, uint n_nodes);

  /* ATTRIBUTES */
private:
  // set on indexes corresponding to rows/columns in a distance matrix

  /* METHODS */
public:
  // creation, destruction
  NodeSet();
  // modification
  void add(uint node_i);
  // query

};

#endif // NODESET_HPP_INCLUDED
