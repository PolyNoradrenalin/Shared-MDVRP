#include <iostream>
#include "gasolver.h"
#include "parser.h"
#include <filesystem>

int main()
{
    std::vector<std::string> instancesPaths = {
            "I_03_05_T1-TA_0.txt",
            "I_03_05_T2-TA_0.txt",
            "I_03_05_TR-TA_0.txt",
            "I_05_10_T1-TA_0.txt",
            "I_05_10_T2-TA_0.txt",
            "I_05_10_TR-TA_0.txt",
            "I_08_15_T1-TA_0.txt",
            "I_08_15_T2-TA_0.txt",
            "I_08_15_TR-TA_0.txt"
    };

    std::filesystem::create_directories("./solutions");

    for (const std::string &path: instancesPaths)
    {
        Parser parser("./instances/" + path);
        Instance inst = parser.parse();
        std::cout << "INSTANCE LOADED " << path << std::endl;
        auto jsonPath = "params.json";

        GASolver::isVerbose = false;
        GAType &sol = GASolver::solveProblem(inst, jsonPath, path);

        Solution best = getSimpleSolution(inst);
        best.isValid = isSolutionValid(best, inst);

        MiddleCost simpleScore{};
        best.evalSolution(simpleScore);

        std::cout << "Simple solution score: " << simpleScore.distanceCost << std::endl;

        exportSolution(best, "./solutions/" + path + "simpleSolution.txt");
    }
    return 0;
}
