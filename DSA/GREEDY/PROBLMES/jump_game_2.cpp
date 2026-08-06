#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//we will keep track of the left and right most farthest index that we can reach from the current index and keep on updating it until we reach the last index 
//each tiem we update the left and right pointer we will increase the jump by 1 because we are taking the jump from the current range to the next range
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();

        int left = 0; //left most far of the range 
        int right = 0; //right most far in the range 
        int jump = 0 ;

        while(right < n -1){
            int farthest = 0;

            //now search farthest element of that range 
            for ( int i = left ; i <= right ; i++){
                farthest = max( farthest , i + nums[i]);
            }
            //upadate the pointers for the next range 
            left  = right + 1;
            right = farthest;
            //and increse the jump which comes form the this range 
            jump++;
        }

        return jump;
    }
};


int main(){
    Solution sol;
    vector<int> nums = {2, 3, 1, 1, 4};
    int ans = sol.jump(nums);
    cout<<"Minimum number of jumps to reach the last index is : "<< ans << endl;
    
    return 0;
}