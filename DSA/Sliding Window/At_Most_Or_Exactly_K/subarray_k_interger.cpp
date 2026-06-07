#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Input: nums = [1, 2, 1, 2, 3], k = 2  
Output: 7
Explanation: The 7 subarrays with exactly 2 different integers are:
[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]


Input: nums = [1, 2, 1, 3, 4], k = 3  
Output: 3
Explanation: The 3 subarrays with exactly 3 different integers are:  
[1,2,1,3], [2,1,3], [1,3,4] 
*/
class Solution {
public:

    int atMost(vector<int>& nums, int k){
        int right = 0 ;
        int left  = 0 ;
        int count = 0;
        unordered_map<int , int> mpp;
        while( right < nums.size()){
            mpp[nums[right]]++;

            while( mpp.size() > k ){
                mpp[nums[left]]--;
                if( mpp[nums[left]]== 0){
                    mpp.erase(nums[left]);
                }
                left++;
            }
            count+= right - left + 1 ;
            right ++;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        cout<<atMost( nums , k )<<" "<<atMost( nums , k -1 )<<endl;
        return atMost( nums , k ) - atMost( nums , k -1 );
    }
};
int main(){
    vector<int> arr = {1,2,1,2,3};
    int k = 2;
    Solution obj;
    int ans = obj.subarraysWithKDistinct( arr , k);
    cout<<"The number of subarrays with exactly k distinct integers is: "<<ans<<endl;
    
    return 0;
}
