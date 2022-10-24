#include "gasolver.h"

void GASolver::initGenes(Solution &p, const std::function<double(void)> &rnd01)
{
    // TODO: Implement
}

bool GASolver::evalSolution(const Solution &p, MiddleCost &c)
{
    // TODO: Implement
    return false;
}

Solution GASolver::mutate(const Solution &X_base, const std::function<double(void)> &rnd01, double shrink_scale)
{
    // TODO: Implement
    return Solution();
}

Solution GASolver::crossover(const Solution &X1, const Solution &X2, const std::function<double(void)> &rnd01)
{
    // TODO: Implement
    return Solution();
}

std::vector<double> GASolver::calculateMOObjectives(const EA::Genetic<Solution, MiddleCost>::thisChromosomeType &X)
{
    // TODO: Implement
    return std::vector<double>();
}

void GASolver::MOReportGeneration(int generation_number, const GenerationType &last_generation,
                                  const std::vector<unsigned int> &pareto_front)
{
    // TODO: Implement
}

GAType GASolver::solveProblem(Instance instance)
{
    EA::Chronometer timer;
    timer.tic();

    GAType gaObj;
    gaObj.problem_mode = EA::GA_MODE::NSGA_III;
    gaObj.multi_threading = true;
    gaObj.idle_delay_us = 1; // switch between threads quickly
    gaObj.verbose = false;
    gaObj.population = 40;
    gaObj.generation_max = 100;
    gaObj.calculate_MO_objectives = calculateMOObjectives;
    gaObj.init_genes = initGenes;
    gaObj.eval_solution = evalSolution;
    gaObj.mutate = mutate;
    gaObj.crossover = crossover;
    gaObj.MO_report_generation = MOReportGeneration;
    gaObj.crossover_fraction = 0.7;
    gaObj.mutation_rate = 0.4;
    gaObj.solve();

    std::cout << "The problem is optimized in " << timer.toc() << " seconds." << std::endl;

    return gaObj;
}
