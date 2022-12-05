#ifndef S_MDVRP_GASOLVER_H
#define S_MDVRP_GASOLVER_H

#include <vector>
#include <random>
#include "solution.h"
#include "instance.h"
#include "utils.h"
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
    /**
     * Initialise une solution p en générant les routes de livraison de chaque producteur.
     * @param p Solution à initialiser
     * @param rnd01 Variable aléatoire
     */
    static void initGenes(Solution &p, const std::function<double(void)> &rnd01);

    /**
     * Permet de récupérer le fitness d'une solution et d'évaluer si elle est valide.
     * @param p Solution à évaluer
     * @param c Coût (ou fitness) à calculer
     * @return Vrai si la solution est acceptée, faux sinon.
     */
    static bool evalSolution(const Solution &p, MiddleCost &c);

    /**
     * Fonction de mutation qui applique une mutation à une solution.
     * @param X_base Solution de base
     * @param rnd01 Variable aléatoire
     * @param shrink_scale Non-utilisée
     * @return La solution mutée.
     */
    static Solution mutate(const Solution &X_base, const std::function<double(void)> &rnd01, double shrink_scale);

    /**
     * Applique une opération de crossover sur une solution à partir de deux solution de départ.
     * @param X1 Solution 1
     * @param X2 Solution 2
     * @param rnd01 Variable aléatoire
     * @return Solution modifiée
     */
    static Solution crossover(const Solution &X1, const Solution &X2, const std::function<double(void)> &rnd01);

    static std::vector<double> calculateMOObjectives(const GAType::thisChromosomeType &X);

    static void
    MOReportGeneration(int generation_number, const EA::GenerationType<Solution, MiddleCost> &last_generation,
                       const std::vector<unsigned int> &pareto_front);

public:
    inline static Instance instance = Instance(std::vector<Node>(), std::vector<Node>(), Matrix2D<int>(),
                                               Matrix2D<int>());

    inline static bool isVerbose = false;

    inline static double biCriteriaRatio = 0.5;

    static GAType &solveProblem(Instance instance);
};

#endif //S_MDVRP_GASOLVER_H
