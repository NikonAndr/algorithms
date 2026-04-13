#pragma once
#include <iostream>

class DynamicArray 
{
private:
    size_t size;
    int capacity;
    int* Array;
public:

    DynamicArray();

    DynamicArray(const DynamicArray& other);

    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    void ensure_capacity();

    void push_back(int value);

    void set_element(int index, int value);

    int* get_array() const;

    size_t size_of() const;


    void print();
};