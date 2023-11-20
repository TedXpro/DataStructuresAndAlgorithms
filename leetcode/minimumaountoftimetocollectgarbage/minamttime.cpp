/* 2391. Minimum Amount of time to collect garbage. */
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    static const int garbageType = 3;

    vector<int> getGarbageCount(string str)
    {
        vector<int> garbages(garbageType, 0);
        for (int i = 0; i < str.length(); i++)
        {
            int index = getTruckIndexBasedOnGarbageType(str[i]);
            garbages[index] = garbages[index] + 1;
        }
        return garbages;
    }

    int getTruckIndexBasedOnGarbageType(char ch)
    {
        switch (ch)
        {
        case 'G':
            return 0;
        case 'M':
            return 1;
        case 'P':
            return 2;
        }
        return -1;
    }

    void sum(vector<int> &vect, int val)
    {
        for (int i = 0; i < vect.size(); i++)
            vect[i] = vect[i] + val;
    }

    int sum(vector<int> vect)
    {
        int sum = 0;
        for (int val : vect)
            sum += val;
        return sum;
    }

public:
    // int garbageCollection(vector<string>& garbage, vector<int>& travel) {
    //     vector<int> prefixSum(travel.size() + 1, 0);
    //     prefixSum[1] = travel[0];
    //     for(int i = 1; i < travel.size(); i++)
    //         prefixSum[i + 1] = prefixSum[i] + travel[i];

    //     unordered_map<char, int> garbageLastPos; // the last position the garbage has been spoted.
    //     unordered_map<char, int> garbageCount; // number of garbages in the town.

    //     for(int i = 0; i < garbage.size(); i++){
    //         for(char c: garbage[i]){
    //             garbageLastPos[c] = i;
    //             garbageCount[c]++;
    //         }
    //     }

    //     char garbageTypes[3] = {'M', 'P', 'G'};
    //     int ans = 0;
    //     for(char c : garbageTypes){
    //         if(garbageCount[c])
    //             ans += (prefixSum[garbageLastPos[c]] + garbageCount[c]);
    //     }

    //     return ans;
    // }

    int garbageCollection(vector<string> &garbage, vector<int> &travel)
    {
        vector<int> distance(garbageType, 0);           // the distance traveled to pick up certain garbage
        vector<int> time = getGarbageCount(garbage[0]); // number of garbage at a particular house;

        for (int i = 1; i < garbage.size(); i++)
        {
            sum(distance, travel[i - 1]);
            vector<int> houseGarbage = getGarbageCount(garbage[i]);
            for (int j = 0; j < garbageType; j++)
            {
                if (houseGarbage[j] > 0)
                {
                    time[j] += (distance[j] + houseGarbage[j]);
                    distance[j] = 0;
                }
            }
        }

        return sum(time);
    }
};

int main(){

}