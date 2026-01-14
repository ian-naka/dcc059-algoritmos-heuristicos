#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Graph {
public:
    int n; // número de vértices
    int m; // número de arestas
    std::vector<std::vector<int>> adj; // Lista de adjacência

    Graph(int n = 0);

    void addEdge(int u, int v);
    void readFromDIMACS(const std::string& filename);
    int getDegree(int v) const;
};

#endif
