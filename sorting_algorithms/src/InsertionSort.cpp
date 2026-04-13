#include "InsertionSort.h"
#include <iostream>

void InsertionSort(DynamicArray& arr)
{
    int* A = arr.get_array();
    size_t n = arr.size_of();

    for (int i = 1; i < n; i++)
    {
        int key = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = key;
    }
}