#ifndef SHORTESTPATHS_HPP_INCLUDED
#define SHORTESTPATHS_HPP_INCLUDED

#include "NodeSet.hpp"

class ShortestPaths
{
  /* ATTRIBUTES */
private:

  /* METHODS */
public:
  // creation, destruction
  ShortestPaths();
  // query
  // modification
  void setDistance(NodeSet* set, uint end_i);
};

#endif // SHORTESTPATHS_HPP_INCLUDED
