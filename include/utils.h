#ifndef S_MDVRP_UTILS_H
#define S_MDVRP_UTILS_H

#include "solution.h"
#include <random>
#include <iostream>
#include <list>

/**
 * Vérifie si la solution est valide.
 * @param solution Solution à vérifier
 * @return <b>true</b> si valide, <b>false</b> sinon
 */
bool isSolutionValid(Solution &solution);

/**
 * Vérifie si les producteurs produisent un cycle (ce qui générerait un deadlock).
 * @param solution Solution à vérifier
 * @return<b>true</b> s'ils cyclent, <b>false</b> sinon
 */
bool producersCycling(Solution &solution);

/**
 * Détecte quels clients ne sont pas desservis pour chaque producteur d'une solution.
 * @param solution Solution à vérifier
 * @return std::vector de taille nbProducteurs rempli avec des paires de <Route, std::vector<Node>> correspondant
 * aux clients non-livrés par un producteur.
 */
std::vector<std::pair<Route, std::vector<Node>>> getInvalidRoutesIfAny(const Solution &solution, const Instance &i);

/**
 * Génère un entier aléatoire dans [minVal; maxVal] en excluant les valeurs dans excludedVals.
 * @param minVal Valeur minimale du nombre aléatoire généré
 * @param maxVal Valeur maximale du nombre aléatoire généré
 * @param excludedVals Liste d'entiers qu'on souhaite exclure. Seulement ceux entre minVal et maxVal seront considérés.
 * @return Entier entre minVal et maxVal qui n'appartient pas à excludedVals.
 */
std::discrete_distribution<>
getRandomIntDistribution(int minVal, int maxVal, const std::vector<int>& excludedVals);

/**
 * Filtre un vector de Nodes en enlevant les doublons qui sont côte-à-côte.
 * @param vector Vecteur à filtrer
 * @return Vecteur filtré
 */
std::vector<Node> removeSideBySideDuplicatesInVector(const std::vector<Node> &vector);

/**
 * Filtre un vector de Nodes en enlevant les doublons.
 * @param vector Vecteur à filtrer
 * @return Vecteur filtré, sans doublons
 */
std::vector<Node> removeDuplicatesInVector(std::vector<Node> vector);

#endif //S_MDVRP_UTILS_H