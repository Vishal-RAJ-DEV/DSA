#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem:
// Given an array, find the k-th smallest absolute difference among all pairs.
// Example: nums = [1,3,1]
// Pair distances are: |1-3|=2, |1-1|=0, |3-1|=2
// Sorted distances: [0,2,2], so for k = 1 the answer is 0.

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        int maxele  = *max_element( nums.begin() , nums.end());
        // vec[d] stores how many pairs have absolute difference d.
        // This works because the distance range is small enough to count directly.
        vector<int>vec(maxele + 1 , 0);

        // Check every pair and count its distance.
        for( int i= 0 ; i < n ; i++){
            for( int j = i + 1 ; j < n ; j++){
                int diff = abs( nums[i] - nums[j]);
                vec[diff]++;
            }
        }

        // Walk through distances from smallest to largest.
        // Subtract each bucket size from k until k becomes <= 0.
        // The current distance is then the k-th smallest pair distance.
        for( int i = 0 ; i<= maxele ;i++){
            k -= vec[i];
            if( k <= 0){
                return i;
            }
        }

        return -1;
    }
};


int main(){
    Solution sol;
    vector<int> nums = {1, 3, 1};
    int k = 1;
    int result = sol.smallestDistancePair(nums, k);
    cout << "The " << k << "-th smallest distance pair is: " << result << endl;
    
    return 0;
}
