#include <iostream>
#include <fstream>
#include <list>
#include <vector>


int main()
{
    int n;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("grasshopper.in");
    out_stream.open("grasshopper.out");

    in_stream >> n;


    for (auto const& t:sorted_customers)
    {
        out_stream << t << '\n';
    }

    in_stream.close();
    out_stream.close();
    return 0;
}
