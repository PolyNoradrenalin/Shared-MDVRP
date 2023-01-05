//
// Created by noepe on 05/01/2023.
//

#include "localsearch.h"

#include <utility>

LocalSearch::LocalSearch(function<void(Solution &)> &editFunction)
{
    this->editFunction = editFunction;
}

FirstImprovement::FirstImprovement(function<void(Solution &)> &editFunction) : LocalSearch(editFunction) { }

Solution FirstImprovement::search(Solution &s)
{
    Solution bestSolution = s;
    Solution currentSolution = s;
    bool improved = false;
    while (!improved)
    {
        editFunction(currentSolution);
        if (currentSolution.fitness < bestSolution.fitness)
        {
            bestSolution = currentSolution;
            improved = true;
        }
    }
    return bestSolution;
}