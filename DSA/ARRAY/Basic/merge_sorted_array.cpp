/*
 * Problem: Merge Two Sorted Arrays In-Place
 * 
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing order,
 * and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
 * 
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 * The final sorted array should be stored inside nums1.
 * 
 * nums1 has a size of m + n where the last n elements are set to 0 and should be ignored.
 * 
 * Example: 
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * 
 * Algorithm: Use three-pointer approach working backwards to avoid overwriting
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Initialize three pointers working backwards from the end
        int num1Mp = m - 1;     // Pointer to last valid element in nums1
        int num2Mp = n - 1;     // Pointer to last element in nums2 
        int right = m + n - 1;  // Pointer to last position in nums1 (where we place merged elements)
        
        // Why work backwards? To avoid overwriting unprocessed elements in nums1
        // We fill from the largest elements first, placing them at the end
        
        // Continue until all elements from nums2 are processed
        while(num2Mp >= 0) {
            // Compare elements from both arrays and place the larger one at 'right' position
            if(num1Mp >= 0 && nums1[num1Mp] > nums2[num2Mp]) {
                // nums1 element is larger, place it at current right position
                nums1[right] = nums1[num1Mp];
                num1Mp--;  // Move nums1 pointer backwards
            }
            else {
                // nums2 element is larger (or nums1 is exhausted), place nums2 element
                nums1[right] = nums2[num2Mp];
                num2Mp--;  // Move nums2 pointer backwards
            }
            right--;  // Move to next position (working backwards)
        }
        // Note: If nums1 still has elements left, they're already in correct position
    }
};

int main() {
    // Test case setup
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};  // Array with extra space for merging
    vector<int> nums2 = {2, 5, 6};           // Second sorted array to merge
    int m = 3;  // Number of actual elements in nums1 (excluding trailing zeros)
    int n = 3;  // Number of elements in nums2
    
    cout << "Before merging:" << endl;
    cout << "nums1: [1, 2, 3, 0, 0, 0]" << endl;
    cout << "nums2: [2, 5, 6]" << endl;
    
    Solution s;
    s.merge(nums1, m, nums2, n);
    
    cout << "After merging: ";
    for (int i = 0; i < m + n; i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;
    // Expected output: [1, 2, 2, 3, 5, 6]
    
    return 0;
}
