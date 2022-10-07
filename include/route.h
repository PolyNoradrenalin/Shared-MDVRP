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
    std::vector<Node> prodRoute;
    std::vector<Node> clientRoute;
};

#endif //S_MDVRP_ROUTE_H
