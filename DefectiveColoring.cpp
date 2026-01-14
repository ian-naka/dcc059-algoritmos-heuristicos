#include "DefectiveColoring.h"
#include "Utils.h"
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

// --------------------------------------------------
// Função auxiliar: verifica se pintar v com 'color' viola o limite d
bool canAssignColor(int v, int color, const Graph& g, const std::vector<int>& colors, int d) {
    int defects = 0;
    for (int neighbor : g.adj[v]) {
        if (colors[neighbor] == color) {
            defects++;
            if (defects > d) return false;
        }
    }
    return true;
}

// --------------------------------------------------
// Guloso simples: ordenado por grau
std::vector<int> greedyDefectiveColoring(const Graph& g, int d) {
    vector<int> colors(g.n, -1);
    // Cria vetor de índices e ordena por grau (maior grau primeiro)
    vector<int> nodes(g.n);
    iota(nodes.begin(), nodes.end(), 0);
    
    sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return g.getDegree(a) > g.getDegree(b);
    });

    int maxColorUsed = 0;
    for (int v : nodes) {
        int c = 0;
        while (true) {
            if (canAssignColor(v, c, g, colors, d)) {
                colors[v] = c;
                if (c > maxColorUsed) maxColorUsed = c;
                break; 
            }
            c++;
        }
    }
    return colors;
}

// --------------------------------------------------
// Guloso randomizado: (GRASP com Alpha)
vector<int> greedyRandomizedDefectiveColoring(const Graph& g, int d, double alpha) {
    vector<int> colors(g.n, -1);
    vector<int> candidates(g.n);
    iota(candidates.begin(), candidates.end(), 0);

    while (!candidates.empty()) {
        // Ordena candidatos restantes pelo grau
        sort(candidates.begin(), candidates.end(), [&](int a, int b) {
            return g.getDegree(a) > g.getDegree(b);
        });

        // Define tamanho da Lista Restrita de Candidatos (RCL)
        int range = max(1, (int)(candidates.size() * alpha));

        // Sorteia dentro da RCL
        uniform_int_distribution<int> dist(0, range - 1);
        int idx = dist(rng);
        
        int v = candidates[idx];
        candidates.erase(candidates.begin() + idx);

        int c = 0;
        while (true) {
            if (canAssignColor(v, c, g, colors, d)) {
                colors[v] = c;
                break;
            }
            c++;
        }
    }
    return colors;
}

// --------------------------------------------------
// Guloso Randomizado Reativo: auto-ajuste
vector<int> greedyReactiveDefectiveColoring(
    const Graph& g, int d, 
    const vector<double>& alphas, 
    int iterations, 
    int blockSize
) {
    int m = alphas.size();
    vector<double> probabilities(m, 1.0 / m); 
    vector<double> sumSolutions(m, 0.0);      
    vector<int> countUsage(m, 0);             

    vector<int> bestSolution;
    int bestCost = numeric_limits<int>::max();

    for (int it = 1; it <= iterations; it++) {
        // Escolhe Alpha
        discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
        int idx = dist(rng);
        double alpha = alphas[idx];

        // Executa
        vector<int> sol = greedyRandomizedDefectiveColoring(g, d, alpha);
        int cost = countColors(sol); 

        // Atualiza melhor
        if (cost < bestCost) {
            bestCost = cost;
            bestSolution = sol;
        }

        // Estatísticas
        sumSolutions[idx] += cost;
        countUsage[idx]++;

        // Atualiza probabilidades no fim do bloco
        if (it % blockSize == 0) {
            double sumQ = 0.0;
            vector<double> q(m, 0.0);

            for(int i=0; i<m; i++) {
                if(countUsage[i] > 0) {
                    double avg = sumSolutions[i] / countUsage[i];
                    // Q = (Melhor / Média)^10
                    q[i] = pow((double)bestCost / avg, 10.0); 
                } else {
                    q[i] = 0.01; 
                }
                sumQ += q[i];
            }

            for(int i=0; i<m; i++) {
                probabilities[i] = q[i] / sumQ;
            }
        }
    }
    return bestSolution;
}
