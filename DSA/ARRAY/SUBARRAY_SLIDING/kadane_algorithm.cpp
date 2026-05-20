// Question:
// Given an array of integers, find the maximum sum of any contiguous subarray.
// Return the maximum sum.
//
// Detailed Algorithm (Kadane's Algorithm, sum reset version):
// 1) Start with sum = 0 and maxi = -infinity.
// 2) Add each element to sum as you move right.
// 3) Update maxi with the largest sum seen so far.
// 4) If sum becomes negative, reset it to 0 (start a new subarray).
// 5) After the loop, maxi is the answer.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//this code for the maximum sum of any contiguous subarray using Kadane's Algorithm (sum reset version)
int kadane(vector<int>& arr) {
    int maxi = INT_MIN;
    int sum = 0;

    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];

        // update maximum
        maxi = max(maxi, sum);

        // if sum becomes negative, discard it
        if (sum < 0) {
            sum = 0;
        }
    }

    return maxi;
}

//and this is for minimum sum of any contiguous subarray using Kadane's Algorithm (sum reset version)
int minimumSubarraySum(vector<int>& arr) {

    int mini = INT_MAX;
    int sum = 0;

    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];

        mini = min(mini, sum);

        if (sum > 0)
            sum = 0;
    }

    return mini;
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // sample input
    int answer = kadane(arr); // compute result
    cout << "Maximum subarray sum is: " << answer; // print result
    return 0; // end program
}
