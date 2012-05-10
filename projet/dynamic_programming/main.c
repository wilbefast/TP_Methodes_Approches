#include <stdio.h>
#include <stdlib.h>

#include "knapsack.h"
#include "partition.h"
#include "salesman.h"

#include "assert.h"

int main()
{
  // test matrix
  ASSERT(matrix_unit() != EXIT_FAILURE, "matrix structure unit test");

  // test knapsack
  ASSERT(knapsack_unit() != EXIT_FAILURE, "knapsack unit test");

  // test partition
  ASSERT(partition_unit() != EXIT_FAILURE, "partition unit test");

  // test tsp
  ASSERT((salesman_unit()) != EXIT_FAILURE, "tsp unit test");

  return EXIT_SUCCESS;
}
