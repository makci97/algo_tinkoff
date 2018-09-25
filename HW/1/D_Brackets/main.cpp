#include <iostream>
#include <fstream>
#include <stack>


bool is_valid(char l, char r)
{
    bool is_valid;
    
    switch (l)
    {
        case '(':
            is_valid = (r == ')');
            break;
        case '[':
            is_valid = (r == ']');
            break;
        case '{':
            is_valid = (r == '}');
            break;
        default:
            is_valid = false;
            break;
    }
    
    return is_valid;
}


int main() {
    bool is_right_seq = true;
    char c, last;
    std::stack<char> brackets;
    std::ifstream in_stream;
    std::ofstream out_stream;
    in_stream.open ("brackets.in");
    out_stream.open("brackets.out");

    while(in_stream.get(c)) {
        if (isspace(c))
            continue;
        if (c == '(' || c == '[' || c == '{')
        {
            brackets.push(c);
        } 
        else if (!brackets.empty())
        {
            last = brackets.top();
            brackets.pop();
            
            if (!is_valid(last, c))
            {
                is_right_seq = false;
                break;
            }
        } 
        else
        {
            is_right_seq = false;
            break;
        }
    }

    if (is_right_seq && brackets.empty())
    {
        out_stream << "YES";
    }
    else
    {
        out_stream << "NO";
    }

    in_stream.close();
    out_stream.close();

    return 0;
}