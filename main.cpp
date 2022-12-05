#include <iostream>
#include "gasolver.h"
#include "parser.h"

int main()
{
    Parser parser("./instances/I_10_50_T1-TA_0.txt");
    Instance inst = parser.parse();
    Solution sol = Solution();
    std::vector<Node> nodes = std::vector<Node>();
    for (int i=0; i<5; i++)
    {
        nodes.emplace_back(i, Producer, 0, 0);
    }
    Route r1 = Route({nodes[2], nodes[1], nodes[0], nodes[2]}, std::vector<Node>());
    Route r2 = Route({nodes[0], nodes[1], nodes[2]}, std::vector<Node>());
    Route r3 = Route({nodes[1], nodes[3], nodes[2]}, std::vector<Node>());


    sol.routes.emplace_back(r1);
    // sol.routes.emplace_back(r2);
    // sol.routes.emplace_back(r3);

    bool test = sol.producersCycling();
    std::cout << test;
    return 0;
}
