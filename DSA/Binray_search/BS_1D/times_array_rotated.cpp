// Problem Statement: Given an integer array arr of size N, sorted in ascending order (with distinct values). Now the array is rotated between 1 to N times which is unknown. Find how many times the array has been rotated. 


// Example 1:
// Input Format: arr = [4,5,6,7,0,1,2,3]
// Result: 4
// Explanation: The original array should be [0,1,2,3,4,5,6,7]. So, we can notice that the array has been rotated 4 times.

// Example 2:
// Input Format: arr = [3,4,5,1,2]
// Result: 3
// Explanation: The original array should be [1,2,3,4,5]. So, we can notice that the array has been rotated 3 times.
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

int findkrotation(vector<int>& arr){
    /*
    Algorithm:
    1. The number of rotations is equal to the index of the minimum element.
       Example:
       original: [1,2,3,4,5]
       rotated : [4,5,1,2,3]
       minimum element is 1 at index 2, so array is rotated 2 times.

    2. Use binary search because the array is made of two sorted parts.

    3. At any step:
       - if the current search space is already sorted, then arr[low] is the
         minimum of that whole part
       - otherwise, one half is definitely sorted and the other half contains
         the rotation point

    4. Track the smallest value seen so far and its index.

    5. Return the index of the minimum element.
    */

    int low = 0, high = arr.size()-1;
    int ans = INT_MAX;
    int index = -1;
    while(low <=high){
        int mid = (low + high) / 2;

        // If the current search space is already sorted,
        // then the leftmost element is the minimum in this part.
        // So we can update the answer and stop.
        if(arr[low]<=arr[high]){
            if(arr[low]<ans){  // store the minimum element and its index
                index = low;
                ans = arr[low];
            }
            break;
        }

        /*
        Intuition:
        In a rotated sorted array, one side of mid will always be sorted.

        Case 1: Left half is sorted
        arr[low] <= arr[mid]
        This means all values from low to mid are in proper order.
        So the smallest value of this left half is arr[low].
        The actual rotation point, if it exists, must be on the right side.

        Case 2: Right half is not making left sorted
        Then the rotation point lies in the left half including mid.
        In that case arr[mid] can itself be the minimum candidate.
        */
        if(arr[low] <= arr[mid]) {
            // Left part is sorted, so arr[low] is the smallest in this half.
            if(arr[low]< ans){
            index = low;
            ans = arr[low];
            }

            // Since left half is sorted, the rotation point must be on right side.
            low = mid + 1;
        }

        else{
            // Mid lies in the unsorted half, so it can be the minimum candidate.
            if(arr[mid] < ans){
                index = mid;
                ans = arr[mid];
            }

            // Search in the left half because rotation point is there.
            high = mid -1;
        }
    }
    return index;
}
int main(){
     vector<int> arr = {4, 5, 6, 7, 1, 2, 3};
    int ans = findkrotation(arr);
    cout << "times the arr is rotated is : " << ans << "\n";
    return 0;
}

// time complexity is o(log n) and space complexity is o(1)
