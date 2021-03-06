#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "types.h"

// unit test

int matrix_unit();

// cell structure : a row-column pair
typedef struct
{
  uint row, col;
}
cell_t;

// valued index : an index-value pair
typedef struct
{
  int value;
  uint index;
}
valued_index_t;

// matrix structure
typedef struct
{
  int** t;
  uint n_rows, n_cols;
}
matrix_t;

// allocate and free
void calloc_matrix(matrix_t* m);
void malloc_matrix(matrix_t* m);
void free_matrix(matrix_t* m);

// print to standard output
void print_matrix(matrix_t* m);

// query
valued_index_t min_col(matrix_t* m, uint row);

#endif // MATRIX_H_INCLUDED
