#include <iostream>
#include <fstream>
#include <vector>


int main()
{
    int N, K, num, min;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("min.in");
    out_stream.open("min.out");

    in_stream >> N >> K;
    std::vector<int> nums;
    nums.reserve(N);

    for (int i = 0; i < N; ++i)
    {
        in_stream >> num;
        nums.push_back(num);
    }

    for (int i = 0; i < N - K + 1; ++i)
    {
        min = nums[i];
        for (int j = i + 1; j < i + K; ++j)
        {
            if (min > nums[j])
                min = nums[j];
        }
        out_stream << min << '\n';
    }

    in_stream.close();
    out_stream.close();
    return 0;
}
