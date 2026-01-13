#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>

extern std::mt19937 rng;

void initRandom(int seed = -1);

int countColors(const std::vector<int>& colors);

#endif
