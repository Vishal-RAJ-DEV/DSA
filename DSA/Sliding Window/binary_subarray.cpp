/*
Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.
Input: nums = [1, 0, 0, 1, 1, 0], goal = 2  
Output: 6
Explanation: There are 6 subarrays with sum exactly equal to 2:
[1, 0, 0, 1], [0, 0, 1, 1], [0, 1, 1], [1, 1], [1, 1, 0], [0,0,1,1,0]
    
Input: nums = [0,0,0,0,0,0], goal = 0  
Output: 21  
Explanation: All subarrays with only 0s will have sum = 0.  
There are 21 such subarrays in total (n(n+1)/2 = 6*7/2 = 21).
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// better approch using hashmap
int numSubarraysWithSum(vector<int> &nums, int goal)
{
    int n = nums.size();
    unordered_map<int, int> mpp;
    int prefix_sum = 0;
    int cnt = 0;
    mpp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        prefix_sum += nums[i];

        int remove = prefix_sum - goal;
        cnt += mpp[remove];

        mpp[prefix_sum] += 1;
    }
    return cnt;
}

//optimal approch using sliding window

class Solution {
public:
    // Function to calculate number of subarrays with sum exactly equal to goal
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // Return difference between subarrays with sum at most goal and at most (goal - 1)
        // cout<<atMost(nums, goal)<<" "<<atMost(nums, goal - 1)<<endl;
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }

private:
    // Helper function to compute number of subarrays with sum at most k
    int atMost(vector<int>& nums, int k) {
        // If k is negative, no such subarrays exist
        if (k < 0) return 0;

        int left = 0;
        int sum = 0;
        int count = 0;

        // Traverse the array using right pointer
        for (int right = 0; right < nums.size(); right++) {
            // Add current element to sum
            sum += nums[right];

            // Shrink the window from the left if sum exceeds k
            while (sum > k) {
                sum -= nums[left];
                left++;
            }

            // Add the number of valid subarrays ending at right
            count += (right - left + 1);
        }

        return count;
    }
};


int main()
{
    vector<int> nums = {1,0,1,0,1};
    int goal = 2;
    Solution sol;
    cout << sol.numSubarraysWithSum(nums, goal) << endl;

    
    return 0;
}