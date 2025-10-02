#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THRESHOLD 1000  // Limite para trocar para bubble sort

// Função Bubble Sort
void bubbleSort(int array[], int left, int right) {
    for (int i = left; i <= right; i++) {
        for (int j = left; j < right - (i - left); j++) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

// Função Merge
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Erro ao alocar memória temporária.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1)
        array[k++] = L[i++];
    while (j < n2)
        array[k++] = R[j++];

    free(L);
    free(R);
}

// Merge Sort com troca para Bubble Sort
void hybridSort(int array[], int left, int right) {
    int size = right - left + 1;
    if (size <= THRESHOLD) {
        bubbleSort(array, left, right);
    } else {
        int mid = left + (right - left) / 2;
        hybridSort(array, left, mid);
        hybridSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

int main() {
    int n = 100000000;
    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    srand(42);  // Garante a mesma sequência em todas as execuções

    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }

    printf("Iniciando ordenação híbrida...\n");
    clock_t start = clock();

    hybridSort(array, 0, n - 1);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tamanho do vetor: %d\n", n);
    printf("Ordenação concluída em %.2f segundos.\n", time_spent);

    printf("Primeiros 20 elementos ordenados:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}

//100 mil
// | Nível | Sub-vetores | Tamanho de cada um (aproximado) |
// | ----- | ----------- | ------------------------------- |
// | 0     | 1           | 100,000                         |
// | 1     | 2           | 50,000                          |
// | 2     | 4           | 25,000                          |
// | 3     | 8           | 12,500                          |
// | 4     | 16          | 6,250                           |
// | 5     | 32          | 3,125                           |
// | 6     | 64          | 1,562                           |
// | 7     | 128         | 781                             |
// | 8     | 256         | 391                             |
// | 9     | 512         | 195                             |
// | 10    | 1,024       | 97                              |
// | 11    | 2,048       | 48                              |
// | 12    | 4,096       | 24                              |
// | 13    | 8,192       | 12                              |
// | 14    | 16,384      | 6                               |
// | 15    | 32,768      | 3                               |
// | 16    | 65,536      | 1–2                             |
// | 17    | ~100,000    | 1                               |


// 10 milhões
// | Nível | Sub-vetores | Tamanho de cada um |
// | ----- | ----------- | ------------------ |
// | 0     | 1           | 10,000,000         |
// | 1     | 2           | 5,000,000          |
// | 2     | 4           | 2,500,000          |
// | 3     | 8           | 1,250,000          |
// | 4     | 16          | 625,000            |
// | 5     | 32          | 312,500            |
// | 6     | 64          | 156,250            |
// | 7     | 128         | 78,125             |
// | 8     | 256         | 39,062             |
// | 9     | 512         | 19,531             |
// | 10    | 1,024       | 9,765              |
// | 11    | 2,048       | 4,882              |
// | 12    | 4,096       | 2,441              |
// | 13    | 8,192       | 1,220              |
// | 14    | 16,384      | 610                |
// | 15    | 32,768      | 305                |
// | 16    | 65,536      | 152                |
// | 17    | 131,072     | 76                 |
// | 18    | 262,144     | 38                 |
// | 19    | 524,288     | 19                 |
// | 20    | 1,048,576   | 9                  |
// | 21    | 2,097,152   | 4–5                |
// | 22    | 4,194,304   | 2–3                |
// | 23    | 8,388,608   | 1–2                |
// | 24    | ~10,000,000 | 1                  |


// 100 milhões
// | Nível | Sub-vetores  | Tamanho de cada sub-vetor |
// | ----- | ------------ | ------------------------- |
// | 0     | 1            | 100,000,000               |
// | 1     | 2            | 50,000,000                |
// | 2     | 4            | 25,000,000                |
// | 3     | 8            | 12,500,000                |
// | 4     | 16           | 6,250,000                 |
// | 5     | 32           | 3,125,000                 |
// | 6     | 64           | 1,562,500                 |
// | 7     | 128          | 781,250                   |
// | 8     | 256          | 390,625                   |
// | 9     | 512          | 195,312                   |
// | 10    | 1,024        | 97,656                    |
// | 11    | 2,048        | 48,828                    |
// | 12    | 4,096        | 24,414                    |
// | 13    | 8,192        | 12,207                    |
// | 14    | 16,384       | 6,104                     |
// | 15    | 32,768       | 3,052                     |
// | 16    | 65,536       | 1,526                     |
// | 17    | 131,072      | 763                       |
// | 18    | 262,144      | 381                       |
// | 19    | 524,288      | 190                       |
// | 20    | 1,048,576    | 95                        |
// | 21    | 2,097,152    | 47                        |
// | 22    | 4,194,304    | 23                        |
// | 23    | 8,388,608    | 11                        |
// | 24    | 16,777,216   | 5–6                       |
// | 25    | 33,554,432   | 2–3                       |
// | 26    | 67,108,864   | 1–2                       |
// | 27    | ~100,000,000 | 1                         |


// 1 bilhão
// | Nível | Quantidade de Sub-vetores | Tamanho de Cada Sub-vetor |
// | ----- | ------------------------- | ------------------------- |
// | 0     | 1                         | 1_000_000_000             |
// | 1     | 2                         | 500_000_000               |
// | 2     | 4                         | 250_000_000               |
// | 3     | 8                         | 125_000_000               |
// | 4     | 16                        | 62_500_000                |
// | 5     | 32                        | 31_250_000                |
// | 6     | 64                        | 15_625_000                |
// | 7     | 128                       | 7_812_500                 |
// | 8     | 256                       | 3_906_250                 |
// | 9     | 512                       | 1_953_125                 |
// | 10    | 1024                      | 976_562                   |
// | 11    | 2048                      | 488_281                   |
// | 12    | 4096                      | 244_140                   |
// | 13    | 8192                      | 122_070                   |
// | 14    | 16_384                    | 61_035                    |
// | 15    | 32_768                    | 30_517                    |
// | 16    | 65_536                    | 15_258                    |
// | 17    | 131_072                   | 7_629                     |
// | 18    | 262_144                   | 3_814                     |
// | 19    | 524_288                   | 1_907                     |
// | 20    | 1_048_576                 | 953                       |
// | 21    | 2_097_152                 | 476                       |
// | 22    | 4_194_304                 | 238                       |
// | 23    | 8_388_608                 | 119                       |
// | 24    | 16_777_216                | 59                        |
// | 25    | 33_554_432                | 29                        |
// | 26    | 67_108_864                | 14                        |
// | 27    | 134_217_728               | 7                         |
// | 28    | 268_435_456               | 3                         |
// | 29    | 536_870_912               | 1–2                       |
// | 30    | 1_073_741_824             | 1                         |