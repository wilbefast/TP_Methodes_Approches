#include <stdio.h>
#include <stdlib.h>

#include "glpk_ex.hpp"
#include "boost_graph_ex.hpp"
#include "astar_cities.hpp"
#include "matching_ex.hpp"

int main(int argc, char** argv, char** envp)
{
  glpk_ex();
  boost_graph_ex();
  astar_cities();
  matching_ex();

  return EXIT_SUCCESS;
}
