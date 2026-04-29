#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem Statement: Given an integer N and an array of size N-1 containing N-1 numbers between 1 to N. Find the number(between 1 to N), that is not present in the given array.


//navie approach: using two loops to check if the number from 1 to N is present in the array or not
int missingNum(vector<int>& arr) {
    int n = arr.size() + 1;

    // Iterate from 1 to n and check
    // if the current number is present
    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] == i) {
                found = true;
                break;
            }
        }

        // If the current number is not present
        if (!found)
            return i;
    }
    return -1;
}

//approch using the hash map to store the frequency of the element and then check which number is missing
int missingNum(vector<int> &arr) {

    int n = arr.size() + 1;

    // Create hash array of size n+1
    vector<int> hash(n + 1, 0);

    // Store frequencies of elements
    for (int i = 0; i < n - 1; i++) {
        hash[arr[i]]++;
    }

    // Find the missing number
    for (int i = 1; i <= n; i++) {
        if (hash[i] == 0) {
            return i;
        }
    }
    return -1;
}
// optimal approach 1: using the formula of sum of n natural numbers
// Time complexity: O(N), where N = size of array+1
// Space complexity: O(1)   
int missing(vector<int>& arr){
    int n = arr.size(); 
    cout<<"n is"<<n<<endl;
    int total = n*(n+1)/2;
    cout<<"total is"<<total<<endl;
    for(int i=0;i<arr.size();i++){
        total -= arr[i];
    }
    return total;
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