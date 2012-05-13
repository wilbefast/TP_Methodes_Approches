#ifndef PARTITION_H_INCLUDED
#define PARTITION_H_INCLUDED

#include "types.h"

// knapsack instance type
typedef struct
{
  size_t n_obj, *values;
}
partition_instance_t;

// partition problem solver
bool_t partition(partition_instance_t inst);

// partition solver which takes the unrolled parameter list
bool_t partition_aux(size_t n_obj, size_t values[]);

#endif // PARTITION_H_INCLUDED
