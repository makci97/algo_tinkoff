#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

int global_time = 0;

enum color {white, grey, black};


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


void tarjan(
        int vertex,
        const std::vector<std::list<int> >& graph,
        std::vector<color>& v_colors,
        std::vector<int>& in_time
)
{
    ++global_time;
    v_colors[vertex] = grey;
    if (in_time[vertex] == -1)
        in_time[vertex] = global_time;
    else
        in_time[vertex] = std::min(global_time, in_time[vertex]);
    for (int v : graph[vertex])
    {
        if (v_colors[v] == white)
        {
            in_time[v] = in_time[vertex];
            tarjan(v, graph, v_colors, in_time);
        }
        if (in_time[vertex] > in_time[v])
            in_time[vertex] = in_time[v];
    }
    v_colors[vertex] = black;
}


int main() {
    int n, m;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("matrix2.in");
    out_stream.open("matrix2.out");

    // read graph
    in_stream >> n >> m;
    auto graph = read_pairs_graph(n, m, in_stream);

    // prepare containers
    std::vector<color> v_colors(n + 1, white);
    std::vector<int> in_time(n + 1, -1);

    // Tarjan's strongly connected components algorithm
    for (int i = 1; i <= n; ++i)
        tarjan(i, graph, v_colors, in_time);
    std::vector<std::list<int> > components(global_time + 1);
    for (int i = 1; i <= n; ++i)
    {
        components[in_time[i]].push_back(i);
    }

    // output
    int n_components = 0;
    for (int i = 1; i <= global_time; ++i)
    {
        if (!components[i].empty())
            ++n_components;
    }
    out_stream << n_components << std::endl;
    for (int i = 1; i <= global_time; ++i)
    {
        if (components[i].empty())
            continue;
        out_stream << components[i].size() << std::endl;
        for (int v : components[i])
        {
            out_stream << v << ' ';
        }
        out_stream << std::endl;
    }

    in_stream.close();
    out_stream.close();

    return 0;
}