#include <stdlib.h>

#include "knapsack.h"
#include "math.h"
#include "matrix.h"

#define KNAPS_N_OBJ 7
#define KNAPS_CAPACITY 2
#define KNAPS_WEIGHTS {3,5,1,5,7,2,6}
#define KNAPS_UTILITIES {2,5,3,3,6,2,4}

bool_t knapsack_unit()
{
  // instance sac a dos : on veut maximiser l'utilite
  size_t weights[KNAPS_N_OBJ] = KNAPS_WEIGHTS;
  size_t utilities[KNAPS_N_OBJ] = KNAPS_UTILITIES;

  // solve the problem
  knapsack(KNAPS_CAPACITY, KNAPS_N_OBJ, weights, utilities);

  // unit test result
  return TRUE;
}

size_t knapsack(size_t capacity, size_t n_obj, size_t weights[], size_t utilities[])
{
  // tableau central de la programmation dynamique
  matrix_t m;
    m.n_rows = n_obj;
    m.n_cols = capacity + 1;
  malloc_matrix(&m);

  // initialisation de la table
  size_t col;
  for (col = 0; col < capacity + 1; col++)
    m.t[0][col] = 0;

  // remplissage de la table selon les formules de la prog dyn
  size_t line;
  for (line = 1; line < n_obj; line++)
    for (col = 0; col < capacity + 1; col++)
    {
      if (col >= weights[line])
        m.t[line][col] =
          max(m.t[line-1][col], m.t[line-1][col-weights[line]] + utilities[line]);
      else
        m.t[line][col] = m.t[line-1] [col];
    }

  // free the matrix
  free_matrix(&m);

  // la valeur qui nous interesse
  return (m.t[n_obj -1][capacity]);
}

