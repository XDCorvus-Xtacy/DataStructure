#include "../include/graph.hpp"
#include <iostream>

////////////////////////////////////////////////////////////////////
Graph::Graph(int n)
{
    vertexCount = n;
    adj.resize(n);
}

////////////////////////////////////////////////////////////////////
Graph::~Graph()
{

}

////////////////////////////////////////////////////////////////////
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

////////////////////////////////////////////////////////////////////
void Graph::printData()
{
    for (int i=0; i < vertexCount; i++)
    {
        std::cout << i << " -> ";
        for (int neighbor : adj[i])
        {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

////////////////////////////////////////////////////////////////////
void Graph::dfs(int start)
{
    std::vector<bool> visited(vertexCount, false);
    dfsHelper(start, visited);
}

////////////////////////////////////////////////////////////////////
void Graph::dfsHelper(int node, std::vector<bool>& visited)
{
    visited[node] = true;
    std::cout << node << " ";

    for (int next : adj[node])
    {
        if (!visited[next])
            dfsHelper(next, visited);
    }
}

////////////////////////////////////////////////////////////////////
