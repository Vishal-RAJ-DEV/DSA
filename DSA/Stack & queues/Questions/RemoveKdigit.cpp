#include <bits/stdc++.h>
using namespace std;
/*
Example 1:
Input:
 nums = "541892", k = 2
Output:
 "1892"
Explanation:
 Removing the two digits 5 and 4 yields the smallest number, 1892.

Example 2:
Input:
 nums = "1002991", k = 3
Output:
 "21"
Explanation:
 Remove the three digits 1(leading one), 9, and 9 to form the new number 21(Note that the output must not contain leading zeroes) which is the smallest.
*/
class Solution {
public:
    /* Function to find the smallest possible 
    integer after removing k digits */
    string removeKdigits(string nums, int k) {
        
        stack <char> st; // Stack

        //--------------------------------------------------------
        // Traverse on the given string
        for(int i=0; i < nums.size(); i++) {
            
            // Current digit
            char digit = nums[i];
            
            /* Pop last digits (when possible)
            if a smaller digit is found*/
            while(!st.empty() && k > 0
                  && st.top() > digit) {

                st.pop(); // Pop the last digit
                k--; // Decrement K by 1
            }
            
            // Push the current digit
            st.push(digit);
        }
        //--------------------------------------------------------

        // If more digits can be removed
        while(!st.empty() && k > 0) {
            
            st.pop(); // Pop the last added digits
            k--; // Decrement K by 1
        }
        
        // Handling edge case
        if(st.empty()) return "0";
        
        // To store the result
        string res = "";
        
        // Adding digits in stack to result
        while(!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        // Trimming the zeroes at the back
        while(res.size() > 0 && 
              res.back() == '0') { //if last character is '0' then pop it to remove leading zeroes  

            res.pop_back();
        }
        
        // Reverse to get the actual number
        reverse(res.begin(), res.end());  //reverse the string to get the correct order
        
        // Edge case
        if(res.empty()) return "0"; //if the result is empty after removing leading zeroes then return "0"
        
        // Return the stored result
        return res;
    }
};

int main() {
    string nums = "541892";
    int k = 2;
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to find the smallest 
    possible integer after removing k digits */
    string ans = sol.removeKdigits(nums, k);
    
    cout << "The smallest possible integer after removing k digits is: " << ans;
    
    return 0;
}