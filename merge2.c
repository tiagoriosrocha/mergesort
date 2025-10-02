#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int *array, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Aloca vetores temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    // Copia dados para vetores temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Mescla os vetores temporários de volta em array[left..right]
    i = 0; // Índice inicial de L[]
    j = 0; // Índice inicial de R[]
    k = left; // Índice inicial do array final

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    // Libera memória temporária
    free(L);
    free(R);
}

void mergeSort(int *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena as duas metades
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        // Junta as metades ordenadas
        merge(array, left, mid, right);
    }
}

int main() {
    int n = 100000000;
    int *array = (int *)malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    // semente fixa: sempre a mesma sequência
    srand(42); 

    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }

    printf("Iniciando ordenação...\n");
    clock_t start = clock();

    mergeSort(array, 0, n - 1);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tamanho do vetor: %d\n", n);
    printf("Ordenação concluída em %.2f segundos.\n", time_spent);

    // Exibe os primeiros 10 elementos ordenados
    printf("Primeiros 20 elementos ordenados:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}

