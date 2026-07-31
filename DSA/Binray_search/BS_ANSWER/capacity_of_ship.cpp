#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int totalday(vector<int> &arr, int cap)
{
    int load = 0;
    int day = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (load + arr[i] > cap)
        { // if total load is greater then  reset the load
            day++;
            load = arr[i];
        }
        else
        {
            load += arr[i];
        }
    }
    return day;
}
int shipWithinDays(vector<int> &weights, int days)
{
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (totalday(weights, mid) <= days)
        { // search of the high capacity in the right side
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}

int main()
{
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;
    cout << shipWithinDays(weights, days) << endl;
    return 0;
}
