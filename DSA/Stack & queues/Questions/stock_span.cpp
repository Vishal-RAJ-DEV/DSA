/*
Problem Statement: Given an array arr of size n, where each element arr[i] represents the stock price on day i. Calculate the span of stock prices for each day.
Example 1:
Input:
 n = 7, arr = [120, 100, 60, 80, 90, 110, 115]
Output:
 1 1 1 2 3 5 6
Explanation:

Traversing the given input span:
120 is greater than or equal to 120 and there are no more elements behind it so the span is 1,
100 is greater than or equal to 100 and smaller than 120 so the span is 1,
60 is greater than or equal to 60 and smaller than 100 so the span is 1,
80 is greater than or equal to 60, 80 and smaller than 100 so the span is 2,
90 is greater than or equal to 60, 80, 90 and smaller than 100 so the span is 3,
110 is greater than or equal to 60, 80, 90, 100, 110 and smaller than 120 so the span is 5,
115 is greater than or equal to all previous elements and smaller than 120 so the span is 6.
Hence the output will be 1 1 1 2 3 5 6.

Example 2:
Input:
 n = 6, arr = [15, 13, 12, 14, 16, 20]
Output:
 1 1 1 3 5 6
Explanation:

Traversing the given input span:
15 is greater than or equal to 15 and there are no more elements behind it, so the span is 1.
13 is smaller than 15, so the span is 1.
12 is smaller than 13, so the span is 1.
14 is greater than or equal to 12 and 13, but smaller than 15, so the span is 3 (days with values 12, 13, and 14).
16 is greater than or equal to 14, 12, 13, and 15, so the span is 5.
20 is greater than or equal to all previous elements, so the span is 6.
Hence the output will be 1 1 1 3 5 6.
*/

#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
//approach 1: brute force approach
//time complexity: O(n^2) as we are traversing the array twice
class Solution {
public:
    // Function to find the span of stock prices for each day
    vector <int> stockSpan(vector<int> arr, int n) {
        
        // To store the answer
        vector<int> ans(n);
        
        // Traverse on the array
        for(int i=0; i < n; i++) {
            
            // To store the current span of stocks
            int currSpan = 0;
            
            // Traversing backwards to find stock span
            for(int j=i; j >= 0; j--) {
            
                // Update stock span
                if(arr[j] <= arr[i]) {
                    currSpan++;
                }
                
                // Else break out from loop
                else break;
            }
            
            // Store the current span
            ans[i] = currSpan;
        }
        
        // Return the result
        return ans;
    }
};


//optimal approach using stack 
//time complexity: o(n) as we are traversing the array once and each elemeent is pushed and popped at most once from the stack 
class Solution {
private:
    /* Function to find the indices of previous 
    greater element for each element in the array */
    vector<int> findPGE(vector<int> arr) {
        
        int n = arr.size(); //size of array
        
        // To store the previous greater elements
        vector<int> ans(n);
        
        // Stack to get elements in LIFO fashion
        stack<int> st;
        
        // Start traversing from the front
        for(int i=0; i < n; i++) {
            
            // Get the current element
            int currEle = arr[i];
            
            /* Pop the elements in the stack until 
            the stack is not empty and the top 
            element is not the greater element */
            while(!st.empty() && arr[st.top()] <= currEle) {
                st.pop();
            }
            
            /* If the greater element is not 
            found, stack will be empty */
            if(st.empty()) 
                ans[i] = -1;
                
            // Else store the answer
            else 
                ans[i] = st.top();
            
            // Push the current index in the stack 
            st.push(i);
        }
        
        // Return the result
        return ans;
    }
    
public:
    // Function to find the span of stock prices for each day
    vector <int> stockSpan(vector<int> arr, int n) {
        
        // Get the indices of previous greater elements
        vector<int> PGE = findPGE(arr);
        
        
        // To store the answer
        vector<int> ans(n);
        
        // Compute the result
        for(int i=0; i < n; i++) {
            ans[i] = i - PGE[i];
        }
        
        // Return the result
        return ans;
    }
};

int main() {
    int n = 7;
    vector<int> arr = {120, 100, 60, 80, 90, 110, 115};
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to find the span 
    of stock prices for each day */
    vector<int> ans = sol.stockSpan(arr, n);
    
    cout << "The span of stock prices is: ";
    for(int i=0; i < n; i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}