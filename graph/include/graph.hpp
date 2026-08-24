#pragma once
#include <vector>

class Graph
{
private:
    int vertexCount = 0;
    std::vector<std::vector<int>> adj;
    void dfsHelper(int node, std::vector<bool>& visited);

public:
    Graph(int n);
    ~Graph();
    void addEdge(int u, int v);
    void printData();
    void dfs(int start);
    void bfs(int start);
    void addDirectedEdge(int u, int v);
    void topologicalSort();
};