#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main() {
    const char *input_filename = "resultados_parciais/merge-insertion-summary_results.csv";
    const char *output_filename = "resultados_parciais/best_merge_results.csv";

    FILE *in_file = fopen(input_filename, "r");
    if (in_file == NULL) {
        perror("Erro ao abrir o arquivo de entrada (merge-insertion-summary_results.csv)");
        return EXIT_FAILURE;
    }

    FILE *out_file = fopen(output_filename, "w");
    if (out_file == NULL) {
        perror("Erro ao criar o arquivo de saída");
        fclose(in_file);
        return EXIT_FAILURE;
    }

    char line_buffer[MAX_LINE_LEN];

    // 1. Ler e pular a linha do cabeçalho
    if (fgets(line_buffer, MAX_LINE_LEN, in_file) == NULL) {
        fprintf(stderr, "Arquivo de entrada vazio ou erro de leitura\n");
        fclose(in_file);
        fclose(out_file);
        return EXIT_FAILURE;
    }
    
    // 2. Escrever o novo cabeçalho no arquivo de saída
    fprintf(out_file, "Tamanho,Threshold,MediaCPU,DesvioCPU,MediaReal,DesvioReal,Algoritmo\n");

    // 3. Processar cada linha de dados
    while (fgets(line_buffer, MAX_LINE_LEN, in_file)) {
        
        // Copia a linha para análise, pois strtok modifica a string
        char line_copy[MAX_LINE_LEN];
        strcpy(line_copy, line_buffer);
        
        // Remove o caractere de nova linha (\n) do final, se existir
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        char *token;
        long tamanho;
        int threshold;

        // Parse (análise) apenas das duas primeiras colunas para verificar
        token = strtok(line_copy, ",");
        if (token == NULL) continue; // Linha mal formatada
        tamanho = atol(token);
        
        token = strtok(NULL, ",");
        if (token == NULL) continue; // Linha mal formatada
        threshold = atoi(token);

        // 4. LÓGICA PRINCIPAL: Filtrar
        if (threshold == -1) {
            // Encontramos uma linha do Merge Puro.
            // Escreve a linha original (com \n) e adiciona ",Merge"
            fprintf(out_file, "%s,Merge\n", line_buffer);
        }
        // Se threshold != -1, a linha é simplesmente ignorada
    }

    // 5. Fechar os arquivos
    fclose(in_file);
    fclose(out_file);

    printf("Arquivo '%s' gerado com sucesso!\n", output_filename);

    return EXIT_SUCCESS;
}