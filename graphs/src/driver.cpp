#include "driver.h"

#include <iostream>
#include <exception>

void drive(int V, double density, char type, size_t start)
{
    if (V < 1)
    {
        throw std::runtime_error("V cannot be less than 1!");
    }

    if (density < 0 || density > 1)
    {
        throw std::runtime_error("Wrong density! density range [0;1]");
    }

    if (start >= V)
    {
        throw std::runtime_error("Start cannot be greater than V");
    }

    auto edges = generateEdges(V, density);
    std::vector<int> result;

    if (type == 'L')
    {
        GraphList g(V, edges);
        g.print();
        result = dijkstraList(g, start);
    }
    else if (type == 'M')
    {
        GraphMatrix g(V, edges);
        g.print();
        result = dijkstraMatrix(g, start);
    }
    else 
    {
        throw std::runtime_error("Wrong type: Only 'L' and 'M' allowed!");
    }

    std::cout << "Graph type: " << type << std::endl;
    std::cout << "Start: " << start << "\n\n";

    std::cout << "Dijkstra:\n";
    for (int i = 0; i < V; i++)
    {
        std::cout << i << ": ";
        if (result[i] == INT_MAX)
        {
            std::cout << "INF";
        }
        else 
        {
            std::cout << result[i];
        }

       std::cout << " "; 
    }
}