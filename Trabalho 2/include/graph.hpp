#pragma once
#include "defines.hpp"
#include "edge.hpp"
#include "vertex.hpp"

struct ResultadoAnalise {
    bool isConnected;
    long long duration_us;
};

class Graph
{
private:
    vector<Vertex> vertices; // Mapa de vértices, onde a chave é o rótulo do vértice
    size_t numEdges;         // Número de arestas no grafo
    size_t numVertices;      // Número de vértices no grafo
    bool directed;           // Indica se o grafo é direcionado ou não

public:
    // Construtor que inicializa o grafo a partir de um arquivo de entrada
    Graph(const string &filename);

    // Função para calcular o fecho transitivo do grafo
    ResultadoAnalise verifica_conexo();

    // Função para a IA
    ResultadoAnalise verifica_conexo_n_direcionado_ai();
    ResultadoAnalise verifica_conexo_direcionado_ai();

    size_t getNumVertices() const { return numVertices; }
    size_t getNumEdges() const { return numEdges; }
    bool isDirected() const { return directed; }

private:
    // Função auxiliar para realizar busca em profundidade (DFS)
    void dfs(const string &startLabel, const string &currentLabel, map<string, bool> &visited);
    void make_non_directed();
};
