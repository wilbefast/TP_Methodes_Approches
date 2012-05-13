#ifndef PARTITION_STRESS_H_INCLUDED
#define PARTITION_STRESS_H_INCLUDED

#include "types.h"

// timed execution on random instances
void partition_stress();

// allocate, solve and free random instance
size_t partition_rand(size_t n_obj, size_t max_value);

// calls the above, returns the time taken to solve
long time_partition_rand(size_t n_obj, size_t max_value, size_t n_tests);


#endif // PARTITION_STRESS_H_INCLUDED
