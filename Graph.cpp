#include "Graph.h"

using namespace std;

Graph::Graph(int n) : n(n), adj(n) {}

void Graph::addEdge(int u, int v) {
    if(u >= n || v >=n){ // redimensiona caso o vértice lido for maior que o tamanho atual;
        int max_v = max(u, v);
        adj.resize(max_v + 1);
        n = max_v + 1;
    }
    adj[u].push_back(v);
    adj[v].push_back(u);
    m++;
}


int Graph::getDegree(int v) const {
    if(v >= 0 && v < n) return adj[v].size();
    return 0;
}

void Graph::readFromDIMACS(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Não foi possível abrir o arquivo." << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == 'c') continue; // Ignora linhas vazias ou comentários
        stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'p') { // Linha de definição: p edge V E
            string format;
            int numV, numE;
            ss >> format >> numV >> numE;
            this->n = numV;
            this->m = 0;
            this->adj.assign(numV, vector<int>());
        } 
        else if (type == 'e') { // Linha de aresta: e u v
            int u, v;
            ss >> u >> v;
            addEdge(u - 1, v - 1); // Arquivos DIMACS começam em 1, convertemos para 0
        }
    }
    file.close();
}