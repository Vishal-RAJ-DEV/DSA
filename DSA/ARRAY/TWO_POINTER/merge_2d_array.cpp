/*
 * Problem: Merge Two 2D Arrays by Index
 * 
 * You are given two 2D integer arrays nums1 and nums2 where:
 * - Each sub-array contains exactly two elements: [index, value]
 * - Both arrays are sorted by their index values
 * 
 * Merge the two arrays into a single sorted array by index:
 * - If indices are different: include both pairs, maintaining sorted order
 * - If indices are same: merge by adding their values together
 * 
 * Example:
 * nums1 = [[1,2],[2,3],[4,5]]
 * nums2 = [[1,4],[3,2],[4,1]] 
 * Output: [[1,6],[2,3],[3,2],[4,6]]
 * 
 * Explanation:
 * - Index 1: 2+4=6, Index 2: only 3, Index 3: only 2, Index 4: 5+1=6
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> result;
        int i = 0;  // Pointer to traverse nums1 array
        int j = 0;  // Pointer to traverse nums2 array
        
        // Merge process: compare indices and handle accordingly
        while(i < nums1.size() && j < nums2.size()) {
            // Extract index and value from current elements of both arrays
            int idx1 = nums1[i][0], val1 = nums1[i][1];  // nums1: [index, value]
            int idx2 = nums2[j][0], val2 = nums2[j][1];  // nums2: [index, value]
            
            if(idx1 < idx2) {
                // nums1 has smaller index: add it to result and advance nums1 pointer
                result.push_back({idx1, val1});
                i++;
            }
            else if(idx1 > idx2) {
                // nums2 has smaller index: add it to result and advance nums2 pointer
                result.push_back({idx2, val2});
                j++;
            }
            else {
                // Same indices found: merge by adding values and advance both pointers
                result.push_back({idx1, val1 + val2});
                i++;
                j++;
            }
        }
        
        // Add remaining elements from nums1 (if any)
        while(i < nums1.size()) {
            result.push_back(nums1[i]);
            i++;
        }
        
        // Add remaining elements from nums2 (if any)
        while(j < nums2.size()) {
            result.push_back(nums2[j]);
            j++;
        }
        
        return result;
    }
};
int main() {
    // Test case: Arrays with [index, value] pairs
    vector<vector<int>> nums1 = {{1,2}, {2,3}, {4,5}};  // Sorted by index
    vector<vector<int>> nums2 = {{1,4}, {3,2}, {4,1}};  // Sorted by index
    
    cout << "Input Arrays:" << endl;
    cout << "nums1: [[1,2], [2,3], [4,5]]" << endl;
    cout << "nums2: [[1,4], [3,2], [4,1]]" << endl;
    cout << endl;
    
    Solution s;
    vector<vector<int>> ans = s.mergeArrays(nums1, nums2);
    
    cout << "Merged 2D Array (sorted by index):" << endl;
    for(const auto& pair : ans) {
        cout << "[" << pair[0] << ", " << pair[1] << "] ";
    }
    cout << endl;
    
    cout << "\nExplanation:" << endl;
    cout << "Index 1: 2+4=6, Index 2: 3, Index 3: 2, Index 4: 5+1=6" << endl;
    // Expected output: [[1,6], [2,3], [3,2], [4,6]]

    return 0;
}