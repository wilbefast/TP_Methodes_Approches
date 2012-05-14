#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "salesman.hpp"
#include "salesman_unit.hpp"
#include "salesman_stress.hpp"

#include "assert.h"

int main()
{
  // initialise random number generator
  srand(time(NULL));

  // test tsp
  //ASSERT((salesman_unit()) != EXIT_FAILURE, "tsp unit test");
  salesman_stress();

  return EXIT_SUCCESS;
}
