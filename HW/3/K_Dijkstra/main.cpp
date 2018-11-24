#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <limits>
#include <map>


const int INF = std::numeric_limits<int>::max();

std::vector<std::vector<int> > read_matrix_graph(
        int n, std::ifstream& in_stream
)
{
    int v;
    std::vector<std::vector<int> > graph;
    for (int i = 0; i < n; ++i)
    {
        std::vector<int> vertex;
        for (int j = 0; j < n; ++j)
        {
            in_stream >> v;
            vertex.push_back(v);
        }
        graph.push_back(std::move(vertex));
    }
    return std::move(graph);
}


std::vector<std::list<std::pair<int, int> > > matrix2list(
        std::vector<std::vector<int> >&& matrix_graph
)
{
    int n = matrix_graph.size();
    std::vector<std::list<std::pair<int, int> > > list_graph(n + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix_graph[i][j] != -1 && i != j)
            {
                list_graph[i + 1].push_back({j + 1, matrix_graph[i][j]});
            }
        }
    }
    return std::move(list_graph);
}


std::multimap<int, int> dist2queue(
        const std::vector<int>& dist,
        const std::vector<bool>& used
)
{
    std::multimap<int, int> queue;

    for(int i = 1; i < dist.size(); ++i)
    {
        if (!used[i])
            queue.insert({dist[i], i});
    }
    return std::move(queue);
}


int main() {
    int n, s, f, v, d;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("dijkstra.in");
    out_stream.open("dijkstra.out");

    // read graph
    in_stream >> n >> s >> f;
    auto graph = matrix2list(read_matrix_graph(n, in_stream));

    // prepare containers
    std::vector<int> dist(n + 1, INF);
    std::vector<bool> used(n + 1, false);
    dist[s] = 0;
    auto queue = dist2queue(dist, used);  // {dist, vertex}

    // Dijkstra
    while (!queue.empty() && !used[f])
    {
        d = queue.begin()->first;
        v = queue.begin()->second;
        used[v] = true;

        for (auto pair: graph[v])
        {
            if (!used[pair.first])
            {
                dist[pair.first] = std::min(dist[pair.first], d + pair.second);
            }
        }
        queue = dist2queue(dist, used);
    }

    // output
    if (dist[f] == INF)
        out_stream << -1;
    else
        out_stream << dist[f];

    in_stream.close();
    out_stream.close();

    return 0;
}