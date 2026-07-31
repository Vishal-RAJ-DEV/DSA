#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
We need to split the array into exactly k continuous parts such that the
largest subarray sum is as small as possible.

Think of the answer as a value X = "allowed maximum subarray sum".
- If X is very small, splitting is not possible.
- If X is large enough, splitting is possible.

This gives a monotonic condition (false -> true), so we can binary search X.

Search range:
- low  = max element (no subarray can avoid containing that element)
- high = sum of all elements (put everything in one subarray)
*/
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        // Build binary search boundaries for the answer.
        int low = 0, high = 0;
        for (int num : nums) {
            low = max(low, num); // Minimum possible largest sum.
            high += num;         // Maximum possible largest sum.
        }

        // Store best valid answer found so far.
        int ans = high;

        // Binary search on "largest allowed subarray sum".
        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If we can split with max subarray sum <= mid,
            // try to minimize it further.
            if (isFeasible(nums, mid, k)) {
                ans = mid;
                high = mid - 1;
            } else {
                // mid is too small, need a larger allowed sum.
                low = mid + 1;
            }
        }
        return ans;
    }
    
    bool isFeasible(vector<int>& nums, int maxSum, int k) {
        // Greedily form subarrays: keep adding until exceeding maxSum,
        // then start a new subarray.
        int count = 1;
        int currentSum = 0;
        for (int num : nums) {
            currentSum += num;
            if (currentSum > maxSum) {
                count++;
                currentSum = num; // Start new subarray with current element.
                if (count > k) return false;
            }
        }

        // Needed subarrays <= k means this maxSum is feasible.
        return true;
    }
};

int main(){
    vector<int> nums = {7, 2, 5, 10, 8};
    int k = 2;
    Solution obj;

    // Example result:
    // Best split is [7,2,5] and [10,8]
    // Largest sum = max(14, 18) = 18 (minimum possible answer).
    int result = obj.splitArray(nums, k);
    cout << "Minimum largest sum after splitting into " << k << " subarrays: " << result << endl;
    
    return 0;
}
