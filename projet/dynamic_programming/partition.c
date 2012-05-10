#include <stdlib.h>
#include <string.h>

#include "math.h"
#include "partition.h"

#define PART_N_OBJ 7
#define PART_WEIGHTS {5,5}

bool_t partition_unit()
{
  // instance partition : on veut savoir si on peut partager en deux
  size_t weights[PART_N_OBJ] = PART_WEIGHTS;
  partition(PART_N_OBJ, weights);

  // unit test result
  return TRUE;
}

size_t partition(size_t n_obj, size_t weights[])
{
  size_t line, col;

  // calcul de la somme totale des poids
  size_t total_weight = 0;
  for(line = 0; line < n_obj; line++ )
    total_weight += weights[line];

  // initialisation de la table de booleens
  bool_t* tab = (bool_t*) malloc(sizeof(bool_t) * total_weight);
  tab[0] = TRUE;
  memset(tab+1, 0, total_weight-1);

  // remplissage de la table selon les formules de la prog dyn
  for(line = 0; line < n_obj; line++ )
    for(col = total_weight - weights[line]; col >= 0; col--)
      if(tab[col])
        tab[col + weights[line]] = TRUE;


  // free the table
  bool_t result = tab[total_weight / 2];
  free(tab);

  // la reponse qui nous interesse
  return result;
}
