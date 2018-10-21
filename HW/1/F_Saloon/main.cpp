#include <iostream>
#include <fstream>
#include <list>
#include <vector>


const int SERVICE_TIME = 20;


struct Time
{
    friend std::ostream& operator<<(std::ostream& os, const Time& t);

    Time() = default;
    Time(int h, int m): _h(h), _m(m) {}

    Time add(int m) const
    {
        Time sum = *this;
        sum._m += m;
        sum._h += m/60;
        sum._m %= 60;
        return sum;
    }

    bool operator<=(const Time& other) const
    {
        if (_h < other._h || (_h == other._h && _m <= other._m))
            return true;
        return false;
    }

    bool operator<(const Time& other) const
    {
        if (_h < other._h || (_h == other._h && _m < other._m))
            return true;
        return false;
    }
private:
    int _h;
    int _m;
};


std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << t._h << ' ' << t._m;
    return os;
}


int main()
{
    int n, h, m, p;
    Time last_out;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("saloon.in");
    out_stream.open("saloon.out");

    in_stream >> n;
    std::vector<Time> sorted_customers(n);
    std::list<std::pair<int, Time> > customers;

    for (int i = 0; i < n; ++i)
    {
        in_stream >> h >> m >> p;
        Time welcome_time(h, m);

        if (customers.empty())
        {
            last_out = welcome_time;
            customers.emplace_back(i, welcome_time);
        }
        else
        {
            while (!customers.empty())
            {
                if (std::max(last_out, customers.front().second).add(SERVICE_TIME) <= welcome_time)
                {
                    last_out = std::max(last_out, customers.front().second).add(SERVICE_TIME);
                    sorted_customers[customers.front().first] = last_out;
                    customers.pop_front();
                }
                else
                {
                    break;
                }
            }
            if (customers.size() <= p)
            {
                customers.emplace_back(i, welcome_time);
            }
            else
            {
                sorted_customers[i] = welcome_time;
            }
        }
    }
    while (!customers.empty())
    {
        last_out = std::max(last_out, customers.front().second).add(SERVICE_TIME);
        sorted_customers[customers.front().first] = last_out;
        customers.pop_front();
    }

    for (auto const& t:sorted_customers)
    {
        out_stream << t << '\n';
    }

    in_stream.close();
    out_stream.close();
    return 0;
}
