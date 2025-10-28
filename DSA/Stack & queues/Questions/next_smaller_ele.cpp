#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<int> nextSmallerElement(vector<int>& arr) {
        
        int n = arr.size(); // size of array
        
        // To store the next smaller elements
        vector<int> ans(n, -1);
        
        for (int i = 0; i < n; ++i) {
            
            // Get the current element
            int currEle = arr[i];
            
            /* Nested loop to get the 
            next smaller element */
            for (int j = i + 1; j < n; ++j) {
                
                // If the next smaller element is found
                if (arr[j] < currEle) {
                    
                    // Store the next smaller element
                    ans[i] = arr[j];
                    
                    // Break from the loop
                    break;
                }
            }
        }
        
        // Return the answer
        return ans;
    }
    // Optimized approach using stack
    vector<int> nextSmallerElement1(vector<int>& arr) {
        int n = arr.size();

        // Stack to store potential next smaller elements
        stack<int> st;

        // Answer array initialized with -1
        vector<int> ans(n, -1);

        // Traverse the array from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Pop elements from stack while they are >= current element
            while (!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }

            // If stack is not empty, top is the next smaller element
            if (!st.empty()) {
                ans[i] = st.top();
            }

            // Push current element to stack
            st.push(arr[i]);
        }

        // Return result
        return ans;
    }
};

int main() {
    vector<int> arr = {1, 3, 2, 4};
    Solution sol;

    // Get result
    vector<int> ans = sol.nextSmallerElement(arr);

    // Print result
    cout << "The next smaller elements are: ";
    for (int val : ans) {
        cout << val << " ";
    }

    return 0;
}