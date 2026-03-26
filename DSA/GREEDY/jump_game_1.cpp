#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//algorithm :-
//first we will keep the track of the farthest index that we can reach from the current index 
//if the index is greater than the farthest index that we can reach then we can't jump to the last index and return false
//and update the farthest index that we can reach from the current index and keep on doing this until we reach the last index or we can't jump to the last index
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxidx = 0 ;
        for( int i = 0 ; i < n ; i++){

            //if the max index is lesser than the current index 
            //means it it can't go to last index or further index
            if( i > maxidx) return false;

            maxidx  = max( maxidx , i + nums[i]);
        }

        return true;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {2, 3, 1, 1, 4};
    bool ans = sol.canJump(nums);
    if(ans) cout<<"We can jump to the last index "<<endl;
    else cout<<"We cannot jump to the last index "<<endl;
    return 0;
}
