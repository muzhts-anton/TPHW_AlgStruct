#ifndef SETGRAPH_H
#define SETGRAPH_H

#include "igraph.h"
#include <set>

class SetGraph : public IGraph {
public:
    SetGraph(int vertexnum)
        : _treeVector(vertexnum) {};
    SetGraph(IGraph& graph);

    virtual inline void addEdge(int from, int to) override { _treeVector[from].insert(to); }
    virtual inline int verticesCount() const override { return _treeVector.size(); }
    virtual std::vector<int> getNextVertices(int vertex) const override;
    virtual std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> _treeVector;
};

#endif // SETGRAPH_H
