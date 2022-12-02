#include "gasolver.h"

#include <utility>

void GASolver::initGenes(Solution &p, const std::function<double(void)> &rnd01)
{
    // Création des générateurs de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> producerDistribution(0, (int) instance.getProducers().size());
    std::uniform_int_distribution<> clientDistribution(0, (int) instance.getClients().size());

    std::cout << "Number of Producers: " << instance.getProducers().size() << std::endl;
    std::cout << "Number of Clients: " << instance.getClients().size() << std::endl;

    // Ensemble de routes vides à initialiser
    std::vector<Route> routes;

    // Générer la route de livraison aux autres producteurs et clients pour chaque producteur
    for (int prodId = 0; prodId < instance.getProducers().size(); prodId++)
    {
        // Route de livraison aux producteurs
        std::vector<Node> prodRoute;

        // Taille de la route des producteurs
        int prodRouteLength = producerDistribution(gen);

        std::cout << "Generating producer route with " << prodRouteLength << " producers for producer " << prodId << "..." << std::endl;

        std::vector<int> excludedVals{prodId};

        // Créer la distribution aléatoire permettant de faire le tirage d'un producteur
        auto distrib = getRandomIntDistribution(0, (int) instance.getProducers().size(), excludedVals);

        // Générer la route du producteur
        for (int j = 0; j < prodRouteLength; j++)
        {
            // Ajoute le nœud à la route du producteur
            prodRoute.push_back(instance.getProducers().at(distrib(gen)));
        }

        // Enlever les doublons côte à côte de la liste (un trajet d'un point A au même point A est considéré comme instantané)
        prodRoute = removeSideBySideDuplicatesInVector(prodRoute);

        // Route de livraison aux clients
        std::vector<Node> clientRoute;

        // Taille de la route de livraison aux clients
        int clientRouteLength = clientDistribution(gen);

        std::cout << "Generating client route with " << clientRouteLength << " clients for producer " << prodId << "..." << std::endl;

        distrib = getRandomIntDistribution(0, (int) instance.getClients().size(), std::vector<int>{});

        // Générer la route de livraison aux clients du producteur
        for (int j = 0; j < clientRouteLength; j++)
        {
            // Ajoute le nœud à la route de livraison aux clients
            clientRoute.push_back(instance.getClients().at(distrib(gen)));
        }

        // Enlever les doublons côte à côte de la liste (un trajet d'un point A au même point A est considéré comme instantané)
        clientRoute = removeSideBySideDuplicatesInVector(clientRoute);

        routes.emplace_back(prodRoute, clientRoute);
    }

    // On ajoute la route à la solution p
    p.routes = routes;

    // On rajoute des clients pour que la solution devienne valide
    std::vector<Route> fixedRoutes;
    // Cette variable permet de déterminer pour chaque producteur, quels clients n'ont pas été livrés
    auto missingClientsPerProducer = getInvalidRoutesIfAny(p, instance);
    int routeIndex = 0;

    // On itère sur chaque paire <route, liste des clients non-livrés> pour les ajouter à la route
    for (const auto &clientPair : missingClientsPerProducer)
    {
        if (routes.size() < routeIndex)
        {
            std::cerr << "An error has occurred during the reparation of initialized solution." << std::endl;
            throw std::exception();
        }
        std::vector<Node> clientsRoute = p.routes[routeIndex].clientRoute;

        if (clientPair.second.empty())
        {
            continue;
        }

        for (auto missingClient : clientPair.second)
        {
            clientsRoute.push_back(missingClient);
        }

        fixedRoutes.emplace_back(clientPair.first.prodRoute, clientsRoute);

        routeIndex++;
    }

    // On ajoute la route réparée à la solution p
    p.routes = fixedRoutes;

    std::cout << "DONE GENERATING SOLUTION, FINAL RESULT: " << std::endl;

    // Print to console
    int count = 0;
    for (const auto& prod: p.routes)
    {
        std::cout << "Producers: " << count << "->";
        for (Node n: prod.prodRoute)
        {
            std::cout << n.id << "->";
        }
        std::cout << count << std::endl;

        std::cout << "Clients: " << count << "->";
        for (Node n: prod.clientRoute)
        {
            std::cout << n.id << "->";
        }
        std::cout << count << std::endl;

        count++;
    }
}

bool GASolver::evalSolution(const Solution &p, MiddleCost &c)
{
    // TODO: Implement
    return false;
}

Solution GASolver::mutate(const Solution &X_base, const std::function<double(void)> &rnd01, double shrink_scale)
{
    // TODO: Implement
    return {};
}

Solution GASolver::crossover(const Solution &X1, const Solution &X2, const std::function<double(void)> &rnd01)
{
    // TODO: Implement
    return {};
}

std::vector<double> GASolver::calculateMOObjectives(const EA::Genetic<Solution, MiddleCost>::thisChromosomeType &X)
{
    // TODO: Implement
    return {};
}

void GASolver::MOReportGeneration(int generation_number, const GenerationType &last_generation,
                                  const std::vector<unsigned int> &pareto_front)
{
    // TODO: Implement
}

GAType &GASolver::solveProblem(Instance inst)
{
    instance = std::move(inst);
    EA::Chronometer timer;
    timer.tic();

    auto *gaObj = new GAType();
    /**
    gaObj->problem_mode = EA::GA_MODE::NSGA_III;
    gaObj->multi_threading = true;
    gaObj->idle_delay_us = 1; // switch between threads quickly
    gaObj->verbose = false;
    gaObj->population = 40;
    gaObj->generation_max = 100;
    gaObj->calculate_MO_objectives = calculateMOObjectives;
    gaObj->init_genes = initGenes;
    gaObj->eval_solution = evalSolution;
    gaObj->mutate = mutate;
    gaObj->crossover = crossover;
    gaObj->MO_report_generation = MOReportGeneration;
    gaObj->crossover_fraction = 0.7;
    gaObj->mutation_rate = 0.4;
    gaObj->solve();
    */
    std::mt19937_64 rng; // random generator

    Solution s;
    initGenes(s, rng);

    std::cout << "The problem is optimized in " << timer.toc() << " seconds." << std::endl;


    return *gaObj;
}
