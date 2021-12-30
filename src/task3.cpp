#include <cassert>
#include <cmath> // for infty
#include <iostream>
#include <queue>
#include <set>
#include <vector>

struct IGraph {
    virtual ~IGraph() { }

    virtual void addEdge(int from, int to, int weight) = 0;

    virtual int verticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> getNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> getPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int vertexnum)
        : _vertices(vertexnum) {};
    ListGraph(IGraph& graph);

    virtual inline void addEdge(int from, int to, int weight) override { _vertices[to].emplace_back(from, weight); }
    virtual inline int verticesCount() const override { return _vertices.size(); }
    virtual inline std::vector<std::pair<int, int>> getNextVertices(int vertex) const override { return _vertices[vertex]; }
    virtual std::vector<std::pair<int, int>> getPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<std::pair<int, int>>> _vertices;
};

ListGraph::ListGraph(IGraph& graph)
    : _vertices(graph.verticesCount())
{
    for (size_t i = 0; i < _vertices.size(); ++i)
        _vertices[i] = graph.getNextVertices(i);
}

std::vector<std::pair<int, int>> ListGraph::getPrevVertices(int vertex) const
{
    std::vector<std::pair<int, int>> result;
    for (size_t from = 0; from < _vertices.size(); ++from)
        for (size_t i = 0; i < _vertices[from].size(); ++i)
            if (_vertices[from][i].first == vertex)
                result.emplace_back(from, _vertices[from][i].second);

    return result;
}

int getWayLen(const ListGraph& graph, int from, int to)
{
    std::vector<int64_t> way(graph.verticesCount(), INT64_MAX);
    std::set<std::pair<int, int>> s;
    way[from] = 0;
    s.emplace(0, from);

    while (!s.empty()) {
        auto v = *s.begin();
        for (auto& nextVertex : graph.getNextVertices(v.second)) {
            if (way[nextVertex.first] > way[v.second] + nextVertex.second) {
                std::pair<int, int> weightNextVertex(way[nextVertex.first], nextVertex.first);
                auto tmp = s.find(weightNextVertex);
                if (tmp != s.end())
                    s.erase(tmp);

                way[nextVertex.first] = way[v.second] + nextVertex.second;
                s.insert(std::pair<int, int>(way[nextVertex.first], nextVertex.first));
            }
        }
        s.erase(s.find(v));
    }
    return way[to];
}

int main()
{
    int vN = 0;
    int eN = 0;
    std::cin >> vN >> eN;
    ListGraph graph(vN);

    int from = 0;
    int to = 0;
    int weight = 0;
    for (int i = 0; i < eN; i++) {
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }

    std::cin >> from >> to;
    std::cout << getWayLen(graph, from, to);
    return 0;
}
