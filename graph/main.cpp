#include <iostream>
#include "include/graph.hpp"

int main()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    g.printData();

    std::cout << "DFS: ";
    g.dfs(0);
    std::cout << std::endl;

    std::cout << "BFS: ";
    g.bfs(0);
    std::cout << std::endl;

    return 0;
}