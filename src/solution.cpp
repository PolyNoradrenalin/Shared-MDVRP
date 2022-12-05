#include "solution.h"

Solution::Solution()
{
    isValid = false;
    distFitness = 0;
    travelTimeFitness = 0;
}

bool Solution::producersCycling()
{
    Graph g = Graph();
    detect_loops dfs;

    for (const Route &route: this->routes)
    {
        const std::vector<Node> &nodes = route.getProdRoute();
        for (int i = 0; i < nodes.size() - 1; i++)
        {
            boost::add_edge(nodes[0].id, nodes[1].id, g);
        }
    }

    boost::depth_first_search(g,dfs, );
    std::cout << dfs.GetCycles().size();

    return false;
}
