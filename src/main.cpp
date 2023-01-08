#include <iostream>
#include "gasolver.h"
#include "parser.h"

int main()
{
    Parser parser("./instances/I_05_10_T1-TC_0.txt");
    Instance inst = parser.parse();
    std::cout << "INSTANCE LOADED" << std::endl;
    auto jsonPath = "params.json";

    GASolver::isVerbose = false;
    GAType& sol = GASolver::solveProblem(inst, jsonPath);

    Solution best = getSimpleSolution(inst);
    best.isValid = isSolutionValid(best, inst);

    MiddleCost simpleScore{};
    best.evalSolution(simpleScore);

    std::cout << "Simple solution score: " << simpleScore.distanceCost << std::endl;

    return 0;
}
