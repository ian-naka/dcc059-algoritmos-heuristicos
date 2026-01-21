#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>
#include <string>
#include "Graph.h"
#include <set>


extern std::mt19937 rng; // Declaração externa do gerador de números aleatórios

void initRandom(int seed = -1);
int countColors(const std::vector<int>& colors);
void printGraphCSAcademy(const Graph& g, const std::string& filename = "");
void printColoredGraphCSAcademy(const Graph& g, const std::vector<int>& colors, const std::string& filename = "");
bool validateSolution(const Graph& g, const std::vector<int>& solution, int d);


#endif
