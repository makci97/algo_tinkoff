#include <iostream>
#include <fstream>
#include <stack>

const int MAX_SCORE = 600;

int main()
{
    int n, k, num;
    int n_trucks = 0;
    std::stack<int> boxs;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("trucks.in");
    out_stream.open("trucks.out");

    in_stream >> n >> k;
    boxs.push(n);

    while (!boxs.empty())
    {
        num = boxs.top();
        boxs.pop();

        if (num <= k)
        {
            ++n_trucks;
        }
        else if (num % 2 == 0)
        {
            boxs.push(num/2);
            boxs.push(num/2);
        }
        else
        {
            boxs.push(num/2);
            boxs.push(num/2 + 1);
        }
    }

    out_stream << n_trucks;

    in_stream.close();
    out_stream.close();

    return 0;
}