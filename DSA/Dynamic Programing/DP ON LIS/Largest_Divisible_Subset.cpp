#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ------------------------------------------------------------
    Logic:
    ------------------------------------------------------------

    This problem is almost identical to the "Printing Longest Increasing
    Subsequence (LIS)" problem.

    In LIS:
        Condition:
            nums[j] < nums[i]

    Here (Largest Divisible Subset):
        Condition:
            nums[i] % nums[j] == 0

    Since the array is sorted, every valid divisible subset can only be
    formed by extending a previous element that divides the current element.

    We use exactly the same DP + Parent reconstruction technique used for
    printing LIS.

    dp[i]
        = Length of the largest divisible subset ending at index i.

    parent[i]
        = Previous index used to reach i in the optimal subset.
          This allows us to reconstruct the final subset.

    Steps:
    1. Sort the array.
    2. For every index i, try all previous indices j.
    3. If nums[j] divides nums[i], try extending j's subset.
    4. Store the best previous index in parent[].
    5. Keep track of the index where the maximum subset ends.
    6. Follow parent[] backwards to rebuild the subset.
    7. Reverse the result because reconstruction starts from the last element.

    Time Complexity : O(n²)
    Space Complexity: O(n)
    */

    vector<int> largestDivisibleSubset(vector<int>& nums) {

        // Edge case: empty array
        if (nums.empty()) return {};

        // Sorting ensures every possible divisor appears before its multiples.
        sort(nums.begin(), nums.end());

        int n = nums.size();

        // dp[i] = length of the largest divisible subset ending at index i.
        vector<int> dp(n, 1);

        // parent[i] = previous index used to build the optimal subset ending at i.
        vector<int> parent(n);

        int maxi = 1;      // Maximum subset length found so far.
        int lastidx = 0;   // Index where the maximum subset ends.

        for (int i = 0; i < n; i++) {

            // Initially every element forms a subset of length 1,
            // so its parent is itself.
            parent[i] = i;

            // Try extending every previous valid subset.
            for (int j = 0; j < i; j++) {

                // If nums[j] divides nums[i], we can append nums[i]
                // to the subset ending at j.
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {

                    // Update the best subset length ending at i.
                    dp[i] = dp[j] + 1;

                    // Store the previous index used to reach i.
                    parent[i] = j;
                }
            }

            // Update the overall longest subset.
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastidx = i;
            }
        }

        // Reconstruct the subset by following parent pointers backwards.
        vector<int> ans;

        while (parent[lastidx] != lastidx) {
            ans.push_back(nums[lastidx]);
            lastidx = parent[lastidx];
        }

        // Push the first element of the subset.
        ans.push_back(nums[lastidx]);

        // Reconstruction is from end to beginning,
        // so reverse to obtain the correct order.
        reverse(ans.begin(), ans.end());

        return ans;
    }
};



int main(){
    return 0;
}