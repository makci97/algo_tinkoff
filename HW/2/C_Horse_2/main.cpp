#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int n_ways(
        std::vector<std::vector<std::pair<int, bool> > >& desk,
        int n, int m, int N, int M)
{
    if (n < 0 || n > N || m < 0 || m > M)
        return 0;
    if (n == 0 && m == 0)
        desk[0][0] = {1, true};
    if (desk[n][m].second)
        return desk[n][m].first;

    desk[n][m].first += n_ways(desk, n - 2, m - 1, N, M);
    desk[n][m].first += n_ways(desk, n - 1, m - 2, N, M);
    desk[n][m].first += n_ways(desk, n + 1, m - 2, N, M);
    desk[n][m].first += n_ways(desk, n - 2, m + 1, N, M);
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

    out_stream << n_ways(desk, n - 1, m - 1, n - 1, m - 1);

    in_stream.close();
    out_stream.close();

    return 0;
}