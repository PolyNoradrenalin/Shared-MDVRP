#include "gasolver.h"

void GASolver::initGenes(Solution &p, const std::function<double(void)> &rnd01)
{
    // Création des générateurs de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> producerDistribution(0, int(instance.getProducers().size()));
    std::uniform_int_distribution<> clientDistribution(0, int(instance.getClients().size()));

    if (isVerbose)
    {
        std::cout << "Number of Producers: " << instance.getProducers().size() << std::endl;
        std::cout << "Number of Clients: " << instance.getClients().size() << std::endl;
    }
    // Ensemble de routes vides à initialiser
    std::vector<Route> routes;

    // Générer la route de livraison aux autres producteurs et clients pour chaque producteur
    for (int prodId = 0; prodId < instance.getProducers().size(); prodId++)
    {
        // Route de livraison aux producteurs
        std::vector<Node> prodRoute;

        // Taille de la route des producteurs
        int prodRouteLength = producerDistribution(gen);

        if (isVerbose)
        {
            std::cout << "Generating producer route with " << prodRouteLength << " producers for producer " << prodId
                      << "..." << std::endl;
        }

        std::vector<int> excludedVals{prodId};

        // Créer la distribution aléatoire permettant de faire le tirage d'un producteur
        std::discrete_distribution<> distrib = getRandomIntDistribution(0, int(instance.getProducers().size()),
                                                                        excludedVals);

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

        if (isVerbose)
        {
            std::cout << "Generating client route with " << clientRouteLength << " clients for producer " << prodId
                      << "..."
                      << std::endl;
        }
        distrib = getRandomIntDistribution(0, int(instance.getClients().size()), std::vector<int>{});

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

    // TODO: Allow for the option to accept invalid solutions in initialisation
    // On rajoute des clients pour que la solution devienne valide
    std::vector<Route> fixedRoutes;
    // Cette variable permet de déterminer pour chaque producteur, quels clients n'ont pas été livrés
    auto missingClientsPerProducer = getInvalidRoutesIfAny(p, instance);
    int routeIndex = 0;

    // On itère sur chaque paire <route, liste des clients non-livrés> pour les ajouter à la route
    for (const auto &clientPair: missingClientsPerProducer)
    {
        if (routes.size() <= routeIndex)
        {
            std::cerr << "An error has occurred during the reparation of initialized solution." << std::endl;
            throw std::exception();
        }
        std::vector<Node> clientsRoute = p.routes[routeIndex].clientRoute;

        if (clientPair.second.empty())
        {
            fixedRoutes.push_back(clientPair.first);
            continue;
        }

        for (Node missingClient: clientPair.second)
        {
            clientsRoute.push_back(missingClient);
        }

        fixedRoutes.emplace_back(clientPair.first.prodRoute, clientsRoute);

        routeIndex++;
    }

    // Si pas de cycles et si la solution est devenue valide, on l'indique comme valide
    p.isValid = p.producersCycling();

    // On ajoute la route réparée à la solution p
    p.routes = fixedRoutes;

    if (isVerbose)
    {
        std::cout << "DONE GENERATING SOLUTION, FINAL RESULT: " << std::endl;
    }
    // Print to console initialisation if verbose solution
    if (isVerbose)
    {
        int count = 0;
        for (const auto &prod: p.routes)
        {
            std::cout << "Route for producer " << count << std::endl;
            std::cout << "Producer route: " << count << "->";
            for (Node n: prod.prodRoute)
            {
                std::cout << n.id << "->";
            }
            std::cout << count << std::endl;

            std::cout << "Client route: " << count << "->";
            for (Node n: prod.clientRoute)
            {
                std::cout << n.id << "->";
            }
            std::cout << count << std::endl;

            std::cout << "---------------------" << std::endl;

            count++;
        }
    }
}

bool GASolver::evalSolution(const Solution &p, MiddleCost &c)
{
    // On vérifie la validité de la solution
    if (!p.isValid)
    {
        return false;
    }

    // Si la solution est valide, on calcule les coûts moyens
    c.distanceCost = 0;
    c.travelTimeCost = 0;

    for (const auto &route: p.routes)
    {
        std::vector<Node> fullRoute = route.getRoute();
        for (auto it = fullRoute.begin(); it != std::prev(fullRoute.end()); ++it)
        {
            if (std::next(it) != fullRoute.end())
            {
                c.distanceCost += instance.getDistance(*it, *std::next(it));
                c.travelTimeCost += instance.getTravelTime(*it, *std::next(it));
            }
        }
    }

    if (isVerbose)
    {
        std::cout << "Solution Fitness: " << std::endl;
        std::cout << "Distance Cost: " << c.distanceCost << std::endl;
        std::cout << "Travel Time Cost: " << c.travelTimeCost << std::endl;
    }

    return true;
}

Solution GASolver::mutate(const Solution &X_base, const std::function<double(void)> &rnd01, double shrink_scale)
{
    // Exchange Mutation
    Solution offspring = X_base;
    // On effectue la mutation sur chaque route
    for (int prodIndex = 0; prodIndex < int(instance.getProducers().size()); prodIndex++)
    {
        bool useProducerRoute = (rnd01() < 0.5);

        std::vector<Node> r;
        r = (useProducerRoute ? X_base.routes.at(prodIndex).prodRoute : X_base.routes.at(prodIndex).clientRoute);
        // Appliquer la mutation sur les producteurs
        if (r.size() > 1)
        {
            // Récupérer deux indices pour la mutation par échange
            int index1 = randomIntInInterval(0, int(r.size()) - 1, rnd01);
            int index2 = randomIntInInterval(0, int(r.size()) - 1, rnd01);

            // Faire la mutation
            std::iter_swap(r.begin() + index1, r.begin() + index2);

            // Remplacer l'ancienne route par la nouvelle
            useProducerRoute ? offspring.routes.at(prodIndex).prodRoute = r : offspring.routes.at(
                    prodIndex).clientRoute = r;
        }
    }
    offspring.isValid = isSolutionValid(offspring, instance);

    return offspring;
}

Solution GASolver::crossover(const Solution &X1, const Solution &X2, const std::function<double(void)> &rnd01)
{
    // Ordered Crossover
    Solution offspring = X1;

    for (int i = 0; i < int(instance.getProducers().size()); i++)
    {
        // On récupère une route aléatoire pour effectuer le crossover
        int prodIndex1 = randomIntInInterval(0, int(instance.getProducers().size()) - 1, rnd01);
        int prodIndex2 = randomIntInInterval(0, int(instance.getProducers().size()) - 1, rnd01);

        std::vector<Node> r1;
        std::vector<Node> r2;
        bool useProducerRoute = (rnd01() < 0.5);

        if (useProducerRoute)
        {
            // Appliquer le crossover à la route de livraison aux producteurs
            r1 = X1.routes.at(prodIndex1).prodRoute;
            r2 = X2.routes.at(prodIndex2).prodRoute;
        } else
        {
            // Appliquer le crossover à la route de livraison aux clients
            r1 = X1.routes.at(prodIndex1).clientRoute;
            r2 = X2.routes.at(prodIndex2).clientRoute;
        }

        // Si r1 vide, on va forcément utiliser r2
        if (r1.empty())
        {
            useProducerRoute ? offspring.routes.at(prodIndex1).prodRoute = r2 : offspring.routes.at(
                    prodIndex1).clientRoute = r2;
            return offspring;
        }

        std::vector<Node> r = r1;

        // On récupère le dernier indice de la plus petite des deux routes
        int substringUpperBounds = std::max(std::min(int(r1.size()) - 1, int(r2.size()) - 1), 0);

        // On récupère les deux indices permettant l'Ordered Crossover tels que : 0 <= index1 <= index2 <= substringUpperBounds
        int index1 = randomIntInInterval(0, substringUpperBounds, rnd01);
        int index2 = randomIntInInterval(index1, substringUpperBounds, rnd01);

        // On copie le substring de r1 vers r
        std::vector<Node> substring = {r1.begin() + index1, r1.begin() + index2 + 1};

        // On enlève tous les éléments de r après index2
        r = {r.begin(), r.begin() + index2 + 1};

        // Itérer dans r2 et enlever une fois chaque élément de substring s'il existe
        for (const auto &elem: substring)
        {
            auto it = std::find(r2.begin(), r2.end(), elem);

            if (it != r2.end())
            {
                r2.erase(it);
            }
        }

        // On complète les Nodes de r en dehors du substring par ceux de r2
        int rCounter = 0;
        for (const auto &elem: r2)
        {
            if (rCounter < index1)
            {
                // Remplacer élément si l'indice rCounter se situe avant les nodes de substring
                r[rCounter] = elem;
                rCounter++;
            } else
            {
                // Sinon l'ajouter à la fin de la route
                r.push_back(elem);
            }
        }

        // Insérer la nouvelle route dans le descendant
        useProducerRoute ? offspring.routes.at(prodIndex1).prodRoute = r : offspring.routes.at(
                prodIndex1).clientRoute = r;
    }

    offspring.isValid = isSolutionValid(offspring, instance);

    return offspring;
}

std::vector<double> GASolver::calculateMOObjectives(const EA::Genetic<Solution, MiddleCost>::thisChromosomeType &X)
{
    return {
            X.middle_costs.distanceCost,
            X.middle_costs.travelTimeCost
    };
}

void GASolver::MOReportGeneration(int generation_number, const GenerationType &last_generation,
                                  const std::vector<unsigned int> &pareto_front)
{
    (void) last_generation;

    std::cout << "Generation [" << generation_number << "], ";
    std::cout << "Pareto-Front {" << std::endl;

    for (unsigned int i = 0; i < pareto_front.size(); i++)
    {
        std::cout << (i > 0 ? "," : "");
        std::cout << "Individual: " << pareto_front[i] << std::endl;
        std::cout << "Distance: " << last_generation.chromosomes.at(pareto_front[i]).middle_costs.distanceCost
                  << std::endl;
        std::cout << "Travel time: " << last_generation.chromosomes.at(pareto_front[i]).middle_costs.travelTimeCost
                  << std::endl;
    }
    std::cout << "}" << std::endl;
}

GAType &GASolver::solveProblem(Instance inst, const std::string &jsonFilePath)
{
    instance = std::move(inst);
    std::ifstream f(jsonFilePath);
    json params = json::parse(f);
    f.close();
    EA::Chronometer timer;
    timer.tic();
    auto *gaObj = new GAType();

    gaObj->problem_mode = EA::GA_MODE::NSGA_III;
    gaObj->multi_threading = true;
    gaObj->idle_delay_us = 1; // switch between threads quickly
    gaObj->verbose = false;
    gaObj->population = params.value("population", 40);
    gaObj->generation_max = params.value("generation_max", 1000);
    gaObj->calculate_MO_objectives = calculateMOObjectives;
    gaObj->init_genes = initGenes;
    gaObj->eval_solution = evalSolution;
    gaObj->mutate = mutate;
    gaObj->crossover = crossover;
    gaObj->MO_report_generation = MOReportGeneration;
    gaObj->crossover_fraction = params.value("crossover_rate", 0.7);
    gaObj->mutation_rate = params.value("mutation_rate", 0.4);
    gaObj->solve();

    std::cout << "The problem is optimized in " << timer.toc() << " seconds." << std::endl;

    return *gaObj;
}
