#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"
#include "partition.h"
#include "salesman.h"

#include "assert.h"

int main()
{
  // initialise random number generator
  srand(time(NULL));

  // test matrix
  ASSERT(matrix_unit() != EXIT_FAILURE, "matrix structure unit test");

  // test knapsack
  ASSERT(knapsack_unit() != EXIT_FAILURE, "knapsack unit test");
  knapsack_stress();

  // test partition
  ASSERT(partition_unit() != EXIT_FAILURE, "partition unit test");
  partition_stress();

  // test tsp
  ASSERT((salesman_unit()) != EXIT_FAILURE, "tsp unit test");
  //tsp_stress();

  return EXIT_SUCCESS;
}
