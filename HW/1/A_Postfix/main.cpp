#include <iostream>
#include <fstream>
#include <stack>
#include <string>

int main() {
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("./postfix.txt");
//    out_stream.open("postfix.out");

//    char c;
    std::string str;
    std::getline(in_stream, str);
//    in_stream >> c;
    std::cout << str;
    std::cout << "12";
//    out_stream << c;

    in_stream.close();
//    out_stream.close();

    return 0;
}