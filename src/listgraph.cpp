#include "listgraph.h"

ListGraph::ListGraph(IGraph& graph)
    : _vertices(graph.verticesCount())
{
    for (size_t i = 0; i < _vertices.size(); ++i)
        _vertices[i] = graph.getNextVertices(i);
}

std::vector<int> ListGraph::getPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (size_t from = 0; from < _vertices.size(); ++from)
        for (size_t i = 0; i < _vertices[from].size(); ++i)
            if (_vertices[from][i] == vertex)
                result.push_back(from);
    return result;
}