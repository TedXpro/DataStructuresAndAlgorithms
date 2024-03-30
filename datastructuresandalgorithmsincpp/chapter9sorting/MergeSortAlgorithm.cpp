#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &numbers, int first, int last)
{
    int mid = (first + last) / 2;
    int index1 = 0;
    int index2 = first;
    int index3 = mid + 1;

    vector<int> temp(last - first + 1);
    while (index2 <= mid && index3 <= last)
    {
        if (numbers[index2] < numbers[index3])
            temp[index1++] = numbers[index2++];
        else
            temp[index1++] = numbers[index3++];
    }

    while (index2 <= mid)
        temp[index1++] = numbers[index2++];

    while (index3 <= last)
        temp[index1++] = numbers[index3++];

    for (int i = 0; i < temp.size(); i++)
        numbers[first + i] = temp[i];
}

void mergeSort(vector<int> &numbers, int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergeSort(numbers, first, mid);
        mergeSort(numbers, mid + 1, last);
        merge(numbers, first, last);
    }
}

int main()
{
    vector<int> numbers{9, 8, 7, 6, 5, 4, 3, 2, 1};
    cout << "Before sorting the array using MERGE SORT\n";
    for (int num : numbers)
        cout << num << " ";
    cout << "\n\n--------------------\n\n";

    mergeSort(numbers, 0, 8);

    cout << "After sorting the array\n";
    for (int num : numbers)
        cout << num << " ";
    cout << endl;
}