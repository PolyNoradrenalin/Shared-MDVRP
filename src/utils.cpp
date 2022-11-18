#include "utils.h"

bool isSolutionValid(Solution &p)
{
    // TODO: Verify that all clients receive all products from the producers
    return !producersCycling(p);
}

bool producersCycling(Solution &p)
{
    // TODO: Implement cycling detection algorithm
    return false;
}

std::discrete_distribution<>
getRandomIntDistributionWithExclusion(int minVal, int maxVal, const std::vector<int> excludedVals)
{
    std::vector<int> distVals(abs(maxVal - minVal));
    std::fill(distVals.begin(), distVals.end(), 1);

    for (int i: excludedVals)
    {
        if (i < distVals.size())
        {
            distVals[i] = 0;
        }
    }

    std::discrete_distribution<> distribution(distVals.begin(), distVals.end());

    return distribution;
}