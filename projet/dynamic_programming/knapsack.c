#include <stdlib.h>

#include "knapsack.h"
#include "math.h"
#include "matrix.h"

/* UNIT TEST */

#include "assert.h"

#define KNAPS_UNIT1_N_OBJ 7
#define KNAPS_UNIT1_CAPACITY 2
#define KNAPS_UNIT1_WEIGHTS {3,5,1,5,7,2,6}
#define KNAPS_UNIT1_UTILITIES {2,5,3,3,6,2,4}
#define KNAPS_UNIT1_RIGHT_ANSWER 3 // take item number 2, with utility 3


int knapsack_unit()
{
  // test 1
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT1_N_OBJ] = KNAPS_UNIT1_WEIGHTS;
    size_t utilities[KNAPS_UNIT1_N_OBJ] = KNAPS_UNIT1_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack(KNAPS_UNIT1_CAPACITY, KNAPS_UNIT1_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT1_RIGHT_ANSWER, "knapsack result check 1");
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

