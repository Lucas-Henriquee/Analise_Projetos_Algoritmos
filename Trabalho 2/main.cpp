#include "./include/defines.hpp"
#include "./include/graph.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        cerr << "Uso normal: " << argv[0] << " <arquivo_entrada>" << endl;
        cerr << "Uso para CSV: " << argv[0] << " <arquivo_entrada> --csv" << endl;
        return 1;
    }
    
    string arquivoEntrada = argv[1];
    bool modo_csv = (argc == 3 && string(argv[2]) == "--csv");

    Graph g(arquivoEntrada);

    ResultadoAnalise resultado_manual = g.verifica_conexo();
    ResultadoAnalise resultado_ia_direcionado = g.verifica_conexo_ai_direcionado();
    ResultadoAnalise resultado_ia_nao_direcionado = g.verifica_conexo_ai_nao_direcionado();


    if (modo_csv)
    {
        size_t posBarra = arquivoEntrada.find_last_of("/\\");
        string nomeComExt = (posBarra == string::npos) ? arquivoEntrada : arquivoEntrada.substr(posBarra + 1);
        size_t posPonto = nomeComExt.find_last_of(".");
        string nomeLimpo = (posPonto == string::npos) ? nomeComExt : nomeComExt.substr(0, posPonto);

        cout << nomeLimpo << ","
             << g.getNumVertices() << "," << g.getNumEdges() << ","
             << (g.isDirected() ? "1" : "0") << ","
             << (resultado_manual.isConnected ? "1" : "0") << ","
             << resultado_manual.duration_us << ",Manual" << endl;

        cout << nomeLimpo << ","
             << g.getNumVertices() << "," << g.getNumEdges() << ","
             << (g.isDirected() ? "1" : "0") << ","
             << (resultado_ia.isConnected ? "1" : "0") << ","
             << resultado_ia.duration_us << ",IA" << endl;
    }
    else
    {
        cout << "--- Análise para o arquivo: " << arquivoEntrada << " ---" << endl;
        cout << "  - Vértices: " << g.getNumVertices() << ", Arestas: " << g.getNumEdges() << endl;
        cout << "----------------------------------------" << endl;
        cout << "Algoritmo Manual:" << endl;
        cout << "  - Status: " << (resultado_manual.isConnected ? "Conexo" : "Desconexo") << endl;
        cout << "  - Tempo: " << resultado_manual.duration_us << " us" << endl;
        
        cout << "\nAlgoritmo da IA não Direcionado:" << endl;
        cout << "  - Status: " << (resultado_ia_nao_direcionado.isConnected ? "Conexo" : "Desconexo") << endl;
        cout << "  - Tempo: " << resultado_ia_nao_direcionado.duration_us << " us" << endl;

        cout << "\nAlgoritmo da IA Direcionado:" << endl;
        cout << "  - Status: " << (resultado_ia_direcionado.isConnected ? "Conexo" : "Desconexo") << endl;
        cout << "  - Tempo: " << resultado_ia_direcionado.duration_us << " us" << endl;
    }

    return 0;
}