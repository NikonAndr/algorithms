#include "benchmark.h"
#include "driver.h"

#include <iostream>

int main()
{ 
    const std::vector<int> V_values = {10, 50, 100, 500, 1000};
    const std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};

    //benchmark("results/res.csv", V_values, densities);

    int V;
    double density;
    char type;
    size_t start;

    std::cout << "please type: V, density, type, start\n";
    std::cin >> V >> density >> type >> start;

    drive(V, density, type, start);
    return 0;
}