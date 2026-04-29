#pragma once

#include "Edge.h"

#include <vector>

class GraphMatrix
{
private:
    std::vector<std::vector<int>> matrix;
    int V;
public:
    GraphMatrix(int V, const std::vector<Edge>& edges);

    int getWeight(int u, int v) const;
    int getV() const;

    void print() const;
};