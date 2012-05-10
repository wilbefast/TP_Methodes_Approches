#include <stdlib.h>

#include "salesman.h"

#define TSP_N_OBJ 5
#define TSP_DISTANCES {               \
                        {0,1,2,1,0},  \
                        {1,0,3,5,0},  \
                        {2,3,0,2,1},  \
                        {1,5,2,0,4},  \
                        {0,0,1,4,0}   \
                      }

bool_t salesman_uint()
{
  /* instance voyageur de commerce : on veut minimiser la valeur du circuit hamiltonien */

  // allocate distance matrix
  matrix_t distances;
    distances.n_rows = distances.n_cols = TSP_N_OBJ;
  malloc_matrix(&distances);

  // intialise distances
  {
    size_t temp[TSP_N_OBJ][TSP_N_OBJ] = TSP_DISTANCES, line, col;
    for(line = 0; line < TSP_N_OBJ; line++)
      for(col = 0; col < TSP_N_OBJ; col++)
        distances.t[line][col] = temp[line][col];
  }

  // launch the TSP solver
  salesman(&distances, TSP_N_OBJ);

  // unit test result
  return TRUE;
}

int salesman(matrix_t* weights, size_t n_obj)
{
  /// TODO
  return 0;
}
