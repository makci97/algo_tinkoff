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


int main() {
    int n;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("floyd.in");
    out_stream.open("floyd.out");

    // read graph
    in_stream >> n;
    auto graph = read_matrix_graph(n, in_stream);

    // Floyd
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    // output
    for (const auto line: graph)
    {
        for (int v: line)
        {
            out_stream << v << ' ';
        }
        out_stream << std::endl;
    }

    in_stream.close();
    out_stream.close();

    return 0;
}