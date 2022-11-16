#ifndef S_MDVRP_UTILS_H
#define S_MDVRP_UTILS_H

#include "solution.h"

/**
 * Checks if the solution is valid/feasible.
 * @param p Solution to check
 * @return <b>true</b> if valid, <b>false</b>otherwise/
 */
static bool isSolutionValid(Solution &p);
/**
 * Checks if the producers are producing a cycle which means they are interlocking themselves.
 * @param p Solution to check
 * @return<b>true</b> if they are cycling (interlocking), <b>false</b>otherwise/
 */
static bool producersCycling(Solution &p);

#endif //S_MDVRP_UTILS_H
