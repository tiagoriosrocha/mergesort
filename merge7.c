#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> // biblioteca OpenMP

void merge(int *array, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int *array, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

// Criamos duas tarefas paralelas
#pragma omp task shared(array) if (right - left > 10000) // threshold evita overhead
        mergeSort(array, left, mid);

#pragma omp task shared(array) if (right - left > 10000)
        mergeSort(array, mid + 1, right);

#pragma omp taskwait
        merge(array, left, mid, right);
    }
}

int main()
{
    int n = 100000000;
    int *array = (int *)malloc(n * sizeof(int));

    if (array == NULL)
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
    double start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        mergeSort(array, 0, n - 1);
    }

    double end = omp_get_wtime();
    double time_spent = end - start;

    printf("Tamanho do vetor: %d\n", n);
    printf("Ordenação concluída em %.2f segundos.\n", time_spent);

    printf("Primeiros 20 elementos ordenados:\n");
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}

// gcc -fopenmp merge7.c -o mergesort_omp
// OMP_NUM_THREADS=4 ./mergesort_omp