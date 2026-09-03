// Problem Statement: Given an array of N integers. Every number in the array except one appears twice. Find the single number in the array.

// Example 1:
// Input Format: arr[] = {1,1,2,2,3,3,4,5,5,6,6}
// Result: 4
// Explanation: Only the number 4 appears once in the array.

// Example 2:

// Input Format: arr[] = {1,1,3,5,5}
// Result: 3
// Explanation: Only the number 3 appears once in the array.



#include <bits/stdc++.h>
using namespace std;

int singleNonDuplicate(vector<int>& arr) {
    int n = arr.size(); //size of the array.

    /*
    Algorithm:
    1. Handle boundary cases first:
       - if array has only one element, that is the answer
       - if first element is different from second, first is the single
       - if last element is different from second last, last is the single

    2. Apply binary search on the range [1 ... n-2].

    3. For every mid:
       - if arr[mid] is different from both neighbours, it is the answer
       - otherwise use the index-parity pattern to decide which side contains
         the single element

    4. Return the unique element in O(log n) time.
    */

    // Edge cases:
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = (low + high) / 2;

        // If current element is different from both neighbours,
        // then this is the element that appears only once.
        if (arr[mid] != arr[mid + 1] && arr[mid] != arr[mid - 1]) {
            return arr[mid];
        }

        /*
        Intuition:
        Before the single element, pairs start from even indices:
        [1,1] [2,2] [3,3] ...
         0 1   2 3   4 5

        After the single element appears, this pattern shifts by one index:
        ... [5,5] [6,6]
             7 8   9 10

        So:
        - On the left side of the single element:
          even index matches next, odd index matches previous
        - On the right side of the single element:
          this pairing rule breaks

        If:
        - mid is odd and arr[mid] == arr[mid-1], pairing is normal
        - mid is even and arr[mid] == arr[mid+1], pairing is normal

        That means we are still on the left side of the single element,
        so the answer must lie on the right side.
        */
        if ((mid % 2 == 1 && arr[mid] == arr[mid - 1])
                || (mid % 2 == 0 && arr[mid] == arr[mid + 1])) {
            // Pairing pattern is correct till mid,
            // so eliminate left half and search right.
            low = mid + 1;
        }
        else {
            // Pairing pattern is broken at mid,
            // so the single element lies on the left side.
            high = mid - 1;
        }
    }

    // Dummy return, control should not normally reach here.
    return -1;
}

int main()
{
    vector<int> arr = {1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6};
    int ans = singleNonDuplicate(arr);
    cout << "The single element is: " << ans << "\n";
    return 0;
}

