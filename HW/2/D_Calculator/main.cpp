#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


enum operation {none, plus_1, prod_2, prod_3};


void min_n_with_op(
        std::vector<std::pair<int, operation> >& ways2num,
        int n, operation op, int prev_min_n_operations)
{
    if (ways2num[n].second == none || ways2num[n].first > prev_min_n_operations + 1)
    {
        ways2num[n] = {prev_min_n_operations + 1, op};
    }
}


int n_ways(std::vector<std::pair<int, operation> >& ways2num, int n)
{
    ways2num[1] = {0, none};
    for (int i = 1; i < n; ++i)
    {
        if (i * 3 <= n)
            min_n_with_op(ways2num, i * 3, prod_3, ways2num[i].first);
        if (i * 2 <= n)
            min_n_with_op(ways2num, i * 2, prod_2, ways2num[i].first);
        min_n_with_op(ways2num, i + 1, plus_1, ways2num[i].first);
    }
    return ways2num[n].first;
}

int get_prev(int n, operation op)
{
    if (op == plus_1)
        return n - 1;
    else if (op == prod_2)
        return n/2;
    else if (op == prod_3)
        return n/3;
    return -1;
}

void print_way(
        std::ofstream& out_stream,
        std::vector<std::pair<int, operation> >& ways2num,
        int n
)
{
    std::stack<int> way;
    while (n != 1)
    {
        way.push(n);
        n = get_prev(n, ways2num[n].second);
    }

    out_stream << 1;
    while (!way.empty())
    {
        out_stream << ' '  << way.top();
        way.pop();
    }
}

int main() {
    int n;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open("input");
    out_stream.open("output");

    in_stream >> n;
    std::vector<std::pair<int, operation> > ways2num(n + 1, {0, none});
    out_stream << n_ways(ways2num, n) << std::endl;
    print_way(out_stream, ways2num, n);

    in_stream.close();
    out_stream.close();

    return 0;
}