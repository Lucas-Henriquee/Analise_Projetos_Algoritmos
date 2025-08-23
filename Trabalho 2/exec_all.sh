#!/bin/bash

mkdir -p output
> output/resultados.txt  # Limpa o arquivo de resultados

for arquivo in input_data/*.txt; do
    echo "$(basename "$arquivo"):" >> output/resultados.txt
    ./apa "$arquivo" >> output/resultados.txt 2>&1
    echo "" >> output/resultados.txt
done

echo "Resultados salvos em output/resultados.txt"