#include "DijkstraList.h"

#include <queue> 

std::vector<int> dijkstraList(const GraphList& g, int start)
{
    std::vector<int> dist(g.getV(), INT_MAX);
    std::vector<bool> visited(g.getV(), false);

    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u])
            continue;
        
        visited[u] = true;

        for (const auto& [v, w] : g.neighbours(u))
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }    
    }

    return dist;
}