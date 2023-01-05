#ifndef S_MDVRP_UTILS_H
#define S_MDVRP_UTILS_H

#include "solution.h"
#include <random>
#include <iostream>
#include <list>
#include <functional>

/**
 * Vérifie si la solution est valide.
 * @param solution Solution à vérifier
 * @return <b>true</b> si valide, <b>false</b> sinon
 */
bool isSolutionValid(const Solution &solution, const Instance& instance);


/**
 * Détecte quels clients ne sont pas desservis pour chaque producteur d'une solution.
 * @param solution Solution à vérifier
 * @return std::vector de taille nbProducteurs rempli avec des paires de <Route, std::vector<Node>> correspondant
 * aux clients non-livrés par un producteur.
 */
std::vector<std::pair<Route, std::vector<Node>>> getInvalidRoutesIfAny(const Solution &solution, const Instance &i);

/**
 * Retourne les routes réparées d'une solution en rajoutant les clients manquants pour chaque producteur à leur route de livraison.
 * @param p Solution à réparer
 * @param instance Instance du problème
 * @return std::vector<Route> les routes réparées
 */
std::vector<Route> fixInvalidRoutes(const Solution &p, const Instance &instance);

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

/**
 * Retourne un entier aléatoire entre deux entiers a et b
 * @param a Borne inférieure de la valeur de retour
 * @param b Borne supérieure de la valeur de retour
 * @param rnd01 Fonction aléatoire donnant un nombre aléatoire entre 0 et 1
 * @return Entier aléatoire entre a et b
 */
int randomIntInInterval(int a, int b, const std::function<double(void)> &rnd01);

#endif //S_MDVRP_UTILS_H