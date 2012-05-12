#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "math.h"
#include "partition.h"


/* PRIVATE FUNCTIONS */

// create and destruction of partition problem instances
void create_partition_i(partition_instance_t* inst, size_t _n_obj);
void destroy_partition_i(partition_instance_t* inst);

// partition solver which takes the unrolled parameter list
bool_t partition_aux(size_t n_obj, size_t values[]);


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
    size_t values[PART_UNIT1_N_OBJ] = PART_UNIT1_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT1_N_OBJ, values);
    ASSERT(result == PART_UNIT1_RIGHT_ANSWER, "partition result check 1");
  }

  // test 2
  {
    size_t values[PART_UNIT2_N_OBJ] = PART_UNIT2_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT2_N_OBJ, values);
    ASSERT(result == PART_UNIT2_RIGHT_ANSWER, "partition result check 2");
  }

  // test 3
  {
    size_t values[PART_UNIT3_N_OBJ] = PART_UNIT3_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT3_N_OBJ, values);
    ASSERT(result == PART_UNIT3_RIGHT_ANSWER, "partition result check 3");
  }

  // test 4
  {
    size_t values[PART_UNIT4_N_OBJ] = PART_UNIT4_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT4_N_OBJ, values);
    ASSERT(result == PART_UNIT4_RIGHT_ANSWER, "partition result check 4");
  }

  // all tests were successful
  return EXIT_SUCCESS;
}


/* STRESS TEST */

#define PART_STRESS_N_OBJ 500
#define PART_STRESS_N_TESTS 100

void partition_stress()
{
  printf("partition stress test:\n\t%d objects\n\t%d tests\n",
        PART_STRESS_N_OBJ, PART_STRESS_N_TESTS);
  double t = time_partition_rand(PART_STRESS_N_OBJ, PART_STRESS_N_TESTS);
  printf("\taverage solving time = %es\n", t);
}



/* RANDOM GENERATOR */


size_t partition_rand(size_t n_obj)
{
  // create a random partition problem instance
  partition_instance_t inst;
  create_partition_i(&inst, n_obj);

  // solve and destroy instance
  size_t result = partition(inst);
  destroy_partition_i(&inst);

  // return result
  return result;
}

double time_partition_rand(size_t n_obj, size_t n_tests)
{
  // time before tests began
  long unsigned int start = time(NULL);

  // launch the required number of tests on random instances
  size_t test;
  for(test = 0; test < n_tests; test++)
    partition_rand(n_obj);

  // return the difference in time between before and after
  long unsigned int end = time(NULL);
  return (end-start)/(double)n_tests;
}

void create_partition_i(partition_instance_t* inst, size_t _n_obj)
{
  // initialise parameters
  inst->n_obj = _n_obj;
  inst->values = malloc(sizeof(size_t) * _n_obj);

  // randomise values and utilities
  size_t obj;
  for(obj = 0; obj < _n_obj; obj++)
    inst->values[obj] = rand();
}

void destroy_partition_i(partition_instance_t* inst)
{
  free(inst->values);
}


/* PARTITION PROBLEM SOLVER */

bool_t partition_aux(size_t n_obj, size_t values[])
{
  // calcul de la somme totale des poids
  size_t obj, total_weight = 0;
  for(obj = 0; obj < n_obj; obj++ )
    total_weight += values[obj];

  // can't partition an uneven number in two !
  if(total_weight%2)
    return FALSE;

  // initialisation du tableau de booleens
  bool_t* can_sum = calloc(total_weight+1, sizeof(bool_t));
  can_sum[0] = TRUE;

  // remplissage de la table selon les formules de la programmation dynamique
  int weight;
  for(obj = 0; obj < n_obj; obj++ )
    for(weight = total_weight-values[obj]; weight >= 0; weight--)
      if(can_sum[weight])
        can_sum[weight + values[obj]] = TRUE;


  // free the table
  bool_t result = can_sum[total_weight / 2];
  free(can_sum);

  // la reponse qui nous interesse
  return result;
}

bool_t partition(partition_instance_t inst)
{
  return partition_aux(inst.n_obj, inst.values);
}
