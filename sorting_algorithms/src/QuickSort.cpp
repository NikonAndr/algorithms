#include "QuickSort.h"
#include <iostream>

void QuickSort(DynamicArray& arr, int low, int high)
{
    if (low >= high) return;

    int* A = arr.get_array();

    //set pivot at the middle 
    int mid = (low + high) / 2;
    int pivot = A[mid];

    int lt = low; //less than pivot
    int gt = high; //greater than pivor
    int i = low;

    while (i <= gt)
    {
        if (A[i] < pivot)
        {
            std::swap(A[lt], A[i]);
            lt++;
            i++;
        }
        else if (A[i] > pivot)
        {
            std::swap(A[i], A[gt]);
            gt--;
        }
        else
        {
            i++;
        } 
    }
    QuickSort(arr, low, lt - 1);
    QuickSort(arr, gt + 1, high);
}

void QuickSort(DynamicArray& arr)
{
    QuickSort(arr, 0, arr.size_of() - 1);
}