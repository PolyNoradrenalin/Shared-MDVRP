#ifndef S_MDVRP_SOLUTION_H
#define S_MDVRP_SOLUTION_H
#include <vector>
#include "route.h"
#include "instance.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/tiernan_all_cycles.hpp>
#include <iostream>
#include <stack>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::property<boost::vertex_index_t, int>>;

namespace boost { [[maybe_unused]] void renumber_vertex_indices(Graph const&); }

class Visitor {
private:
    std::vector<std::set<int>>& cycles;

public:
    explicit Visitor(std::vector<std::set<int>> &cycles);

    [[maybe_unused]] void cycle(auto const& path, Graph const& g);
};


/**
 * Solution individuelle pour la résolution du MD-VRP.
 */
class Solution
{
public:
    // Détermine si la solution est valide.
    bool isValid = false;
    // La valeur de fitness correspondant à la distance.
    double distFitness = 0;
    // La valeur de fitness correspondant au temps nécessaire pour parcourir la route.
    double travelTimeFitness = 0;
    // Routes des producteurs.
    std::vector<Route> routes;

    /**
     * Constructeur de l'objet Solution.
     */
    Solution();

    /**
     * Vérifie s'il y a un cycle dans les tournées de producteurs.
     * @param p Solution à vérifier
     * @return<b>true</b> s'il y a un cycle (interlocking), <b>false</b>sinon
     */
    bool producersCycling();
};

#endif //S_MDVRP_SOLUTION_H
