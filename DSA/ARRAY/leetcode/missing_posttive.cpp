#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
You are given an unsorted integer array.
You must return:
The smallest positive integer that is missing from the array.

🔎 Example 1
nums = [1,2,0]
Positive numbers present: 1, 2
Smallest missing positive = 3

🔎 Example 2
nums = [3,4,-1,1]
Positive numbers present: 1, 3, 4
Smallest missing positive = 2

🔎 Example 3
nums = [7,8,9,11,12]
No 1 present
Smallest missing positive = 1
*/


//time complexity : O(n) and space complexity : O(n)
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        set<int> st ;

        for( int num : nums ){
            st.insert(num); //push the element in the set
        }

        for( int i = 1; i < n+1 ; i++){
            //first number which not find will return , beacuse no should be smallest 
            if(st.find(i) == st.end()) return i; //goes to the n elements 
        }

        return n + 1; //at last all elements are present , so just return n + element 
    }
};
//optimal approach : using cyclic sort
//time complexity : O(n) and space complexity : O(1)
class Solution2 {
    public :
    int firstMissingPositive( vector<int>&nums){
        bool contain1 = false;
        int n = nums.size();
        for( int i = 0 ; i < n ; i++){
            if( nums[i] == 1) contain1 = true; //check that 1 is present or not 
            if( nums[i] <= 0 || nums[i] > n) nums[i] = 1; //if the number is negative or greater than n , then we can ignore it and replace it with 1
        }

        if( !contain1) return 1; //if 1 is not present then return 1

        for( int i = 0 ; i < n ; i++){
            int num = abs(nums[i]); //take the absolute value of the number
            int idx = num - 1; //the index will be num - 1 because the number is from 1 to n and index is from 0 to n-1
            if( nums[idx] > 0) nums[idx] = -nums[idx]; //mark the index as negative to indicate that the number is present  
        }
        for( int i = 0 ; i < n ; i++){
            if( nums[i] > 0) return i + 1; //if the number is positive, it means that the index + 1 is missing
        }
        return n + 1; //if all numbers are present, return n + 1
    }
};
int main(){
    vector<int> nums = {3, 4, -1, 1};
    Solution sol;
    cout<<"first missing positive is"<<"\n"<<sol.firstMissingPositive(nums);

    return 0;
}