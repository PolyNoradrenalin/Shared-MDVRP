#ifndef S_MDVRP_PARSER_H
#define S_MDVRP_PARSER_H
#include <string>
#include "instance.h"

/**
 * Parseur générant des instances à partir d'un fichier en entrée.
 * <br>
 * <br>
 * <b>Format attendu<\b>: <br>
 *  NB_PRODUCTEURS <br>
 *  NB_CLIENTS <br>
 *  0 d01 d02 d03 .. d0N <br>
 *  d10 0 ... <br>
 *  d20   ... <br>
 *  d30   ... <br>
 *  dN0   ... <br>
 *  0 t01  t02 .. t0N <br>
 *  t10 0 ... <br>
 *  t20   ... <br>
 *  t30   ... <br>
 *  tN0   ... <br>
 *  x0 y0 <br>
 *  x1 y1 <br>
 *  x2 y2 <br>
 *  . <br>
 *  . <br>
 *  . <br>
 *  xN yN <br>
 */
class Parser
{
private:
    std::string path;
public:
    explicit Parser(std::string p);

    /**
     * Modifie le non
     * @param p
     */
    void setPath(std::string p);

    /**
     * Parse l'instance du fichier cible sélectionné.
     * @return L'instance parsée
     */
    Instance parse() const;
};
#endif //S_MDVRP_PARSER_H
