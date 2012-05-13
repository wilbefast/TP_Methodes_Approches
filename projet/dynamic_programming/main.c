#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

#include "knapsack_unit.h"
#include "knapsack_stress.h"

#include "partition_unit.h"
#include "partition_stress.h"

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

  return EXIT_SUCCESS;
}
