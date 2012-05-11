#include <stdlib.h>
#include <string.h>

#include "math.h"
#include "partition.h"

/* UNIT TEST */

#include "assert.h"

#define PART_UNIT1_N_OBJ 4
#define PART_UNIT1_WEIGHTS {2,6,2,2}
#define PART_UNIT1_RIGHT_ANSWER TRUE

#define PART_UNIT2_N_OBJ 3
#define PART_UNIT2_WEIGHTS {1,4,3}
#define PART_UNIT2_RIGHT_ANSWER TRUE

#define PART_UNIT3_N_OBJ 3
#define PART_UNIT3_WEIGHTS {1,2,7}
#define PART_UNIT3_RIGHT_ANSWER FALSE

#define PART_UNIT4_N_OBJ 4
#define PART_UNIT4_WEIGHTS {14,5,2,6}
#define PART_UNIT4_RIGHT_ANSWER FALSE

int partition_unit()
{
  // test 1
  {
    size_t weights[PART_UNIT1_N_OBJ] = PART_UNIT1_WEIGHTS;
    bool_t result = partition(PART_UNIT1_N_OBJ, weights);
    ASSERT(result == PART_UNIT1_RIGHT_ANSWER, "partition result check 1");
  }

  // test 2
  {
    size_t weights[PART_UNIT2_N_OBJ] = PART_UNIT2_WEIGHTS;
    bool_t result = partition(PART_UNIT2_N_OBJ, weights);
    ASSERT(result == PART_UNIT2_RIGHT_ANSWER, "partition result check 2");
  }

  // test 3
  {
    size_t weights[PART_UNIT3_N_OBJ] = PART_UNIT3_WEIGHTS;
    bool_t result = partition(PART_UNIT3_N_OBJ, weights);
    ASSERT(result == PART_UNIT3_RIGHT_ANSWER, "partition result check 3");
  }

  // test 4
  {
    size_t weights[PART_UNIT4_N_OBJ] = PART_UNIT4_WEIGHTS;
    bool_t result = partition(PART_UNIT4_N_OBJ, weights);
    ASSERT(result == PART_UNIT4_RIGHT_ANSWER, "partition result check 4");
  }

  // all tests were successful
  return EXIT_SUCCESS;
}

/* PARTITION PROBLEM SOLVER */

bool_t partition(size_t n_obj, size_t weights[])
{
  // calcul de la somme totale des poids
  size_t obj, total_weight = 0;
  for(obj = 0; obj < n_obj; obj++ )
    total_weight += weights[obj];

  // can't partition an uneven number in two !
  if(total_weight%2)
    return FALSE;

  // initialisation du tableau de booleens
  bool_t* can_sum = calloc(total_weight+1, sizeof(bool_t));
  can_sum[0] = TRUE;

  // remplissage de la table selon les formules de la programmation dynamique
  int weight;
  for(obj = 0; obj < n_obj; obj++ )
    for(weight = total_weight-weights[obj]; weight >= 0; weight--)
      if(can_sum[weight])
        can_sum[weight + weights[obj]] = TRUE;


  // free the table
  bool_t result = can_sum[total_weight / 2];
  free(can_sum);

  // la reponse qui nous interesse
  return result;
}
