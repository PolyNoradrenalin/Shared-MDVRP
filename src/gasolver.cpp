#include "gasolver.h"

#include <utility>

void GASolver::initGenes(Solution &p, const std::function<double(void)> &rnd01)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> producerDistribution(0, (int) instance.getProducers().size());
    std::uniform_int_distribution<> clientDistribution(0, (int) instance.getClients().size());

    // Générer la route de livraison aux autres producteurs pour chaque producteur
    for (int i = 0; i < instance.getProducers().size(); i++)
    {
        // Route qui sera générée
        std::vector<Node> prodRoute;

        // Taille de la route des producteurs
        int nbProds = producerDistribution(gen);

        std::vector<int> excludedVals(nbProds);
        excludedVals.push_back(i);

        // Créer la distribution aléatoire permettant de faire le tirage d'un producteur
        auto distrib = getRandomIntDistributionWithExclusion(0, (int) instance.getProducers().size(), excludedVals);

        // Générer la route
        for (int j = 0; j < nbProds; j++)
        {
            // Ajoute le nœud à la route du producteur
            prodRoute.push_back(instance.getProducers().at(distrib(gen)));
            std::cout << prodRoute.end()->id;
        }

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
