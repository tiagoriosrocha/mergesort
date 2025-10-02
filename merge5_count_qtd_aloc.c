#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THRESHOLDS 8

// Thresholds a testar
int thresholds[NUM_THRESHOLDS] = {-1, 1000, 100, 50, 25, 15, 10, 5};

// Tamanhos dos vetores
#define NUM_SIZES 3
int sizes[NUM_SIZES] = {100000, 10000000, 100000000};

// Contador global de movimentações
long long moves = 0;

// Prototipagem
void merge(int *array, int *temp, int left, int mid, int right);
void hybridSort(int *array, int *temp, int left, int right, int threshold);
void insertionSort(int *array, int left, int right);
void mergeSort(int *array, int *temp, int left, int right);

// Insertion Sort para subvetores pequenos com contagem de movimentações
void insertionSort(int *array, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = array[i];
        moves++; // leitura da key
        int j = i - 1;
        while (j >= left && array[j] > key)
        {
            array[j + 1] = array[j];
            moves++; // deslocamento de elemento
            j--;
        }
        array[j + 1] = key;
        moves++; // escrita da key
    }
}

// Merge com vetor temporário global, contando movimentações
void merge(int *array, int *temp, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;

    // Copia para temp (ida)
    for (int l = left; l <= right; l++)
    {
        temp[l] = array[l];
        moves++;
    }

    // Merge (volta)
    while (i <= mid && j <= right)
    {
        if (temp[i] <= temp[j])
            array[k++] = temp[i++];
        else
            array[k++] = temp[j++];
        moves++; // escrita no array
    }

    while (i <= mid)
        array[k++] = temp[i++];
    moves++;

    while (j <= right)
        array[k++] = temp[j++];
    moves++;
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

// Merge Sort híbrido com insertion para sub-vetores pequenos
void hybridSort(int *array, int *temp, int left, int right, int threshold)
{
    if (right - left + 1 <= threshold)
    {
        insertionSort(array, left, right);
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
long long test_sort(int *original, int n, int threshold)
{
    moves = 0;
    int *array = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));
    if (!array || !temp)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    memcpy(array, original, n * sizeof(int));
    moves += n; // inicialização do array

    if (threshold == -1)
        mergeSort(array, temp, 0, n - 1);
    else
        hybridSort(array, temp, 0, n - 1, threshold);

    free(array);
    free(temp);

    return moves;
}

int main()
{
    srand(42);

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

        int *original = malloc(n * sizeof(int));
        if (!original)
        {
            printf("Erro ao alocar vetor original\n");
            return 1;
        }

        for (int i = 0; i < n; i++)
            original[i] = rand();

        for (int t = 0; t < NUM_THRESHOLDS; t++)
        {
            long long mv = test_sort(original, n, thresholds[t]);
            printf("\t%lld", mv);
        }

        printf("\n");
        free(original);
    }

    return 0;
}