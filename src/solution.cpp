#include "solution.h"

Solution::Solution()
{
    isValid = false;
    distFitness = 0;
    travelTimeFitness = 0;
}

bool Solution::producersCycling()
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