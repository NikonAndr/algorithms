#include "GraphMatrix.h"
#include <iostream>
#include <iomanip>

GraphMatrix::GraphMatrix(int V, const std::vector<Edge>& edges) : V(V)
{
    matrix.resize(V, std::vector<int>(V, 0));

    for (const auto& e : edges)
    {
        matrix[e.u][e.v] = e.w;
        matrix[e.v][e.u] = e.w;
    }
}

int GraphMatrix::getWeight(int u, int v) const
{
    return matrix[u][v];
}

int GraphMatrix::getV() const
{
    return V;
}

void GraphMatrix::print() const
{
    std::cout << "Neighbour Matrix:\n\n";

    std::cout << "   ";
    for (int i = 0; i < V; i++)
        std::cout << std::setw(3) << i;
    std::cout << "\n";

    for (int i = 0; i < V; i++)
    {
        std::cout << std::setw(3) << i;

        for (int j = 0; j < V; j++)
        {
            std::cout << std::setw(3) << matrix[i][j];
        }

        std::cout << "\n";
    }
}

