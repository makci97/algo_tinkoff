#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <queue>
#include <cmath>
#include <bitset>


const int MAX_VAL = 9999;


int get_digits_sum(int v)
{
    int sum = 0;
    while (v >= 10)
    {
        sum += v % 10;
        v = std::floor(v / 10);
    }
    sum += v;
    return sum;
}


std::vector<int> get_neighbours(int v)
{
    int nums[] = {v * 3, v - 2, v + get_digits_sum(v)};
    std::vector<int> neighbours;

    for (int num : nums)
    {
        if (num >= 0 && num <= MAX_VAL)
            neighbours.push_back(num);
    }
    return neighbours;
}


int main() {
    int a, b, v;
    std::string line;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("crazycalc.in");
    out_stream.open("crazycalc.out");

    // prepare data containers
    in_stream >> a >> b;
    std::bitset<MAX_VAL + 1> used(false);
    std::vector<int> dist(MAX_VAL + 1, -1);
    std::queue<int> q;

    // start values
    used[a] = true;
    dist[a] = 0;
    q.push(a);

    // BFS
    while (!q.empty() && !used[b])
    {
        v = q.front();
        q.pop();
        auto neighbours = get_neighbours(v);
        for (int neigh: neighbours)
        {
            if (used[neigh])
                continue;
            used[neigh] = true;
            dist[neigh] = dist[v] + 1;
            q.push(neigh);
        }
    }

    // output
    out_stream << dist[b];

    in_stream.close();
    out_stream.close();

    return 0;
}