## streamlit-mergesort

Repositório com implementações e benchmarks de variações do Merge Sort e híbridos (Merge + Insertion / Merge + Bubble), além de ferramentas de medição (tempo CPU/real, contagem de instruções, memória e quantidade de cópias). Contém também scripts para processar os resultados e notebooks de análise.

## Visão geral

O objetivo deste projeto é comparar diferentes variações de Merge Sort (puro e híbridos que usam Insertion ou Bubble para subvetores pequenos), medir desempenho em diferentes tamanhos e limites (thresholds), e gerar arquivos CSV para análise posterior.

As medições incluem:
- Tempo CPU e tempo real (wall-clock)
- Contagem de comparações / instruções (quando aplicável)
- Contagem de movimentações (quantidade de cópias para o vetor temporário)
- Medição de memória alocada

## Estrutura do repositório

- `merge1.c`, `merge2.c`, `merge3.c`, `merge4.c`, `merge5.c`, `merge6.c`, `merge7.c`, `merge8.c` — implementações/experimentos com diferentes variações (ex.: hybrid com bubble ou insertion, timsort, OpenMP, vetor global).
- `merge4_final.c`, `merge5_final.c` — programas de benchmark que geram CSVs (execuções repetidas, médias e desvios).
- `merge4_count_instructions.c`, `merge5_count_instructions.c` — versões que contam instruções/comparações.
- `merge4_count_memory.c` — medição de memória alocada.
- `merge4_count_qtd_aloc.c`, `merge5_count_qtd_aloc.c` — medem a quantidade de cópias/alocações de dados entre vetor original e temporário.
- `execmerge4`, `execmerge5` etc — arquivos binários de exemplo (se presentes).
- `process_best_merge_results.c`, `process_best_mergebubble_results.c`, `process_best_mergeinsertion_results.c` — scripts para processar arquivos de saída e produzir resumos (por exemplo, selecionar melhor algoritmo para cada tamanho).
- `analises/` — notebooks Jupyter e CSVs usados para análise e visualização.
- `resultados_parciais/` — CSVs com resultados parciais e resumos utilizados nas análises.

## Como compilar

Recomenda-se compilar com otimizações (-O2) e, quando necessário, link com `-lm`. Exemplos:

```bash
# Merge + Bubble (exemplo):
gcc -O2 -o execmerge4 merge4_final.c -lm

# Merge + Insertion (exemplo):
gcc -O2 -o execmerge5 merge5_final.c -lm

# Versões que usam OpenMP (se aplicável):
gcc -O2 -fopenmp -o execmerge7 merge7.c -lm
```

Alguns arquivos de exemplo contêm comentários com o comando de compilação recomendado no final do código.

Observação: os testes com vetores muito grandes exigem muita memória (por exemplo, n = 3e8 inteiros ~ >1GB). Garanta memória suficiente antes de executar testes grandes.

## Como executar

Os programas de benchmark normalmente geram arquivos CSV na pasta do projeto. Exemplos de saída esperada (conforme os fontes):

- `merge-bubble-raw_times.csv` e `merge-bubble-summary_results.csv` (gerados por `merge4_final.c` / versão bubble)
- `merge-insertion-raw_times.csv` e `merge-insertion-summary_results.csv` (gerados por `merge5_final.c` / versão insertion)

Exemplo de uso (após compilar `execmerge4`):

```bash
./execmerge4
# gera: merge-bubble-raw_times.csv e merge-bubble-summary_results.csv
```

Os arquivos de saída CSV possuem colunas como `Tamanho,Threshold,Execucao,TempoCPU,TempoReal` (raw) e resumos com médias e desvios. Consulte os fontes (`merge4_final.c` e `merge5_final.c`) para detalhes sobre nomes e formato.

## Processamento de resultados

Há programas C para processar os CSVs gerados e selecionar os melhores resultados por tamanho. Exemplo:

```bash
gcc -O2 -o process_best_merge_results process_best_merge_results.c
./process_best_merge_results
# Lê: resultados_parciais/merge-insertion-summary_results.csv
# Gera: resultados_parciais/best_merge_results.csv
```

Os notebooks em `analises/` usam esses CSVs para gerar gráficos e realizar comparações detalhadas.

## Observações importantes

- Muitos dos benchmarks usam `srand(42)` para garantir repetibilidade (mesma sequência pseudoaleatória).

## Reproduzindo as análises

1. Compile os programas de benchmark (`merge4_final.c`, `merge5_final.c`, etc.).
2. Execute-os em uma máquina com memória suficiente. Atenção ao tempo de execução para n muito grandes.
3. Use os `raw` e `summary` CSVs gerados como entrada para os scripts em `process*` ou abra os notebooks em `analises/`.

<!-- README gerado automaticamente a partir de readme.txt e análise dos fontes -->
