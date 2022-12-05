#include "route.h"

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

std::vector<Node> Route::getRoute() const
{
    std::vector<Node> route(prodRoute);
    route.insert(route.end(), clientRoute.begin(), clientRoute.end());

    return route;
}
