#include <stdlib.h>

#include "knapsack_unit.h"
#include "knapsack.h"

#include "assert.h"

#define KNAPS_UNIT1_N_OBJ 7
#define KNAPS_UNIT1_CAPACITY 2
#define KNAPS_UNIT1_WEIGHTS   {3,5,1,5,7,2,6}
#define KNAPS_UNIT1_UTILITIES {2,5,3,3,6,2,4}
#define KNAPS_UNIT1_RIGHT_ANSWER 3 // take item 3

#define KNAPS_UNIT2_N_OBJ 10
#define KNAPS_UNIT2_CAPACITY 5
#define KNAPS_UNIT2_WEIGHTS   {1,2,3,4,5,1,2,3,4,5}
#define KNAPS_UNIT2_UTILITIES {4,3,1,3,6,2,2,4,3,7}
#define KNAPS_UNIT2_RIGHT_ANSWER 10 // take items 1, 6 and 8

#define KNAPS_UNIT3_N_OBJ 5
#define KNAPS_UNIT3_CAPACITY 11
#define KNAPS_UNIT3_WEIGHTS   {1,2,5,6,7}
#define KNAPS_UNIT3_UTILITIES {1,6,18,22,28}
#define KNAPS_UNIT3_RIGHT_ANSWER 40 // take items 3 and 4

#define KNAPS_UNIT4_N_OBJ 2
#define KNAPS_UNIT4_CAPACITY 1
#define KNAPS_UNIT4_WEIGHTS   {1,1}
#define KNAPS_UNIT4_UTILITIES {1,0}
#define KNAPS_UNIT4_RIGHT_ANSWER 1 // take item 1

int knapsack_unit()
{
  // test 1
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT1_N_OBJ] = KNAPS_UNIT1_WEIGHTS;
    size_t utilities[KNAPS_UNIT1_N_OBJ] = KNAPS_UNIT1_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT1_CAPACITY, KNAPS_UNIT1_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT1_RIGHT_ANSWER, "knapsack result check 1");
  }

  // test 2
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT2_N_OBJ] = KNAPS_UNIT2_WEIGHTS;
    size_t utilities[KNAPS_UNIT2_N_OBJ] = KNAPS_UNIT2_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT2_CAPACITY, KNAPS_UNIT2_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT2_RIGHT_ANSWER, "knapsack result check 2");
  }

  // test 3
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT3_N_OBJ] = KNAPS_UNIT3_WEIGHTS;
    size_t utilities[KNAPS_UNIT3_N_OBJ] = KNAPS_UNIT3_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT3_CAPACITY, KNAPS_UNIT3_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT3_RIGHT_ANSWER, "knapsack result check 3");
  }

  // test 4
  {
    // instance sac a dos : on veut maximiser l'utilite
    size_t weights[KNAPS_UNIT4_N_OBJ] = KNAPS_UNIT4_WEIGHTS;
    size_t utilities[KNAPS_UNIT4_N_OBJ] = KNAPS_UNIT4_UTILITIES;
    // solve the problem
    size_t max_utility =
      knapsack_aux(KNAPS_UNIT4_CAPACITY, KNAPS_UNIT4_N_OBJ, weights, utilities);
    // check the result
    ASSERT(max_utility == KNAPS_UNIT4_RIGHT_ANSWER, "knapsack result check 4");
  }

  // unit test result
  return EXIT_SUCCESS;
}
