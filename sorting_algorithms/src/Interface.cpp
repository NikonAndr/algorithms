#include "Interface.h"
#include <iostream>
#include <filesystem>

std::vector<std::string> list_csv_files(const std::string& folder)
{
    std::vector<std::string> files;

    int index = 1;
    for (const auto& entry : std::filesystem::directory_iterator(folder))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".csv")
        {
            std::string path = entry.path().string();
            files.push_back(path);

            std::cout << index << ": " << entry.path().filename().string() << "\n";
            index++;
        }
    }

    return files;
}

std::string choose_file(const std::vector<std::string>& files)
{
    if (files.empty())
    {
        throw std::runtime_error("No CSV files found in data/");
    }

    while (true)
    {
        int choice;
    
        std::cin >> choice;

        if (choice >= 1 && choice <= files.size())
        {
            return files[choice - 1];
        }

        std::cout << "Invalid choice, try again: ";
    }
}

Interface::Interface() = default;
Interface::~Interface() = default;

void Interface::main_if()
{
    int choice;

    while (choice != 4)
    {
        std::cout << "\nSorting Algorithms menu: " << std::endl;
        std::cout << "1: load data\n2: sort\n3: run benchmark\n4: exit" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            load_data_if();
            break;
        case 2: 
            sort_if();
            break;
        case 3: 
            if (sort_data.size_of() == 0)
            {
                std::cout << "Load Data first!" << std::endl;
                break;
            }

            run_benchmarks(sort_data);
            break;
        case 4:
            std::cout << "bye!" << std::endl;
            break;
        default:
            std::cout << "invalid choice!" << std::endl;
            break;
        }
    }
}

void Interface::load_data_if()
{
    std::cout << "Available CSV files:\n";
    
    auto files = list_csv_files("data");

    std::string selected = choose_file(files);

    std::cout << "Loading: " << selected << "\n";

    sort_data = load_csv(selected);
}

void Interface::sort_if()
{
    std::cout << "Sorting Algorithms:\n";
    std::cout << "1: QuickSort\n2: MergeSort\n3: BucketSort\n";

    int choice;

    while (true)
    {
        std::cin >> choice;

        if (choice >= 1 && choice <= 3)
        {
            break;
        }

        std::cout << "Invalid choice, try again: ";
    }

    if (sort_data.size_of() == 0)
    {
        std::cout << "Load Data first!" << std::endl;
        return;
    }

    switch (choice)
    {
        case 1: 
            single_benchmark(sort_data, "QuickSort");

            QuickSort(sort_data);
            
            std::cout << "Sorting Done, open results/ to see statistics\n";
            //ask for print if arr size <= 100
            if (sort_data.size_of() <= 100)
            {
                char choice_p;
                std::cout << "Print arr? (y/n): ";
                std::cin >> choice;

                if (choice == 'y')
                {
                    sort_data.print();
                }
            }
            break;

        case 2:
            single_benchmark(sort_data, "MergeSort");

            MergeSort(sort_data);
            
            std::cout << "Sorting Done, open results/ to see statistics\n";
            //ask for print if arr size <= 100
            if (sort_data.size_of() <= 100)
            {
                char choice_p;
                std::cout << "Print arr? (y/n): ";
                std::cin >> choice;

                if (choice == 'y')
                {
                    sort_data.print();
                }
            }
            break;
        case 3:
            single_benchmark(sort_data, "BucketSort");

            BucketSort(sort_data);
            
            std::cout << "Sorting Done, open results/ to see statistics\n";
            //ask for print if arr size <= 100
            if (sort_data.size_of() <= 100)
            {
                char choice_p;
                std::cout << "Print arr? (y/n): ";
                std::cin >> choice_p;

                if (choice == 'y')
                {
                    sort_data.print();
                }
            }
            break;
        default:
            std::cout << "Invalid choice! \n";
            break;
    }
    
    
}