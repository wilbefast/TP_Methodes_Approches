#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#define size_t unsigned int

// cell structure : a line-column pair
typedef struct
{
  size_t line, col;
}
cell_t;

// valued index : an index-value pair
typedef struct
{
  int value;
  size_t index;
}
valued_index_t;

// matrix structure
typedef struct
{
  int** t;
  size_t n_rows, n_cols;
}
matrix_t;

// allocate and free
void malloc_matrix(matrix_t* m);
void free_matrix(matrix_t* m);

// query
valued_index_t min_col(matrix_t* m, size_t line);

#endif // MATRIX_H_INCLUDED
