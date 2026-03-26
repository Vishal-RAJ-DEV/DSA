/*
 * Problem: Vowel Strings in Ranges
 * 
 * You are given a 0-indexed array of strings 'words' and a 2D array 'queries'.
 * Each query queries[i] = [li, ri] asks for the count of strings in words[li...ri] 
 * that start AND end with a vowel.
 * 
 * A vowel string is a string that starts and ends with a vowel (a, e, i, o, u).
 * 
 * Example:
 * words = ["aba","bcb","ece","aa","e"]
 * queries = [[0,2],[1,4],[1,1]]
 * Output: [2,3,0]
 * 
 * Explanation:
 * - Query [0,2]: "aba", "ece" are vowel strings → count = 2
 * - Query [1,4]: "ece", "aa", "e" are vowel strings → count = 3  
 * - Query [1,1]: "bcb" is not a vowel string → count = 0
 * 
 * Approach: Use cumulative sum (prefix sum) for efficient range queries
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper function: Check if a character is a vowel (lowercase only)
    bool isVowel(char &ch) {
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }
    
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        // Strategy: Use cumulative sum for O(1) range query answering
        // Build prefix sum array where cumSum[i] = count of vowel strings from index 0 to i
        
        int q = queries.size();  // Number of queries to process
        int w = words.size();    // Number of words in the input array
        
        vector<int> result(q);   // Store results for each query
        vector<int> cumSum(w);   // Cumulative sum array for prefix sums
        
        // Build the cumulative sum array
        int sum = 0;  // Running count of vowel strings found so far
        
        for(int i = 0; i < w; i++) {
            // Check if current word starts AND ends with a vowel
            if(isVowel(words[i].front()) && isVowel(words[i].back())) {
                sum++;  // Increment count if word qualifies as vowel string
            }
            // Store cumulative count up to index i
            // cumSum[i] = total vowel strings from index 0 to i (inclusive)
            cumSum[i] = sum;
        }
        
        // Process each query using the precomputed cumulative sum
        for(int i = 0; i < q; i++) {
            int l = queries[i][0];  // Left boundary of range
            int r = queries[i][1];  // Right boundary of range
            
            // Calculate count in range [l, r] using prefix sum technique:
            // Count in range = cumSum[r] - cumSum[l-1]
            // Handle edge case when l = 0 (no elements to subtract)
            result[i] = cumSum[r] - ((l > 0) ? cumSum[l - 1] : 0);
        }
        
        return result;
    }
};

int main() {
    // Test case setup
    vector<string> words = {"aba", "bcb", "ece", "aa", "e"};
    vector<vector<int>> queries = {{0,2}, {1,4}, {1,1}};
    
    cout << "Input words: [\"aba\", \"bcb\", \"ece\", \"aa\", \"e\"]" << endl;
    cout << "Vowel strings: \"aba\"(✓), \"bcb\"(✗), \"ece\"(✓), \"aa\"(✓), \"e\"(✓)" << endl;
    cout << "Queries: [[0,2], [1,4], [1,1]]" << endl;
    cout << endl;
    
    Solution s;
    vector<int> result = s.vowelStrings(words, queries);
    
    cout << "Results: ";
    for(int count : result) {
        cout << count << " ";
    }
    cout << endl;
    
    cout << "\nExplanation:" << endl;
    cout << "Query [0,2]: \"aba\", \"ece\" are vowel strings → count = 2" << endl;
    cout << "Query [1,4]: \"ece\", \"aa\", \"e\" are vowel strings → count = 3" << endl; 
    cout << "Query [1,1]: \"bcb\" is not a vowel string → count = 0" << endl;
    // Expected output: [2, 3, 0]
    
    return 0;
}