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

    std::vector<std::set<int>> original_routes{};
    std::vector<std::set<int>> cycles;
    auto vis = Visitor(cycles);

    for (const auto& route : this->routes)
    {
        const std::vector<Node> &nodes = route.getProdRoute();
        const size_t route_nb_nodes = nodes.size();

        std::set<int> cycle{};

        for (int j = 0; j < route_nb_nodes; j++)
        {
            boost::add_edge(nodes[j].id, nodes[(j + 1) % route_nb_nodes].id, g);
            cycle.insert(nodes[j].id);
        }

        original_routes.push_back(cycle);
    }

    boost::tiernan_all_cycles(g, vis);

    for(const auto& c : original_routes)
    {
        std::erase(cycles, c);
    }

    return !cycles.empty();
}

[[maybe_unused]] void boost::renumber_vertex_indices(const Graph &)
{}

void Visitor::cycle(const auto &path, const Graph &g)
{
    auto indices = get(boost::vertex_index, g);
    std::set<int> c;

    for (auto v: path)
        c.emplace(get(indices, v));

    cycles.emplace_back(c);
}

Visitor::Visitor(std::vector<std::set<int>> &cycles) : cycles(cycles)
{
    cycles = std::vector<std::set<int>>();
}
