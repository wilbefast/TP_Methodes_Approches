#ifndef KNAPSACK_H_INCLUDED
#define KNAPSACK_H_INCLUDED

#include "types.h" // for size_t

// knapsack instance type
typedef struct
{
  size_t capacity, n_obj, *weights, *utilities;
}
knapsack_instance_t;

// allocate, solve and free random instance
size_t knapsack_rand(size_t capacity, size_t n_obj);

// calls the above, returns the time taken to solve
long time_knapsack_rand(size_t capacity, size_t n_obj, size_t n_tests);

// tests
int knapsack_unit();
void knapsack_stress();

// knapsack problem solver
size_t knapsack(knapsack_instance_t inst);

#endif // KNAPSACK_H_INCLUDED
