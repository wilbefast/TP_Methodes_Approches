#include <stdlib.h>

#include "knapsack.h"
#include "math.h"
#include "matrix.h"

/* UNIT TEST */

#include "assert.h"

#define UNIT1_KNAPS_N_OBJ 7
#define UNIT1_KNAPS_CAPACITY 2
#define UNIT1_KNAPS_WEIGHTS {3,5,1,5,7,2,6}
#define UNIT1_KNAPS_UTILITIES {2,5,3,3,6,2,4}
#define UNIT1_KNAPS_RIGHT_ANSWER 3 // take item number 2, with utility 3


int knapsack_unit()
{
  // test 1
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[UNIT1_KNAPS_N_OBJ] = UNIT1_KNAPS_WEIGHTS;
    size_t utilities[UNIT1_KNAPS_N_OBJ] = UNIT1_KNAPS_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack(UNIT1_KNAPS_CAPACITY, UNIT1_KNAPS_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == UNIT1_KNAPS_RIGHT_ANSWER, "knapsack result check");
  }

  // unit test result
  return EXIT_SUCCESS;
}

/* KNAPSACK PROBLEM SOLVER */

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
  size_t row;
  for (row = 1; row < n_obj; row++)
    for (col = 0; col < capacity + 1; col++)
    {
      if (col >= weights[row])
        m.t[row][col] =
          max(m.t[row-1][col], m.t[row-1][col-weights[row]] + utilities[row]);
      else
        m.t[row][col] = m.t[row-1] [col];
    }

  // store the result and free the matrix
  size_t result = m.t[n_obj -1][capacity];
  free_matrix(&m);

  // la valeur qui nous interesse
  return result;
}

