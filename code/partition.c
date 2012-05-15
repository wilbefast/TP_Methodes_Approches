bool_t partition(size_t n_obj, size_t values[])
{
  // calculate the total of all the values
  size_t obj, total = 0;
  for(obj = 0; obj < n_obj; obj++ )
    total += values[obj];

  // we can't cut an uneven number in two !
  if(total%2)
    return FALSE;

  // can_sum[i] is true if and only if we are able to add our objects together
  // in some configuration and arrive at i. It is important to check whether
  // malloc returns NULL, as depending on the total weight there may simple not
  // be enough memory !
  size_t table_size = (total/2)+1;
  bool_t* can_sum = calloc(table_size, sizeof(bool_t));
  if(!can_sum)
  {
    printf("total of values is %d : can't allocate an array that big!\n",
          total+1);
    return FALSE;
  }
  // it is always possible to sum 0. Duh.
  can_sum[0] = TRUE;

  // NB - value must be a signed integer as the second for loop break when we
  // have value == -1.
  int value;
  for(obj = 0; obj < n_obj; obj++ )
    for(value = table_size-1-values[obj]; value >= 0; value--)
      if(can_sum[value])
        can_sum[value + values[obj]] = TRUE;


  // free the table
  bool_t result = can_sum[table_size-1];
  free(can_sum);

  // la reponse qui nous interesse
  return result;
}
