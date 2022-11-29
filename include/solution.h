#ifndef S_MDVRP_SOLUTION_H
#define S_MDVRP_SOLUTION_H

#include <vector>
#include "route.h"
#include "instance.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
#include <stack>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

struct detect_loops : public boost::dfs_visitor<>
{
    using colormap = std::map<Graph::vertex_descriptor, boost::default_color_type>;
    colormap vertex_coloring;

    using edgeColorMap = std::map<Graph::edge_descriptor, boost::default_color_type>;
    edgeColorMap  edge_coloring;

    template <class Graph>
    void tree_edge(Edge e, const Graph& g) {
        std::cout << "tree_edge: " << boost::source(e, g) << " --> " << boost::target(e, g) << std::endl;

        edgeVisited.push(e);
        if (vertexVisited.empty()) {
            vertexVisited.push(boost::source(e, g));
        }
        vertexVisited.push(boost::target(e, g));
    }

    template <class Graph>
    void back_edge(Edge e, const Graph& g) {
        Vertex v2;

        std::cout << " Cycle detected with back-edge= " << e << std::endl;
        std::cout << " vertexVisited size= " << vertexVisited.size() << std::endl;

        std::cout << "Cycle end= " << boost::target(e, g) << std::endl;
        //std::cout << "vertexVisited.top= " << vertexVisited.top() << std::endl;
        while ( vertexVisited.top() != boost::target(e, g) )
        {
            std::cout << " Cycle middle=" << vertexVisited.top() << std::endl;
            v2 = vertexVisited.top();
            vertexVisited.pop();
        }
        std::cout << "Cycle starting= " << vertexVisited.top() << std::endl;
        vertexVisited.push(v2);
    }

    //interface to the main.
    std::vector<Vertex> GetCycles() const { return Cycle; }

private:
    std::vector<Vertex> Cycle;

    //std::stack<Edge> visited;
    std::stack<Edge> edgeVisited;
    std::stack<Vertex> vertexVisited;
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
