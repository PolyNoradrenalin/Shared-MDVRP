#ifndef S_MDVRP_NODE_H
#define S_MDVRP_NODE_H

/**
 * Classe permettant de représenter le noeud d'une instance.
 */
class Node
{
public:
    // Identifiant du nœud
    int id;

    // Cordonnées du nœud dans l'instance
    float x;
    float y;

    Node(int id, float x, float y);
};

/**
 * Type du noeud, sert à savoir si le noeud est un producteur ou un client.
 */
enum NodeType
{
    Client,
    Producer
};

#endif //S_MDVRP_NODE_H
