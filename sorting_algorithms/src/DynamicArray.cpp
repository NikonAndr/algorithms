#include "DynamicArray.h"
#include <iostream>

DynamicArray::DynamicArray()
{
    capacity = 1;
    size = 0;
    Array = new int[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
    capacity = other.capacity;
    size = other.size;

    Array = new int[capacity];

    for (size_t i = 0; i < size; i++)
    {
        Array[i] = other.Array[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] Array;

    size = other.size;
    capacity = other.capacity;

    Array = new int[capacity];

    for (size_t i = 0; i < size; i++)
    {
        Array[i] = other.Array[i];
    }

    return *this;
}


DynamicArray::~DynamicArray()
{
    delete[] Array;
}

void DynamicArray::ensure_capacity()
{
    if (size == capacity)
    {
        int new_capacity = capacity * 2;
        int* new_Array = new int[new_capacity];
        
        for (size_t i = 0; i < size; i++)
        {
            new_Array[i] = Array[i];
        }

        delete[] Array;

        capacity = new_capacity;
        Array = new_Array;
    }
}

void DynamicArray::push_back(int value)
{
    ensure_capacity();

    Array[size] = value;

    size++;
}

void DynamicArray::set_element(int index, int value)
{
    Array[index] = value;
}

int* DynamicArray::get_array() const
{
    return Array;
}

size_t DynamicArray::size_of() const
{
    return size;
}

void DynamicArray::print()
{
    std::cout << "[";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << Array[i];
        if (i != size - 1)
        {
            std::cout << ",";
        }
    }

    std::cout << "]" << std::endl;
}