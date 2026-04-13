#pragma once 
#include "DynamicArray.h"
#include "Benchmark.h"
#include "csvReader.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "BucketSort.h"
#include <vector>

class Interface
{
private:
    DynamicArray sort_data;
public:
    Interface();
    ~Interface();
    void main_if();
    void load_data_if();
    void sort_if();
};

std::vector<std::string> list_csv_files(const std::string& folder);

std::string choose_file(const std::vector<std::string>& files);