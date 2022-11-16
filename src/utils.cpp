#include "utils.h"

bool isSolutionValid(Solution &p)
{
    return !producersCycling(p);
}

bool producersCycling(Solution &p)
{
    // TODO: Implement cycling detection algorithm
    return false;
}
