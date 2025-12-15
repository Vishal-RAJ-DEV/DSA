#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Example 1:
Input: array = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation: 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
             7 is a candidate, and 7 = 7.
             These are the only two combinations.


Example 2:
Input: array = [2], target = 1
Output: []
Explaination: No combination is possible.
            
*/
void generate1(int indx, int target, vector<int> &arr, vector<int> &current, vector<vector<int>> &result)
{
    // Base case: target achieved
    if (target == 0)
    {
        result.push_back(current);
        return;
    }
    
    // Base case: out of bounds or target becomes negative
    if (indx == arr.size() || target < 0)
    {
        return;
    }

    // Include current element (can use same element again)
    current.push_back(arr[indx]);
    generate1(indx, target - arr[indx], arr, current, result);  // Same index for reuse
    current.pop_back();  // Backtrack

    // Exclude current element (move to next)
    generate1(indx + 1, target, arr, current, result);
}
void generate(int indx, int n, int s, int sum, vector<int> &arr, vector<int> &subset)
{
    // base case
    if (indx == n || s > sum) //if the sum exceeds the target sum then return 
    {
        if (s == sum)
        { // if the sum matches the target sum then print the subset
            cout << "[ ";
            for (auto &it : subset)
            {
                cout << it << " ";
            }
            cout << "]";
            cout << endl;
        }
        return;
    }

    subset.push_back(arr[indx]);
    s += arr[indx];
    // exclude the element which is at indx
    generate(indx, n, s, sum, arr, subset);
    // include after the recursion backtrack the changes

    s -= arr[indx];
    subset.pop_back();
    // include call which adds the element at indx
    generate(indx + 1, n, s, sum, arr, subset);
    // backtrack again and remove the element at index here
}

int main()
{
    vector<int> arr = {2, 3, 5};
    int n = arr.size(); // Length of the string "abc"
    int sum = 8;        // The target sum we want to achieve
    vector<int> subset;
    sort(arr.begin(), arr.end());
    generate(0, n, 0, sum, arr, subset);

    
    vector<vector<int>> result;
    vector<int> current;
    generate1(0, sum, arr, current, result);
    cout << "Combinations summing to " << sum << " are:" << endl;
    for (auto &combination : result)
    {
        cout << "[ ";
        for (auto &num : combination)
        {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}