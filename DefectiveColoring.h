#ifndef DEFECTIVE_COLORING_H
#define DEFECTIVE_COLORING_H

#include "Graph.h"
#include <vector>

// Função auxiliar
bool canAssignColor(
    int v,
    int color,
    const Graph& g,
    const std::vector<int>& colors,
    int d
);

// Guloso simples
std::vector<int> greedyDefectiveColoring(
    const Graph& g,
    int d
);

// Guloso randomizado (GRASP)
std::vector<int> greedyRandomizedDefectiveColoring(
    const Graph& g,
    int d,
    double alpha
);

// Guloso randomizado reativo
std::vector<int> greedyReactiveDefectiveColoring(
    const Graph& g,
    int d,
    const std::vector<double>& alphas,
    int iterations,
    int blockSize
);

#endif
