#ifndef KNAPSACK_STRESS_H_INCLUDED
#define KNAPSACK_STRESS_H_INCLUDED

#include "types.h"

// timed execution on random instances
void knapsack_stress();

// allocate, solve and free random instance
size_t knapsack_rand(size_t capacity, size_t n_obj);

// calls the above, returns the time taken to solve
long time_knapsack_rand(size_t capacity, size_t n_obj, size_t n_tests);

#endif // KNAPSACK_STRESS_H_INCLUDED
