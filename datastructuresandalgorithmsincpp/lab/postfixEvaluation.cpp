#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string postfixExpression = "23*54*+9-";
    stack<double> postfix;

    for(char ch : postfixExpression){
        if(ch >= '0' || ch <= 9)
            postfix.push(ch - '0');
        else {
            double second = postfix.top();
            postfix.pop();
            double first = postfix.top();
            postfix.pop();
            if(ch == '+')
                postfix.push(first + second);
            else if(ch == '-')
                postfix.push(first - second);
            else if(ch == '*')
                postfix.push(first * second);
            else if(ch == '/')
                postfix.push(first / second);
        }
    }

    cout << "The answer is " << postfix.top() << endl;
}