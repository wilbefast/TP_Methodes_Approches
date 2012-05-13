#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "math.h"
#include "partition.h"

/* PARTITION PROBLEM SOLVER */

bool_t partition_aux(size_t n_obj, size_t values[])
{
  // calcul de la somme totale des poids
  size_t obj, total_weight = 0;
  for(obj = 0; obj < n_obj; obj++ )
    total_weight += values[obj];

  // can't partition an uneven number in two !
  if(total_weight%2)
    return FALSE;

  // initialisation du tableau de booleens
  bool_t* can_sum = calloc(total_weight+1, sizeof(bool_t));
  if(!can_sum)
  {
    printf("total weight is %d : can't allocate array that big!\n",
          total_weight+1);
    return FALSE;
  }

  can_sum[0] = TRUE;

  // remplissage de la table selon les formules de la programmation dynamique
  int weight;
  for(obj = 0; obj < n_obj; obj++ )
    for(weight = total_weight-values[obj]; weight >= 0; weight--)
      if(can_sum[weight])
        can_sum[weight + values[obj]] = TRUE;


  // free the table
  bool_t result = can_sum[total_weight / 2];
  free(can_sum);

  // la reponse qui nous interesse
  return result;
}

bool_t partition(partition_instance_t inst)
{
  return partition_aux(inst.n_obj, inst.values);
}
