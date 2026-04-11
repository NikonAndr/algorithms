#include "QuickSort.h"
#include "MergeSort.h"

int main()
{
    DynamicArray arr;

    for (int i = 10; i >= 0; i--)
    {
        arr.push_back(i);
    }

    arr.print();

    MergeSort(arr);

    arr.print();
}