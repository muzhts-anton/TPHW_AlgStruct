#ifndef ARCGRAPH_H
#define ARCGRAPH_H

#include "igraph.h"

class ArcGraph : public IGraph {
public:
    ArcGraph(int vertexCount)
        : _vertex(vertexCount) {};
    ArcGraph(IGraph& graph);

    virtual inline void addEdge(int from, int to) override { _pairs.push_back(std::make_pair(from, to)); }
    virtual inline int verticesCount() const override { return _vertex; }
    virtual std::vector<int> getNextVertices(int vertex) const override;
    virtual std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> _pairs;
    int _vertex;
};

#endif // ARCGRAPH_H
