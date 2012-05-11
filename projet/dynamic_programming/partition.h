#ifndef PARTITION_H_INCLUDED
#define PARTITION_H_INCLUDED

#include "types.h"

int partition_unit();
bool_t partition(size_t n_obj, size_t weights[]);

#endif // PARTITION_H_INCLUDED
