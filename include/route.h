#ifndef S_MDVRP_ROUTE_H
#define S_MDVRP_ROUTE_H

#include <vector>
#include "node.h"

/*
 * Route d'un producteur pour livrer ses clients.
 */
class Route
{
public:
    // Route de mutualisation du producteur.
    std::vector<Node> prodRoute;

    // Route du producteur chez les clients.
    std::vector<Node> clientRoute;

    /**
     * Constructeur par défaut.
     */
    Route();

    /**
     * Constructeur avec des routes prédéfini.
     * @param prodRoute Route de mutualisation du producteur.
     * @param clientRoute Route du producteur chez les clients.
     */
    Route(std::vector<Node> const &prodRoute, std::vector<Node> const &clientRoute);

    [[nodiscard]] std::vector<Node> getRoute() const;
};


#endif //S_MDVRP_ROUTE_H
