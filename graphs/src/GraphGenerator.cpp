#include "GraphGenerator.h"

#include <algorithm>
#include <random>

std::vector<Edge> generateEdges(int V, double density)
{
    int maxEdges = V * (V-1) / 2;
    int E = static_cast<int>(density * maxEdges);

    std::vector<Edge> edges;
    edges.reserve(maxEdges);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);

    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            edges.push_back({i, j , distr(gen)});
        }
    }
    
    std::shuffle(std::begin(edges), std::end(edges), gen);

    E = std::min(E, (int)edges.size());

    return std::vector<Edge>(edges.begin(), edges.begin() + E);
}