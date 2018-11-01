#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


enum direction {none, south, east};


void eval_ways(
        std::vector<std::vector<std::pair<int, direction> > >& ways_map,
        const std::vector<std::vector<int> >& map,
        int n, int m
)
{
    ways_map[0][0] = {map[0][0], none};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (j == 0)
            {
                if (i != 0)
                {
                    ways_map[i][j] = {ways_map[i - 1][j].first + map[i][j], south};
                }
            }
            else
            {
                if (i != 0 && ways_map[i - 1][j].first < ways_map[i][j - 1].first)
                {
                    ways_map[i][j] = {ways_map[i - 1][j].first + map[i][j], south};
                }
                else
                {
                    ways_map[i][j] = {ways_map[i][j - 1].first + map[i][j], east};
                }
            }
        }
    }
}


void print_way(
        std::ofstream& out_stream,
        std::vector<std::vector<std::pair<int, direction> > >& ways_map,
        int n, int m
)
{
    --n;
    --m;
    out_stream << ways_map[n][m].first << std::endl;

    std::stack<std::pair<int, int> > way;
    while (n > 0 || m > 0)
    {
        way.push({n + 1, m + 1});

        if (ways_map[n][m].second == east)
            --m;
        else if (ways_map[n][m].second == south)
            --n;
    }
    way.push({1, 1});

    out_stream << way.size() << std::endl;

    while (!way.empty())
    {
        out_stream << way.top().first << ' ' << way.top().second << std::endl;
        way.pop();
    }
}


int main() {
    int n, m, cost;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("atm.in");
    out_stream.open("output");

    in_stream >> n >> m;
    std::vector<std::vector<int> > map;
    for (int i = 0; i < n; ++i)
    {
        std::vector<int> row;
        for (int j = 0; j < m; ++j)
        {
            in_stream >> cost;
            row.push_back(cost);
        }
        map.push_back(std::move(row));
    }


    std::vector<std::vector<std::pair<int, direction> > > ways_map;
    std::vector<std::pair<int, direction>> clear_row(m, {0, none});
    for (int i = 0; i < n; ++i)
        ways_map.push_back(clear_row);

    eval_ways(ways_map, map, n, m);
    print_way(out_stream, ways_map, n, m);

    in_stream.close();
    out_stream.close();

    return 0;
}