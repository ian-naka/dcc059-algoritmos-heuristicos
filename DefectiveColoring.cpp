#include "DefectiveColoring.h"

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
