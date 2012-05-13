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

#define KNAPS_UNIT1_N_OBJ 7
#define KNAPS_UNIT1_CAPACITY 2
#define KNAPS_UNIT1_WEIGHTS   {3,5,1,5,7,2,6}
#define KNAPS_UNIT1_UTILITIES {2,5,3,3,6,2,4}
#define KNAPS_UNIT1_RIGHT_ANSWER 3 // take item 3

#define KNAPS_UNIT2_N_OBJ 10
#define KNAPS_UNIT2_CAPACITY 5
#define KNAPS_UNIT2_WEIGHTS   {1,2,3,4,5,1,2,3,4,5}
#define KNAPS_UNIT2_UTILITIES {4,3,1,3,6,2,2,4,3,7}
#define KNAPS_UNIT2_RIGHT_ANSWER 10 // take items 1, 6 and 8

#define KNAPS_UNIT3_N_OBJ 5
#define KNAPS_UNIT3_CAPACITY 11
#define KNAPS_UNIT3_WEIGHTS   {1,2,5,6,7}
#define KNAPS_UNIT3_UTILITIES {1,6,18,22,28}
#define KNAPS_UNIT3_RIGHT_ANSWER 40 // take items 3 and 4

#define KNAPS_UNIT4_N_OBJ 2
#define KNAPS_UNIT4_CAPACITY 1
#define KNAPS_UNIT4_WEIGHTS   {1,1}
#define KNAPS_UNIT4_UTILITIES {1,0}
#define KNAPS_UNIT4_RIGHT_ANSWER 1 // take item 1

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

  // test 2
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT2_N_OBJ] = KNAPS_UNIT2_WEIGHTS;
    size_t utilities[KNAPS_UNIT2_N_OBJ] = KNAPS_UNIT2_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT2_CAPACITY, KNAPS_UNIT2_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT2_RIGHT_ANSWER, "knapsack result check 2");
  }

  // test 3
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT3_N_OBJ] = KNAPS_UNIT3_WEIGHTS;
    size_t utilities[KNAPS_UNIT3_N_OBJ] = KNAPS_UNIT3_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT3_CAPACITY, KNAPS_UNIT3_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT3_RIGHT_ANSWER, "knapsack result check 3");
  }

  // test 4
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT4_N_OBJ] = KNAPS_UNIT4_WEIGHTS;
    size_t utilities[KNAPS_UNIT4_N_OBJ] = KNAPS_UNIT4_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT4_CAPACITY, KNAPS_UNIT4_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT4_RIGHT_ANSWER, "knapsack result check 4");
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
  // max_value.t[i,j] is the maximum value we can achieve with objects 0 to to i
  // while taking a maximum weight of j.
  matrix_t max_value;
    max_value.n_rows = n_obj;
    max_value.n_cols = capacity + 1;
  calloc_matrix(&max_value);

  // first row requires special treatment : the maximum value obtained by taking
  // only the first object is always the utility of the object
  size_t max_w;
  for(max_w = 0; max_w <= capacity; max_w++)
    if(weights[0] <= max_w)
      max_value.t[0][max_w] = utilities[0];

  // fill the table to build the solution step by step, varying the set of
  // objects to be used as well as the maximum capacity to be taken until
  // arriving at the full capacity and all of the objects
  size_t obj;
  for (obj = 1; obj < n_obj; obj++)
    for (max_w = 0; max_w <= capacity; max_w++)
    {
      // if this object fits under the sliding weight limit
      if (weights[obj] <= max_w)
      {
        // maximum utility if this object is NOT part of the solution
        size_t leave = max_value.t[obj-1][max_w];
        // maximum utility if this object IS part of the solution
        size_t take = max_value.t[obj-1][max_w - weights[obj]] + utilities[obj];
        // choose whether or not to take this object
        max_value.t[obj][max_w] = max(leave, take);
      }
      else
        max_value.t[obj][max_w] = max_value.t[obj-1][max_w];
    }

  // store the result (maximum utility) and free the matrix
  size_t result = max_value.t[n_obj -1][capacity];
  free_matrix(&max_value);

  // return the result
  return result;
}

size_t knapsack(knapsack_instance_t i)
{
  return knapsack_aux(i.capacity, i.n_obj, i.weights, i.utilities);
}
