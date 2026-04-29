#include "benchmark.h"
#include "GraphGenerator.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "DijkstraList.h"
#include "DijkstraMatrix.h"

#include <fstream>
#include <chrono>
#include <filesystem> 
#include <iostream>

void ensure_parent_directory(const std::string& filename)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
}

void benchmark(const std::string& output_path, const std::vector<int>& V_values, const std::vector<double>& densities)
{
    ensure_parent_directory(output_path);
    std::ofstream file(output_path);

    file << "V,density,representation,time\n";

    for (int V : V_values)
    {
        for (double density : densities)
        {
            double totalTimeList = 0;
            double totalTimeMatrix = 0;

            for (int i = 0; i < 100; i++)
            {
                auto edges = generateEdges(V, density);

                GraphList gList(V, edges);
                GraphMatrix gMatrix(V, edges);

                //List
                auto start1 = std::chrono::high_resolution_clock::now();
                dijkstraList(gList, 0);
                auto end1 = std::chrono::high_resolution_clock::now();

                totalTimeList += std::chrono::duration<double, std::milli>(end1 - start1).count();

                //Matrix
                auto start2 = std::chrono::high_resolution_clock::now();
                dijkstraMatrix(gMatrix, 0);
                auto end2 = std::chrono::high_resolution_clock::now();

                totalTimeMatrix += std::chrono::duration<double, std::milli>(end2 - start2).count();
            }

            double avgList = totalTimeList / 100.0;
            double avgMatrix = totalTimeMatrix / 100.0;

            file << V << "," << density << ",list," << avgList << "\n";
            file << V << "," << density << ",matrix," << avgMatrix << "\n";

            std::cout << "Done V=" << V << "density=" << density << "\n";
        }
    }

    file.close();
}