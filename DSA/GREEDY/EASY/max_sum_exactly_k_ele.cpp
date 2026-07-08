#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class solution{
    public:
    int maxSum(vector<int> & nums , int k ){
        int sum = 0;
        int n = nums.size();
        int max = nums[0];
        for(int i = 1; i < n; i++){
            if(nums[i] > max) max = nums[i];
        }
        return (max*k) + (k *(k-1)/2);
    }
};
class Solution {
public:
    int maximizeSum(vector<int>& nums, int k) {
        int maxele = *max_element(nums.begin() , nums.end());
        int sum = 0;

        while( k--){
            sum += maxele;
            maxele++;
            
        }
        return sum ;
    }
};
int main(){
    vector<int> nums = {1,2,3,4,5};
    int k = 3;
    Solution sol;
    cout << sol.maximizeSum(nums, k) << endl; // Output: 18
    
    return 0;
}
