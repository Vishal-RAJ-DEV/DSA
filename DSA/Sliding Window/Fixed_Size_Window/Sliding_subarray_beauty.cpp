/*
 * Problem: For each subarray of size k, find "beauty" = x-th smallest negative number.
 * If fewer than x negatives exist, beauty = 0.
 *
 * Intuition:
 * - Constraint: -50 <= nums[i] <= 50. Only negatives matter.
 * - Use freq[50] mapping index 0→-50, 1→-49, ..., 49→-1.
 * - Scan freq from smallest (-50→-1), accumulate count. When count >= x, index→value is the answer.
 * - Sliding window: update freq as window moves, recompute beauty via linear scan of 50-sized freq.
 *
 * Algo:
 * 1. freq[50] = {0}. Build first window: for each negative, freq[val+50]++.
 * 2. For each window:
 *    - Remove outgoing: if negative, freq[val+50]--.
 *    - Add incoming: if negative, freq[val+50]++.
 *    - getBeauty: iterate i=0..49, cnt += freq[i]; when cnt >= x, return i-50.
 *      If loop ends, return 0.
 * 3. Return ans vector.
 *
 * TC: O(n * 50) = O(n) per input. Space: O(50 + n) = O(n).
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int getBeauty(vector<int>& freq, int x) {
        int cnt = 0;
        for (int i = 0; i < 50; i++) {
            cnt += freq[i];
            if (cnt >= x)
                return i - 50;
        }
        return 0;
    }

    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        vector<int> freq(50, 0);
        vector<int> ans;

        for (int i = 0; i < k; i++)
            if (nums[i] < 0)
                freq[nums[i] + 50]++;

        ans.push_back(getBeauty(freq, x));

        for (int i = k; i < nums.size(); i++) {
            if (nums[i - k] < 0)
                freq[nums[i - k] + 50]--;
            if (nums[i] < 0)
                freq[nums[i] + 50]++;
            ans.push_back(getBeauty(freq, x));
        }

        return ans;
    }
};



int main(){
    Solution sol;
    vector<int> nums = {1,-1,-3,-2,3};
    int k = 3;
    int x = 2;
    vector<int> result = sol.getSubarrayBeauty(nums, k, x);
    
    return 0;
}
