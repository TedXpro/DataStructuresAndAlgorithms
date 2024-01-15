#include <iostream>
#include <stack>

using namespace std;

bool isValid(string);

int main()
{
    string balExpression = "{{[([)]]}}";
    if(isValid(balExpression))
        cout << "The Expression is valid!\n";
    else
        cout << "The Expression is not valid!\n";
}

bool isValid(string s)
{
    stack<char> balanced;
    for (char ch : s)
    {
        if (ch == '}')
        {
            if (balanced.empty() || balanced.top() != '{')
                return false;
            balanced.pop();
        }
        else if (ch == ']')
        {
            if (balanced.empty() || balanced.top() != '[')
                return false;
            balanced.pop();
        }
        else if (ch == ')')
        {
            if (balanced.empty() || balanced.top() != '(')
                return false;
            balanced.pop();
        }
        else
            balanced.push(ch);
    }
    return balanced.empty();
}