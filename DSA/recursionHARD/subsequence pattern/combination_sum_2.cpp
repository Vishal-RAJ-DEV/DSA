#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]]
Explanation: These are the unique combinations whose sum is equal to target.
 
Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: [[1,2,2],[5]]
Explanation: These are the unique combinations whose sum is equal to target.
*/
void generate(int indx, int n, int s, int sum, vector<int> &arr, vector<int> &subset)
{
    // base case
    if (s == sum)
    { // if the sum matches the target sum then print the subset
        cout << "[ ";
        for (auto &it : subset)
        {
            cout << it << " ";
        }
        cout << "]";
        cout << endl;
        return; //return here because we have found a valid subset so no need to proceed further
    }
    if (indx == n || s > sum) return; //if we have reached the end of the array or sum exceeds the target sum then return

    subset.push_back(arr[indx]);
    s += arr[indx];
    // exclude the element which is at indx
    generate(indx + 1, n, s, sum, arr, subset);
    // include after the recursion backtrack the changes

    s -= arr[indx];
    subset.pop_back();
    // this while loop will skip all the duplicates of the current element
    while (indx + 1 < n && arr[indx] == arr[indx + 1]) {
        indx++; //skip the duplicates
    }

    // include call which adds the element at indx
    generate(indx + 1, n, s, sum, arr, subset);
    // backtrack again and remove the element at index here
}

int main()
{
    vector<int> arr = {10,1,2,7,6,1,5};
    int n = arr.size(); // Length of the string "abc"
    int sum = 8;        // The target sum we want to achieve
    vector<int> subset;
    sort(arr.begin(), arr.end());
    generate(0, n, 0, sum, arr, subset);

    


    return 0;
}

