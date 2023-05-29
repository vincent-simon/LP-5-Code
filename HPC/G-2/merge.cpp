#include <iostream>
#include <cstdlib>
#include <omp.h>

void mergesort_seq(int[], int, int);
void mergesort_parallel(int[], int, int);
void merge(int[], int, int, int, int);

void mergesort_seq(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
        mergesort_seq(a, i, mid);
        mergesort_seq(a, mid + 1, j);
        merge(a, i, mid, mid + 1, j);
    }
}

void mergesort_parallel(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                mergesort_parallel(a, i, mid);
            }

#pragma omp section
            {
                mergesort_parallel(a, mid + 1, j);
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[1000];
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;

    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= j1)
    {
        temp[k++] = a[i++];
    }

    while (j <= j2)
    {
        temp[k++] = a[j++];
    }

    for (i = i1, j = 0; i <= j2; i++, j++)
    {
        a[i] = temp[j];
    }
}

int main()
{
    int *a, *b, n, i;
    double start_time, end_time, seq_time, par_time;

    std::cout << "\n enter total no of elements => ";
    std::cin >> n;

    a = new int[n];
    b = new int[n];

    std::cout << "\n enter elements => ";
    for (i = 0; i < n; i++)
    {
        std::cin >> a[i];
        b[i] = a[i]; // Copying elements to b
    }

    // Sequential algorithm
    start_time = omp_get_wtime();
    mergesort_seq(a, 0, n - 1);
    end_time = omp_get_wtime();
    seq_time = end_time - start_time;
    std::cout << "\nSequential Time: " << seq_time << " seconds" << std::endl;

    // Parallel algorithm
    start_time = omp_get_wtime();
    mergesort_parallel(b, 0, n - 1);
    end_time = omp_get_wtime();
    par_time = end_time - start_time;
    std::cout << "\nParallel Time: " << par_time << " seconds" << std::endl;
    
    std::cout << "\nSorted array (sequential) => ";
    for (i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }

    std::cout << "\nSorted array (parallel) => ";
    for (i = 0; i < n; i++)
    {
        std::cout << b[i] << " ";
    }

    std::cout << std::endl;

    delete[] a;
    delete[] b;

    return 0;
}

/*
Command to run: 
g++ merge.cpp -lgomp -o test
./test

Input: 
9
2 6 5 4 8 9 1 3 5
Output: 1 2 3 4 5 6 7 8 9*/