#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
  printf("knapsack stress test:\n\tcapacity of %d\n\t%d objects\n\t%d tests\n",
        KNAPS_STRESS_CAPACITY, KNAPS_STRESS_N_OBJ, KNAPS_STRESS_N_TESTS);
  double t = time_knapsack_rand(KNAPS_STRESS_CAPACITY, KNAPS_STRESS_N_OBJ,
                                KNAPS_STRESS_N_TESTS);
  printf("\taverage solving time = %es\n", t);
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

double time_knapsack_rand(size_t capacity, size_t n_obj, size_t n_tests)
{
  // time before tests began
  long unsigned int start = time(NULL);

  // launch the required number of tests on random instances
  size_t test;
  for(test = 0; test < n_tests; test++)
    knapsack_rand(capacity, n_obj);

  // return the difference in time between before and after
  long unsigned int end = time(NULL);
  return (end-start)/(double)n_tests;
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

size_t knapsack(knapsack_instance_t i)
{
  return knapsack_aux(i.capacity, i.n_obj, i.weights, i.utilities);
}
