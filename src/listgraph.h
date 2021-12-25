#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "igraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int vertexnum)
        : _vertices(vertexnum) {};
    ListGraph(IGraph& graph);

    virtual inline void addEdge(int from, int to) override { _vertices[from].push_back(to); }
    virtual inline int verticesCount() const override { return _vertices.size(); }
    virtual inline std::vector<int> getNextVertices(int vertex) const override { return _vertices[vertex]; }
    virtual std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> _vertices;
};

#endif // LISTGRAPH_H
