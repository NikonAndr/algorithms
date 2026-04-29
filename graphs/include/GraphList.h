#pragma once
#include "Edge.h"

#include <vector>


class GraphList
{
private:
    std::vector<std::vector<std::pair<int, int>>> adj;
    int V;
public:
    GraphList(int V, const std::vector<Edge>& edges);
    const std::vector<std::pair<int,int>>& neighbours(int u) const;
    int getV() const;

    void print() const;
};