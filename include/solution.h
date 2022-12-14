#ifndef S_MDVRP_SOLUTION_H
#define S_MDVRP_SOLUTION_H

#include <vector>
#include "route.h"
#include "instance.h"
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
#include <stack>

struct MiddleCost
{
    double distanceCost;
};

typedef boost::adjacency_matrix<boost::directedS> Graph;
typedef std::exception cycle_exception;

class dfs_visitor : public boost::default_dfs_visitor
{
public:
    dfs_visitor() = default;

    template<typename Vertex, typename Graph>
    [[maybe_unused]] void back_edge(Vertex u, const Graph &g) const
    {
        throw cycle_exception();
    }
};


/**
 * Solution individuelle pour la résolution du MD-VRP.
 */
class Solution
{
public:
    // Détermine si la solution est valide.
    bool isValid = false;
    // Routes des producteurs.
    std::vector<Route> routes;
    // Instance de la solution.
    const Instance* instance;

    /**
     * Constructeur de l'objet Solution.
     */
    Solution();

    /**
     * Vérifie s'il y a un cycle dans les tournées de producteurs.
     * @param p Solution à vérifier
     * @return<b>true</b> s'il y a un cycle (interlocking), <b>false</b>sinon
     */
    bool producersCycling() const;

    /**
     * Évalue la solution.
     * @param c Fitness de la solution
     * @return <b>true</b> si la solution est valide, <b>false</b> sinon
     */
    bool evalSolution(MiddleCost &c) const;

    /**
     * Enlève les destinations doublons dans chaque route de la solution.
     */
    void cleanSolution();
};

#endif //S_MDVRP_SOLUTION_H
