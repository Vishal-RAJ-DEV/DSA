#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin() , nums.end());
        
        long long windowsum = 0;
        int left = 0;
        int ans = 1;//if nothing match the then highest frequency will be the 1 

        for(int right = 0 ; right < n ; right++){
            windowsum += nums[right];

            long long cost = 1LL * nums[right] * (right - left + 1) - windowsum;

            //while cost increse k then remove the left elemnet and shirk the window 
            //with that calcuate the cost and remove till cost is valid which is less than k 
            //beacuse our window is depends on the value of the cost , if cost is valid than window is also valid r - l + 1
            while( cost > k){
                windowsum -= nums[left];
                left++;
                
                //calcualte current window cost 
                cost = 1LL * nums[right] * ( right - left + 1) - windowsum;
            }

            //now at this point cost is valid , so window is also valid 
            ans = max(ans , right - left + 1);
        }

        return ans;
    }

};


int main(){
    return 0;
}