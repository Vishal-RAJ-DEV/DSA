#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    void solve( vector<int>&nums , int idx , set<vector<int>>&result , vector<int>&curr){
        // Base case:
        // If we have considered every element, check whether the current
        // subsequence has length at least 2. Only then it is a valid answer.
        if( idx == nums.size()){
            if( curr.size() >= 2){
                result.insert(curr);
            }
            return ;
        }

        // Choice 1: take nums[idx]
        // We can take it only if the subsequence stays non-decreasing.
        // That means either curr is empty, or the last chosen element is <= nums[idx].
        if(curr.empty() || curr.back() <= nums[idx]){
            // Include the current number in the subsequence.
            curr.push_back( nums[idx]);

            // Recurse to the next index after choosing nums[idx].
            solve( nums , idx + 1 , result , curr);

            // Backtracking step:
            // Remove exactly the element we just added so the vector returns
            // to its previous state before exploring the next choice.
            // This pop_back() is inside the if because push_back() happened only
            // inside this branch. If we did not push, we must not pop.
            curr.pop_back();
        }

        // Choice 2: do not take nums[idx]
        // Explore the path where the current element is skipped.
        solve( nums , idx + 1 , result , curr);
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        // Use a set to avoid duplicate subsequences.
        // Different recursion paths can create the same sequence,
        // so the set keeps only unique results.
        set<vector<int>>result;
        vector<int>curr;
        solve( nums , 0 , result , curr);
        return vector<vector<int>>(result.begin() , result.end());

    }
};


int main(){
    vector<int> nums = {4, 6, 7, 7};
    Solution sol;
    vector<vector<int>> ans = sol.findSubsequences(nums);
    
    return 0;
}
