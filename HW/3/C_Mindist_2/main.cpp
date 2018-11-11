#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>

const int MAX_VER = 50000;

std::vector<std::list<int> > read_pairs_graph(
        int n, int m, std::ifstream& in_stream
)
{
    int u, v;
    std::vector<std::list<int> > graph(n + 1);
    for (int i = 0; i < m; ++i)
    {
        in_stream >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}


int main() {
    int n, m, a, b, v;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("mindist2.in");
    out_stream.open("mindist2.out");

    // read graph
    in_stream >> n >> m;
    in_stream >> a >> b;
    auto graph = read_pairs_graph(n, m, in_stream);

    // prepare data containers
    std::bitset<MAX_VER + 1> used(false);
    std::vector<std::pair<int, int> > dist(n + 1, {-1, -1});
    std::queue<int> q;

    // start values
    used[b] = true;
    dist[b] = {0, -1};
    q.push(b);

    // BFS
    while (!q.empty() && !used[a])
    {
        v = q.front();
        q.pop();
        for (int neigh: graph[v])
        {
            if (used[neigh])
                continue;
            used[neigh] = true;
            dist[neigh] = {dist[v].first + 1, v};
            q.push(neigh);
        }
    }

    // output
    out_stream << dist[a].first;
    if (dist[a].first != -1)
    {
        out_stream << std::endl;
        while (a != b)
        {
            out_stream << a << ' ';
            a = dist[a].second;
        }
        out_stream << b;
    }

    in_stream.close();
    out_stream.close();

    return 0;
}