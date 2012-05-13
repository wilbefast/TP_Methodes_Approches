#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "partition_stress.h"
#include "partition.h"

/* PRIVATE FUNCTIONS */

// create and destruction of partition problem instances
void create_partition_i(partition_instance_t* inst, size_t _n_obj,
                        size_t max_value);
void destroy_partition_i(partition_instance_t* inst);

/* STRESS TEST */

#define PART_STRESS_N_OBJ 500
#define PART_STRESS_N_TESTS 100
#define PART_STRESS_MAX_VALUE 50

void partition_stress()
{
  printf("partition stress test:\n\t%d objects\n\tmax value = %d\n\t%d tests\n",
        PART_STRESS_N_OBJ, PART_STRESS_MAX_VALUE, PART_STRESS_N_TESTS);
  long t = time_partition_rand(PART_STRESS_N_OBJ, PART_STRESS_MAX_VALUE,
                                PART_STRESS_N_TESTS);
  printf("\taverage solving time = %ldms\n", t);
}

/* RANDOM GENERATOR */

size_t partition_rand(size_t n_obj, size_t max_value)
{
  // create a random partition problem instance
  partition_instance_t inst;
  create_partition_i(&inst, n_obj, max_value);

  // solve and destroy instance
  size_t result = partition(inst);
  destroy_partition_i(&inst);

  // return result
  return result;
}

long time_partition_rand(size_t n_obj, size_t max_value, size_t n_tests)
{
  // time before tests began
  struct timeval start;
  gettimeofday(&start, NULL);

  // launch the required number of tests on random instances
  size_t test;
  for(test = 0; test < n_tests; test++)
    partition_rand(n_obj, max_value);

  // return the difference in time between before and after
  struct timeval end;
  gettimeofday(&end, NULL);
  long time_s  = end.tv_sec  - start.tv_sec;
  long time_ms = end.tv_usec - start.tv_usec;
  long time_total = ((time_s) * 1000 + time_ms/1000.0) + 0.5;
  return time_total/n_tests;
}

void create_partition_i(partition_instance_t* inst, size_t _n_obj,
                      size_t max_value)
{
  // initialise parameters
  inst->n_obj = _n_obj;
  inst->values = (size_t*)malloc(sizeof(size_t) * _n_obj);

  // randomise values and utilities
  size_t obj;
  for(obj = 0; obj < _n_obj; obj++)
    inst->values[obj] = rand() % max_value;
}

void destroy_partition_i(partition_instance_t* inst)
{
  free(inst->values);
}
