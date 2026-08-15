#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int median(vector<vector<int>> &mat) {
        int n = mat.size();
        int m = mat[0].size();

        // Find minimum and maximum possible values
        int low = INT_MAX;
        int high = INT_MIN;

        for (int i = 0; i < n; i++) {
            low = min(low, mat[i][0]);
            high = max(high, mat[i][m - 1]);
        }

        // We need this many elements to be <= median
        int required = (n * m) / 2 + 1;

        // Binary search on answer
        while (low < high) {
            int mid = low + (high - low) / 2;

            int count = 0;

            // Count elements <= mid
            for (int i = 0; i < n; i++) {
                count += upper_bound(mat[i].begin(), mat[i].end(),  mid) - mat[i].begin();
            }

            if (count < required) {
                // Too few elements <= mid
                // Median must be bigger
                low = mid + 1;
            }
            else {
                // Enough elements <= mid
                // Try to find a smaller answer
                high = mid;
            }
        }

        return low;
    }
};


class Solution {
public:
    // Function to find the median of a row-wise sorted matrix
    int findMedian(vector<vector<int>>& matrix) {
        
        // Create a list to store all elements
        vector<int> elements;

        // Traverse each row of the matrix
        for (auto& row : matrix) {

            // Traverse each element in the current row
            for (int val : row) {

                // Add the element to the list
                elements.push_back(val);
            }
        }

        // Sort the collected elements
        sort(elements.begin(), elements.end());

        // Return the middle element (median)
        int n = elements.size();
        return elements[n / 2];
    }
};




int main(){
    return 0;
}