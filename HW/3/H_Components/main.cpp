#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

int global_time = 0;

enum color {white, grey, black};


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
    int n;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("components.in");
    out_stream.open("components.out");

    // read graph
    in_stream >> n;
    auto graph = matrix2list(read_matrix_graph(n, in_stream));

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
    out_stream << n_components;

    in_stream.close();
    out_stream.close();

    return 0;
}