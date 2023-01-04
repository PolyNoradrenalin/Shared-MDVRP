#include "solution.h"

Solution::Solution()
{
    isValid = false;
    distFitness = 0;
    travelTimeFitness = 0;
}

/**
 * Utilise l'algorithme DFS (Depth First Search) sur le graphe d'attente de la solution. Si un cycle est détecté, cela
 * implique un interblocage et donc une invalidité de la solution.
 * @return Vrai si la solution a un cycle, non sinon
 */
bool Solution::producersCycling() const
{
    unsigned long long nbRoutes = this->routes.size();

    Graph g = Graph(nbRoutes);

    auto vis = dfs_visitor();
    bool cycleFound = false;

    for (int i = 0; i < nbRoutes; i++)
    {
        const Route& route = this->routes[i];
        for (const Node& node : route.prodRoute)
        {
            boost::add_edge(i, node.id, g);
        }
    }
    try
    {
        boost::depth_first_search(g, boost::visitor(vis));
    } catch (cycle_exception& e)
    {
        cycleFound = true;
    }

    return cycleFound;
}