#include "./include/defines.hpp"
#include "./include/graph.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada>" << endl;
        return 1;
    }

    string arquivoEntrada = argv[1];
    Graph g(arquivoEntrada);
    g.verifica_conexo();

    return 0;
}