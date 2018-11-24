#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>


std::vector<std::list<std::pair<int, int> > > read_pairs_graph(
        int n, int m, std::ifstream& in_stream
)
{
    int u, v, w;
    std::vector<std::list<std::pair<int, int> > > graph(n + 1);
    for (int i = 0; i < m; ++i)
    {
        in_stream >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    return graph;
}


int main() {
    int n, m, s, f;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("distance.in");
    out_stream.open("distance.out");

    // read graph
    in_stream >> n >> m;
    in_stream >> s >> f;
    auto graph = read_pairs_graph(n, m, in_stream);
    std::vector<std::pair<int, int> > dist(n + 1, {-1, -1});    // {dist, parent_v}
    dist[f] = {0, -1};

    // Bellman–Ford
    for (int n_iter = 0; n_iter < n - 1; ++n_iter)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (graph[i].empty() || dist[i].first == -1)
                continue;
            for (auto pair: graph[i])
            {
                if (dist[pair.first].first == -1 ||
                    dist[pair.first].first > dist[i].first + pair.second)
                {
                    dist[pair.first] = {dist[i].first + pair.second, i};
                }
            }
        }
    }

    // output
    out_stream << dist[s].first;
    if (dist[s].first != -1)
    {
        out_stream << std::endl;
        while (s != f)
        {
            out_stream << s << ' ';
            s = dist[s].second;
        }
        out_stream << f;
    }

    in_stream.close();
    out_stream.close();

    return 0;
}