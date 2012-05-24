#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "types.h"

// unit test

int matrix_unit();

// matrix structure
typedef struct
{
  int** t;
  size_t n_rows, n_cols;
}
matrix_t;

// allocate and free
void calloc_matrix(matrix_t* m);
void malloc_matrix(matrix_t* m);
void free_matrix(matrix_t* m);

// print to standard output
void print_matrix(matrix_t* m);

#endif // MATRIX_H_INCLUDED
