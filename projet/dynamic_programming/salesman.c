#include <stdlib.h>

#include "salesman.h"

/* TSP UNIT TEST */

#include "assert.h"

#define TSP_N_OBJ 5
#define TSP_DISTANCES {               \
                        {0,1,2,1,0},  \
                        {1,0,3,5,0},  \
                        {2,3,0,2,1},  \
                        {1,5,2,0,4},  \
                        {0,0,1,4,0}   \
                      }

int salesman_unit()
{
  /* instance voyageur de commerce : on veut minimiser la valeur du circuit hamiltonien */

  // allocate distance matrix
  matrix_t distances;
    distances.n_rows = distances.n_cols = TSP_N_OBJ;
  malloc_matrix(&distances);

  // intialise distances
  {
    size_t temp[TSP_N_OBJ][TSP_N_OBJ] = TSP_DISTANCES, row, col;
    for(row = 0; row < TSP_N_OBJ; row++)
      for(col = 0; col < TSP_N_OBJ; col++)
        distances.t[row][col] = temp[row][col];
  }

  // launch the TSP solver
  salesman(&distances, TSP_N_OBJ);

  // success
  return EXIT_SUCCESS;
}

/* TRAVELLING SALESMAN PROBLEM SOLVER */

int salesman(matrix_t* weights, size_t n_obj)
{
  /// TODO
  return 0;
}
