#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int findKthPositive(vector<int> &arr, int k)
{
    int n = arr.size();              // Store the size of the array
    int low = 0;                     // Initialize left pointer for binary search
    int high = n - 1;                // Initialize right pointer for binary search
    
    while (low <= high)              // Continue binary search until pointers cross
    {
        int mid = (low + high) / 2;  // Calculate middle index
        
        // Key insight: Calculate how many positive numbers are missing up to arr[mid]
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k)             // If missing count is less than k
            low = mid + 1;           // Search in the right half
        else                         // If missing count >= k
            high = mid - 1;          // Search in the left half
    }
    
    // Formula to find the kth missing positive number
    return high + 1 + k;
}
int main()
{
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;
    cout << findKthPositive(arr, k) << endl;
    return 0;
}