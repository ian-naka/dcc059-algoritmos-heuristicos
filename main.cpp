#include <iostream>
#include "Graph.h"
#include "DefectiveColoring.h"
#include "Utils.h"

int main() {
    initRandom(); // semente aleatória (exigência do trabalho)

    // Exemplo simples de grafo
    int n = 6;
    Graph g(n);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 0);
    g.addEdge(1, 3);

    int d = 1; // defeito máximo permitido

    auto colors = greedyDefectiveColoring(g, d);

    std::cout << "\nResultado da Coloração Defeituosa:\n";
    std::cout << "Cores utilizadas: " << countColors(colors) << "\n\n";

    for (int i = 0; i < n; i++) {
        std::cout << "Vertice " << i
                  << " -> cor " << colors[i] << "\n";
    }

    return 0;
}
