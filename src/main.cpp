#include <iostream>
#include "gasolver.h"
#include "parser.h"

int main()
{
    std::vector<std::string> instancesPaths = {
            "./instances/I_03_05_T1-TA_0.txt"
            "./instances/I_03_05_T2-TA_0.txt"
            "./instances/I_03_05_T3-TA_0.txt"
            "./instances/I_05_10_T1-TA_0.txt"
            "./instances/I_05_10_T2-TA_0.txt"
            "./instances/I_05_10_T3-TA_0.txt"
            "./instances/I_08_15_T1-TA_0.txt"
            "./instances/I_08_15_T2-TA_0.txt"
            "./instances/I_08_15_T3-TA_0.txt"
    } ;

    for(std::string path : instancesPaths)
    {
        Parser parser(path);
        Instance inst = parser.parse();
        std::cout << "INSTANCE LOADED " << path << std::endl;
        auto jsonPath = "params.json";

        GASolver::isVerbose = false;
        GAType& sol = GASolver::solveProblem(inst, jsonPath);

        Solution best = getSimpleSolution(inst);
        best.isValid = isSolutionValid(best, inst);

        MiddleCost simpleScore{};
        best.evalSolution(simpleScore);

        std::cout << "Simple solution score: " << simpleScore.distanceCost << std::endl;

        exportSolution(best,path + "simpleSolution.txt");
    }



    return 0;
}
