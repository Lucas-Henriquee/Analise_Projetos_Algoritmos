#!/bin/bash

INPUT_DIR="input_data"
OUTPUT_FILE="output/results.csv"
EXECUTABLE="./apa"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Erro: Executável '$EXECUTABLE' não encontrado. Compile o projeto primeiro."
    exit 1
fi

echo "filename,num_vertices,num_edges,is_directed,is_connected,execution_time_us,versao_algoritmo" > $OUTPUT_FILE

for arquivo in $INPUT_DIR/*.txt; do
    echo "Processando: $arquivo"
    "$EXECUTABLE" "$arquivo" --csv >> $OUTPUT_FILE
done

echo "Análise concluída. Resultados salvos em $OUTPUT_FILE"