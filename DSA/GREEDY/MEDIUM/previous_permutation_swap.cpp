#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Question:
// Given an array of positive integers, find the previous
// permutation with exactly one swap. The previous permutation
// is the largest permutation that is lexicographically smaller
// than the current array. If no such permutation exists, return
// the array itself.
//
// Example:
// Input: arr = [3,2,1]
// Output: [3,1,2]
// Explanation: Swapping 2 and 1 gives the largest smaller
// permutation.
//
// Input: arr = [1,1,5]
// Output: [1,1,5]
// Explanation: No smaller permutation possible.
// ============================================================

class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = arr.size();

        // step 1: find the first index from the right where
        // arr[i] > arr[i+1]
        // intuition: to get a smaller permutation, we need to
        // move a larger digit leftwards. We look for the rightmost
        // ascending pair (from right to left) because we want the
        // smallest possible decrease in value.
        int cand  = -1;
        for(int i = n-2 ; i >= 0 ; i--){
            if( arr[i] > arr[i+1]){
                cand = i;
                break;
            }
        }

        // if no such index exists, array is already sorted ascending
        // -> no smaller permutation possible
        if( cand == -1) return arr;

        // step 2: find the largest element strictly smaller than
        // arr[cand] to its right (from the rightmost side)
        // we scan from the end because we want the rightmost
        // candidate — this gives us the closest (largest) smaller
        // number.
        int j = n-1;
        while( j > cand && arr[cand] <= arr[j])j--;

        // step 3: handle duplicates — we want the leftmost occurrence
        // of the value we found. This ensures we get the largest
        // possible previous permutation.
        while( j > cand + 1 && arr[j] == arr[j-1])j--;

        // step 4: perform the swap — this yields the immediate
        // previous permutation.
        swap(arr[j] , arr[cand]);

        return arr;
    }
};



int main(){
    Solution sol;
    vector<int> arr = {3, 2, 1};
    arr = sol.prevPermOpt1(arr);
    for(int x : arr){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
