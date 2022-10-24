#include "node.h"

/**
 * Constructeur avec paramètres.
 * @param id Identifiant du noeud.
 * @param x Position x du noeud.
 * @param y Position y du noeud.
 */
Node::Node(int id, NodeType nodeType, double x, double y)
{
    this->id = id;
    this->nodeType = nodeType;
    this->x = x;
    this->y = y;
}
