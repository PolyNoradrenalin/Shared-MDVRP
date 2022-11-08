#include "parser.h"


#include <utility>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

Parser::Parser(std::string p)
{
    setPath(std::move(p));
}

void Parser::setPath(std::string p)
{
    this->path = std::move(p);
}

Instance Parser::parse() const
{
    std::ifstream filestream(path);
    std::string line;

    if (filestream.is_open())
    {
        // Lecture du nombre de nœuds producteurs
        getline(filestream, line);
        unsigned int nProducers = std::stoi(line);

        // Lecture du nombre de nœuds clients
        getline(filestream, line);
        unsigned int nClients = std::stoi(line);
        unsigned int nNodes = nClients + nProducers;

        // Lecture de la matrice de distance
        Matrix2D<int> distances = std::vector<std::vector<int>>(nNodes);
        for (int i = 0; i < nNodes; i++)
        {
            distances[i] = std::vector<int>();
            getline(filestream, line);

            std::istringstream split(line);
            for (std::string each; std::getline(split, each, ' '); distances[i].push_back(std::stoi(each)));
        }

        std::vector<Node> producers = std::vector<Node>();
        std::vector<Node> clients = std::vector<Node>();

        // Lecture des positions de chaque nœud
        for (int i = 0; i < nNodes; i++)
        {
            std::vector<int> nodePos = std::vector<int>(2);

            getline(filestream, line);

            std::istringstream split(line);
            for (int j=0; j<2; j++)
            {
                std::string each;
                std::getline(split, each, ' ');
                nodePos[j] = std::stoi(each);
            }

            if (i < nProducers)
            {
                producers.emplace_back(i, Producer, nodePos[0], nodePos[1]);
            }
            else
            {
                clients.emplace_back(i, Client, nodePos[0], nodePos[1]);
            }
        }

        // Lecture de la matrice de distance
        Matrix2D<int> travelTimes = std::vector<std::vector<int>>(nNodes);
        for (int i = 0; i < nNodes; i++)
        {
            travelTimes[i] = std::vector<int>(nNodes);
            getline(filestream, line);

            std::istringstream split(line);
            for (std::string each; std::getline(split, each, ' '); travelTimes[i].push_back(std::stoi(each)));
        }

        filestream.close();

        return {producers, clients, distances, travelTimes};
    }

    throw ;
}


