#include "Utils.h"
#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;

mt19937 rng;

void initRandom(int seed) {
    if (seed == -1) {
        seed = chrono::steady_clock::now().time_since_epoch().count();
    }
    rng.seed(seed);
    cout << 'SEED: ' << seed << endl;
}

int countColors(const vector<int>& colors) {
    if (colors.empty()) return 0;
    int max_c = -1;
    for(int c : colors) {
        if(c > max_c) max_c = c;
    }
    return max_c + 1;
}
