#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include "Graph.h"
#include "DefectiveColoring.h"
#include "Utils.h"

using namespace std;

void saveToCSV(string filename, string instance, string algo, string params, 
               long seed, double timeSec, int result) {
    ofstream file(filename, ios::app); 
    if (file.is_open()) {
        file << instance << "," << algo << "," << params << "," 
             << seed << "," << timeSec << "," << result << endl;
        file.close();
    } else {
        cerr << "Erro ao salvar no CSV." << endl;
    }
}

int main(int argc, char* argv[]) {
    // Validação de argumentos
    if (argc < 4) {
        cout << "USO: ./main <arquivo> <algoritmo> <d> [params...]" << endl;
        cout << "Algoritmos: guloso, randomizado, reativo" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string algo = argv[2];
    int d = stoi(argv[3]);

    long seed = time(0);
    initRandom(seed);

    Graph g;
    cout << "Lendo arquivo " << inputFile << "..." << endl;
    g.readFromDIMACS(inputFile);
    cout << "Grafo: " << g.n << " vertices, " << g.m << " arestas." << endl;

    vector<int> solution;
    string params = "d=" + to_string(d);
    
    auto start = chrono::high_resolution_clock::now();

    if (algo == "guloso") {
        solution = greedyDefectiveColoring(g, d);
    } 
    else if (algo == "rand") {
        if (argc < 6) { cerr << "Faltam args: alpha iteracoes" << endl; return 1; }
        double alpha = stod(argv[4]);
        int iter = stoi(argv[5]);
        params += " alpha=" + to_string(alpha) + " iter=" + to_string(iter);

        int bestVal = 1e9;
        for(int i=0; i<iter; i++) {
            vector<int> temp = greedyRandomizedDefectiveColoring(g, d, alpha);
            int val = countColors(temp);
            if(val < bestVal) {
                bestVal = val;
                solution = temp;
            }
        }
    } 
    else if (algo == "reativo") {
        if (argc < 6) { cerr << "Faltam args: iteracoes block_size" << endl; return 1; }
        int iter = stoi(argv[4]);
        int block = stoi(argv[5]);
        params += " iter=" + to_string(iter) + " block=" + to_string(block);
        
        vector<double> alphas = {0.05, 0.10, 0.20, 0.30, 0.50, 0.75, 1.0};
        solution = greedyReactiveDefectiveColoring(g, d, alphas, iter, block);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    int coresUsadas = countColors(solution);
    cout << "----------------------------------" << endl;
    cout << "Resultado: " << coresUsadas << " cores." << endl;
    cout << "Tempo: " << duration.count() << "s" << endl;

    saveToCSV("outputs/resultados.csv", inputFile, algo, params, seed, duration.count(), coresUsadas);

    return 0;
}