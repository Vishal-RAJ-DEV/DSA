// Question:
// Given an array of positive integers and a target sum, find the
// 1-based start and end indices of the first subarray whose sum is
// exactly the target. If no such subarray exists, return -1.


#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Detailed Algorithm (sliding window for positive numbers):
// 1) Start with an empty window [start..end] and sum = 0.
// 2) Expand the window by moving end to the right and add arr[end] to sum.
// 3) If sum becomes greater than target, shrink from the left by moving start
//    forward and subtract arr[start] until sum <= target.
// 4) If sum == target, return the 1-based indices [start+1, end+1].
// 5) If the loop ends with no match, return {-1}.
class Solution {
  public:
    vector<int> subarraySum(vector<int> &arr, int target) {
        int start = 0, end = 0; // window boundaries
        vector<int> res; // stores answer indices
        int sum = 0; // sum of current window
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i]; // expand window by adding arr[i]

            // when sum reaches or exceeds target, set end and try to shrink
            if (sum >= target) {
                end = i; // current right boundary

                // shrink from left until sum <= target
                while (sum > target && start < end) {
                    sum -= arr[start];
                    start++;
                }
                // if exact target found, return 1-based indices
                if (sum == target) {
                    res.push_back(start + 1);
                    res.push_back(end + 1);
                    return res;
                }
            }
        }
        return {-1}; // no subarray found
    }
};

int main() {
    Solution sol; // create object
    vector<int> arr = {1, 2, 3, 7, 5}; // sample array
    int target = 12; // target sum
    vector<int> result = sol.subarraySum(arr, target); // find indices
    for (int i : result) {
        cout << i << " "; // print result
    }

    return 0; // end program
}