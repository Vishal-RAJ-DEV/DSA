
#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count Inversions in an Array

An inversion is a pair of indices (i, j) such that:
1) i < j
2) arr[i] > arr[j]

Goal: Return the total number of inversion pairs.

Example:
Input: arr = [5, 4, 3, 2, 1]
Output: 10
Explanation: Every pair is inverted because the array is in descending order.
*/
int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;      // Temporary array to store merged sorted elements
    int left = low;        // Pointer for left sorted half: [low ... mid]
    int right = mid + 1;   // Pointer for right sorted half: [mid+1 ... high]

    // Count inversions formed across left and right halves.
    int cnt = 0;

    // Merge two sorted halves while counting cross inversions.

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            // No inversion: left element is smaller/equal.
            temp.push_back(arr[left]);
            left++;
        }
        else {
            // Inversion found: arr[left] > arr[right].
            // Since left half is sorted, all elements from 'left' to 'mid'
            // will also be greater than arr[right].
            temp.push_back(arr[right]);
            cnt += (mid - left + 1);
            right++;
        }
    }

    // Copy remaining elements from left half (if any).

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    // Copy remaining elements from right half (if any).
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // Write merged sorted result back into original array segment.
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt;
}

int mergeSort(vector<int> &arr, int low, int high) {
    // Base case: single element has 0 inversions.
    int cnt = 0;
    if (low >= high) return cnt;

    // Divide array into two halves.
    int mid = (low + high) / 2 ;
    cnt += mergeSort(arr, low, mid);        // Count inversions in left half
    cnt += mergeSort(arr, mid + 1, high);   // Count inversions in right half

    // Count cross inversions and merge sorted halves.
    cnt += merge(arr, low, mid, high);
    return cnt;
}

int numberOfInversions(vector<int>&a, int n) {
    // Run merge-sort based counting in O(N log N).
    return mergeSort(a, 0, n - 1);
}

int main()
{
    vector<int> a = {5, 4, 3, 2, 1};
    int n = 5;

    // For this example, answer is 10.
    int cnt = numberOfInversions(a, n);
    cout << "The number of inversions are: "
         << cnt << endl;
    return 0;
}


