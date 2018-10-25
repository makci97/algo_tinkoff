#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int n_ways(std::vector<int>& ways, int n, int k)
{
    if(n == 1)
        ways[0] = 1;
    if(ways[n - 1] != 0)
        return ways[n - 1];

    for(int i = 1; i <= k; ++i)
    {
        if(n - i < 1)
            break;
        ways[n - 1] += n_ways(ways, n - i, k);
    }
    return ways[n - 1];
}

int main() {
    int n, k;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("grasshopper.in");
    out_stream.open("grasshopper.out");

    in_stream >> n >> k;
    std::vector<int> ways(n, 0);
    out_stream << n_ways(ways, n, k);

    in_stream.close();
    out_stream.close();

    return 0;
}