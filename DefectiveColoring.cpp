#include "DefectiveColoring.h"
#include "Utils.h"
#include <algorithm>
#include <random>
#include <limits>

// --------------------------------------------------
// Função auxiliar
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

// --------------------------------------------------
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

        if (colors[v] == -1)
            colors[v] = ++maxColor;
    }

    return colors;
}

// --------------------------------------------------
// Guloso randomizado
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
        std::sort(uncolored.begin(), uncolored.end(),
            [&](int a, int b) {
                return g.adj[a].size() > g.adj[b].size();
            });

        int rclSize = std::max(1, (int)(alpha * uncolored.size()));
        std::uniform_int_distribution<int> dist(0, rclSize - 1);

        int idx = dist(rng);
        int v = uncolored[idx];

        for (int c = 0; c <= maxColor; c++) {
            if (canAssignColor(v, c, g, colors, d)) {
                colors[v] = c;
                break;
            }
        }

        if (colors[v] == -1)
            colors[v] = ++maxColor;

        uncolored.erase(uncolored.begin() + idx);
    }

    return colors;
}

// --------------------------------------------------
// Guloso Randomizado Reativo
std::vector<int> greedyReactiveDefectiveColoring(
    const Graph& g,
    int d,
    const std::vector<double>& alphas,
    int iterations,
    int blockSize
) {
    int m = alphas.size();

    std::vector<double> probabilities(m, 1.0 / m);
    std::vector<double> avgQuality(m, 0.0);
    std::vector<int> usage(m, 0);

    std::vector<int> bestSolution;
    int bestCost = std::numeric_limits<int>::max();

    std::discrete_distribution<int> alphaDist(
        probabilities.begin(), probabilities.end()
    );

    for (int it = 1; it <= iterations; it++) {
        int idx = alphaDist(rng);
        double alpha = alphas[idx];

        auto solution = greedyRandomizedDefectiveColoring(g, d, alpha);
        int cost = countColors(solution);

        usage[idx]++;
        avgQuality[idx] += cost;

        if (cost < bestCost) {
            bestCost = cost;
            bestSolution = solution;
        }

        // Atualiza probabilidades a cada bloco
        if (it % blockSize == 0) {
            double sum = 0.0;

            for (int i = 0; i < m; i++) {
                if (usage[i] > 0)
                    avgQuality[i] /= usage[i];
                else
                    avgQuality[i] = bestCost * 2;

                probabilities[i] = 1.0 / avgQuality[i];
                sum += probabilities[i];
            }

            for (int i = 0; i < m; i++) {
                probabilities[i] /= sum;
                avgQuality[i] = 0.0;
                usage[i] = 0;
            }

            alphaDist = std::discrete_distribution<int>(
                probabilities.begin(), probabilities.end()
            );
        }
    }

    return bestSolution;
}
