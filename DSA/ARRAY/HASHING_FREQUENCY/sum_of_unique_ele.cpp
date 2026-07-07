#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem idea:
// Given an array of integers, return the sum of the values that appear exactly once.
//
// Example:
// nums = [1, 2, 3, 2]
// Frequency:
// - 1 appears once  -> keep it
// - 2 appears twice -> ignore it
// - 3 appears once  -> keep it
// Answer = 1 + 3 = 4
//
// Approach used here:
// - First count how many times each number appears.
// - Then scan the frequency table and add only the values whose count is 1.
//
// Why this works:
// The first pass stores the frequency of every element.
// The second pass filters out all repeated numbers and keeps only unique ones.
// This is a hashing/frequency counting pattern.
class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int n = nums.size();
        int mpp[101] = {};

        // Count how many times each value appears.
        // This version assumes the numbers are in the range [0, 100].
        for(int num : nums){
            mpp[num]++;
        }

        // Add only the numbers that appeared exactly once.
        int sum =0 ;
        for( int i = 0; i < 101; i++){
            if( mpp[i] == 1) {
                sum += i;
            }
        }

        return sum;

    }
};

int main(){
    return 0;
}