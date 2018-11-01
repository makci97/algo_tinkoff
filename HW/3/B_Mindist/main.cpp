#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>


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


std::vector<std::list<int> > matrix2list(
        std::vector<std::vector<int> >&& matrix_graph
)
{
    int n = matrix_graph.size();
    std::vector<std::list<int> > list_graph(n + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix_graph[i][j] == 1)
            {
                list_graph[i + 1].push_back(j + 1);
            }
        }
    }
    return std::move(list_graph);
}


int main() {
    int n, v, x;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("mindist.in");
    out_stream.open("mindist.out");

    // read graph
    in_stream >> n >> x;
    auto graph = matrix2list(read_matrix_graph(n, in_stream));
    std::vector<int> dist(n + 1, -1);
    dist[x] = 0;

    // Bellman–Ford
    for (int n_iter = 0; n_iter < n - 1; ++n_iter)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (graph[i].empty() || dist[i] == -1)
                continue;
            for (auto j: graph[i])
            {
                if (dist[j] == -1 || dist[j] > dist[i] + 1)
                {
                    dist[j] = dist[i] + 1;
                }
            }
        }
    }

    // output
    for (auto it = dist.begin() + 1, end = dist.end(); it != end; ++it)
    {
        out_stream << *it << ' ';
    }

    in_stream.close();
    out_stream.close();

    return 0;
}