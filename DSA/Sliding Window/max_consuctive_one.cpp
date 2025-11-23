#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//brute force approach
int maxConsuctiveOnes(vector<int>& nums, int k){
    int n = nums.size();
    int maxLen = 0 ;
    for(int i = 0 ;i<n ;i++){
        int zeros = 0 ;
        for (int j = i ; j < n ; j++){  //loop start form i to n to create the window 
            if(nums[j] == 0) zeros++;
            if(zeros > k) break; //if zeros exceed k then break the loop we get the window which flips the k zeros
            maxLen = max(maxLen , j - i + 1); //update the max length
        }
    }
    return maxLen;
}

//better approach using sliding window
int maxConsuctiveOne1(vector<int>& nums, int k ){
    int n = nums.size();
    int left = 0 ;
    int right = 0 ;
    int zeros = 0 ;
    int maxlen = 0 ;
    while(right < n ){
        if(nums[right] == 0 ) zeros++; //only increase the zero count when we encounter a zero 
        while(zeros > k){  //shrink the window from left until the zeros are less than or equal to k
            if(nums[left] == 0) zeros--; //if the zero is at the left pointer decrease the zero count
            left ++; // and increase the left pointer to shrink the window
        }
        maxlen = max(maxlen , right-left+1);  //calculate the max length of the window `
        right++;  //increse the right pointer to expand the window
    }
    return maxlen;
}
int main(){
    vector<int> nums = {1,1,1,0,0,0,1,1,1,1,0};
    int k = 2;
    cout<<maxConsuctiveOnes(nums, k)<<endl;
    cout<<maxConsuctiveOne1(nums, k)<<endl;
    return 0;
}