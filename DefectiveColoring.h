#ifndef DEFECTIVE_COLORING_H
#define DEFECTIVE_COLORING_H

#include "Graph.h"
#include <vector>

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

// Guloso randomizado 
std::vector<int> greedyRandomizedDefectiveColoring(
    const Graph& g,
    int d,
    double alpha
);

#endif
