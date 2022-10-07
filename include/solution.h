#ifndef S_MDVRP_SOLUTION_H
#define S_MDVRP_SOLUTION_H

#include <vector>
#include "route.h"

/**
 * Solution individuelle pour la résolution du VRP.
 */
class Solution
{
public:
    bool isValid;
    float distFitness;
    float travelTimeFitness;
    std::vector<Route> routes;

    Solution();
};

#endif //S_MDVRP_SOLUTION_H
