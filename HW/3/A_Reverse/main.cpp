#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>


int main() {
    int n, v;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("reverse.in");
    out_stream.open("reverse.out");

    in_stream >> n;
    getline(in_stream, line); // end first line
    std::vector<std::list<int> > reverse_graph(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        getline(in_stream, line);
        std::istringstream is(line);
        while (!is.eof() && !line.empty())
        {
            is >> v;
            reverse_graph[v].push_back(i);
        }
    }

    out_stream << n << std::endl;
    for (int i = 1; i <= n; ++i)
    {
        if (reverse_graph[i].empty())
        {
            out_stream << std::endl;
            continue;
        }
        for (auto ver: reverse_graph[i])
        {
            out_stream << ver << ' ';
        }
        out_stream << std::endl;
    }

    in_stream.close();
    out_stream.close();

    return 0;
}