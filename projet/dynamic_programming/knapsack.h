#ifndef KNAPSACK_H_INCLUDED
#define KNAPSACK_H_INCLUDED

#include "types.h" // for bool_t, size_t

bool_t knapsack_unit();

size_t knapsack(size_t capacity, size_t n_obj, size_t weights[], size_t utilities[]);

#endif // KNAPSACK_H_INCLUDED
