#ifndef SALESMAN_STRESS_HPP_INCLUDED
#define SALESMAN_STRESS_HPP_INCLUDED

#include "types.h"

// timed execution on random instances
void salesman_stress();

// allocate, solve and free random instance
uint salesman_rand(uint n_nodes);

// calls the above, returns the time taken to solve
long time_salesman_rand(uint n_nodes, uint n_tests);


#endif // SALESMAN_STRESS_HPP_INCLUDED
