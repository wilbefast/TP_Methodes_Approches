#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "salesman_stress.hpp"
#include "salesman.hpp"

/* PRIVATE FUNCTIONS */

// create and destruction of salesman problem instances
void create_salesman_i(salesman_instance_t* inst, matrix_t* m, uint n_nodes);
void destroy_salesman_i(salesman_instance_t* inst);

/* STRESS TESTS */

#define TSP_STRESS_MAX_DISTANCE 1000
#define TSP_STRESS_N_NODES 11 // with 11 takes about 1 second o_O
#define TSP_STRESS_N_TESTS 5

void salesman_stress()
{
  printf("salesman stress test:\n\t%d nodes (cities)\n\t%d tests\n",
          TSP_STRESS_N_NODES, TSP_STRESS_N_TESTS);
  long t = time_salesman_rand(TSP_STRESS_N_NODES, TSP_STRESS_N_TESTS);
  printf("\taverage solving time = %ldms\n", t);
}


/* RANDOM GENERATOR */

uint salesman_rand(uint n_nodes)
{
  // create a random salesman problem instance
  salesman_instance_t inst;
  matrix_t dist_matrix;
  create_salesman_i(&inst, &dist_matrix, n_nodes);

  // solve and destroy instance
  size_t result = salesman(&inst);
  destroy_salesman_i(&inst);

  // return result
  return result;
}

long time_salesman_rand(uint n_nodes, uint n_tests)
{
  // time before tests began
  struct timeval start;
  gettimeofday(&start, NULL);

  // launch the required number of tests on random instances
  size_t test;
  for(test = 0; test < n_tests; test++)
    salesman_rand(n_nodes);

  // return the difference in time between before and after
  struct timeval end;
  gettimeofday(&end, NULL);
  long time_s  = end.tv_sec  - start.tv_sec;
  long time_ms = end.tv_usec - start.tv_usec;
  long time_total = ((time_s) * 1000 + time_ms/1000.0) + 0.5;
  return time_total/n_tests;
}

void create_salesman_i(salesman_instance_t* inst, matrix_t* m, uint _n_nodes)
{
  // initialise parameters
  inst->n_nodes = _n_nodes;

  // allocate matrix
  inst->distances = m;
    m->n_cols = m->n_rows = _n_nodes;
    calloc_matrix(m);

  // randomise value : remember, the matrix must be symetric !

  //   .------------------.
  //   |      0           |
  //   |       0          |
  //   | random 0 reflect |
  //   |         0        |
  //   |          0       |
  //   '------------------'
  //

  // we're iterating the wrong way around here so that we can deal with the
  // random elements first
  for(uint col = 0; col < _n_nodes; col++)
    for(uint row = 0; row < _n_nodes; row++)
    {

      if(col < row)
        m->t[row][col] = rand()%TSP_STRESS_MAX_DISTANCE;
        // random

      else if (col == row)
        // distance from a node to itself is 0
        m->t[row][col] = 0;

      else
        // reflect
        m->t[row][col] = m->t[col][row];
    }
}

void destroy_salesman_i(salesman_instance_t* inst)
{
  free_matrix(inst->distances);
}
