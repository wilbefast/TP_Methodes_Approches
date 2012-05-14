#include <stdlib.h>

#include "salesman_unit.hpp"
#include "salesman.hpp"

#include "assert.h"

#define TSP_UNIT1_N_OBJ 4
#define TSP_UNIT1_DISTANCES {               \
                              {0,1,2,1},  \
                              {1,0,1,2},  \
                              {2,1,0,1},  \
                              {1,2,1,0},  \
                            }
#define TSP_UNIT1_RIGHT_ANSWER 4

#define TSP_UNIT2_N_OBJ 5
#define TSP_UNIT2_DISTANCES {               \
                              {0,1,2,1,0},  \
                              {1,0,3,5,0},  \
                              {2,3,0,2,1},  \
                              {1,5,2,0,4},  \
                              {0,0,1,4,0}   \
                            }
#define TSP_UNIT2_RIGHT_ANSWER 5

using namespace std;

int salesman_unit()
{
  // test 1
  {
    // allocate distance matrix
    matrix_t distances;
      distances.n_rows = distances.n_cols = TSP_UNIT1_N_OBJ;
    malloc_matrix(&distances);

    // intialise distances
    {
      uint temp[TSP_UNIT1_N_OBJ][TSP_UNIT1_N_OBJ]
                  = TSP_UNIT1_DISTANCES, row, col;
      for(row = 0; row < TSP_UNIT1_N_OBJ; row++)
        for(col = 0; col < TSP_UNIT1_N_OBJ; col++)
          distances.t[row][col] = temp[row][col];
    }

    // launch the TSP solver
    uint result = salesman(&distances, TSP_UNIT1_N_OBJ);
    ASSERT(result == TSP_UNIT1_RIGHT_ANSWER, "tsp result check 1");
  }

  // test 2
  {
    // allocate distance matrix
    matrix_t distances;
      distances.n_rows = distances.n_cols = TSP_UNIT2_N_OBJ;
    malloc_matrix(&distances);

    // intialise distances
    {
      uint temp[TSP_UNIT2_N_OBJ][TSP_UNIT2_N_OBJ]
                  = TSP_UNIT2_DISTANCES, row, col;
      for(row = 0; row < TSP_UNIT2_N_OBJ; row++)
        for(col = 0; col < TSP_UNIT2_N_OBJ; col++)
          distances.t[row][col] = temp[row][col];
    }

    // launch the TSP solver
    uint result = salesman(&distances, TSP_UNIT2_N_OBJ);
    ASSERT(result == TSP_UNIT2_RIGHT_ANSWER, "tsp result check 2");
  }

  // success
  return EXIT_SUCCESS;
}
