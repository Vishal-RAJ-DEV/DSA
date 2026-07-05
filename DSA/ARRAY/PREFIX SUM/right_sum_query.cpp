#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// This is a simple implementation of the NumArray class that allows for efficient range sum queries using prefix sums. The first implementation uses a straightforward approach to calculate the sum of elements in a given range, while the second implementation utilizes prefix sums to optimize the sumRange function.
//time complexity of sumRange function is O(n) in first implementation and O(1) in second implementation.
class NumArray {
public:
    vector<int>array;
    NumArray(vector<int>& nums) {
        array.resize(nums.size());
        for( int i = 0 ; i< nums.size(); i++){
            array[i] = nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        int sum= 0 ;
        for( int i = left; i <= right ; i++){
            sum += array[i];
        }
        return sum;
    }
};


//time complexity of sumRange function is O(1) in this implementation using prefix sum technique.
class NumArray {
public:
    vector<int> prefix;

    NumArray(vector<int>& nums) {
        prefix.resize(nums.size() + 1);

        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};


int main(){
    return 0;
}