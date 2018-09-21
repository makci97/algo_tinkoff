#include <algorithm>
#include <iostream>
#include <fstream>
#include <stack>

//bool is_num(const std::string& s)
//{
//    return std::all_of(
//            s.begin(), s.end(),
//            [](unsigned char c){ return std::isdigit(c); }
//    );
//}

int main() {
    int num;
    char str;
    std::stack<int> numbers;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("postfix.in");
    out_stream.open("postfix.out");

    while(in_stream.get(str)) {
//        if (isspace(str))
//            continue;
//    while(!in_stream.eof()) {
//        in_stream >> str;

//        if(is_num(str)){
//            num = std::stoi(str);
        if(std::isdigit(str)){
//            std::cout << str << std::endl;
            num = std::atoi(&str);
            numbers.push(num);
        }
        else {
            switch(str) {
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
//        std::cout << str << " " << numbers.top() << std::endl;
    }
    out_stream << numbers.top();
//    std::cout << str << " " << numbers.top() << std::endl;

    in_stream.close();
    out_stream.close();

    return 0;
}