#ifndef SALESMAN_H_INCLUDED
#define SALESMAN_H_INCLUDED

#include "matrix.h"

// knapsack problem instance type
typedef struct
{
  matrix_t* distances;
  uint n_nodes;
}
salesman_instance_t;


// travelling salesman problem solver
uint salesman(salesman_instance_t* i);
uint salesman_aux(matrix_t* distances, uint n_nodes);

#endif // SALESMAN_H_INCLUDED
