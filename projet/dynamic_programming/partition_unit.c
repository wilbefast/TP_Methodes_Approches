#include <stdlib.h>

#include "partition_unit.h"
#include "partition.h"

#include "assert.h"

#define PART_UNIT1_N_OBJ 4
#define PART_UNIT1_WEIGHTS {2,6,2,2}
#define PART_UNIT1_RIGHT_ANSWER TRUE

#define PART_UNIT2_N_OBJ 3
#define PART_UNIT2_WEIGHTS {1,4,3}
#define PART_UNIT2_RIGHT_ANSWER TRUE

#define PART_UNIT3_N_OBJ 3
#define PART_UNIT3_WEIGHTS {1,2,7}
#define PART_UNIT3_RIGHT_ANSWER FALSE

#define PART_UNIT4_N_OBJ 4
#define PART_UNIT4_WEIGHTS {14,5,2,6}
#define PART_UNIT4_RIGHT_ANSWER FALSE

int partition_unit()
{
  // test 1
  {
    size_t values[PART_UNIT1_N_OBJ] = PART_UNIT1_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT1_N_OBJ, values);
    ASSERT(result == PART_UNIT1_RIGHT_ANSWER, "partition result check 1");
  }

  // test 2
  {
    size_t values[PART_UNIT2_N_OBJ] = PART_UNIT2_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT2_N_OBJ, values);
    ASSERT(result == PART_UNIT2_RIGHT_ANSWER, "partition result check 2");
  }

  // test 3
  {
    size_t values[PART_UNIT3_N_OBJ] = PART_UNIT3_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT3_N_OBJ, values);
    ASSERT(result == PART_UNIT3_RIGHT_ANSWER, "partition result check 3");
  }

  // test 4
  {
    size_t values[PART_UNIT4_N_OBJ] = PART_UNIT4_WEIGHTS;
    bool_t result = partition_aux(PART_UNIT4_N_OBJ, values);
    ASSERT(result == PART_UNIT4_RIGHT_ANSWER, "partition result check 4");
  }

  // all tests were successful
  return EXIT_SUCCESS;
}
