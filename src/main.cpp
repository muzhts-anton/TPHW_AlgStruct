#include "arcgraph.h"
#include "listgraph.h"
#include "matrixgraph.h"
#include "setgraph.h"

#include <iostream>
#include <queue>

void bfs(const IGraph& graph, void (*callback)(int))
{
    std::vector<bool> visited(graph.verticesCount(), false);
    std::queue<int> q;

    for (int vertex = 0; vertex < graph.verticesCount(); ++vertex) {
        if (visited[vertex])
            continue;

        visited[vertex] = true;
        q.push(vertex);
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            callback(v);

            std::vector<int> children = graph.getNextVertices(v);
            for (auto& child : children) {
                if (visited[child])
                    continue;

                visited[child] = true;
                q.push(child);
            }
        }
    }
}

void buildGraph(IGraph& graph)
{
    /* the built graph is taken from the seminar */
    graph.addEdge(0, 1);
    graph.addEdge(1, 5);
    graph.addEdge(6, 0);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 2);
    graph.addEdge(0, 7);
    graph.addEdge(0, 8);
}

int main()
{
    ListGraph listgraph(9);
    buildGraph(listgraph);

    bfs(listgraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << "\n";

    MatrixGraph matrixgraph(listgraph);
    bfs(matrixgraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << "\n";

    ArcGraph arcgraph(listgraph);
    bfs(arcgraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << "\n";

    SetGraph setgraph(listgraph);
    bfs(setgraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << "\n";

    return 0;
}
