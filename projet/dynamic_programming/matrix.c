#include <stdlib.h>

#include "matrix.h"

/* UNIT TEST */

#include "assert.h"

#define UNIT_MATRIX_N_ROWS 2
#define UNIT_MATRIX_N_COLS 3


int matrix_unit()
{
  // allocate
  matrix_t m;
    m.n_rows = UNIT_MATRIX_N_ROWS;
    m.n_cols = UNIT_MATRIX_N_COLS;
  malloc_matrix(&m);

  // write
  size_t row, col;
  for(row = 0; row < m.n_rows; row++)
    for(col = 0; col < m.n_cols; col++)
      m.t[row][col] = col + m.n_cols*row;

  // read
  for(row = 0; row < m.n_rows; row++)
    for(col = 0; col < m.n_cols; col++)
      ASSERT(m.t[row][col] == col + m.n_cols*row,
              "matrix read/write test");

  // free
  free_matrix(&m);

  // success
  return EXIT_SUCCESS;
}

/* ALLOCATE AND FREE */

void malloc_matrix(matrix_t* m)
{
  // allocate memory
  m->t = (int**)malloc(sizeof (int*) * m->n_rows);
  m->t[0] = (int*)malloc(sizeof (int) * m->n_rows * m->n_cols);

  // save row-pointers
  size_t i;
  for(i = 1; i < m->n_rows; i++)
    m->t[i] = m->t[i-1] + m->n_cols;
}

void free_matrix(matrix_t* m)
{
  free(m->t[0]);
  free(m->t);
}


// find the index/value of the minimum cell of this row
valued_index_t min_col(matrix_t* m, size_t row)
{
  // local variables
  valued_index_t min;
    min.index = 0;
    min.value = m->t[row][0];
  size_t col;

  // search for the column
  for(col = 0; col < m->n_cols; col++)
  {
    if(m->t[row][col] < min.value)
    {
      min.index = col;
      min.value = m->t[row][col];
    }
  }

  // return the result
  return min;
}

