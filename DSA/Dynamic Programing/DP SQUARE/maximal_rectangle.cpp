// =============================================================================
// MAXIMAL RECTANGLE IN BINARY MATRIX
// =============================================================================
// Problem: Find the largest rectangle containing only 1s in a binary matrix
//
// ALGORITHM OVERVIEW (3 Steps):
//   Step 1: Build "heights" matrix (prefix sum column-wise)
//   Step 2: For each row, treat heights as histogram → find largest rectangle
//   Step 3: Track overall maximum across all rows
//
// KEY INSIGHT:
//   By counting consecutive 1s vertically, any rectangle of 1s becomes
//   a histogram bar, and we can use the standard largest rectangle algorithm.
//
// TIME COMPLEXITY: O(N * M) where N = rows, M = columns
// SPACE COMPLEXITY: O(N * M) for prefix sum matrix
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // =========================================================================
    // LARGEST RECTANGLE IN HISTOGRAM (Monotonic Stack)
    // =========================================================================
    // Given an array of heights, find the largest rectangular area.
    //
    // HOW IT WORKS:
    //   - Use monotonic increasing stack to find Next Smaller Element (NSE)
    //     and Previous Smaller Element (PSE) for each bar
    //   - For each bar, width = NSE - PSE - 1
    //   - Area = height * width
    //
    // FORMULA: area = heights[ind] * (nse - pse - 1)
    //
    // EXAMPLE: heights = [3, 1, 3, 2, 2]
    //
    //   Index:    0     1     2     3     4
    //   Height:  [3]   [1]   [3]   [2]   [2]
    //             █     █     █     █     █
    //             █     █     █     █     █
    //             █     █     █     █     █
    //
    //   For index 2 (height=3):
    //     PSE = index 1 (height=1)
    //     NSE = index 3 (height=2)
    //     Width = 3 - 1 - 1 = 1
    //     Area = 3 * 1 = 3
    //
    //   For index 3 (height=2):
    //     PSE = index 1 (height=1)
    //     NSE = index 5 (end)
    //     Width = 5 - 1 - 1 = 3
    //     Area = 2 * 3 = 6  ← MAXIMUM
    // =========================================================================
    int largestRectangleArea(vector<int> &heights) {
        
        int n = heights.size(); // Size of array
        
        // Stack to store indices in increasing order of heights
        stack<int> st;
        
        // To store largest area
        int largestArea = 0;
        
        // To store current area
        int area;
        
        /* To store the indices of next 
        and previous smaller elements */
        int nse, pse;
        
        // Traverse on the array
        for(int i=0; i < n; i++) {
            
            /* Pop the elements in the stack until 
            the stack is not empty and the top 
            elements is not the smaller element */
            while(!st.empty() && 
                  heights[st.top()] >= heights[i]){
                      
                // Get the index of top of stack
                int ind = st.top(); 
                st.pop();
                
                /* Update the index of 
                previous smaller element */
                pse = st.empty() ? -1 : st.top();
                
                /* Next smaller element index for 
                the popped element is current index */
                nse = i;
                
                // Calculate the area of the popped element
                // Width = nse - pse - 1 (elements between PSE and NSE)
                area = heights[ind] * (nse-pse-1);
                
                // Update the maximum area
                largestArea = max(largestArea, area);
            }
            
            // Push the current index in stack
            st.push(i);
        }
        
        // For elements that are not popped from stack
        while(!st.empty()) {
            
            // NSE for such elements is size of array
            nse = n;
            
            // Get the index of top of stack
            int ind = st.top(); 
            st.pop();
            
            // Update the previous smaller element
            pse = st.empty() ? -1 : st.top();
            
            // Calculate the area of the popped element
            area = heights[ind] * (nse-pse-1);
            
            // Update the maximum area
            largestArea = max(largestArea, area);
        }
        
        // Return largest area found
        return largestArea;
    }
    
public:
    // =========================================================================
    // MAIN FUNCTION: Maximal Rectangle in Binary Matrix
    // =========================================================================
    int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &matrix){
        
        // Determine the size of matrix
        int n = matrix.size();
        int m = matrix[0].size();
        
        /* Prefix sum matrix to store heights 
        for different ground levels */
        vector<vector<int>> prefixSum(n, vector<int>(m));
        
        // Fill up the prefix sum matrix column wise
        for(int j=0; j < m; j++) {
            int sum = 0;
            
            for(int i=0; i < n; i++) {
                sum += matrix[i][j];
                
                // If there is no base present
                if(matrix[i][j] == 0) {
                    prefixSum[i][j] = 0;
                    sum = 0;
                }
                
                // Store the height
                prefixSum[i][j] = sum;
            }
        }
        
        // To store the maximum area
        int maxArea = 0;
        
        // Traverse for different levels of ground
        for(int i = 0; i < n; i++) {
            
            // Get the largest area for current level
            int area = largestRectangleArea(prefixSum[i]);
            
            // Update the maximum area
            maxArea = max(area, maxArea);
        }
        
        // Return the maximum area
        return maxArea;
    }
};

// =============================================================================
// MAIN - Test the algorithm with detailed trace
// =============================================================================
int main() {
    vector<vector<int>> matrix = {
        {1, 0, 1, 0, 0}, 
        {1, 0, 1, 1, 1}, 
        {1, 1, 1, 1, 1}, 
        {1, 0, 0, 1, 0}
    };
    
    /*
    STEP-BY-STEP TRACE:
    
    Original Matrix:
        col0  col1  col2  col3  col4
    row0  1     0     1     0     0
    row1  1     0     1     1     1
    row2  1     1     1     1     1
    row3  1     0     0     1     0
    
    STEP 1: Build Prefix Sum Matrix (heights for each row)
    
    Row 0 heights: [1, 0, 1, 0, 0]
        █     _     █     _     _
        col0  col1  col2  col3  col4
    
    Row 1 heights: [2, 0, 2, 1, 1]
        █     _     █     █     █
        █     _     █     █     █
        col0  col1  col2  col3  col4
    
    Row 2 heights: [3, 1, 3, 2, 2]
        █     █     █     █     █
        █     █     █     █     █
        █     █     █     █     █
        col0  col1  col2  col3  col4
    
    Row 3 heights: [4, 0, 0, 3, 0]
        █     _     _     █     _
        █     _     _     █     _
        █     _     _     █     _
        █     _     _     █     _
        col0  col1  col2  col3  col4
    
    STEP 2: Find Largest Rectangle for Each Row
    
    Row 0: [1, 0, 1, 0, 0] → Area = 1
    Row 1: [2, 0, 2, 1, 1] → Area = 3
    Row 2: [3, 1, 3, 2, 2] → Area = 6  ← MAXIMUM
    Row 3: [4, 0, 0, 3, 0] → Area = 4
    
    ANSWER: 6
    */
    
    Solution sol; 
    int ans = sol.maximalAreaOfSubMatrixOfAll1(matrix);
    
    cout << "The largest rectangle area containing all 1s is: " << ans << endl;
    
    return 0;
}