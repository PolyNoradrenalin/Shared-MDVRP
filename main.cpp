#include <iostream>
#include "gasolver.h"
#include "parser.h"

int main()
{
    Parser parser("./instances/I_10_50_T1-TA_0.txt");
    Instance inst = parser.parse();
    std::cout << "salut";

    return 0;
}
