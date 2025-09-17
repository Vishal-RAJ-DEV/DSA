// Problem Statement: Given an integer array arr of size N, sorted in ascending order (with distinct values). Now the array is rotated between 1 to N times which is unknown. Find the minimum element in the array. 

// Example 1:
// Input Format: arr = [4,5,6,7,0,1,2,3]
// Result: 0
// Explanation: Here, the element 0 is the minimum element in the array.

// Example 2:
// Input Format: arr = [3,4,5,1,2]
// Result: 1
// Explanation: Here, the element 1 is the minimum element in the array.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int findMin(vector<int>& arr){
    int low = 0, high = arr.size()-1;
    int ans = INT_MAX;
    while(low <=high){
        int mid = (low + high) / 2;
        //search space is already sorted
        //then arr[low] will always be
        //the minimum in that search space:
        if(arr[low]<=arr[high]){
            ans  = min(ans , arr[low]);
            break;
        }

        if(arr[low] <= arr[mid]) {
            //left part is sorted:
            ans = min(ans , arr[low]);
            low = mid + 1; // search in the sorted right part
        }

        else{
            ans = min(ans , arr[mid]);
            high = mid -1;  //search in the sorted left part
        }
    }
    return ans;
}
int main(){
     vector<int> arr = {4, 5, 6, 7, 1, 2, 3};
    int ans = findMin(arr);
    cout << "The minimum element is: " << ans << "\n";
    return 0;
}