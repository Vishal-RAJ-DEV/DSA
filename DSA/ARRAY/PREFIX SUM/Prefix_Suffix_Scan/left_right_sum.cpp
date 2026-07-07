#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int>left(n);
        vector<int>right(n);
        left[0] = nums[0];
        right[n-1] = nums[n-1];

        for( int i = 1 ; i < n ; i++){
            left[i] = left[i-1] + nums[i];
            right[n - i - 1] = right[n - i] + nums[n - i - 1];
        } 

        vector<int>ans(n);
        for( int i = 0 ; i<n ; i++){
            ans[i] = abs( left[i] - right[i] );
        }

        return ans;
    }
};


int main(){
    vector<int> nums = {10, 4, 8, 3};
    Solution obj;
    vector<int> result = obj.leftRightDifference(nums);
    
    return 0;
}