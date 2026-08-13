#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
🧠 What is the question ACTUALLY asking?

You are given a histogram.
Each bar has:
height = heights[i]
width = 1
Bars are placed side by side
👉 You must find the largest rectangular area that can be formed using one or more consecutive bars.
❓ What does “largest rectangle” mean?

You can:
Choose any continuous range of bars
The rectangle height = minimum height in that range
Width = number of bars in that range

Area formula:
area = height × width

🔍 Example rectangles
Single bar
Bar 5 → area = 5 × 1 = 5

Two bars [5,6]
Min height = 5
Width = 2
Area = 5 × 2 = 10 ✅

Three bars [5,6,2]
Min height = 2
Width = 3
Area = 2 × 3 = 6
👉 So the largest rectangle = 10*/

//brute force approach
// Time Complexity: O(N^2)
// Brute Force Approach to find largest rectangle area in Histogram
int largestarea(int arr[], int n) {
    int maxArea = 0;  // Variable to store maximum area found

    // Outer loop to set the starting index of the subarray
    for (int i = 0; i < n; i++) {
        int minHeight = INT_MAX;  // To track minimum height in the subarray

        // Inner loop to set the ending index of the subarray
        for (int j = i; j < n; j++) {
            // Update minimum height in the current window
            minHeight = min(minHeight, arr[j]);

            // Calculate area = height * width
            int width = j - i + 1;
            int area = minHeight * width;

            // Update maxArea if this area is larger
            maxArea = max(maxArea, area);
        }
    }

    return maxArea;  // Return the largest area found
}

// Approach: Nearest Smaller to Left and Nearest Smaller to Right using stack two times 
// Time Complexity: O(N) + O(N) + O(N) = O(N)
// Space Complexity: O(N) + O(N) + O(N) = O(N)
class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        stack<int> st;

        int leftsmall[n], rightsmall[n];

        // Compute Nearest Smaller to Left (NSL) for each bar
        for (int i = 0; i < n; i++) {
            // Pop until a smaller element is found or stack is empty
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }

            // If stack is empty, no smaller element on the left
            leftsmall[i] = st.empty() ? 0 : st.top() + 1;

            // Push current index to stack
            st.push(i);
        }

        // Clear stack to reuse for NSR
        while (!st.empty()) st.pop();

        // Compute Nearest Smaller to Right (NSR) for each bar
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }

            // If stack is empty, no smaller to the right
            rightsmall[i] = st.empty() ? n - 1 : st.top() - 1;

            st.push(i);
        }

        // Calculate max area using NSL and NSR
        int maxA = 0;
        for (int i = 0; i < n; i++) {
            int width = rightsmall[i] - leftsmall[i] + 1;
            maxA = max(maxA, heights[i] * width);
        }

        return maxA;
    }
};

// optiaml solution using single stack
// Time Complexity: O(N)
// Space Complexity: O(N)
int largestArea(vector<int> height)
{
    int maxArea = 0;
    stack<int> st; // Stack to store indices of histogram bars in increasing order of heights
    // this stack will actually store is pse and next smaller element when we pop the element from the stack

    for (int i = 0; i <= height.size(); i++)
    {
        while (!st.empty() && height[st.top()] > height[i])
        {
            // When height[i] < height[st.top()]:-> And to maintain the increasing order we pop the top element
            // - height[i] is the NSE (Next Smaller Element) of st.top()
            // - The element just below st.top() in stack is the PSE (Previous Smaller Element) of st.top()
            // - Now we can calculate rectangle area with st.top() as the minimum height


            int currentHeight = height[st.top()]; //element for which we are calculating area
            st.pop(); //pop the top element to get the PSE from the new top of stack

            int nse = i; // index of next smaller element for which is current i because we are in the loop where height[i] < height[st.top()]  height[i] is the NSE for st.top()
            int pse = st.empty() ? -1 : st.top(); //if stack is empty then there is no smaller element on left side so pse = -1 else pse is the new top of stack ( stack is in increasing order so new top is smaller than current element)

            int width = nse - pse - 1; // A window width where currentHeight is the minimum height which is between pse and nse 
            int area = currentHeight * width; //area calculation where currentHeight is the minimum height in that width
            maxArea = max(maxArea, area); //update max area
        }
        st.push(i);
    }

    //edge case: if there is still element left in the stack
    while(!st.empty()){ //if there is still element left in the stack and no nse for them because we have reached the end of the array 
        int currentHeight = height[st.top()]; //element for which we are calculating area 
        st.pop(); //pop the top element to get the PSE from the new top of stack

        int nse = height.size(); //if there is no nse for the element then we consider nse as size of the array
        int pse = st.empty() ? -1 : st.top(); //if stack is empty then there is no smaller element on left side so pse = -1 else pse is the new top of stack ( stack is in increasing order so new top is smaller than current element)

        int width = nse - pse - 1; // A window width where currentHeight is the minimum height which is between pse and nse
        int area = currentHeight * width; //area calculation where currentHeight is the minimum height in that width
        maxArea = max(maxArea, area); //update max area

    }
    return maxArea;
}
int main()
{
    vector<int> height = {2, 1, 5, 6, 2, 3};
    cout << "Largest Rectangle Area in Histogram: " << largestArea(height) << endl;

    return 0;
}
