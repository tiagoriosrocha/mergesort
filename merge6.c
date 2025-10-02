#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_THRESHOLDS 8

// Thresholds a testar
int thresholds[NUM_THRESHOLDS] = {-1, 1000, 100, 50, 25, 15, 10, 5}; // -1 significa "merge sort puro"

// Tamanhos dos vetores
#define NUM_SIZES 3
int sizes[NUM_SIZES] = {100000, 10000000, 100000000};

// Definição do tamanho mínimo de run para Timsort
#define RUN 32

// Prototipagem
void merge(int *array, int *temp, int left, int mid, int right);
void hybridSort(int *array, int *temp, int left, int right, int threshold);
void timsort(int *array, int *temp, int left, int right);
void insertionSort(int *array, int left, int right);
void mergeSort(int *array, int *temp, int left, int right);

// Insertion Sort para runs pequenas (usado dentro do Timsort)
void insertionSort(int *array, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= left && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// Merge com vetor temporário global
void merge(int *array, int *temp, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    for (int l = left; l <= right; l++)
        temp[l] = array[l];

    while (i <= mid && j <= right)
    {
        if (temp[i] <= temp[j])
            array[k++] = temp[i++];
        else
            array[k++] = temp[j++];
    }

    while (i <= mid)
        array[k++] = temp[i++];
    while (j <= right)
        array[k++] = temp[j++];
}

// Merge Sort puro
void mergeSort(int *array, int *temp, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(array, temp, left, mid);
        mergeSort(array, temp, mid + 1, right);
        merge(array, temp, left, mid, right);
    }
}

// Implementação simplificada do Timsort para subvetores
void timsort(int *array, int *temp, int left, int right)
{
    int n = right - left + 1;

    // Ordena blocos pequenos com insertion sort
    for (int i = left; i <= right; i += RUN)
    {
        insertionSort(array, i, (i + RUN - 1 < right) ? (i + RUN - 1) : right);
    }

    // Merge progressivo usando temp já alocado fora
    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int start = left; start <= right; start += 2 * size)
        {
            int mid = start + size - 1;
            int end = (start + 2 * size - 1 < right) ? (start + 2 * size - 1) : right;

            if (mid < end)
            {
                merge(array, temp, start, mid, end);
            }
        }
    }
}

// Hybrid Sort modificado: agora usa Timsort em vez de insertion
void hybridSort(int *array, int *temp, int left, int right, int threshold)
{
    if (right - left + 1 <= threshold)
    {
        timsort(array, temp, left, right);
    }
    else
    {
        int mid = left + (right - left) / 2;
        hybridSort(array, temp, left, mid, threshold);
        hybridSort(array, temp, mid + 1, right, threshold);
        merge(array, temp, left, mid, right);
    }
}

// Função para testar uma única estratégia
double test_sort(int *original, int n, int threshold)
{
    int *array = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));
    if (!array || !temp)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    memcpy(array, original, n * sizeof(int));

    clock_t start = clock();

    if (threshold == -1)
        mergeSort(array, temp, 0, n - 1); // Merge puro
    else
        hybridSort(array, temp, 0, n - 1, threshold); // Híbrido com Timsort

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    free(array);
    free(temp);

    return time_spent;
}

int main()
{
    srand(42); // Semente fixa

    printf("Tamanho\\Threshold");
    for (int i = 0; i < NUM_THRESHOLDS; i++)
    {
        if (thresholds[i] == -1)
            printf("\tMerge");
        else
            printf("\tHybrid(%d)", thresholds[i]);
    }
    printf("\n");

    for (int s = 0; s < NUM_SIZES; s++)
    {
        int n = sizes[s];
        printf("%d", n);

        // Gera vetor original uma vez
        int *original = malloc(n * sizeof(int));
        if (!original)
        {
            printf("Erro ao alocar vetor original\n");
            return 1;
        }

        for (int i = 0; i < n; i++)
        {
            original[i] = rand(); // Sempre a mesma sequência
        }

        for (int t = 0; t < NUM_THRESHOLDS; t++)
        {
            double time = test_sort(original, n, thresholds[t]);
            printf("\t%.2f", time);
        }

        printf("\n");
        free(original);
    }

    return 0;
}

// gcc -O2 -o hybrid_benchmark hybrid_benchmark.c
