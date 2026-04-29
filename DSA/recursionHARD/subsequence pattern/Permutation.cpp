#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void perms( vector<int>&nums , int idx , vector<vector<int>>&res){
        // Base case: one full permutation is formed when idx reaches the end.
        if(idx == nums.size()){
            res.push_back(nums);
            return;
        }

        // Try every candidate element at position idx.
        for( int j = idx; j < nums.size(); j++){
            // Choose: place nums[j] at the current position.
            swap(nums[idx] , nums[j]);
            // Explore: build permutations for the remaining positions.
            perms(nums , idx+1 , res);
            // Undo choice (backtrack) to restore original state.
            swap(nums[idx] , nums[j]);
        } 
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        // Start generating permutations from index 0.
        perms(nums , 0 , res);
        return res;
    }
};


int main(){
    int n;
    cin>>n;
    // Read input array.
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }

    // Generate all permutations.
    Solution s;
    vector<vector<int>> res = s.permute(nums);

    // Print each permutation in a separate line.
    for(auto &it : res){
        for(auto &el : it){
            cout<<el<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}
