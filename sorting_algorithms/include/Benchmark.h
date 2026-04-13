#pragma once

#include "DynamicArray.h"
#include "csvReader.h"
#include "BucketSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using SortFunc = void(*)(DynamicArray&);

struct Algorithm
{
    std::string name;
    SortFunc func;
};

bool is_sorted(DynamicArray& arr);

double calculate_median(const DynamicArray& arr);

double calculate_mean(const DynamicArray& arr);

void save_result(const std::string& algo, size_t n, double time);

void single_benchmark(DynamicArray& arr, std::string algorithm_name);

void benchmark(DynamicArray& original, size_t n);

void run_benchmarks(DynamicArray& data);