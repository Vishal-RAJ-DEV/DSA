/*
Problem: LeetCode 74 - Search a 2D Matrix
Given an m x n integer matrix where:
- Each row is sorted in ascending order (left to right)
- The first integer of each row is GREATER than the last integer
  of the previous row

...return true if target exists in the matrix, else false.

Approach: Standard Binary Search on a "flattened" matrix
Intuition:
Because every row is sorted AND the rows are ordered one after
another (row i's values are all smaller than row i+1's values),
the entire matrix behaves like ONE sorted array of size m*n.

So we simply binary search over the virtual 1D array
indices 0 .. (m*n - 1), and convert each 1D index into
(row, col) using division and modulo.

Time Complexity : O(log(m * n))
Space Complexity : O(1)
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();     // number of rows
        int n = matrix[0].size();  // number of columns

        int low = 0;        // first index of the virtual 1D array
        int high = n * m - 1; // last index of the virtual 1D array

        // Standard binary search over virtual 1D range [low, high]
        while (low <= high) {
            // Mid index in the virtual 1D array.
            // Using low + (high - low)/2 instead of (low + high)/2
            // prevents integer overflow for large bounds.
            int mid = low + (high - low) / 2;

            // Convert the 1D index 'mid' into 2D coordinates:
            // row = how many FULL rows fit in mid = mid / n
            // col = position inside that row = mid % n
            int row = mid / n;
            int col = mid % n;

            // Target found at the middle element
            if (matrix[row][col] == target) return true;

            // Middle element is smaller than target
            // → target must lie in the RIGHT half
            // (since the matrix is sorted ascending)
            else if (matrix[row][col] < target) low = mid + 1;

            // Middle element is larger than target
            // → target must lie in the LEFT half
            else high = mid - 1;
        }

        // Search space exhausted → target not present
        return false;
    }
};

/* Why does mapping mid → (row, col) work?
Example: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], m=3, n=4

Virtual 1D array (conceptually):
index:  0  1  2  3   4   5   6   7   8   9  10  11
value:  1  3  5  7  10  11  16  20  23  30  34  60

mid = 5 → row = 5/4 = 1, col = 5%4 = 1 → matrix[1][1] = 11
mid = 8 → row = 8/4 = 2, col = 8%4 = 0 → matrix[2][0] = 23

So the mapping:
- Every n consecutive 1D indices map to the same row
  (indices 0..3 → row 0, 4..7 → row 1, 8..11 → row 2)
- The remainder mod n gives the column inside that row
*/

int main() {
    return 0;
}
