#include "solution.h"

Solution::Solution()
{
    isValid = false;
    instance = nullptr;
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

bool Solution::evalSolution(MiddleCost &c) const
{
    // On vérifie la validité de la solution
    if (!isValid)
    {
        return false;
    }

    // Si la solution est valide, on calcule les coûts moyens
    c.distanceCost = 0;

    for (const auto &route: routes)
    {
        std::vector<Node> fullRoute = route.getRoute();
        for (auto it = fullRoute.begin(); it != std::prev(fullRoute.end()); ++it)
        {
            if (std::next(it) != fullRoute.end())
            {
                c.distanceCost += instance->getDistance(*it, *std::next(it));
            }
        }
    }

    return true;
}

void Solution::cleanSolution()
{
    for (auto &r: routes) {
        r.cleanRoute();
    }
}
