#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Problem Statement: Given an array containing both positive and negative integers, we have to find the length of the longest subarray with the sum of all elements equal to zero.

int maxLen(vector<int> & A)
{
    int n = A.size();
    unordered_map<int,int> mpp; 
    int maxi = 0;
    int sum = 0; 
    for(int i = 0;i<n;i++) {
        sum += A[i]; 
        if(sum == 0) {
            maxi = i + 1; 
        }
        else {
            if(mpp.find(sum) != mpp.end()) {
                maxi = max(maxi, i - mpp[sum]); 
            }
            else {
                mpp[sum] = i;
            }
        }   
    }

    return maxi; 
}


int main(){
    vector<int> A = {9, -3, 3, -1, 6, -5};
    cout << maxLen(A) << endl;

    return 0;
}