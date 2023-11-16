/* Given an array of integers, find maximum / minimum
 sum subarray of the required size and return the 
 subarray elements. */
#include <iostream>
#include <vector>

using namespace std;

vector<int> findMaxSubarraySum(vector<int>, int);

int main(){
    vector<int> numbers = {6, -3, -5, 1, 2, 0, 4};
    int k = 4;

    vector<int> ans = findMaxSubarraySum(numbers, k);
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
}

vector<int> findMaxSubarraySum(vector<int> numbers, int k){
    if(k >= numbers.size())
        return numbers;
    
    int max = INT_MIN + 1;
    int sum = 0;
    for (int i = 0; i < k; i++)
        sum += numbers[i];
    max = sum;
    int start = 0, end = k - 1;

    for (int i = 0, j = k; j < numbers.size(); i++, j++){
        sum -= numbers[i];
        sum += numbers[j];
        if(sum > max) {
            max = sum;
            start = i + 1;
            end = j;
        }
    }

    return vector<int>(numbers.begin() + start, numbers.begin() + end + 1);
}