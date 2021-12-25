#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "igraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int vertexnum);
    MatrixGraph(IGraph& graph);

    virtual inline void addEdge(int from, int to) override { _matrix[from][to] = true; }
    virtual inline int verticesCount() const override { return _matrix.size(); }
    virtual std::vector<int> getNextVertices(int vertex) const override;
    virtual std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> _matrix;
};

#endif // MATRIXGRAPH_H
