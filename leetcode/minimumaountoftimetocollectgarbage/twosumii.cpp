/* 167. Two Sum II - Array is Sorted */
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        vector<int> ans;
        int lower = 0, higher = numbers.size() - 1;

        while (lower < higher)
        {
            int sum = numbers[lower] + numbers[higher];

            if (sum == target)
            {
                ans.push_back(lower + 1);
                ans.push_back(higher + 1);
                break;
            }
            else if (sum > target)
                higher--;
            else
                lower++;
        }

        return ans;
    }
};