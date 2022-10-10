#ifndef S_MDVRP_SOLUTION_H
#define S_MDVRP_SOLUTION_H

#include <vector>
#include "route.h"

/**
 * Solution individuelle pour la résolution du MD-VRP.
 */
class Solution
{
public:
    // Détermine si la solution est valide.
    bool isValid;
    // La valeur de fitness correspondant à la distance.
    float distFitness;
    // La valeur de fitness correspondant au temps nécessaire pour parcourir la route.
    float travelTimeFitness;
    // Routes des producteurs.
    std::vector<Route> routes;

    /**
     * Constructeur de l'objet Solution.
     */
    Solution();
};

#endif //S_MDVRP_SOLUTION_H
