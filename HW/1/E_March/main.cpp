#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <forward_list>

const int MAX_SCORE = 10000;

int main()
{
    long int N, base_high, high;
    std::string str;
    std::vector<std::forward_list<long int> > highs(2 * MAX_SCORE + 1);
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("input");
    out_stream.open("output");

    in_stream >> N;
    in_stream >> base_high;
    highs[MAX_SCORE].push_front(base_high);
    for(int i = 1; i < N; ++i)
    {
        in_stream >> high;

        highs[MAX_SCORE + high - base_high].push_front(high);
    }

    for(auto vec_it = highs.begin(); vec_it != highs.end(); ++vec_it)
    {
        for(auto list_it = (*vec_it).begin(); list_it != (*vec_it).end(); ++list_it)
        {
            out_stream << *list_it << " ";
        }
    }

    in_stream.close();
    out_stream.close();

    return 0;
}