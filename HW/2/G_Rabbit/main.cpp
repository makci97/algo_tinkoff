#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


enum direction {none, south, east};


int get_max_squares(std::vector<std::vector<int> >& map, int n, int m)
{
    int max_squares = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (i == 0 || j == 0)
            {
                if (max_squares < map[i][j])
                    max_squares = map[i][j];
            }
            else
            {
                if (map[i][j] == 1)
                {
                    int min = std::min(
                            std::min(map[i - 1][j], map[i][j - 1]), map[i - 1][j - 1]);
                    map[i][j] = min + 1;
                    if (max_squares < map[i][j])
                        max_squares = map[i][j];
                }
            }
        }
    }
    return max_squares;
}


int main() {
    int n, m, carrot;
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
            in_stream >> carrot;
            row.push_back(carrot);
        }
        map.push_back(std::move(row));
    }

    out_stream << get_max_squares(map, n, m);

    in_stream.close();
    out_stream.close();

    return 0;
}