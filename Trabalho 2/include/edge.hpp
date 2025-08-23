#pragma once
#include "defines.hpp"

class Edge {
   private:
    string destination;  // Rótulo do vértice de destino

   public:
    // Construtor que inicializa a aresta com o rótulo do vértice de destino e o peso
    Edge(const string &dest) : destination(dest){}

    // Função para obter o rótulo do vértice de destino
    string getDestination() const {
        return destination;
    }
};