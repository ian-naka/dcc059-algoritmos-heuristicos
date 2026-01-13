#include <iostream>
#include "Graph.h"
#include "DefectiveColoring.h"
#include "Utils.h"

int main() {
    initRandom();

    int n = 6;
    Graph g(n);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(5,0);
    g.addEdge(1,3);

    int d = 1;
    double alpha = 0.5;

    auto solGulosa = greedyDefectiveColoring(g, d);
    auto solRand = greedyRandomizedDefectiveColoring(g, d, alpha);

    std::cout << "\nGuloso simples:\n";
    std::cout << "Cores: " << countColors(solGulosa) << "\n";

    std::cout << "\nGuloso randomizado (alpha = " << alpha << "):\n";
    std::cout << "Cores: " << countColors(solRand) << "\n";

    return 0;
}
