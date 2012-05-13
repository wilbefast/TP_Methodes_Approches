#include <stdlib.h>

#include "salesman.h"

/* TSP UNIT TEST */

#include "assert.h"

#define TSP_UNIT1_N_OBJ 5
#define TSP_UNIT1_DISTANCES {               \
                              {0,1,2,1,0},  \
                              {1,0,3,5,0},  \
                              {2,3,0,2,1},  \
                              {1,5,2,0,4},  \
                              {0,0,1,4,0}   \
                            }
#define TSP_UNIT1_RIGHT_ANSWER 5

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
      size_t temp[TSP_UNIT1_N_OBJ][TSP_UNIT1_N_OBJ]
                  = TSP_UNIT1_DISTANCES, row, col;
      for(row = 0; row < TSP_UNIT1_N_OBJ; row++)
        for(col = 0; col < TSP_UNIT1_N_OBJ; col++)
          distances.t[row][col] = temp[row][col];
    }

    // launch the TSP solver
    size_t result = salesman(&distances, TSP_UNIT1_N_OBJ);
    ASSERT(result == TSP_UNIT1_RIGHT_ANSWER, "tsp result check 1");
  }

  // success
  return EXIT_SUCCESS;
}

/* TRAVELLING SALESMAN PROBLEM SOLVER */

int salesman(matrix_t* weights, size_t n_obj)
{
  /// TODO
  return 0;
/*
  function algorithm T SP (G, n)
for k := 2 to n do
C({i, k}, k) := d1,k
end for
for s = 3 to n do
for all S ⊆ {1, 2, . . . , n}||S|| = s do
for all k ∈ S do
{C(S, k) = minm=k,m∈S [C(S − {k}, m) + dm,k ]}
opt := mink=1 [C({1, 2, 3, . . . , n}, k) + d1,k
end for
end for
end for;
return (opt)
end
*/
}
