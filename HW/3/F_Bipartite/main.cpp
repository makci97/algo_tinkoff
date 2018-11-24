#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>


enum color {none, white, black};


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


color get_other_color(color cur_color)
{
    if (cur_color == white)
        return black;
    return white;
}


bool dfs_check_colors(
        int vertex,
        const std::vector<std::list<int> >& graph,
        std::vector<color>& v_colors
)
{
    if (v_colors[vertex] == none)
        v_colors[vertex] = white;
//    else    // ??
//        return true;
    for (int v : graph[vertex])
    {
        if (v_colors[v] == none)
        {
            v_colors[v] = get_other_color(v_colors[vertex]);
            if (!dfs_check_colors(v, graph, v_colors))
                return false;
        }
        else if (v_colors[v] == v_colors[vertex])
            return false;
    }
    return true;
}


int main() {
    int n, m;
    bool flag = true;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("bipartite.in");
    out_stream.open("bipartite.out");

    // read graph
    in_stream >> n >> m;
    auto graph = read_pairs_graph(n, m, in_stream);

    // prepare containers
    std::vector<color> v_colors(n + 1, none);

    for (int i = 1; i <= n; ++i)
    {
        if (!dfs_check_colors(i, graph, v_colors))
        {
            flag = false;
            break;
        }
    }

    // output
    if (flag)
        out_stream << "YES";
    else
        out_stream << "NO";

    in_stream.close();
    out_stream.close();

    return 0;
}