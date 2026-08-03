#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Problem Statement: Given an array containing both positive and negative integers, we have to find the length of the longest subarray with the sum of all elements equal to zero.

//algorithm flow :
/*
store the sum of elements from the start to the current index in a variable called sum.
//If at any index, the sum becomes zero, it means that the subarray from the start to that index has a sum of zero. Update the maximum length accordingly.
// use the map to track the sum and its previous occurrence index.
//if the same sum is encountered again, it means that the elements between the previous index and the current index sum to zero. Update the maximum length if this subarray is longer than the previously recorded maximum length.
*/
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
            if(mpp.find(sum) != mpp.end()) {// this line checks if the sum is already present in the map if it is present then it means that the subarray between the previous index and the current index has a sum of zero
                maxi = max(maxi, i - mpp[sum]); //this will give the length of that subarray 
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
/*
Initial Setup:
n = 6 (array size)
mpp = empty map (will store prefix sum → index)
maxi = 0 (maximum length found)
sum = 0 (running prefix sum)

Iteration 1: i = 0, A[0] = 9
sum += A[0] = 0 + 9 = 9
sum != 0, so skip the if block
mpp.find(9) != mpp.end() → false (9 not in map yet)
mpp[9] = 0 (store first occurrence)
Map: {9: 0}
maxi = 0

Iteration 2: i = 1, A[1] = -3
sum += A[1] = 9 + (-3) = 6
sum != 0
mpp.find(6) != mpp.end() → false (6 not in map yet)
mpp[6] = 1
Map: {9: 0, 6: 1}
maxi = 0

Iteration 3: i = 2, A[2] = 3
sum += A[2] = 6 + 3 = 9
sum != 0
mpp.find(9) != mpp.end() → true (9 was seen at index 0)
maxi = max(0, 2 - 0) = max(0, 2) = 2
Found subarray: indices 1 to 2 → [-3, 3] with sum = 0
Map: {9: 0, 6: 1} (no update, keep first occurrence)
maxi = 2

teration 4: i = 3, A[3] = -1
sum += A[3] = 9 + (-1) = 8
sum != 0
mpp.find(8) != mpp.end() → false (8 not in map yet)
mpp[8] = 3
Map: {9: 0, 6: 1, 8: 3}
maxi = 2

Iteration 5: i = 4, A[4] = 6
sum += A[4] = 8 + 6 = 14
sum != 0
mpp.find(14) != mpp.end() → false (14 not in map yet)
mpp[14] = 4
Map: {9: 0, 6: 1, 8: 3, 14: 4}
maxi = 2

Iteration 6: i = 5, A[5] = -5
sum += A[5] = 14 + (-5) = 9
sum != 0
mpp.find(9) != mpp.end() → true (9 was seen at index 0)
maxi = max(2, 5 - 0) = max(2, 5) = 5
Found subarray: indices 1 to 5 → [-3, 3, -1, 6, -5] with sum = 0
Map: {9: 0, 6: 1, 8: 3, 14: 4} (no update, keep first occurrence)
maxi = 5

Final Result:
maxi = 5
Longest subarray with sum 0: [-3, 3, -1, 6, -5] (length = 5)
*/