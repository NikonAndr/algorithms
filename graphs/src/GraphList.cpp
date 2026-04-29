#include "GraphList.h"
#include <iostream>

GraphList::GraphList(int V, const std::vector<Edge>& edges) : V(V)
{
    adj.resize(V);

    for (const auto& edge : edges)
    {
        adj[edge.u].push_back({edge.v, edge.w});
        adj[edge.v].push_back({edge.u, edge.w});
    }
}

const std::vector<std::pair<int,int>>& GraphList::neighbours(int u) const
{
    return adj[u];
}

int GraphList::getV() const
{
    return V;
}

void GraphList::print() const
{
    std::cout << "Neighbour List:\n";

    for (int u = 0; u < V; u++)
    {
        std::cout << u << ": ";

        for (const auto& [v, w] : adj[u])
        {
            std::cout << "(" << v << ", w=" << w <<") ";
        }

        std::cout << std::endl;
    }

}