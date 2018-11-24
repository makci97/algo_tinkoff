#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <stack>

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
    }
    return graph;
}


bool dfs_acyclic(
        int vertex,
        const std::vector<std::list<int> >& graph,
        std::vector<color>& v_colors,
        std::stack<int>& sorted
)
{
    v_colors[vertex] = grey;
    for (int v : graph[vertex])
    {
        if (v_colors[v] == white)
        {
            if (!dfs_acyclic(v, graph, v_colors, sorted))
                return false;
        }
        else if (v_colors[v] == grey)
                return false;
    }
    v_colors[vertex] = black;
    sorted.push(vertex);

    return true;
}


int main() {
    int n, m;
    bool is_acyclic = true;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("topsort.in");
    out_stream.open("topsort.out");

    // read graph
    in_stream >> n >> m;
    auto graph = read_pairs_graph(n, m, in_stream);

    // prepare containers
    std::vector<color> v_colors(n + 1, white);
    std::stack<int> sorted;

    // dfs + acyclic check
    for (int i = 1; i <= n; ++i)
    {
        if (v_colors[i] == white)
        {
            if (!dfs_acyclic(i, graph, v_colors, sorted))
            {
                is_acyclic = false;
                break;
            }
        }
    }

    // final output
    if (is_acyclic)
    {
        while (!sorted.empty())
        {
            out_stream << sorted.top() << ' ';
            sorted.pop();
        }
    }
    else
        out_stream << -1;

    in_stream.close();
    out_stream.close();
    return 0;
}