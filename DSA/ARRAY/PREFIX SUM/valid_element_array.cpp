/*
You are given an integer array nums.

An element nums[i] is considered valid if it satisfies at least one of the following conditions:

It is strictly greater than every element to its left.
It is strictly greater than every element to its right.
The first and last elements are always valid.

Return an array of all valid elements in the same order as they appear in nums.

 

Example 1:

Input: nums = [1,2,4,2,3,2]

Output: [1,2,4,3,2]

Explanation:

nums[0] and nums[5] are always valid.
nums[1] and nums[2] are strictly greater than every element to their left.
nums[4] is strictly greater than every element to its right.
Thus, the answer is [1, 2, 4, 3, 2].

Note: Please do not copy the description during the contest to maintain the integrity of your submissions.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    std::vector<int> findValidElements(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        std::vector<bool> isValid(n, false);
        
        // The first and last elements are always valid per rules
        isValid[0] = true;
        isValid[n - 1] = true;

        // Check: Strictly greater than everything to the left
        int maxLeft = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] > maxLeft) {
                isValid[i] = true;
            }
            maxLeft = std::max(maxLeft, nums[i]);
        }

        // Check: Strictly greater than everything to the right
        int maxRight = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > maxRight) {
                isValid[i] = true;
            }
            maxRight = std::max(maxRight, nums[i]);
        }

        // Collect results in original order
        //push all the valid element in the result vector

        std::vector<int> result;
        for (int i = 0; i < n; i++) {
            if (isValid[i]) {
                result.push_back(nums[i]);
            }
        }
        
        return result;
    }
};


int main(){
    Solution sol;
    vector<int> nums = {1, 2, 4, 2, 3, 2};
    vector<int> validElements = sol.findValidElements(nums);
    cout << "Valid elements: ";
    for (int elem : validElements) {
        cout << elem << " ";
    }
    
    return 0;
}
