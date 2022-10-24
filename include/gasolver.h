#ifndef S_MDVRP_GASOLVER_H
#define S_MDVRP_GASOLVER_H

#include "solution.h"
#include <vector>
#include "instance.h"
#include "openGA.hpp"

struct MiddleCost
{
    double travelTimeCost;
    double distanceCost;
};

typedef EA::Genetic<Solution, MiddleCost> GAType;
typedef EA::GenerationType<Solution, MiddleCost> GenerationType;

class GASolver
{
private:
    static void initGenes(Solution &p, const std::function<double(void)> &rnd01);

    static bool evalSolution(const Solution &p, MiddleCost &c);

    static Solution mutate(const Solution &X_base, const std::function<double(void)> &rnd01, double shrink_scale);

    static Solution crossover(const Solution &X1, const Solution &X2, const std::function<double(void)> &rnd01);

    static std::vector<double> calculateMOObjectives(const GAType::thisChromosomeType &X);

    static void
    MOReportGeneration(int generation_number, const EA::GenerationType<Solution, MiddleCost> &last_generation,
                       const std::vector<unsigned int> &pareto_front);

public:
    static GAType solveProblem(Instance instance);
};

#endif //S_MDVRP_GASOLVER_H
