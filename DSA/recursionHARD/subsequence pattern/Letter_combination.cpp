#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Recursive function to generate letter combinations
    void func(int ind, string digits, string s, vector<string> &ans, string combos[]) {
        // Base case: if index reaches the end of digits
        if(ind == digits.size()) {
            // Add the current combination to the answer
            ans.push_back(s);
            return;
        }
        // Convert the current character to an integer
        int digit = digits[ind] - '0';
        // Loop through the corresponding characters
        for(int i = 0; i < combos[digit].size(); i++) {
            // Recursively call function with next index
            // Add current character to the string
            func(ind + 1, digits, s + combos[digit][i], ans, combos);
        }
    }

public:
    // Function to get all letter combinations for a given digit string
    vector<string> letterCombinations(string digits) {
        // Mapping digits to corresponding characters
        string combos[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans; // Vector to store results
        string s = ""; // Temporary string to build combinations
        // Initiate recursive function
        func(0, digits, s, ans, combos);
        return ans; // Return the result
    }
};

int main() {
    Solution solution;
    string digits = "23"; // Input digits
    vector<string> result = solution.letterCombinations(digits); // Get combinations

    // Print the results
    for (const string& combination : result) {
        cout << combination << " ";
    }
    return 0;
}