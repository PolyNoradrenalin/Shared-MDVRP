#include "parser.h"


#include <utility>
#include <iostream>
#include <fstream>

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
        // Lecture du nombre de nœuds clients
        getline(filestream, line);
        unsigned int nClient = std::stoi(line);

        // Lecture du nombre de nœuds producteurs
        getline(filestream, line);
        unsigned int nProducteurs = std::stoi(line);

        //while ()
        //{
//
        //}
        filestream.close();
    }

    return Instance();
}


