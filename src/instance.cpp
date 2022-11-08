#include "instance.h"

#include <utility>

const std::vector<Node> &Instance::getProducers() const
{
    return producers;
}

const std::vector<Node> &Instance::getClients() const
{
    return clients;
}

std::vector<Node> Instance::getNodes() const
{
    std::vector<Node> nodes(producers);
    nodes.insert(nodes.end(), clients.begin(), clients.end());
    return nodes;
}

int Instance::getDistance(Node start, Node dest) const
{
    return distances[start.id][dest.id];
}

int Instance::getTravelTime(Node start, Node dest) const
{
    return travelTimes[start.id][dest.id];
}

Instance::Instance(std::vector<Node> producers, std::vector<Node> clients, Matrix2D<int> distances,
                   Matrix2D<int> travelTimes)
{
    this->producers = std::move(producers);
    this->clients = std::move(clients);
    this->distances = std::move(distances);
    this->travelTimes = std::move(travelTimes);
}
