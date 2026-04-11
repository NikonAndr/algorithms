#pragma once

class DynamicArray 
{
private:
    int size;
    int capacity;
    int* Array;
public:

    DynamicArray();

    DynamicArray(const DynamicArray& other);

    ~DynamicArray();

    void ensure_capacity();

    void push_back(int value);

    void set_element(int index, int value);

    int* get_array();

    int size_of();


    void print();
};