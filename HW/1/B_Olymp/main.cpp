#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <forward_list>

const int MAX_SCORE = 600;

int main()
{
    int N, score;
    std::string str;
    std::vector<std::forward_list<int> > members(MAX_SCORE + 1);
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("olymp.in");
    out_stream.open("olymp.out");

    in_stream >> N;
    for(int i = 1; i < N + 1; ++i)
    {
        in_stream >> score;

        members[score].push_front(i);
    }

    for(auto r_vec_it = members.rbegin(); r_vec_it != members.rend(); ++r_vec_it)
    {
        for(auto list_it = (*r_vec_it).begin(); list_it != (*r_vec_it).end(); ++list_it)
        {
            out_stream << *list_it << " ";
        }
    }

    in_stream.close();
    out_stream.close();

    return 0;
}