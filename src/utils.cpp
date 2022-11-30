#include "utils.h"

bool isSolutionValid(Solution &solution)
{
    // TODO: Verify that all clients receive all products from the producers
    return !producersCycling(solution);
}

bool producersCycling(Solution &solution)
{
    // TODO: Implement cycling detection algorithm
    return false;
}

std::vector<std::pair<Route, std::vector<Node>>> getInvalidRoutesIfAny(const Solution &solution, const Instance &i)
{
    std::vector<std::pair<Route, std::vector<Node>>> returnVal;

    // TODO: Discuss about first creating a delivery matrix to reduce duplicate computations

    for (const auto &prodRoute1: solution.routes)
    {
        // Se rappeler des clients que le producteur A a directement livrés
        std::vector<Node> deliveredList = removeDuplicatesInVector(prodRoute1.clientRoute);

        // Itérer sur chaque producteur B qui reçoit les biens du producteur A
        for (const auto &prodRoute2: prodRoute1.prodRoute)
        {
            // Regarder dans tous les clients qui sont livrés
            for (const auto &client: solution.routes.at(prodRoute2.id).clientRoute)
            {
                // Chercher si le client n'existe pas déjà dans deliveredList
                auto id = client.id;
                auto it = std::find_if(deliveredList.begin(), deliveredList.end(),
                                           [id](const Node &obj) { return obj.id == id; });

                // S'il n'existe effectivement pas, on l'ajoute à deliveredList
                if (it == deliveredList.end())
                {
                    deliveredList.push_back(client);
                }
            }
        }

        // On regarde si le producteur 1 a bien livré à tous les clients
        if (deliveredList.size() == i.getClients().size())
        {
            // On ajoute une paire <Route, Vector vide> à returnVal
            returnVal.emplace_back(prodRoute1, std::vector<Node>{});
        }
            // Sinon, on ajoute une paire <Route, Vector contenant les nœuds non visités> à returnVal
        else
        {
            // Rechercher d'abord les livraisons manquantes
            std::vector<Node> missingDeliveries;

            for (const auto &client: i.getClients())
            {
                // Chercher si le client n'existe pas dans deliveredList
                auto id = client.id;
                auto it = std::find_if(deliveredList.begin(), deliveredList.end(),
                                           [id](const Node &obj) { return obj.id == id; });

                // S'il n'existe pas on l'ajoute à deliveredList
                if (it == deliveredList.end())
                {
                    missingDeliveries.push_back(client);
                }
            }

            returnVal.emplace_back(prodRoute1, missingDeliveries);
        }

    }

    return returnVal;
}

std::discrete_distribution<> getRandomIntDistribution(int minVal, int maxVal, const std::vector<int> &excludedVals)
{
    std::vector<int> distVals(abs(maxVal - minVal));
    std::fill(distVals.begin(), distVals.end(), 1);

    for (int i: excludedVals)
    {
        if (i < distVals.size())
        {
            distVals[i] = 0;
        }
    }

    std::discrete_distribution<> distribution(distVals.begin(), distVals.end());

    return distribution;
}

std::vector<Node> removeSideBySideDuplicatesInVector(const std::vector<Node> &vector)
{
    std::list<Node> dest(vector.begin(), vector.end());

    for (auto it = dest.begin(); it != std::prev(dest.end()); ++it)
    {
        if (dest.size() > 1 && std::distance(dest.begin(), it) != dest.size())
        {
            if (it->id == std::next(it)->id)
            {
                it = dest.erase(it);
                it = std::prev(it);

            }
        }
    }

    return std::vector<Node>{std::begin(dest), std::end(dest)};
}

std::vector<Node> removeDuplicatesInVector(std::vector<Node> vector)
{
    std::sort(vector.begin(), vector.end());
    vector.erase(std::unique(vector.begin(), vector.end()), vector.end());
    return vector;
}
