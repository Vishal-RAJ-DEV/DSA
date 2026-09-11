#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: Count Fair Pairs
    ==========================
    A pair (i, j) is called "fair" if:
        1. i < j (i comes before j in the array)
        2. lower <= nums[i] + nums[j] <= upper (sum is within given range)

    APPROACH: Sort + Binary Search
    ==============================
    Instead of checking every pair (O(n^2)), we sort the array and use
    binary search to find valid partners for each element in O(log n).

    KEY INSIGHT:
    For a fixed nums[i], we need to find how many nums[j] (where j > i) satisfy:
        lower <= nums[i] + nums[j] <= upper

    Rearranging:
        lower - nums[i] <= nums[j] <= upper - nums[i]

    So for each nums[i], we count elements in range [leftValue, rightValue] where:
        leftValue  = lower - nums[i]   (minimum valid partner)
        rightValue = upper - nums[i]   (maximum valid partner)

    We use lower_bound and upper_bound to find this count efficiently.

    COMPLEXITY:
        Time:  O(n log n) - sorting + binary search for each element
        Space: O(1) extra space (excluding input)
*/

class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        // Step 1: Sort the array to enable binary search
        // After sorting, for any nums[i], all potential partners nums[j] (j > i)
        // are to its right and in non-decreasing order
        sort(nums.begin(), nums.end());

        long long ans = 0;  // Total count of fair pairs
        int n = nums.size(); // Size of the array

        // Step 2: For each element, count how many elements to its right
        // form a fair pair with it
        for (int i = 0; i < n; i++) {

            // Calculate the range of valid partner values for nums[i]
            // If nums[i] + nums[j] must be in [lower, upper], then:
            //   nums[j] must be in [lower - nums[i], upper - nums[i]]

            long long leftValue = (long long)lower - nums[i];
            // leftValue: minimum value a partner must have to form a valid pair

            long long rightValue = (long long)upper - nums[i];
            // rightValue: maximum value a partner can have to form a valid pair

            // Step 3: Use binary search to find the range of valid elements
            // Search only in elements after index i (nums.begin() + i + 1 to nums.end())
            // This ensures we don't count the same pair twice and j > i

            auto left = lower_bound(
                nums.begin() + i + 1,  // Start searching from i+1 (elements after i)
                nums.end(),            // Search until end of array
                leftValue              // Find first element >= leftValue
            );
            // 'left' points to the first element that is >= leftValue
            // This is the start of our valid range

            auto right = upper_bound(
                nums.begin() + i + 1,  // Start searching from i+1
                nums.end(),            // Search until end of array
                rightValue             // Find first element > rightValue
            );
            // 'right' points to the first element that is > rightValue
            // This is one past the end of our valid range

            // Step 4: Count valid elements in [leftValue, rightValue]
            // The number of elements in range is: (position after last) - (position of first)
            // This is a standard trick with STL iterators
            ans += right - left;
        }

        return ans; // Return total count of fair pairs
    }
};


int main(){
    return 0;
}