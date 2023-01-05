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
    explicit LocalSearch(function<void(Solution &)> &editFunction);
    virtual Solution search(Solution &s) = 0;
};

/**
 * Effectue une recherche locale sur une solution en prenant le premier voisin améliorant la solution.
 */
class FirstImprovement : public LocalSearch
{
public:
    explicit FirstImprovement(function<void(Solution &)> &editFunction);
    Solution search(Solution &s) override;
};


#endif //S_MDVRP_LOCALSEARCH_H
