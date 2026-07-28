#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int low = 0;
        int high = n - 1;
        int ans = INT_MAX;
        while( low <= high){
            int mid = low + ( high - low) /2;

            //if whole array sorted then at low the minimum element 
            if(nums[low] < nums[high]){
                ans = min( ans , nums[low]);
                break;
            }

            //handle the duplicated element 
            if(nums[low] == nums[mid] && nums[mid] == nums[high]){
                ans = min(ans , nums[low]);
                //skips the elements
                low++;
                high--;
                continue;
            }

            //left half is sorted then at low the minimum element
            if(nums[low] <= nums[mid]){
                ans = min(ans , nums[low]);
                //ones get the minimum from left part go to the right part 
                low = mid + 1;
            }
            //right half is sorted here , then mid is minimum there , after go to the left half
            else{
                ans = min(ans , nums[mid]);
                high = mid - 1;

            }
        }

        return ans;
    }
};




int main(){
    return 0;
}