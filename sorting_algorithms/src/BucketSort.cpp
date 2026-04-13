#include "BucketSort.h"
#include <iostream>
#include <cmath>

void BucketSort(DynamicArray& arr)
{
    int* A = arr.get_array();
    size_t n = arr.size_of();

    if (n == 0) return;

    int min = A[0], max = A[0];

    //find max & min values 
    for (int i = 0; i < n; i++)
    {
        if (A[i] < min) min = A[i];
        if (A[i] > max) max = A[i];
    }

    //edge case every element is the same
    if (max == min) return;

    //number of buckets
    int k = (int)sqrt(n);
    if (k < 1) k = 1;

    DynamicArray* buckets = new DynamicArray[k];

    for (int i = 0; i < n; i++)
    {
        int index = (int)((long long)(A[i] - min) * k / (max - min + 1));
        if (index == k) index = k - 1;
        buckets[index].push_back(A[i]);
    }

    for (int i = 0; i < k; i++)
    {
        if (buckets[i].size_of() > 0)
            InsertionSort(buckets[i]);
    }

    int idx = 0;

    for (int i = 0; i < k; i++)
    {
        int* B = buckets[i].get_array();

        for (int j = 0; j < buckets[i].size_of(); j++)
        {
            A[idx++] = B[j];
        }
    }

    delete[] buckets;

}