#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "knapsack.h"
#include "math.h"
#include "matrix.h"


/* PRIVATE FUNCTIONS */

// create and destruction of knapsack problem instances
void create_knapsack_i(knapsack_instance_t* inst, size_t _capacity,
                      size_t _n_obj);
void destroy_knapsack_i(knapsack_instance_t* inst);

// knapsack solver which takes the unrolled parameter list
size_t knapsack_aux(size_t capacity, size_t n_obj, size_t weights[],
                  size_t utilities[]);


/* UNIT TEST */

#include "assert.h"

//#define KNAPS_MAX_UTILITY 100

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
      knapsack_aux(KNAPS_UNIT1_CAPACITY, KNAPS_UNIT1_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT1_RIGHT_ANSWER, "knapsack result check 1");
  }

  // unit test result
  return EXIT_SUCCESS;
}


/* STRESS TEST */

#define KNAPS_STRESS_CAPACITY 5000
#define KNAPS_STRESS_N_OBJ 500
#define KNAPS_STRESS_N_TESTS 100

void knapsack_stress()
{
  printf("knapsack stress test:\n\tcapacity = %d\n\t%d objects\n\t%d tests\n",
        KNAPS_STRESS_CAPACITY, KNAPS_STRESS_N_OBJ, KNAPS_STRESS_N_TESTS);
  long t = time_knapsack_rand(KNAPS_STRESS_CAPACITY, KNAPS_STRESS_N_OBJ,
                                KNAPS_STRESS_N_TESTS);
  printf("\taverage solving time = %ldms\n", t);
}


/* RANDOM GENERATOR */

size_t knapsack_rand(size_t capacity, size_t n_obj)
{
  // create a random knapsack problem instance
  knapsack_instance_t inst;
  create_knapsack_i(&inst, capacity, n_obj);

  // solve and destroy instance
  size_t result = knapsack(inst);
  destroy_knapsack_i(&inst);

  // return result
  return result;
}

long time_knapsack_rand(size_t capacity, size_t n_obj, size_t n_tests)
{
  // time before tests began
  struct timeval start;
  gettimeofday(&start, NULL);

  // launch the required number of tests on random instances
  size_t test;
  for(test = 0; test < n_tests; test++)
    knapsack_rand(capacity, n_obj);

  // return the difference in time between before and after
  struct timeval end;
  gettimeofday(&end, NULL);
  long time_s  = end.tv_sec  - start.tv_sec;
  long time_ms = end.tv_usec - start.tv_usec;
  long time_total = ((time_s) * 1000 + time_ms/1000.0) + 0.5;
  return time_total/n_tests;
}

void create_knapsack_i(knapsack_instance_t* inst, size_t _capacity,
                        size_t _n_obj)
{
  // initialise parameters
  inst->capacity = _capacity;
  inst->n_obj = _n_obj;
  inst->weights = malloc(sizeof(size_t) * _n_obj);
  inst->utilities = malloc(sizeof(size_t) * _n_obj);

  // randomise weights and utilities
  size_t obj;
  for(obj = 0; obj < _n_obj; obj++)
  {
    inst->weights[obj] = rand()%_capacity;
    inst->utilities[obj] = rand();
  }
}

void destroy_knapsack_i(knapsack_instance_t* inst)
{
  free(inst->weights);
  free(inst->utilities);
}

/* KNAPSACK PROBLEM SOLVER */

size_t knapsack_aux(size_t capacity, size_t n_obj, size_t weights[],
                    size_t utilities[])
{
  // Let max_value.t[i,j] is the maximum value we can achieve from objects 1..i
  // while taking a maximum weight of j.
  matrix_t max_value;
    max_value.n_rows = n_obj;
    max_value.n_cols = capacity + 1;
  calloc_matrix(&max_value);

  // remplissage de la table selon les formules de la prog dyn
  size_t obj, weight;
  for (obj = 1; obj < n_obj; obj++)
    for (weight = 0; weight <= capacity; weight++)
    {
      if (weight >= weights[obj])
      {
        // obj is part of the solution
        size_t take = max_value.t[obj-1][weight];
        // obj is not part of the solution
        size_t leave = max_value.t[obj-1][weight - weights[obj]] + utilities[obj];
        max_value.t[obj][weight] = max(take, leave);
      }
      else
        max_value.t[obj][weight] = max_value.t[obj-1][weight];
    }

  // store the result (maximum utility) and free the matrix
  size_t result = max_value.t[n_obj -1][capacity];
  free_matrix(&max_value);

  // la valeur qui nous interesse
  return result;
}

size_t knapsack(knapsack_instance_t i)
{
  return knapsack_aux(i.capacity, i.n_obj, i.weights, i.utilities);
}
