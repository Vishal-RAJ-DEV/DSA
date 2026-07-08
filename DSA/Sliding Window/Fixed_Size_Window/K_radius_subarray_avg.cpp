#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem idea:
// For every index i, we want the average of the subarray centered at i
// with radius k, so the subarray length is always 2k + 1.
//
// If there are not enough elements on either side of i, the answer is -1.
//
// This file shows two ways to solve it:
// 1. Sliding window
// 2. Prefix sum

// Approach 1: Sliding window.
//
// Algorithm:
// - Build the sum of the first window of size 2k+1.
// - That window corresponds to the first valid center at index k.
// - Move the window one step to the right each time.
// - Add the new rightmost element and remove the old leftmost element.
// - Store the average for each valid center.
//
// Why this works:
// Once we know the sum of one window, the next window can be obtained in O(1)
// by shifting the boundary instead of recomputing everything.
class SolutionSlidingWindow {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> avg(n, -1);
        long long sum = 0;

        // If the window size is bigger than the array, no index can have an answer.
        if( 2 * k + 1 > n ) return avg;

        // Build the sum of the first window [0 ... 2k].
        for( int i = 0 ; i <= 2 * k ; i++){
            sum += nums[i];
        }

        // i is the center of the current window.
        for( int i = k ; i < n - k ; i++){
            // Average of the current window.
            avg[i] = sum / (2 * k + 1);

            // Shift the window one step right:
            // - add the next element entering from the right
            // - remove the element leaving from the left
            if( i + k + 1 < n ){
                sum += nums[i + k + 1];
                sum -= nums[i - k];

            }
        }

        return avg;
    }
};

// Approach 2: Prefix sum.
//
// Algorithm:
// - Precompute prefixSum where prefixSum[i] is the sum of nums[0..i-1].
// - Then any window sum from l to r is prefixSum[r+1] - prefixSum[l].
// - For each valid center i, compute the sum of [i-k ... i+k] in O(1).
//
// Why this works:
// Prefix sums store cumulative totals, so each subarray sum becomes a simple
// subtraction instead of a loop.
class SolutionPrefixSum {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size();
        int windowSize = 2 * k + 1;
        vector<int> ans(n, -1);

        // If the array is too small, every position stays -1.
        if (n < windowSize) {
            return ans;
        }

        // Build prefix sums.
        vector<long long> prefixSum(n + 1);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        // Valid centers are from k to n-k-1.
        for (int i = k; i + k < n; ++i) {
            // Sum of nums[i-k ... i+k].
            ans[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / windowSize;
        }

        return ans;
    }
};

int main(){
    return 0;
}