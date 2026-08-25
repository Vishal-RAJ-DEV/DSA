#include <iostream>
#include <vector>
using namespace std;

int missingNumber(vector<int> &arr) {
    int n = arr.size()+1; 
    
    // checking the difference between 
    // index and element
    for (int i = 0; i < n-1; i++) {
        
        // if difference between index and element 
        // is not 1
        if( arr[i] != i+1)

        return i+1; 
    }
    
    // If the diference between index and 
    // element on that inidex
    // for all index is 1 
    return n;
}


int missingNumber(vector<int>& arr) {
    
    // Calculate the total sum
    int n = arr.size() + 1;
    int totalSum = n * (n + 1) / 2;

    // Calculate sum of all elements in the given array
    int arraySum = 0;
    for (int num : arr) {
        arraySum += num;
    }

    // Subtract  and return the total sum with the sum of
    // all elements in the array
    int missingNumber = totalSum - arraySum;

    return missingNumber;
}


int missingNumber(vector<int>& arr) {
    int n = arr.size();

    // Case 1: 1 is missing
    if (arr[0] != 1) {
        return 1;
    }

    // Case 2: Last number (n + 1) is missing
    if (arr[n - 1] != n + 1) {
        return n + 1;
    }

    int lo = 0;
    int hi = n - 1;

    // Binary Search
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        /*
        Before the missing number:

        arr[mid] = mid + 1

        Example:
        index = 2
        arr[2] = 3

        3 == 2 + 1 → correct position
        */

        if (arr[mid] == mid + 1) {
            // Missing number is on the right
            lo = mid + 1;
        }
        else {
            // Missing number is on the left
            hi = mid - 1;
        }
    }

    // lo will point to the position where
    // the missing number should be.
    return lo + 1;
}



int main() {
    vector<int> arr = {1, 2, 3, 4, 6, 7, 8};
    cout << missingNumber(arr);
    return 0;
}