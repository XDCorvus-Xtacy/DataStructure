#include "../include/graph.hpp"
#include <iostream>
#include <queue>

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
    if (start < 0 || start >= vertexCount)
        return;

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
void Graph::bfs(int start)
{
    if (start < 0 || start >= vertexCount)
        return;

    std::vector<bool> visited(vertexCount, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        std::cout << cur << " ";

        for (int next : adj[cur])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////
void Graph::addDirectedEdge(int u, int v)
{
    adj[u].push_back(v);
}

////////////////////////////////////////////////////////////////////
void Graph::topologicalSort()
{
    std::vector<int> inDegree(vertexCount, 0);

    for (int u = 0; u < vertexCount; u++)
    {
        for (int v : adj[u])
        {
            inDegree[v]++;
        }
    }

    std::queue<int> q;
    std::vector<int> result;

    for (int i = 0; i < vertexCount; i++)
    {
        if (inDegree[i] == 0)
            q.push(i);
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        result.push_back(cur);

        for (int next : adj[cur])
        {
            inDegree[next]--;

            if (inDegree[next] == 0)
                q.push(next);
        }
    }

    if (result.size() != vertexCount)
    {
        std::cout << "사이클이 존재합니다! (위상 정렬 불가)" << std::endl;
        return;
    }

    for (int x : result)
        std::cout << x << " ";
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////
