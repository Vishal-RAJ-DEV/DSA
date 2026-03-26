#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Optimal approach for arrays where values are in the range [1, n],
// where n is the size of the array.
// Idea: Use value -> index mapping (value x maps to index x-1).
// First time a value is seen, negate nums[x-1].
// If nums[x-1] is already negative, that value is a duplicate.
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // Stores all duplicate numbers.
        vector<int>ans;

        // Traverse every element once.
        for( int i = 0 ;i < nums.size(); i++){
            
            // Get the original value at nums[i] using abs(), because this element
            // might already have been negated earlier.
            // Convert value to index: value v belongs to index v-1.
            int idx = abs(nums[i]) - 1;

            // If value at mapped index is positive, this is first occurrence.
            if( nums[idx] > 0){
                // Mark as visited by making it negative.
                nums[idx] = -nums[idx];
            }else{
                // Already negative means this value was seen before -> duplicate.
                ans.push_back(abs(nums[i]));
            }
        }

        // Return all duplicates found.
        return ans;
    }
};

int main(){
    // Example input.
    vector<int>nums = {4,3,2,7,8,2,3,1};

    // Create object and call function.
    Solution obj;
    vector<int>ans = obj.findDuplicates(nums);

    // Print duplicates.
    for( int i = 0 ;i < ans.size(); i++){
        cout<<ans[i]<<" ";
    }
    
    // Successful execution.
    return 0;
}
