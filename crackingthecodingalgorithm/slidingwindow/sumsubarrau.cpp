#include <iostream>
#include <vector>

using namespace std;

vector<int> sumSubArrays(vector<int>, int);

int main(){
    vector<int> numbers = {1, 4, 7, 3, 2, 4, 1, 0};

    int k = 3;

    vector<int> answer = sumSubArrays(numbers, k);

    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    cout << endl;
}

vector<int> sumSubArrays(vector<int> numbers, int k){
    vector<int> answer;
    if(k > numbers.size())
        return answer;

    int sum = 0;
    for (int i = 0; i < k; i++)
        sum += numbers[i];
    answer.push_back(sum);

    for (int end = k, start = 0; end < numbers.size(); end++){
        sum = sum - numbers[start] + numbers[end];
        answer.push_back(sum);
        start++;
    }
    return answer;
}