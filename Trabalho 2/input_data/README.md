# Arquivos de Teste para Análise de Grafos

Este diretório contém diversos arquivos de teste para validar o algoritmo de verificação de conectividade em grafos.

## Formato dos Arquivos

Cada arquivo segue o formato:
```
[D|ND]                    // D = Direcionado, ND = Não Direcionado
<num_vertices> <num_arestas>
<rotulo_vertice_1>
<rotulo_vertice_2>
...
<rotulo_vertice_n>
<origem> <destino>        // Arestas
<origem> <destino>
...
```

## Casos de Teste

### Grafos Não Direcionados (ND)

1. **grafo_simples_conexo.txt** - Grafo triangular simples (conexo)
2. **grafo_desconexo.txt** - Grafo com 2 componentes desconexas
3. **grafo_duas_componentes.txt** - Grafo com triângulo + aresta isolada
4. **grafo_vertice_isolado.txt** - Grafo com apenas 1 vértice (trivialmente conexo)
5. **grafo_caminho_longo.txt** - Grafo em forma de caminho linear
6. **grafo_completo.txt** - Grafo completo K4
7. **grafo_estrela.txt** - Grafo em forma de estrela
8. **grafo_grande_conexo.txt** - Grafo maior (10 vértices) conexo
9. **grafo_tres_componentes.txt** - Grafo com 3 componentes separadas

### Grafos Não Direcionados - TESTE DE PERFORMANCE

10. **grafo_grande_50_vertices_caminho.txt** - Caminho com 50 vértices (conexo)
11. **grafo_muito_grande_100_vertices_conexo.txt** - Grafo denso com 100 vértices e 300 arestas (conexo)
12. **grafo_80_vertices_desconexo.txt** - 80 vértices em múltiplas componentes (desconexo)
13. **grafo_enorme_200_vertices_caminho.txt** - Caminho com 200 vértices (conexo)
14. **grafo_120_vertices_multiplas_componentes.txt** - 120 vértices em várias componentes (desconexo)

### Grafos Não Direcionados - TESTE EXTREMO DE PERFORMANCE

15. **grafo_mega_500_vertices_caminho.txt** - Caminho linear com 500 vértices (conexo)
16. **grafo_ultra_denso_300_vertices.txt** - Grafo completo com 300 vértices e 45.000 arestas (conexo)
17. **grafo_gigante_1000_vertices_desconexo.txt** - 1000 vértices com apenas 10 arestas (desconexo)
18. **grafo_extremo_800_vertices_arvore.txt** - Árvore com 800 vértices (conexo)

### Grafos Direcionados (D)

20. **grafo_direcionado_fortemente_conexo.txt** - Grafo fortemente conexo
21. **grafo_direcionado_caminho.txt** - Caminho direcionado (não fortemente conexo)
22. **grafo_direcionado_triangulo.txt** - Triângulo direcionado
23. **grafo_direcionado_complexo.txt** - Grafo direcionado mais complexo
24. **grafo_direcionado_dois_ciclos.txt** - Dois ciclos separados

### Grafos Direcionados - TESTE DE PERFORMANCE

25. **grafo_direcionado_30_vertices_denso.txt** - Grafo denso com 30 vértices e 120 arestas (conexo)
26. **grafo_direcionado_60_vertices_ciclos_conectados.txt** - 60 vértices em ciclos conectados (conexo)

### Grafos Direcionados - TESTE EXTREMO DE PERFORMANCE

27. **grafo_direcionado_400_vertices_denso.txt** - Grafo denso com 400 vértices e 3200 arestas (conexo)

## Resultados Esperados

### Conexos/Fortemente Conexos:
- grafo_simples_conexo.txt
- grafo_vertice_isolado.txt
- grafo_caminho_longo.txt
- grafo_completo.txt
- grafo_estrela.txt
- grafo_grande_conexo.txt
- **grafo_grande_50_vertices_caminho.txt**
- **grafo_muito_grande_100_vertices_conexo.txt**
- **grafo_enorme_200_vertices_caminho.txt**
- **grafo_mega_500_vertices_caminho.txt**
- **grafo_ultra_denso_300_vertices.txt**
- **grafo_extremo_800_vertices_arvore.txt**
- grafo_direcionado_fortemente_conexo.txt
- grafo_direcionado_complexo.txt
- **grafo_direcionado_30_vertices_denso.txt**
- **grafo_direcionado_60_vertices_ciclos_conectados.txt**
- **grafo_direcionado_400_vertices_denso.txt**

### Desconexos/Não Fortemente Conexos:
- grafo_desconexo.txt
- grafo_duas_componentes.txt
- grafo_tres_componentes.txt
- **grafo_80_vertices_desconexo.txt**
- **grafo_120_vertices_multiplas_componentes.txt**
- **grafo_gigante_1000_vertices_desconexo.txt**
- grafo_direcionado_caminho.txt
- grafo_direcionado_triangulo.txt
- grafo_direcionado_dois_ciclos.txt

## Como Testar

```bash
# Compilar o projeto
make clean all

# Roda todos os testes de uma vez
./exec_all.sh
```
