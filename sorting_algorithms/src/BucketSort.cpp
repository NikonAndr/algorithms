#include "BucketSort.h"

void BucketSort(DynamicArray& arr)
{
    int* A = arr.get_array();
    int n = arr.size_of();
    int min = A[0];
    int max = A[0];

    //find max & min values 
    for (int i = 0; i < n; i++)
    {
        if (A[i] < min)
            min = A[i];
        else if (A[i] > max)
            max = A[i];
    }

    int buckets_num = n;

    DynamicArray* buckets = new DynamicArray[buckets_num];

    for (int i = 0; i < n; i++)
    {
        int index = 
        buckets[index].push_back(A[i]);
    }

    for (int i = 0; i < buckets_num; i++)
    {
        if (buckets[i].size_of() != 0)
        {
            InsertionSort(buckets[i]);
        }
    }

}