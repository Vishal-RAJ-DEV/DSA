#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Count how many pairs have distance <= mid
    int countPairs(vector<int>& nums, int mid) {
        int count = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {

            // Move left until the distance becomes <= mid
            while (nums[right] - nums[left] > mid) {
                left++;
            }

            // All elements from left to right-1
            // form valid pairs with nums[right]
            count += right - left;
        }

        return count;
    }

    int smallestDistancePair(vector<int>& nums, int k) {

        // Sorting allows us to use two pointers
        sort(nums.begin(), nums.end());

        int low = 0;
        int high = nums.back() - nums.front();

        // Binary search on the possible distance
        while (low <= high) {

            int mid = low + (high - low) / 2;

            // If at least k pairs have distance <= mid,
            // mid can be the answer, so try smaller.
            if (countPairs(nums, mid) >= k) {
                high = mid -1;
            }

            // Otherwise, mid is too small.
            else {
                low = mid + 1;
            }
        }

        return low;
    }
};



int main(){
    return 0;
}