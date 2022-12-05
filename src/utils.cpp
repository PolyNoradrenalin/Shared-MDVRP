#include "utils.h"

bool isSolutionValid(const Solution &solution)
{
    // TODO: Verify that all clients receive all products from the producers
    return !producersCycling(solution);
}

bool producersCycling(const Solution &solution)
{
    // TODO: Implement cycling detection algorithm
    return false;
}

std::vector<std::pair<Route, std::vector<Node>>> getInvalidRoutesIfAny(const Solution &solution, const Instance &i)
{
    std::vector<std::pair<Route, std::vector<Node>>> returnVal;

    // TODO: Discuss about first creating a delivery matrix to reduce duplicate computations

    // On fait la vérification pour chaque producteur P1
    for (const auto &prodRoute1: solution.routes)
    {
        // Se rappeler des clients que le producteur P1 a directement livré
        std::vector<Node> deliveredList = removeDuplicatesInVector(prodRoute1.clientRoute);

        // Itérer sur chaque producteur P2 qui reçoit les biens du producteur P1
        for (const auto &prodRoute2: prodRoute1.prodRoute)
        {
            // Regarder dans tous les clients qui sont livrés
            for (const auto &client: solution.routes.at(prodRoute2.id).clientRoute)
            {
                // Chercher si le client n'existe pas déjà dans deliveredList
                int id = client.id;
                auto it = std::find_if(deliveredList.begin(), deliveredList.end(),
                                       [id](const Node &obj) { return obj.id == id; });

                // S'il n'existe effectivement pas, on l'ajoute à deliveredList pour indiquer que ce client est desservi
                if (it == deliveredList.end())
                {
                    deliveredList.push_back(client);
                }
            }
        }

        // On regarde si le producteur P1 a bien livré à tous les clients
        if (deliveredList.size() == i.getClients().size())
        {
            // On ajoute une paire <Route, Vector vide> à returnVal
            returnVal.emplace_back(prodRoute1, std::vector<Node>{});
        } else
        {
            // Sinon, on ajoute une paire <Route, Vector contenant les nœuds non visités> à returnVal

            // Rechercher d'abord les livraisons manquantes
            std::vector<Node> missingDeliveries;

            for (const auto &client: i.getClients())
            {
                // Chercher si le client n'existe pas dans deliveredList
                int id = client.id;
                auto it = std::find_if(deliveredList.begin(), deliveredList.end(),
                                       [id](const Node &obj) { return obj.id == id; });

                // S'il n'existe pas on l'ajoute à la liste des livraisons manquantes
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
    // On transforme le vector en std::list car il est beaucoup plus performant pour y effacer des éléments
    // O(n) pour vector et O(1) pour list
    // Source: https://stackoverflow.com/a/11599470
    std::list<Node> dest(vector.begin(), vector.end());

    // Itérer sur chaque élément et le comparer à celui d'après
    for (auto it = dest.begin(); it != dest.end(); ++it)
    {
        // On vérifie qu'il y a bien un élément à l'indice 'n+1'
        if (dest.size() > 1 && std::distance(dest.begin(), it) != dest.size())
        {
            if (it->id == std::next(it)->id)
            {
                // Si l'élément 'n' est identique à l'élément 'n+1', on efface celui à l'indice n et on recule le pointeur d'un indice
                it = dest.erase(it);
                it = std::prev(it);
            }
        }
    }

    return std::vector<Node>{std::begin(dest), std::end(dest)};
}

std::vector<Node> removeDuplicatesInVector(std::vector<Node> vector)
{
    // On effectue un tri par ordre croissant selon les ids de chaque Node
    std::sort(vector.begin(), vector.end());
    // On efface les doublons
    vector.erase(std::unique(vector.begin(), vector.end()), vector.end());
    return vector;
}

int randomIntInInterval(int a, int b, const std::function<double(void)> &rnd01)
{
    if (a > b)
    {
        std::cerr
                << "The upper boundary in the random int interval cannot be lower than the lower boundary. Boundary given: ["
                << a << "; " << b << "]." << std::endl;
        throw std::exception();
    }
    double r = rnd01();
    if (r == 1)
        return b;
    return int(r * (b - a + 1)) + a;
}