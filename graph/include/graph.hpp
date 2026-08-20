#pragma once
#include <vector>

class Graph
{
private:
    int vertexCount = 0;
    std::vector<std::vector<int>> adj;

public:
    Graph(int n);
    ~Graph();
    void addEdge(int u, int v);
    void printData();
};