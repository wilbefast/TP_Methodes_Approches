#ifndef SALESMAN_H_INCLUDED
#define SALESMAN_H_INCLUDED

#include "matrix.h"
#include "types.h"

bool_t salesman_unit();
int salesman(matrix_t* weights, size_t n_obj);

#endif // SALESMAN_H_INCLUDED
