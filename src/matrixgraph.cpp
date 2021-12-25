#include "matrixgraph.h"

MatrixGraph::MatrixGraph(int vertexnum)
    : _matrix(vertexnum)
{
    for (size_t i = 0; i < vertexnum; ++i)
        for (size_t j = 0; j < vertexnum; ++j)
            _matrix[i].push_back(false);
}

MatrixGraph::MatrixGraph(IGraph& graph)
    : _matrix(graph.verticesCount())
{
    for (auto& it : _matrix)
        it.resize(graph.verticesCount());

    for (size_t row = 0; row < verticesCount(); ++row) {
        std::vector<int> next = graph.getNextVertices(row);
        for (auto& it : next)
            addEdge(row, it);
    }
}

std::vector<int> MatrixGraph::getNextVertices(int vertex) const
{
    std::vector<int> tmp;
    for (size_t i = 0; i < verticesCount(); ++i)
        if (_matrix[vertex][i])
            tmp.push_back(i);

    return tmp;
}

std::vector<int> MatrixGraph::getPrevVertices(int vertex) const
{
    std::vector<int> tmp;
    for (size_t i = 0; i < verticesCount(); ++i)
        if (_matrix[i][vertex])
            tmp.push_back(i);

    return tmp;
}
