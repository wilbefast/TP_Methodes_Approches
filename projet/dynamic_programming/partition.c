#include <stdlib.h>
#include <string.h>

#include "math.h"
#include "partition.h"

/* UNIT TEST */

#include "assert.h"

#define UNIT1_PART_N_OBJ 4
#define UNIT1_PART_WEIGHTS {2,6,2,2}
#define UNIT1_PART_RIGHT_ANSWER TRUE

#define UNIT2_PART_N_OBJ 3
#define UNIT2_PART_WEIGHTS {1,4,3}
#define UNIT2_PART_RIGHT_ANSWER TRUE

#define UNIT3_PART_N_OBJ 3
#define UNIT3_PART_WEIGHTS {1,2,7}
#define UNIT3_PART_RIGHT_ANSWER FALSE

#define UNIT4_PART_N_OBJ 4
#define UNIT4_PART_WEIGHTS {14,5,2,6}
#define UNIT4_PART_RIGHT_ANSWER FALSE

int partition_unit()
{
  // test 1
  {
    size_t weights[UNIT1_PART_N_OBJ] = UNIT1_PART_WEIGHTS;
    size_t result = partition(UNIT1_PART_N_OBJ, weights);
    ASSERT(result == UNIT1_PART_RIGHT_ANSWER, "partition result check 1");
  }

  // test 2
  {
    size_t weights[UNIT2_PART_N_OBJ] = UNIT2_PART_WEIGHTS;
    size_t result = partition(UNIT2_PART_N_OBJ, weights);
    ASSERT(result == UNIT2_PART_RIGHT_ANSWER, "partition result check 2");
  }

  // test 3
  {
    size_t weights[UNIT3_PART_N_OBJ] = UNIT3_PART_WEIGHTS;
    size_t result = partition(UNIT3_PART_N_OBJ, weights);
    ASSERT(result == UNIT3_PART_RIGHT_ANSWER, "partition result check 3");
  }

  // test 4
  {
    size_t weights[UNIT4_PART_N_OBJ] = UNIT4_PART_WEIGHTS;
    size_t result = partition(UNIT4_PART_N_OBJ, weights);
    ASSERT(result == UNIT4_PART_RIGHT_ANSWER, "partition result check 4");
  }

  // all tests were successful
  return EXIT_SUCCESS;
}

/* PARTITION PROBLEM SOLVER */

size_t partition(size_t n_obj, size_t weights[])
{
  // calcul de la somme totale des poids
  size_t row, total_weight = 0;
  for(row = 0; row < n_obj; row++ )
    total_weight += weights[row];

  // initialisation du tableau de booleens
  bool_t* bools = malloc(sizeof(bool_t) * total_weight);
  bools[0] = TRUE;
  memset(bools+1, FALSE, total_weight-1);

  // remplissage de la table selon les formules de la programmation dynamique
  int col;
  for(row = 0; row < n_obj; row++ )
    for(col = total_weight-weights[row]-1; col >= 0; col--)
      if(bools[col])
        bools[col + weights[row]] = TRUE;


  // free the table
  bool_t result = bools[total_weight / 2];
  free(bools);

  // la reponse qui nous interesse
  return result;
}

 initialize a list S to contain one element 0.
 for each i from 1 to N do
   let T be a list consisting of xi + y, for all y in S
   let U be the union of T and S
   sort U
   make S empty
   let y be the smallest element of U
   add y to S
   for each element z of U in increasing order do
      //trim the list by eliminating numbers close to one another
      //and throw out elements greater than s
     if y + cs/N < z ≤ s, set y = z and add z to S
 if S contains a number between (1 − c)s and s, output yes, otherwise no
