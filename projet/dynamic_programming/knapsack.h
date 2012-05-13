#ifndef KNAPSACK_H_INCLUDED
#define KNAPSACK_H_INCLUDED

#include "types.h" // for size_t

// knapsack instance type
typedef struct
{
  size_t capacity, n_obj, *weights, *utilities;
}
knapsack_instance_t;

// knapsack problem solver
size_t knapsack(knapsack_instance_t inst);

// knapsack solver which takes the unrolled parameter list
size_t knapsack_aux(size_t capacity, size_t n_obj, size_t weights[],
                  size_t utilities[]);

#endif // KNAPSACK_H_INCLUDED
