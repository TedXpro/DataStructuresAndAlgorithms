#include <iostream>
#include <stack>

using namespace std;

#include <stack>
class Solution
{
public:
    bool isValid(string s)
    {
        bool status = true;
        stack<char> charStack;
        for (int i = 0; i < s.length(); i++)
        {
            char ch = s[i];

            if (ch == ']')
            {
                if (charStack.empty())
                {
                    status = false;
                    break;
                }
                else if (charStack.top() != '[')
                {
                    status = false;
                    break;
                }
                else
                    charStack.pop();
            }
            else if (ch == '}')
            {
                if (charStack.empty())
                {
                    status = false;
                    break;
                }
                else if (charStack.top() != '{')
                {
                    status = false;
                    break;
                }
                else
                    charStack.pop();
            }
            else if (ch == ')')
            {
                if (charStack.empty())
                {
                    status = false;
                    break;
                }
                else if (charStack.top() != '(')
                {
                    status = false;
                    break;
                }
                else
                    charStack.pop();
            }
            else
            {
                charStack.push(ch);
            }
        }

        if (!charStack.empty())
            status = false;
        return status;
    }
};

int main()
{
    Solution solution;
    string s = "[]]]]]]";

    if (solution.isValid(s))
        cout << "Valid" << endl;
    else
        cout << "Invalid" << endl;
}