#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// This function checks whether the array can be divided into groups of size k
// such that no group is forced to contain duplicate copies of the same value.
//
// Main idea:
// If total array size is n, then number of groups formed will be n / k.
// Suppose some value appears more times than the number of groups.
// Then by pigeonhole principle, at least one group would have to take that value twice,
// which would violate the idea of distributing equal elements across different groups.
//
// So this code does not explicitly create the groups.
// It only checks the necessary condition:
// frequency of every number <= total number of groups.
bool partitionArray(vector<int>& nums, int k) {
        /*
        Algorithm:
        1. Let n be the size of the array.
        2. If n is not divisible by k, we cannot split the array into equal groups of size k.
        3. Compute total groups = n / k.
        4. Count frequency of each number.
        5. If any number appears more than total groups times, return false.
           Reason:
           - each group can take at most one copy of that number
           - if copies are more than number of groups, some group must get duplicate copies
        6. If all frequencies satisfy this condition, return true.

        Example:
        nums = [1,1,2,2,3,3], k = 3
        size = 6, groups = 2
        frequency of each number is 2, which is <= groups
        so distribution is possible:
        group1 = [1,2,3]
        group2 = [1,2,3]
        */

        int size = nums.size();

        // If array size is not divisible by k,
        // equal-sized groups cannot be formed at all.
        if(size % k != 0 ) return false;

        map<int , int > mpp;
        int group = size / k; // total number of groups

        for(int i = 0 ; i< size ; i++){
            // Count how many times each value appears.
            mpp[nums[i]]++;

            // Shrinking or sorting is not needed here.
            // We only care whether one value appears too many times to be spread
            // across all groups.
            if(mpp[nums[i]] > group){
                // This value appears in more positions than there are groups,
                // so at least one group would be forced to contain duplicates.
                return false;
            }
        }

        // Every value can be distributed across the groups successfully.
        return true;
    }
int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    int k = 3;
    cout << partitionArray(nums, k) << endl;
    return 0;
}
