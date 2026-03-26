#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        int rightSum = 0;
        for( int i  = 0 ; i < nums.size(); i++){
            rightSum += nums[i];
        }

        int leftSum = 0 ;
        for( int i = 0 ; i < nums.size(); i++){
            rightSum -= nums[i];

            if( rightSum == leftSum) return i;

            leftSum += nums[i];
        }

        return -1;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {1, 7, 3, 6, 5, 6}; 
    int pivot = sol.pivotIndex(nums);
    if(pivot != -1) {
        cout << "Pivot index: " << pivot << endl;
    } else {
        cout << "No pivot index found." << endl;
    }
    return 0;
}