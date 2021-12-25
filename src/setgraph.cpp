#include "setgraph.h"

SetGraph::SetGraph(IGraph& graph)
    : _treeVector(graph.verticesCount())
{
    for (size_t i = 0; i < graph.verticesCount(); ++i)
        for (auto& it : graph.getNextVertices(i))
            _treeVector[i].insert(it);
}

std::vector<int> SetGraph::getNextVertices(int vertex) const
{
    std::vector<int> tmp;
    for (auto& it : _treeVector[vertex])
        tmp.push_back(it);

    return tmp;
}

std::vector<int> SetGraph::getPrevVertices(int vertex) const
{
    std::vector<int> tmp;
    for (size_t i = 0; i < verticesCount(); ++i)
        if (_treeVector[i].find(vertex) != _treeVector[i].end())
            tmp.push_back(i);

    return tmp;
}
