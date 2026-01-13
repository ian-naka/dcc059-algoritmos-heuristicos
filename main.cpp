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

    std::vector<double> alphas = {0.1, 0.3, 0.5, 0.7};
    int iterations = 300;
    int blockSize = 30;

    auto sol = greedyReactiveDefectiveColoring(
        g, d, alphas, iterations, blockSize
    );

    std::cout << "\nGuloso Randomizado Reativo:\n";
    std::cout << "Cores utilizadas: " << countColors(sol) << "\n";

    return 0;
}
