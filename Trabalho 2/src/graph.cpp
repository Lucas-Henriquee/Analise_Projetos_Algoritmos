#include "../include/graph.hpp"
#include "../include/defines.hpp"

Graph::Graph(const string &filename) : numEdges(0), numVertices(0), directed(false)
{
    ifstream inputFile(filename.c_str());
    if (!inputFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    // Lê a primeira linha para determinar se o grafo é direcionado ou não
    if (getline(inputFile, line))
    {
        if (line == "D")
        {
            directed = true;
        }
        else if (line == "ND")
        {
            directed = false;
        }
        else
        {
            cerr << "Formato inválido na primeira linha do arquivo." << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << "Arquivo vazio ou formato inválido." << endl;
        exit(EXIT_FAILURE);
    }

    if (getline(inputFile, line))
    {
        istringstream iss(line);
        if (!(iss >> numVertices >> numEdges))
        {
            cerr << "Formato inválido na segunda linha do arquivo." << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << "Arquivo incompleto ou formato inválido." << endl;
        exit(EXIT_FAILURE);
    }

    // Lê os vértices do arquivo
    for (size_t i = 0; i < numVertices; ++i)
    {
        if (getline(inputFile, line))
        {
            istringstream iss(line);
            string label;
            if (iss >> label)
            {
                vertices.push_back(Vertex(label));
            }
            else
            {
                cerr << "Formato inválido ao ler vértices." << endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cerr << "Número insuficiente de vértices no arquivo." << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Lê as arestas do arquivo
    for (size_t i = 0; i < numEdges; ++i)
    {
        if (getline(inputFile, line))
        {
            istringstream iss(line);
            string fromLabel, toLabel;
            if (iss >> fromLabel >> toLabel)
            {
                Edge edge(toLabel);
                bool fromFound = false;
                for (size_t j = 0; j < vertices.size(); ++j)
                {
                    if (vertices[j].getLabel() == fromLabel)
                    {
                        vertices[j].addEdge(edge);
                        fromFound = true;
                        break;
                    }
                }
                if (!fromFound)
                {
                    cerr << "Vértice de origem não encontrado: " << fromLabel << endl;
                    exit(EXIT_FAILURE);
                }
                if (!directed)
                {
                    Edge reverseEdge(fromLabel);
                    bool toFound = false;
                    for (size_t j = 0; j < vertices.size(); ++j)
                    {
                        if (vertices[j].getLabel() == toLabel)
                        {
                            vertices[j].addEdge(reverseEdge);
                            toFound = true;
                            break;
                        }
                    }
                    if (!toFound)
                    {
                        cerr << "Vértice de destino não encontrado: " << toLabel << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else
            {
                cerr << "Formato inválido ao ler arestas." << endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cerr << "Número insuficiente de arestas no arquivo." << endl;
            exit(EXIT_FAILURE);
        }
    }
    inputFile.close();
}

void Graph::dfs(const string &startLabel, const string &currentLabel, map<string, bool> &visited)
{
    visited[currentLabel] = true;

    const Vertex *currentVertex = NULL;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i].getLabel() == currentLabel)
        {
            currentVertex = &vertices[i];
            break;
        }
    }
    if (!currentVertex)
        return;

    const vector<Edge> &edges = currentVertex->getEdges();
    for (size_t i = 0; i < edges.size(); ++i)
    {
        const string &neighborLabel = edges[i].getDestination();
        if (!visited[neighborLabel])
        {
            dfs(startLabel, neighborLabel, visited);
        }
    }
}

void Graph::make_non_directed()
{
    directed = false;
    // Adiciona arestas reversas para cada aresta existente
    vector<Edge> newEdges;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        const vector<Edge> &edges = vertices[i].getEdges();
        for (size_t j = 0; j < edges.size(); ++j)
        {
            const string &toLabel = edges[j].getDestination();
            bool toFound = false;
            for (size_t k = 0; k < vertices.size(); ++k)
            {
                if (vertices[k].getLabel() == toLabel)
                {
                    // Verifica se a aresta reversa já existe
                    const vector<Edge> &toEdges = vertices[k].getEdges();
                    bool reverseExists = false;
                    for (size_t l = 0; l < toEdges.size(); ++l)
                    {
                        if (toEdges[l].getDestination() == vertices[i].getLabel())
                        {
                            reverseExists = true;
                            break;
                        }
                    }
                    if (!reverseExists)
                    {
                        Edge reverseEdge(vertices[i].getLabel());
                        vertices[k].addEdge(reverseEdge);
                    }
                    toFound = true;
                    break;
                }
            }
            if (!toFound)
            {
                cerr << "Vértice de destino não encontrado ao tornar o grafo direcionado: " << toLabel << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

ResultadoAnalise Graph::verifica_conexo()
{
    auto start = chrono::high_resolution_clock::now();
    map<string, bool> visited;

    bool isConnected;

    bool estadoOriginalDirected = directed;

    for (size_t j = 0; j < vertices.size(); ++j)
    {
        visited[vertices[j].getLabel()] = false;
    }

    if (!vertices.empty())
    {

        Vertex originalVertex = vertices[0];
        if (directed)
        {
            make_non_directed();
        }

        dfs(originalVertex.getLabel(), originalVertex.getLabel(), visited);

        isConnected = true;

        for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it)
        {
            if (!it->second)
            {
                isConnected = false;
                break;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    directed = estadoOriginalDirected;

    return {isConnected, duration};
}

ResultadoAnalise Graph::verifica_conexo_nao_direcionado_ai()
{

    auto start = chrono::high_resolution_clock::now();

    // Considera o grafo como não direcionado para a verificação
    bool estadoOriginalDirected = directed;

    map<string, bool> visited;
    for (size_t j = 0; j < vertices.size(); ++j)
    {
        visited[vertices[j].getLabel()] = false;
    }

    bool ai_isConnected = true; // Por convenção, grafo vazio é conexo

    if (!vertices.empty())
    {
        if (directed)
        {
            make_non_directed();
        }

        const string &startLabel = vertices[0].getLabel();
        dfs(startLabel, startLabel, visited);

        for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it)
        {
            if (!it->second)
            {
                ai_isConnected = false;
                break;
            }
        }
    }

    // Restaura o estado original de direcionamento
    directed = estadoOriginalDirected;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    return {ai_isConnected, duration};
}

ResultadoAnalise Graph::verifica_conexo_direcionado_ai()
{
    auto start = chrono::high_resolution_clock::now();

    bool ai_isConnected = true; // Por convenção, grafo vazio é considerado fortemente conexo

    if (!vertices.empty())
    {
        // 1) DFS normal a partir de um vértice arbitrário
        map<string, bool> visited;
        for (size_t j = 0; j < vertices.size(); ++j)
        {
            visited[vertices[j].getLabel()] = false;
        }

        const string &startLabel = vertices[0].getLabel();
        dfs(startLabel, startLabel, visited);

        for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it)
        {
            if (!it->second)
            {
                ai_isConnected = false;
                break;
            }
        }

        // 2) Se passou no primeiro, faz DFS no grafo transposto (arestas reversas)
        if (ai_isConnected)
        {
            map<string, vector<string> > reverseAdj;
            for (size_t i = 0; i < vertices.size(); ++i)
            {
                reverseAdj[vertices[i].getLabel()] = vector<string>();
            }
            for (size_t i = 0; i < vertices.size(); ++i)
            {
                const string &u = vertices[i].getLabel();
                const vector<Edge> &edges = vertices[i].getEdges();
                for (size_t k = 0; k < edges.size(); ++k)
                {
                    const string &v = edges[k].getDestination();
                    reverseAdj[v].push_back(u);
                }
            }

            for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it)
            {
                it->second = false;
            }

            // DFS iterativo usando pilha sobre o grafo transposto
            stack<string> stackLabels;
            stackLabels.push(startLabel);
            while (!stackLabels.empty())
            {
                string u = stackLabels.top();
                stackLabels.pop();

                if (visited[u])
                    continue;

                visited[u] = true;

                const vector<string> &preds = reverseAdj[u];
                for (size_t i = 0; i < preds.size(); ++i)
                {
                    const string &p = preds[i];
                    if (!visited[p])
                    {
                        stackLabels.push(p);
                    }
                }
            }

            for (map<string, bool>::iterator it = visited.begin(); it != visited.end(); ++it)
            {
                if (!it->second)
                {
                    ai_isConnected = false;
                    break;
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    return {ai_isConnected, duration};
}