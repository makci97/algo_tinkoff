#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int n_ways(std::vector<std::vector<std::pair<int, bool> > >& desk, int n, int m)
{
    if (n == 0 && m == 0)
        desk[0][0] = {1, true};
    if (desk[n][m].second)
        return desk[n][m].first;
    if (n >= 2 && m >= 1)
        desk[n][m].first += n_ways(desk, n - 2, m - 1);
    if (n >= 1 && m >= 2)
        desk[n][m].first += n_ways(desk, n - 1, m - 2);
    desk[n][m].second = true;

    return desk[n][m].first;
}


int main() {
    int n, m;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("atm.in");
    out_stream.open("output");

    in_stream >> n >> m;
    std::vector<std::vector<std::pair<int, bool> > > desk;
    std::vector<std::pair<int, bool> > clear_row(m, {0, false});
    for (int i = 0; i < n; ++i)
        desk.push_back(clear_row);

    out_stream << n_ways(desk, n - 1, m - 1);

    in_stream.close();
    out_stream.close();

    return 0;
}