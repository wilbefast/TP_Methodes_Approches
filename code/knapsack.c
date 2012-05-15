size_t knapsack(size_t capacity, size_t n_obj, size_t weights[],
                    size_t utilities[])
{
  // max_value.t[i,j] is the maximum value we can achieve with objects 0 to to i
  // while taking a maximum weight of j.
  matrix_t max_value;
    max_value.n_rows = n_obj;
    max_value.n_cols = capacity + 1;
  calloc_matrix(&max_value);

  // first row requires special treatment : the maximum value obtained by taking
  // only the first object is always the utility of the object
  size_t max_w;
  for(max_w = 0; max_w <= capacity; max_w++)
    if(weights[0] <= max_w)
      max_value.t[0][max_w] = utilities[0];

  // fill the table to build the solution step by step, varying the set of
  // objects to be used as well as the maximum capacity to be taken until
  // arriving at the full capacity and all of the objects
  size_t obj;
  for (obj = 1; obj < n_obj; obj++)
    for (max_w = 0; max_w <= capacity; max_w++)
    {
      // if this object fits under the sliding weight limit
      if (weights[obj] <= max_w)
      {
        // maximum utility if this object is NOT part of the solution
        size_t leave = max_value.t[obj-1][max_w];
        // maximum utility if this object IS part of the solution
        size_t take = max_value.t[obj-1][max_w - weights[obj]] + utilities[obj];
        // choose whether or not to take this object
        max_value.t[obj][max_w] = max(leave, take);
      }
      else
        max_value.t[obj][max_w] = max_value.t[obj-1][max_w];
    }

  // store the result (maximum utility) and free the matrix
  size_t result = max_value.t[n_obj -1][capacity];
  free_matrix(&max_value);

  // return the result
  return result;
}
