#include <iostream>
#include <fstream>
#include <stack>

bool is_num(const std::string& s)
{
    return std::all_of(
            s.begin(), s.end(),
            [](unsigned char c){ return std::isdigit(c); }
    );
}

int main() {
    int num;
    std::string str;
    std::stack<int> numbers;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("postfix.in");
    out_stream.open("postfix.out");

    while(!in_stream.eof()) {
        in_stream >> str;
        if(is_num(str)){
            num = std::stoi(str);
            numbers.push(num);
        }
        else {
            switch(str[0]) {
                case '+':
                    num = numbers.top();
                    numbers.pop();
                    num += numbers.top();
                    numbers.pop();
                    numbers.push(num);
                    break;
                case '-':
                    num = numbers.top();
                    numbers.pop();
                    num = numbers.top() - num;
                    numbers.pop();
                    numbers.push(num);
                    break;
                case '*':
                    num = numbers.top();
                    numbers.pop();
                    num *= numbers.top();
                    numbers.pop();
                    numbers.push(num);
                    break;
            }
        }
    }
    out_stream << numbers.top();

    in_stream.close();
    out_stream.close();

    return 0;
}