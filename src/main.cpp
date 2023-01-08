#include <iostream>
#include "gasolver.h"
#include "parser.h"

int main()
{
    Parser parser("./instances/I_08_15_T1-TA_0.txt");
    Instance inst = parser.parse();
    std::cout << "INSTANCE LOADED" << std::endl;
    GASolver::isVerbose = false;
    auto jsonPath = "params.json";
    GASolver::solveProblem(inst, jsonPath);


    return 0;
}
