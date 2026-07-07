#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    // Function to calculate trapped rainwater using brute force approach
    int trap(vector<int>& height) {
        int n = height.size();
        
        // Variable to store total trapped water
        int totalWater = 0;
        
        // Iterate over each bar in the elevation map
        for (int i = 0; i < n; i++) {
            // Initialize max heights to the left and right of current bar
            int maxLeft = 0;
            int maxRight = 0;
            
            // Find maximum height to the left of current bar
            for (int j = 0; j <= i; j++) {
                if (height[j] > maxLeft) {
                    maxLeft = height[j];
                }
            }
            
            // Find maximum height to the right of current bar
            for (int j = i; j < n; j++) {
                if (height[j] > maxRight) {
                    maxRight = height[j];
                }
            }
            
            // Water trapped on current bar is min of maxLeft and maxRight minus current height
            totalWater += min(maxLeft, maxRight) - height[i];
        }
        
        // Return total trapped water
        return totalWater;
    }
};

class Solution {
public:
    // Function to calculate trapped rainwater using the optimal two-pointer approach
    int trap(vector<int>& height) {
        int n = height.size();
        
        // Initialize two pointers at both ends of the array
        int left = 0;
        int right = n - 1;
        
        // Variables to track the maximum height to the left and right
        int maxLeft = 0;
        int maxRight = 0;
        
        // Variable to store total trapped water
        int totalWater = 0;
        
        // Iterate until left pointer meets right pointer
        while (left <= right) {
            // If left bar is smaller or equal to right bar
            if (height[left] <= height[right]) {
                // If current left bar is higher than maxLeft, update maxLeft
                if (height[left] >= maxLeft) {
                    maxLeft = height[left];
                } else {
                    // Water trapped on left is difference between maxLeft and current height
                    totalWater += maxLeft - height[left];
                }
                left++; // Move left pointer to the right
            } else {
                // If current right bar is higher than maxRight, update maxRight
                if (height[right] >= maxRight) {
                    maxRight = height[right];
                } else {
                    // Water trapped on right is difference between maxRight and current height
                    totalWater += maxRight - height[right];
                }
                right--; // Move right pointer to the left
            }
        }
        
        // Return total trapped water
        return totalWater;
    }
};

// Driver code
int main() {
    // Input elevation map
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    
    // Create Solution object
    Solution sol;
    Solution1 sol1;
    
    // Calculate trapped water
    int result = sol.trap(height);
    int result1 = sol1.trap(height);
    
    // Print the result
    cout << "Trapped Rainwater (Brute Force): " << result1 << endl;
    cout << "Trapped Rainwater: " << result << endl;
    
    return 0;
}
/*
✅ Two Pointer Variables

left = 0
right = 11
leftmax = 0
rightmax = 0
ans = 0

📘 KEY RULE
At each step:
If height[left] <= height[right] → process left side
Else → process right side

| Step | left | right | height[left] | height[right] | leftmax | rightmax | Water Added   | Why (Move?)                   |
| ---- | ---- | ----- | ------------ | ------------- | ------- | -------- | ------------- | ----------------------------- |
| 1    | 0    | 11    | 0            | 1             | **0→0** | 1        | 0             | left side smaller → move left |
| 2    | 1    | 11    | 1            | 1             | **1→1** | 1        | 0             | left side smaller → move left |
| 3    | 2    | 11    | 0            | 1             | 1       | 1        | 1 - 0 = **1** | left                          |
| 4    | 3    | 11    | 2            | 1             | **2→2** | 1        | 0             | right smaller → move right    |
| 5    | 3    | 10    | 2            | 2             | 2       | **2→2**  | 0             | left (same height)            |
| 6    | 4    | 10    | 1            | 2             | 2       | 2        | 2 - 1 = **1** | left                          |
| 7    | 5    | 10    | 0            | 2             | 2       | 2        | 2 - 0 = **2** | left                          |
| 8    | 6    | 10    | 1            | 2             | 2       | 2        | 2 - 1 = **1** | left                          |
| 9    | 7    | 10    | 3            | 2             | **3→3** | 2        | 0             | right smaller → move right    |
| 10   | 7    | 9     | 3            | 1             | 3       | **2→2**  | 2 - 1 = **1** | right                         |
| 11   | 7    | 8     | 3            | 2             | 3       | 2        | 2 - 2 = **0** | right                         |
| 12   | 7    | 7     | STOP         |               |         |          |               |                               |

*/