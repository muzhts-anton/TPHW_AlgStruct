#include "arcgraph.h"

ArcGraph::ArcGraph(IGraph& graph)
    : _vertex(graph.verticesCount())
{
    for (size_t i = 0; i < _vertex; ++i) {
        std::vector<int> tmp = graph.getNextVertices(i);
        for (auto& it : tmp)
            _pairs.push_back(std::make_pair(i, it));
    }
}
std::vector<int> ArcGraph::getNextVertices(int vertex) const
{
    std::vector<int> tmp;
    for (auto& it : _pairs)
        if (it.first == vertex)
            tmp.push_back(it.second);

    return tmp;
}

std::vector<int> ArcGraph::getPrevVertices(int vertex) const
{
    std::vector<int> tmp;
    for (auto& it : _pairs)
        if (it.second == vertex)
            tmp.push_back(it.first);

    return tmp;
}
