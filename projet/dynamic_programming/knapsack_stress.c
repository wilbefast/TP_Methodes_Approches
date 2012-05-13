#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "knapsack_stress.h"
#include "knapsack.h"

#define KNAPS_STRESS_CAPACITY 5000
#define KNAPS_STRESS_N_OBJ 500
#define KNAPS_STRESS_N_TESTS 100

/* PRIVATE FUNCTIONS */

// create and destruction of knapsack problem instances
void create_knapsack_i(knapsack_instance_t* inst, size_t _capacity,
                      size_t _n_obj);
void destroy_knapsack_i(knapsack_instance_t* inst);

/* STRESS TESTS */

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
  inst->weights = (unsigned int*)malloc(sizeof(size_t) * _n_obj);
  inst->utilities = (unsigned int*)malloc(sizeof(size_t) * _n_obj);

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
