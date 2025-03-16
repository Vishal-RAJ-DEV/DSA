#include <iostream>
#include <bits/stdc++.h>

// Problem Statement: Given an integer N and an array of size N-1 containing N-1 numbers between 1 to N. Find the number(between 1 to N), that is not present in the given array.

// optimal approach 1: using the formula of sum of n natural numbers
// Time complexity: O(N), where N = size of array+1
// Space complexity: O(1)   
using namespace std;
int missing(vector<int>& arr){
    int n = arr.size();
    int total = n*(n+1)/2;
    for(int i=0;i<n;i++){
        total -=arr[i];
    }
}

// optimal approach 2: using XOR operator
// Time complexity: O(N), where N = size of array+1
// Space complexity: O(1)
int missing2(vector<int>&arr){
    int n = arr.size();
    int xor1 = 0;
    int xor2 = 0;
    for(int i=0;i<n;i++){
        xor1 ^= arr[i];
        xor2 ^= i+1;
    }
    return xor1 ^ xor2;

}


int main(){
    vector<int> arr = {1,2,3,4,6,7,8};
    cout<<"missing array is"<<"\n"<<missing(arr);
    return 0;
}