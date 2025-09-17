#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//SLIDING WINDOW APPROACH
//Function to return the minimum size of the subarray whose sum is greater than or equal to the target value.
int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int sum = 0;
        int minn = INT_MAX;
        
        for(int i = 0 ;i< nums.size();i++){
            sum+=nums[i];

            while(sum>=target){
                minn = min(minn , i - left + 1);
                sum -=nums[left];
                left++;
            }
        }
        return minn == INT_MAX ? 0 : minn;
    }
    
int main(){
    int target = 7;
    vector<int> nums = {2,3,1,2,4,3};
    cout<<minSubArrayLen(target, nums);
    return 0;
}
