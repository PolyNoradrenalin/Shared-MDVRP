#ifndef S_MDVRP_INSTANCE_H
#define S_MDVRP_INSTANCE_H

#include <vector>
#include "node.h"
#include "matrix.h"

/**
 * Une instance du problème avec ses producteurs, clients et les distances/temps de trajet les séparant.
 */
class Instance
{
private:
    std::vector<Node> producers;
    std::vector<Node> clients;

    Matrix2D<int> distances;
    Matrix2D<int> travelTimes;
public:

    [[nodiscard]] const std::vector<Node> &getProducers() const;

    [[nodiscard]] const std::vector<Node> &getClients() const;

    [[nodiscard]] std::vector<Node> getNodes() const;

    /**
     * Récupère le type du noeud donné.
     * @param node
     * @return Client ou Producteur selon le type du noeud
     */
    [[nodiscard]] NodeType getNodeType(Node node) const;

    /**
     * Récupère la distance en entre deux noeuds.
     * @param start Départ de l'arc
     * @param dest Fin de l'arc
     * @return Distance entre les deux noeuds
     */
    [[nodiscard]] int getDistance(Node start, Node dest) const;

    /**
     * Récupère le temps de trajet entre deux noeuds.
     * @param start Départ de l'arc
     * @param dest Fin de l'arc
     * @return Temps de trajet entre les deux noeuds
     */
    [[nodiscard]] int getTravelTime(Node start, Node dest) const;
};

#endif //S_MDVRP_INSTANCE_H
