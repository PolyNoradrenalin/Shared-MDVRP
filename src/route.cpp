#include "route.h"

#include <utility>

Route::Route()
{
    this->prodRoute = std::vector<Node>();
    this->clientRoute = std::vector<Node>();
}

Route::Route(std::vector<Node> const &prodRoute, std::vector<Node> const &clientRoute)
{
    this->prodRoute = std::vector<Node>(prodRoute);
    this->clientRoute = std::vector<Node>(clientRoute);
}

Route::Route(const Route &r)
{
    this->prodRoute = std::vector(r.prodRoute);
    this->clientRoute = std::vector(r.clientRoute);
}

inline const std::vector<Node> &Route::getProdRoute() const
{
    return prodRoute;
}

inline const std::vector<Node> &Route::getClientRoute() const
{
    return clientRoute;
}

inline std::vector<Node> Route::getRoute() const
{
    std::vector<Node> route(prodRoute);
    route.insert(route.end(), clientRoute.begin(), clientRoute.end());

    return route;
}
