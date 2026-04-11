#include "MergeSort.h"

void merge(DynamicArray& arr, int low, int mid, int high, int* temp)
{
    
    int* A = arr.get_array();

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (A[i] <= A[j])
        {
            temp[k++] = A[i++];
        }
        else
        {
            temp[k++] = A[j++];
        }
    } 

    while (i <= mid)
    {
        temp[k++] = A[i++];
    }

    while (j <= high)
    {
        temp[k++] = A[j++];
    }

    for (int t = low; t <= high; t++)
    {
        A[t] = temp[t]; 
    }
}

void MergeSort(DynamicArray& arr, int low, int high, int* temp)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2; 

        MergeSort(arr, low, mid, temp);
        MergeSort(arr, mid + 1, high, temp);

        merge(arr, low, mid, high, temp);    
    }
}

void MergeSort(DynamicArray& arr)
{
    int* temp = new int[arr.size_of()];

    MergeSort(arr, 0, arr.size_of() - 1, temp);

    delete[] temp;
}