#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.

A uni-value grid is a grid where all the elements of it are equal.

Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.


Input: grid = [[2,4],[6,8]], x = 2
Output: 4
Explanation: We can make every element equal to 4 by doing the following: 
- Add x to 2 once.
- Subtract x from 6 once.
- Subtract x from 8 twice.
A total of 4 operations were used.
*/



/*
Flatten grid into a single array.
Sort and pick median as target.
For each number, find difference from target.
If difference not divisible by x → return -1.
Else add (difference / x) to total operations.
*/


class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;
        for (auto& row : grid) {
            for (int k : row) {
                nums.push_back(k);
            }
        }
        sort(nums.begin(), nums.end());
        int target = nums[nums.size() / 2];
        long long totalOperations = 0;
        for (int k : nums) {
            int temp = abs(k - target);
            if (temp % x != 0)
                return -1;
            totalOperations += temp / x;
        }
        return totalOperations;
    }
};




int main(){
    return 0;
}