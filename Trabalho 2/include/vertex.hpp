#pragma once
#include "defines.hpp"
#include "edge.hpp"

class Vertex {
   private:
    string label;              // Rótulo do vértice
    vector<Edge> edges;        // Lista de arestas conectadas ao vértice

   public:
    // Construtor que inicializa o vértice com um rótulo
    Vertex(const string &label) : label(label) {}

    // Função para adicionar uma aresta ao vértice
    void addEdge(const Edge &edge) {
        edges.push_back(edge);
    }

    // Função para obter o rótulo do vértice
    string getLabel() const {
        return label;
    }

    // Função para obter a lista de arestas do vértice
    const vector<Edge>& getEdges() const {
        return edges;
    }
};