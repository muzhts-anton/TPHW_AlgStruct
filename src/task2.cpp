#include <iostream>
#include <queue>
#include <vector>

struct IGraph {
    virtual ~IGraph() { }

    virtual void addEdge(int from, int to) = 0;

    virtual int verticesCount() const = 0;

    virtual std::vector<int> getNextVertices(int vertex) const = 0;
    virtual std::vector<int> getPrevVertices(int vertex) const = 0;
};

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

int getWaysCount(const IGraph& graph, int from, int to)
{
    std::queue<int> q;
    q.push(from);

    std::vector<int> way(graph.verticesCount(), __INT32_MAX__);
    way[from] = 0;

    std::vector<int> count(graph.verticesCount(), 0);
    count[from] = 1;

    while (q.size() > 0) {
        int v = q.front();
        q.pop();

        std::vector<int> next = graph.getNextVertices(v);
        for (auto& it : next) {
            if (way[it] > way[v] + 1) {
                way[it] = way[v] + 1;
                q.push(it);
            }

            if (way[it] == way[v] + 1)
                count[it] += count[v];
        }
    }

    return count[to];
}

int main()
{
    int vertices = 0;
    int edges = 0;
    std::cin >> vertices >> edges;

    ListGraph graph(vertices);

    int from = 0, to = 0;
    for (int i = 0; i < edges; ++i) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
        graph.addEdge(to, from);
    }

    std::cin >> from >> to;
    std::cout << getWaysCount(graph, from, to) << std::endl;

    return 0;
}
