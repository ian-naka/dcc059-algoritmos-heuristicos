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
    cout << "SEED: " << seed << endl;
}

int countColors(const vector<int>& colors) {
    if (colors.empty()) return 0;
    int max_c = -1;
    for(int c : colors) {
        if(c > max_c) max_c = c;
    }
    return max_c + 1;
}

void printGraphCSAcademy(const Graph& g, const string& filename) {
    ostream* out = &cout;
    ofstream file;
    
    if (!filename.empty()) {
        file.open(filename);
        if (!file.is_open()) {
            cerr << "Erro ao abrir arquivo " << filename << endl;
            return;
        }
        out = &file;
    }
    

    set<pair<int,int>> edges;
    for (int u = 0; u < g.n; u++) {
        for (int v : g.adj[u]) {
            if (u < v) { 
                edges.insert({u, v});
            }
        }
    }
    
 
    *out << g.n << " " << edges.size() << endl;
    

    for (const auto& [u, v] : edges) {
        *out << u << " " << v << endl;
    }
    
    if (!filename.empty()) {
        file.close();
        cout << "Grafo salvo em: " << filename << endl;
    }
}


void printColoredGraphCSAcademy(const Graph& g, const vector<int>& colors, const string& filename) {
    ostream* out = &cout;
    ofstream file;
    
    if (!filename.empty()) {
        file.open(filename);
        if (!file.is_open()) {
            cerr << "Erro ao abrir arquivo " << filename << endl;
            return;
        }
        out = &file;
    }
    

    set<pair<int,int>> edges;
    for (int u = 0; u < g.n; u++) {
        for (int v : g.adj[u]) {
            if (u < v) {
                edges.insert({u, v});
            }
        }
    }
    
    *out << g.n << " " << edges.size() << endl;
    
 
    for (const auto& [u, v] : edges) {
        int weight = 1;
        if (colors[u] == colors[v]) {
            weight = 999; 
        }
        *out << u << " " << v << " " << weight << endl;
    }
    
    
    *out << endl << "# Cores dos vertices:" << endl;
    for (int v = 0; v < g.n; v++) {
        *out << "# Vertice " << v << " -> Cor " << colors[v] << endl;
    }
    
    if (!filename.empty()) {
        file.close();
        cout << "Grafo colorido salvo em: " << filename << endl;
    }
}