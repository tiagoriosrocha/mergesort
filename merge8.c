#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Vetor temporário global
int *temp;

void merge(int *array, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    // Mescla diretamente no vetor temporário
    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
        {
            temp[k++] = array[i++];
        }
        else
        {
            temp[k++] = array[j++];
        }
    }

    // Copia os elementos restantes da primeira metade
    while (i <= mid)
    {
        temp[k++] = array[i++];
    }

    // Copia os elementos restantes da segunda metade
    while (j <= right)
    {
        temp[k++] = array[j++];
    }

    // Copia de volta para o vetor original
    for (i = left; i <= right; i++)
    {
        array[i] = temp[i];
    }
}

void mergeSort(int *array, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

int main()
{
    int n = 100000000;
    int *array = (int *)malloc(n * sizeof(int));
    temp = (int *)malloc(n * sizeof(int)); // aloca uma vez

    if (array == NULL || temp == NULL)
    {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    srand(42);
    for (int i = 0; i < n; i++)
    {
        array[i] = rand();
    }

    printf("Iniciando ordenação...\n");
    clock_t start = clock();

    mergeSort(array, 0, n - 1);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tamanho do vetor: %d\n", n);
    printf("Ordenação concluída em %.2f segundos.\n", time_spent);

    printf("Primeiros 20 elementos ordenados:\n");
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    free(temp);
    return 0;
}
