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

    Graph dag(4);
    dag.addDirectedEdge(0, 1);
    dag.addDirectedEdge(0, 2);
    dag.addDirectedEdge(1, 3);
    dag.addDirectedEdge(2, 3);

    std::cout << "위상 정렬: ";
    dag.topologicalSort();

    Graph cycle(3);
    cycle.addDirectedEdge(0, 1);   // 0 → 1
    cycle.addDirectedEdge(1, 2);   // 1 → 2
    cycle.addDirectedEdge(2, 0);   // 2 → 0 (사이클!)

    std::cout << "사이클 테스트: ";
    cycle.topologicalSort();   // "사이클이 존재합니다!" 나와야 함

    return 0;
}