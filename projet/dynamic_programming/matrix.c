#include <stdlib.h>

#include "matrix.h"

/* ALLOCATE AND FREE */

void malloc_matrix(matrix_t* m)
{
  // allocate memory
  m->t = (int**)malloc(sizeof (*(m->t)) * m->n_rows);
  m->t[0] = (int*)malloc(sizeof (*(m->t[0])) * m->n_rows * m->n_cols);

  // save line-pointers
  size_t i;
  for(i = 1; i < m->n_rows; i++)
    m->t[i] = m->t[i-1] + m->n_rows;
}

void free_matrix(matrix_t* m)
{
  free(m->t[0]);
  free(m->t);
}


// find the index/value of the minimum cell of this line
valued_index_t min_col(matrix_t* m, size_t line)
{
  // local variables
  valued_index_t min;
    min.index = 0;
    min.value = m->t[line][0];
  size_t col;

  // search for the column
  for(col = 0; col < m->n_cols; col++)
  {
    if(m->t[line][col] < min.value)
    {
      min.index = col;
      min.value = m->t[line][col];
    }
  }

  // return the result
  return min;
}

