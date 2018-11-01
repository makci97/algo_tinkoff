#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main() {
    int n;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("atm.in");
    out_stream.open("output");

    in_stream >> n;
    std::map<int, std::bitset<2> > int2mask;
    for (int i = 0; i < 4; ++i)
    {
        int2mask[i] = std::bitset<2>(i);
    }
    std::map<std::bitset<2>, std::vector<int> > dp;
    std::bitset<16> bits(534);
    bits.
    in_stream.close();
    out_stream.close();

    return 0;
}