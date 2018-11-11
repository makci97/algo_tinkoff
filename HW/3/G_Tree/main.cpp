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


bool dfs_acyclic(
        int vertex, int parent,
        const std::vector<std::list<int> >& graph,
        std::vector<color>& v_colors
)
{
    v_colors[vertex] = grey;
    for (int v : graph[vertex])
    {
        if (v_colors[v] == white)
        {
            if (!dfs_acyclic(v, vertex, graph, v_colors))
                return false;
        }
        else if (v_colors[v] == grey && v != parent)
                return false;
    }
    v_colors[vertex] = black;
    return true;
}


int main() {
    int n;
    bool is_tree = true;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("tree.in");
    out_stream.open("tree.out");

    // read graph
    in_stream >> n;
    auto graph = matrix2list(read_matrix_graph(n, in_stream));

    // prepare containers
    std::vector<color> v_colors(n + 1, white);

    // dfs + acyclic check
    if (!dfs_acyclic(1, 1, graph, v_colors))
    {
        is_tree = false;
    }

    // graph is connected
    if (is_tree)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (v_colors[i] != black)
            {
                is_tree = false;
                break;
            }
        }
    }

    // final output
    if (is_tree)
        out_stream << "YES";
    else
        out_stream << "NO";

    in_stream.close();
    out_stream.close();
    return 0;
}