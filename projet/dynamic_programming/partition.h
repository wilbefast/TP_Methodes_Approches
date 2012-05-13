#ifndef PARTITION_H_INCLUDED
#define PARTITION_H_INCLUDED

#include "types.h"

// knapsack instance type
typedef struct
{
  size_t n_obj, *values;
}
partition_instance_t;

// allocate, solve and free random instance
size_t partition_rand(size_t n_obj, size_t max_value);

// calls the above, returns the time taken to solve
long time_partition_rand(size_t n_obj, size_t max_value, size_t n_tests);

// tests
int partition_unit();
void partition_stress();

// partition problem solver
bool_t partition(partition_instance_t inst);

#endif // PARTITION_H_INCLUDED
