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

std::vector<int> greedyDefectiveColoring(
    const Graph& g,
    int d
);

#endif
