/*
 * Problem: Find Smallest Balanced Index
 * 
 * Find the smallest index i such that:
 * - Sum of elements to the left of i equals Product of elements to the right of i
 * - Left sum: nums[0] + nums[1] + ... + nums[i-1]
 * - Right product: nums[i+1] × nums[i+2] × ... × nums[n-1] 
 * - Element at index i is not included in either calculation
 * 
 * Example:
 * nums = [2, 3, 6, 1, 4]
 * At index 2: Left sum = 2+3 = 5, Right product = 1×4 = 4 (not balanced)
 * At index 3: Left sum = 2+3+6 = 11, Right product = 4 = 4 (not balanced)
 * 
 * Approach: Iterate from right to left, maintaining left sum and right product
 * - Start with total sum, then subtract elements to get left sum
 * - Build right product by multiplying elements as we move left
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestBalancedIndex(vector<int>& nums) {
        int n = nums.size();
        
        // Calculate total sum of all elements
        long long lsum = 0;
        for(int i = 0; i < n; i++) {
            lsum += nums[i];
        }
        
        // Traverse from right to left to find balanced index
        long long rpro = 1;  // Right product: product of elements to the right of current index
        
        for(int i = nums.size() - 1; i >= 0; i--) {
            // Update left sum by removing current element
            // Now lsum represents sum of elements to the LEFT of index i
            lsum -= nums[i];
            
            // Check if current index i is balanced:
            // Left sum == Right product
            if(lsum == rpro) return i;
            
            // Optimization: Break early if right product becomes too large
            // If rpro > lsum/nums[i], then rpro will only grow larger in next iteration
            // This prevents unnecessary computation and potential overflow
            if(rpro > lsum / nums[i]) break;
            
            // Update right product by including current element
            // Now rpro represents product of elements to the RIGHT of next index
            rpro *= nums[i];
        }
        
        // No balanced index found
        return -1;
    }
};


int main() {
    // Test case: Find balanced index where left sum equals right product
    vector<int> nums = {1, 2, 3, 4, 5};
    
    cout << "Input array: [";
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if(i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    Solution obj;
    int balancedIndex = obj.smallestBalancedIndex(nums);
    
    if(balancedIndex != -1) {
        cout << "The smallest balanced index is: " << balancedIndex << endl;
        
        // Show the calculation for verification
        long long leftSum = 0;
        for(int i = 0; i < balancedIndex; i++) {
            leftSum += nums[i];
        }
        
        long long rightProduct = 1;
        for(int i = balancedIndex + 1; i < nums.size(); i++) {
            rightProduct *= nums[i];
        }
        
        cout << "Left sum (0 to " << balancedIndex-1 << "): " << leftSum << endl;
        cout << "Right product (" << balancedIndex+1 << " to " << nums.size()-1 << "): " << rightProduct << endl;
    } else {
        cout << "No balanced index found." << endl;
    }
    
    return 0;
}