#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int maxArea(vector<int> &height)
{
    int left = 0;                           // Initialize left pointer to start of array
    int right = height.size() - 1;          // Initialize right pointer to end of array
    int Maxarea = 0;                        // Track maximum area found so far
    
    while (left < right)                    // Continue until pointers meet
    {
        // Calculate area with current left and right boundaries
        int area = (right - left) * min(height[left], height[right]);  //take the minimum height because water will overflow from the smaller height or we can say water level is limited by the smaller height
        
        // Update maximum area if current area is larger
        Maxarea = max(area, Maxarea);
        
        // Move the pointer which is at the smaller height because the area is decided by the smaller height and if we increase the smaller height we may get a larger area --- important
        if (height[left] < height[right])   //if left height is smaller than right height then to get the larger height we need to move the left pointer to get the larger height
        {
            left++;                         // so here increase the left to get the larger height
        }
        else
        {
            right--;                        // decrease the right to get the larger height
        }
    }
    return Maxarea;                         // Return the maximum area found
}

int main()
{
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "The maximum area is: " << maxArea(height) << endl; 
    return 0;
}
/*
Area Calculation:

Width: Distance between pointers (right - left)
Height: Minimum of the two heights (water level is limited by shorter line)
Pointer Movement Strategy:

Always move the pointer with the smaller height
Why? Moving the pointer with larger height won't increase area (limited by smaller height)
Moving smaller height pointer gives a chance to find a taller line
Example Walkthrough:
Input: height = [1,8,6,2,5,4,8,3,7]

Initial: left=0, right=8, Maxarea=0

Iteration 1:

area = (8-0) * min(1,7) = 8 * 1 = 8
Maxarea = max(0,8) = 8
height[0]=1 < height[8]=7, so left++ → left=1
Iteration 2:

area = (8-1) * min(8,7) = 7 * 7 = 49
Maxarea = max(8,49) = 49
height[1]=8 > height[8]=7, so right-- → right=7
Iteration 3:

area = (7-1) * min(8,3) = 6 * 3 = 18
Maxarea = max(49,18) = 49
height[1]=8 > height[7]=3, so right-- → right=6
Continue until left >= right...

Why This Works:
Greedy Choice: At each step, we eliminate the possibility that gives us no benefit
Optimal Substructure: The optimal solution contains optimal solutions to subproblems
Proof: Moving the taller line inward can only decrease area (width decreases, height stays same or decreases)
Complexity Analysis:
Time Complexity: O(n) - each element is visited at most once
Space Complexity: O(1) - only uses constant extra space
*/