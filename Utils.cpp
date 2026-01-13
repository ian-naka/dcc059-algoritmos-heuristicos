#include "Utils.h"
#include <chrono>
#include <iostream>
#include <algorithm>

std::mt19937 rng;

void initRandom(int seed) {
    if (seed == -1) {
        seed = std::chrono::steady_clock::now()
                   .time_since_epoch()
                   .count();
    }
    rng.seed(seed);
    std::cout << "Seed utilizada: " << seed << std::endl;
}

int countColors(const std::vector<int>& colors) {
    return *std::max_element(colors.begin(), colors.end()) + 1;
}
