#ifndef S_MDVRP_LOCALSEARCH_H
#define S_MDVRP_LOCALSEARCH_H

#include "solution.h"

using std::function;

/**
 * Effectue une recherche locale sur une solution. Cette classe est la base des différentes méthodes de recherche locale.
 */
class LocalSearch
{
protected:

    function<void(Solution &)> editFunction;

public:
    /**
     * Constructeur de la classe LocalSearch. Initialise la fonction d'édition de solution.
     */
    explicit LocalSearch(function<void(Solution &)> &editFunction);
    /**
     * Effectue une recherche locale sur la solution passée en paramètre.
     */
    virtual Solution search(Solution &s) = 0;
};

/**
 * Effectue une recherche locale sur une solution en prenant le premier voisin améliorant la solution.
 */
class FirstImprovement : public LocalSearch
{
public:
    /**
     * Constructeur de la classe FirstImprovement. Initialise la fonction d'édition de solution.
     */
    explicit FirstImprovement(function<void(Solution &)> &editFunction);
    /**
     * Effectue une recherche locale sur la solution passée en paramètre et s'arrête à la première meilleure solution trouvée.
     */
    Solution search(Solution &s) override;
};


#endif //S_MDVRP_LOCALSEARCH_H
