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
        if (!file.is_open()) { return; }
        out = &file;
    }

    for(int i=0; i<g.n; i++) {
        // imprime o nó com a cor ao lado para você ver visualmente

        *out << i << "(C" << colors[i] << ")" << endl;
    }

    // imprime as arestas usando os mesmos nomes
    for (int u = 0; u < g.n; u++) {
        for (int v : g.adj[u]) {
            if (u < v) { 
                *out << u << "(C" << colors[u] << ") " << v << "(C" << colors[v] << ")" << endl;
            }
        }
    }
    
    if (!filename.empty()) file.close();
}

bool validateSolution(const Graph& g, const vector<int>& solution, int d) {
    for (int u = 0; u < g.n; u++) {
        int defects = 0;
        int myColor = solution[u];
        
        // conta vizinhos com a mesma cor
        for (int v : g.adj[u]) {
            if (solution[v] == myColor) {
                defects++;
            }
        }
        
        // se violou a regra, avisa e falha
        if (defects > d) {
            cout << "ERRO! Vertice " << u << " tem " << defects 
                 << " vizinhos da mesma cor (limite: " << d << ")" << endl;
            return false;
        }
    }
    return true;
}