#include "DefectiveColoring.h"
#include "Utils.h"
#include <algorithm>
#include <random>

bool canAssignColor(
    int v,
    int color,
    const Graph& g,
    const std::vector<int>& colors,
    int d
) {
    int conflicts = 0;

    for (int u : g.adj[v]) {
        if (colors[u] == color) {
            conflicts++;
            if (conflicts > d)
                return false;
        }
    }
    return true;
}

// Guloso simples
std::vector<int> greedyDefectiveColoring(
    const Graph& g,
    int d
) {
    std::vector<int> colors(g.n, -1);
    int maxColor = 0;

    for (int v = 0; v < g.n; v++) {
        for (int c = 0; c <= maxColor; c++) {
            if (canAssignColor(v, c, g, colors, d)) {
                colors[v] = c;
                break;
            }
        }

        if (colors[v] == -1) {
            colors[v] = ++maxColor;
        }
    }

    return colors;
}

// Guloso Randomizado 
std::vector<int> greedyRandomizedDefectiveColoring(
    const Graph& g,
    int d,
    double alpha
) {
    std::vector<int> colors(g.n, -1);
    std::vector<int> uncolored(g.n);

    for (int i = 0; i < g.n; i++)
        uncolored[i] = i;

    int maxColor = 0;

    while (!uncolored.empty()) {
        // Ordena vértices não coloridos por grau de forma decrescente
        std::sort(uncolored.begin(), uncolored.end(),
            [&](int a, int b) {
                return g.adj[a].size() > g.adj[b].size();
            });

        int rclSize = std::max(1, (int)(alpha * uncolored.size()));
        std::uniform_int_distribution<int> dist(0, rclSize - 1);

        int idx = dist(rng);
        int v = uncolored[idx];

        // Atribui a menor cor possível
        for (int c = 0; c <= maxColor; c++) {
            if (canAssignColor(v, c, g, colors, d)) {
                colors[v] = c;
                break;
            }
        }

        if (colors[v] == -1) {
            colors[v] = ++maxColor;
        }

        // Remove o vértice colorido
        uncolored.erase(uncolored.begin() + idx);
    }

    return colors;
}
