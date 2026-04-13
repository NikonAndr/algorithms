#include "Benchmark.h"
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>

std::vector<Algorithm> algorithms = {
    {"QuickSort", QuickSort},
    {"MergeSort", MergeSort},
    {"BucketSort", BucketSort}
};

bool is_sorted(DynamicArray& arr)
{
    int* A = arr.get_array();
    size_t n = arr.size_of();

    for(size_t i = 1; i < n; i++)
    {
        if (A[i - 1] > A[i]) 
            return false;
    }

    return true;
}

double calculate_mean(const DynamicArray& arr)
{
    double result = 0.0;

    size_t n = arr.size_of();
    int* A = arr.get_array();

    if (n == 0) return 0.0;

    for (size_t i = 0; i < n; i++)
    {
        result += A[i];
    }

    return result / (double)n;
}

double calculate_median(const DynamicArray& arr)
{
    double result = 0.0;
    size_t n = arr.size_of();
    int* A = arr.get_array();

    if (n == 0) return 0.0;

    if (n % 2 == 0)
    {
        result = (A[n / 2] + A[n / 2 - 1]) / 2.0;
    }
    else
    {
        result = A[n / 2];
    }

    return result;
}

void save_result(const std::string& algo, size_t n, double time, double mean, double median)
{
    std::filesystem::create_directory("results");

    std::string path = "results/" + algo + ".csv";

    bool exists = std::filesystem::exists(path);

    std::ofstream file(path, std::ios::app);

    file << std::fixed;
    file.precision(10);
    
    if (!exists)
    {
        file << "n,time,mean,median\n";
    }

    file << n << "," << time << "," << mean << "," << median << "\n";
}

void single_benchmark(DynamicArray& arr, std::string algorithm_name)
{
    DynamicArray base = arr;

    Algorithm* sorting_algorithm = nullptr;
    const int REPS = 10;

    for (auto& algo : algorithms)
    {
        if (algo.name == algorithm_name)
        {
            sorting_algorithm = &algo;
            break;
        }
    }

    if (sorting_algorithm == nullptr)
    {
        throw std::runtime_error("Algorithm not found: " + algorithm_name);
    }

    
    double total_time = 0.0;

    //mesure time
    for (int i = 0; i < REPS; i++)
    {
        DynamicArray copy = base;

        auto start = std::chrono::high_resolution_clock::now();
        sorting_algorithm->func(copy);
        auto end = std::chrono::high_resolution_clock::now();

        double time = std::chrono::duration<double>(end - start).count();

        total_time += time;
        
        if (!is_sorted(copy))
        {
            std::cerr << "ERROR: " << sorting_algorithm->name << "failed!";
        }
    }
    
    double avg_time = total_time / REPS;

    //calculate mean & median
    DynamicArray copy = base;
    sorting_algorithm->func(copy);

    double mean = calculate_mean(copy);
    double median = calculate_median(copy);


    save_result(sorting_algorithm->name, arr.size_of(), avg_time, mean, median);

}


void benchmark(DynamicArray& original, size_t n)
{
    DynamicArray base = load_data(original, n);

    const int REPS = 10;

    for (auto& algo : algorithms)
    {
        double total_time = 0.0;

        //measure time
        for (int i = 0; i < REPS; i++)
        {
            DynamicArray copy = base;

            auto start = std::chrono::high_resolution_clock::now();
            algo.func(copy);
            auto end = std::chrono::high_resolution_clock::now();

            double time = std::chrono::duration<double>(end - start).count();
            total_time += time;

            if(!is_sorted(copy))
            {
                std::cerr << "ERROR: " << algo.name << " failed!\n";
            }
        }

        double avg_time = total_time / REPS;

        std::cout << algo.name << " | n=" << n << " | avg=" << avg_time << "s\n";

        //calculate mean & median
        DynamicArray copy = base;
        algo.func(copy);

        double mean = calculate_mean(copy);
        double median = calculate_median(copy);


        save_result(algo.name, n, avg_time, mean, median);
    }
}

void run_benchmarks(DynamicArray& data)
{
    std::vector<size_t> sizes = {
        10000, 100000, 500000, data.size_of()
    };

    for (size_t n : sizes)
    {
        benchmark(data, n);
    }
}