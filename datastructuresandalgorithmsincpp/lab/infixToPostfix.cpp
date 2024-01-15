#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string infixExpression = "4 + 3*(6*3-12)"; // " a - (b / (c - d) * e + f) ^ g "
    string postfixExpression = "";
    stack<char> st;

    for (char ch : infixExpression)
    {
        if (ch == ' ')
            continue;
        if (ch >= 'a' && ch <= 'z')
            postfixExpression += ch;
        else if (ch == '+' || ch == '-')
        {
            while (!st.empty() && (st.top() != '('))
            {
                postfixExpression += st.top();
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == '*' || ch == '/')
        {
            while (!st.empty() && (st.top() == '*' || st.top() == '/' || st.top() == '^'))
            {
                postfixExpression += st.top();
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == ')')
        {
            while (st.top() != '(')
            {
                postfixExpression += st.top();
                st.pop();
            }
            st.pop();
        }
        else
            st.push(ch);
    }

    while (!st.empty())
    {
        postfixExpression += st.top();
        st.pop();
    }

    cout << postfixExpression << endl;
}