#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


int main() {
    int n;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("atm.in");
    out_stream.open("output");

    std::vector<int> a;
    while (!in_stream.eof())
    {
        in_stream >> n;
        a.push_back(n);
    }

    std::vector<int> dp(a.size(), 0);
    for (int i = 0; i < a.size(); ++i)
    {
        int max_len = 0;
        for (int j = i - 1; j >= 0; --j)
        {
            if (a[i] % a[j] == 0 && dp[j] > max_len)
                max_len = dp[j];
        }
        dp[i] = max_len + 1;
    }

    out_stream << dp[a.size() - 1];
    in_stream.close();
    out_stream.close();

    return 0;
}