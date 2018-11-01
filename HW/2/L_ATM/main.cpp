#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


int get_min_n_coins(
        int sum, const std::vector<int>& coins,
        std::vector<std::pair<int, int> >& dp,
        std::vector<bool>& is_eval
)
{
    if (sum < 0)
        return -1;
    if (sum == 0)
    {
        dp[0] = {0, 0};
        is_eval[0] = true;
    }
    if (is_eval[sum])
        return dp[sum].first;

    int min_way_len = -1;
    int best_coin = -1;
    for (auto const& c : coins)
    {
        int cur_way_len = get_min_n_coins(sum - c, coins, dp, is_eval);
        if (cur_way_len >= 0)
        {
            if (min_way_len == -1 || min_way_len > cur_way_len)
            {
                min_way_len = cur_way_len;
                best_coin = c;
            }
        }
    }
    if (min_way_len != -1)
        dp[sum] = {min_way_len + 1, best_coin};
    else
        dp[sum] = {min_way_len, best_coin};
    is_eval[sum] = true;
    return dp[sum].first;
}


void print_way(
        int sum, std::vector<std::pair<int, int> >& dp, std::ofstream& out_stream
)
{
    int coin = dp[sum].second;
    while (sum > 0 && coin != -1)
    {
        out_stream << coin;
        sum -= coin;
        if (sum > 0)
            out_stream << ' ';
        coin = dp[sum].second;
    }
}


int main() {
    int n, sum, coin;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("atm.in");
    out_stream.open("atm.out");

    in_stream >> n;
    std::vector<int> coins;
    for (int i = 0; i < n; ++i)
    {
        in_stream >> coin;
        coins.push_back(coin);
    }
    in_stream >> sum;

    std::vector<std::pair<int, int> > dp(sum + 1, {-1, -1});
    std::vector<bool> is_eval(sum + 1, false);
    int min_way_len = get_min_n_coins(sum, coins, dp, is_eval);
    out_stream << min_way_len << std::endl;
    if (min_way_len != -1)
    {
        print_way(sum, dp, out_stream);
    }

    in_stream.close();
    out_stream.close();

    return 0;
}