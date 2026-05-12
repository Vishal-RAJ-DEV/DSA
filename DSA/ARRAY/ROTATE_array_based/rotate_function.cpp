#include <iostream> // basic I/O
#include <bits/stdc++.h> // common STL headers
using namespace std; // avoid std:: prefix
/*
Example 1:

Input: nums = [4,3,2,6]
Output: 26
Explanation:
F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

*/
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size(); // length of the array

        long sum = 0; // sum of all elements (Σ nums[i])
        long F = 0; // F(0) = Σ i * nums[i]

        for (int i = 0; i < n; i++) {
            sum += nums[i]; // add to total sum
            F += (long)i * nums[i]; // accumulate F(0)
        }

        long result = F; // current maximum over all F(k)

        for (int k = 1; k < n; k++) {
            // Formula: F(k) = F(k-1) + sum - n * nums[n-k]
            // Reason: rotating right by 1 shifts each index +1 (adds sum),
            // but the element that wraps from end to index 0 loses n*value.
            F = F + sum - (long)n * nums[n - k]; // update F(k) from F(k-1)

            result = max(result, F); // track best value
        }
        
        return (int)result; // cast back to int for output
    }
};


int main(){
    vector<int> nums = {4, 3, 2, 6}; // sample input
    Solution sol; // create solver
    cout << "Maximum value of F(k): " << sol.maxRotateFunction(nums) << endl; // run and print

    return 0; // success
}