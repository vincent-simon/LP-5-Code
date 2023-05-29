#include <iostream>
#include <cstdlib>
#include <omp.h>

void bubble_seq(int *, int);
void bubble_parallel(int *, int);
void swap(int &, int &);

void bubble_seq(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

void bubble_parallel(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
#pragma omp parallel for shared(a)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}

int main()
{
    int *a, *b, n;
    std::cout << "\n enter total number of elements => ";
    std::cin >> n;

    a = new int[n];
    b = new int[n];

    std::cout << "\n enter elements => ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        b[i] = a[i]; // Copying elements to b
    }

    double start_time = omp_get_wtime(); // Start timer for sequential algorithm
    bubble_seq(a, n);
    double end_time = omp_get_wtime(); // End timer for sequential algorithm

    std::cout << "\n sorted array (sequential) => ";
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }

    std::cout << "\n Time taken by sequential algorithm: " << end_time - start_time << " seconds" << std::endl;

    start_time = omp_get_wtime(); // Start timer for parallel algorithm
    bubble_parallel(b, n);
    end_time = omp_get_wtime(); // End timer for parallel algorithm

    std::cout << "\n sorted array (parallel) => ";
    for (int i = 0; i < n; i++)
    {
        std::cout << b[i] << " ";
    }

    std::cout << "\n Time taken by parallel algorithm: " << end_time - start_time << " seconds" << std::endl;

    delete[] a;
    delete[] b;

    return 0;
}

/*
Command to run: 
g++ bubble.cpp -lgomp -o test
./test

Input: 
9
2 6 5 4 8 9 1 3 5
Output: 1 2 3 4 5 6 7 8 9*/