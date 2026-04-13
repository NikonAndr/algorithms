#include "csvReader.h"

void clear_directory(const std::string& path)
{
    if (!std::filesystem::exists(path)) return;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::filesystem::remove_all(entry.path());
    }
}

DynamicArray load_csv(const std::string& filename)
{
    clear_directory("results");

    DynamicArray arr;
    std::ifstream file(filename);

    std::ofstream bad_file("results/invalid_rows.txt");


    if (!file.is_open())
    {
        std::cerr << "Error opening file\n";
        return arr;
    }

    std::string line;
    //csv statistics
    size_t total = 0;
    size_t valid = 0;
    size_t invalid = 0;

    //skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        total ++;
        size_t last_comma = line.find_last_of(',');

        //invalid rows check
        if (last_comma == std::string::npos)
        {
            bad_file << line << "\n";
            invalid++;
            continue;
        }

        std::string rating_str = line.substr(last_comma + 1);

        //invalid rows check
        if (rating_str.empty())
        {
            bad_file << line << "\n";
            invalid++;
            continue;
        }
        
        try 
        {
            double rating_d = std::stod(rating_str);
            int rating = (int)(rating_d);

            arr.push_back(rating);
            valid++;
        }
        catch (...)
        {
            bad_file << line << "\n";
            invalid++;
        }
    }

    std::cout << "\n===CSV LOAD REPORT===\n";
    std::cout << "TOTAL ROWS: " << total << "\n";
    std::cout << "VALID ROWS: " << valid << "\n";
    std::cout << "INVALID ROWS: " << invalid << "\n";

    return arr;
}

DynamicArray load_data(const DynamicArray& source, int n)
{
    DynamicArray result;

    int* A = source.get_array();
    size_t size = source.size_of();

    if (n > size) n = size;

    for (int i = 0; i < n; i++)
    {
        result.push_back(A[i]);
    }

    return result;
}