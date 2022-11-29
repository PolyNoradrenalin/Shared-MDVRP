#ifndef S_MDVRP_UTILS_H
#define S_MDVRP_UTILS_H

#include "solution.h"
#include <random>

/**
 * Checks if the solution is valid/feasible.
 * @param p Solution to check
 * @return <b>true</b> if valid, <b>false</b>otherwise/
 */
bool isSolutionValid(Solution &p);

/**
 * Checks if the producers are producing a cycle which means they are interlocking themselves.
 * @param p Solution to check
 * @return<b>true</b> if they are cycling (interlocking), <b>false</b>otherwise/
 */
bool producersCycling(Solution &p);

/**
 * Génère un entier aléatoire dans [minVal; maxVal] en excluant les valeurs dans excludedVals.
 * @param minVal Valeur minimale du nombre aléatoire généré
 * @param maxVal Valeur maximale du nombre aléatoire généré
 * @param excludedVals Liste d'entiers qu'on souhaite exclure. Seulement ceux entre minVal et maxVal seront considérés.
 * @return Entier entre minVal et maxVal qui n'appartient pas à excludedVals.
 */
std::discrete_distribution<>
getRandomIntDistributionWithExclusion(int minVal, int maxVal, std::vector<int> excludedVals);

/**
 * Filtre un vector en enlevant les duplicats qui sont côte-à-côte.
 * @param vector Vecteur à filtrer
 * @return Vecteur filtré
 */
std::vector<Node> removeSideBySideDuplicatesInVector(std::vector<Node> vector);

#endif //S_MDVRP_UTILS_H