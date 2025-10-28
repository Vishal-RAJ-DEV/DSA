#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
You are given an array with unique elements of stalls[], which denote the positions of stalls. You are also given an integer k which denotes the number of aggressive cows. The task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.

Examples:

Input: stalls[] = [1, 2, 4, 8, 9], k = 3
Output: 3
Explanation: The first cow can be placed at stalls[0],
the second cow can be placed at stalls[2] and
the third cow can be placed at stalls[3].
The minimum distance between cows in this case is 3, which is the largest among all possible ways.

*/
bool canweplace(vector<int> &stalls, int dist, int k)
{
    int n = stalls.size();
    int cntcow = 1;       // first cow
    int last = stalls[0]; // first cow goes to first index at first time
    for (int i = 1; i < n; i++)
    { // go 1st to last (1st cow already at 0th idx)
        if (stalls[i] - last >= dist)
        { // dist is mid (current distance for checking )
            cntcow++;
            last = stalls[i]; // update the new index
        }
        if (cntcow >= k)
            return true; // we get the required cows
    }
    return false;
}
int aggressiveCows(vector<int> &stalls, int k)
{
    // code here

    int n = stalls.size();
    sort(stalls.begin(), stalls.end());
    int low = 1;
    int high = stalls[n - 1] - stalls[0];
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (canweplace(stalls, mid, k) == true)
        {
            low = mid + 1; // search for the larger distance
        }
        else
        {
            high = mid - 1; // if not found at that mid distance go for smaller value
        }
    }
    return high; // at high the min distance which is max can go
}

int main()
{
    vector<int> stalls = {1, 2, 4, 8, 9};
    int k = 3;
    cout << aggressiveCows(stalls, k) << endl;
    return 0;
}