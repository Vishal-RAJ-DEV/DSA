// Problem: Maximum Length Substring with at Most Two Occurrences
// https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/
//
// APPROACHES:
// 1. Variable Sliding Window with unordered_map (original)
// 2. Variable Sliding Window with array (optimized constant factor)
// 3. Binary Search on answer + validation
// 4. Brute Force (check all substrings)
//
// EXAMPLE: s = "eceba"
//   Valid substrings: "e"(1), "ec"(2), "ece"(3), "eceb"(4 violates),
//   "c"(1), "ce"(2), "ceb"(3 violates), "e"(1), "eb"(2), "b"(1), "ba"(2), "a"(1)
//   Answer: 3 ("ece")
//
// COMPARISON:
// Approach 1: O(n) time, O(k) space  - best overall
// Approach 2: O(n) time, O(1) space  - fastest in practice
// Approach 3: O(n log n) time, O(1) space - good for learning
// Approach 4: O(n^2) time, O(1) space - educational only

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: Variable Sliding Window with unordered_map
// ============================================================================
// TIME: O(n)  |  SPACE: O(k) where k = distinct characters
//
// HOW IT WORKS:
// - Use two pointers (left, right) to define current window
// - Expand right pointer, adding characters to frequency map
// - When any character count > 2, shrink from left until valid
// - Track maximum valid window size
// ============================================================================
class Solution1 {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();

        // Frequency map to track count of each character in current window
        unordered_map<char , int>freq;

        int left = 0;    // Left boundary of sliding window
        int ans = 0;     // Maximum valid window size found

        // Expand window by moving right pointer
        for(int right = 0 ; right < n ; right++){
            // Add right character to window
            freq[s[right]]++;

            // Shrink window from left while constraint is violated
            // (any character appears more than 2 times)
            while(freq[s[right]] > 2){
                freq[s[left]]--;  // Remove left character from window
                left++;           // Move left pointer forward
            }

            // Update maximum length of valid window
            // Window size = right - left + 1
            ans = max(ans , right - left + 1);
        }

        return ans;
    }
};

// ============================================================================
// APPROACH 2: Variable Sliding Window with Array (Optimized)
// ============================================================================
// TIME: O(n)  |  SPACE: O(1) - fixed size array for 26 lowercase letters
//
// OPTIMIZATION over Approach 1:
// - Use int freq[26] instead of unordered_map
// - Array access is faster than hash table lookup
// - Constant space (26 elements) regardless of input
//
// BEST FOR: Competitive programming where speed matters
// ============================================================================
class Solution2 {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();

        // Fixed-size array for lowercase letters (a-z)
        // Much faster than unordered_map due to cache locality
        int freq[26] = {0};

        int left = 0;
        int ans = 0;

        for(int right = 0 ; right < n ; right++){
            // Convert char to index: 'a'->0, 'b'->1, ..., 'z'->25
            freq[s[right] - 'a']++;

            // Shrink while constraint violated
            while(freq[s[right] - 'a'] > 2){
                freq[s[left] - 'a']--;
                left++;
            }

            ans = max(ans , right - left + 1);
        }

        return ans;
    }
};

// ============================================================================
// APPROACH 3: Binary Search on Answer + Validation
// ============================================================================
// TIME: O(n log n)  |  SPACE: O(1)
//
// HOW IT WORKS:
// - Binary search on the answer (length of substring)
// - For each candidate length, check if ANY substring of that length
//   satisfies the constraint (all chars appear <= 2 times)
// - Use sliding window of fixed size to validate each length
//
// WHY USE THIS?
// - Good for learning binary search patterns
// - Can be extended to other constraints easily
// - Useful when you need to find if a valid substring of length L exists
// ============================================================================
class Solution3 {
public:
    // Check if there exists a substring of given length where
    // all characters appear at most 2 times
    bool isValid(string s, int len) {
        int n = s.size();
        if(len > n) return false;

        int freq[26] = {0};
        int uniqueCount = 0;  // Track characters with count > 0

        // Initialize first window of size 'len'
        for(int i = 0; i < len; i++){
            if(freq[s[i] - 'a'] == 0) uniqueCount++;
            freq[s[i] - 'a']++;

            // Check if any character appears more than 2 times
            if(freq[s[i] - 'a'] > 2) return false;
        }

        // Slide window across the string
        for(int i = len; i < n; i++){
            // Remove leftmost character
            freq[s[i - len] - 'a']--;

            // Add new character on right
            if(freq[s[i] - 'a'] == 0) uniqueCount++;
            freq[s[i] - 'a']++;

            // Check constraint
            if(freq[s[i] - 'a'] > 2) return false;
        }

        return true;
    }

    int maximumLengthSubstring(string s) {
        int n = s.size();
        int low = 1, high = n;
        int ans = 0;

        // Binary search on the answer
        while(low <= high){
            int mid = low + (high - low) / 2;

            if(isValid(s, mid)){
                ans = mid;        // Found valid, try larger
                low = mid + 1;
            } else {
                high = mid - 1;   // Invalid, try smaller
            }
        }

        return ans;
    }
};

// ============================================================================
// APPROACH 4: Brute Force (Educational)
// ============================================================================
// TIME: O(n^2)  |  SPACE: O(1)
//
// HOW IT WORKS:
// - Check ALL possible substrings
// - For each substring, count character frequencies
// - Return maximum length where constraint is satisfied
//
// WHY AVOID IN PRACTICE?
// - O(n^2) is too slow for large inputs (n=10^5 -> 10^10 operations)
// - Useful only for understanding the problem or very small inputs
// ============================================================================
class Solution4 {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        int ans = 0;

        // Try all possible starting positions
        for(int i = 0; i < n; i++){
            int freq[26] = {0};

            // Try all possible ending positions from i
            for(int j = i; j < n; j++){
                freq[s[j] - 'a']++;

                // Check if constraint is violated
                if(freq[s[j] - 'a'] > 2) break;  // No need to check longer

                // Update maximum length
                ans = max(ans, j - i + 1);
            }
        }

        return ans;
    }
};

// ============================================================================
// MAIN - Test all approaches
// ============================================================================
int main(){
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;

    // Test cases
    string test1 = "eceba";
    string test2 = "aaa";
    string test3 = "abcabcabc";

    cout << "Test 1: " << test1 << endl;
    cout << "  Approach 1 (Map):        " << s1.maximumLengthSubstring(test1) << endl;
    cout << "  Approach 2 (Array):      " << s2.maximumLengthSubstring(test1) << endl;
    cout << "  Approach 3 (Binary):     " << s3.maximumLengthSubstring(test1) << endl;
    cout << "  Approach 4 (Brute):      " << s4.maximumLengthSubstring(test1) << endl;
    cout << endl;

    cout << "Test 2: " << test2 << endl;
    cout << "  Approach 1 (Map):        " << s1.maximumLengthSubstring(test2) << endl;
    cout << "  Approach 2 (Array):      " << s2.maximumLengthSubstring(test2) << endl;
    cout << "  Approach 3 (Binary):     " << s3.maximumLengthSubstring(test2) << endl;
    cout << "  Approach 4 (Brute):      " << s4.maximumLengthSubstring(test2) << endl;
    cout << endl;

    cout << "Test 3: " << test3 << endl;
    cout << "  Approach 1 (Map):        " << s1.maximumLengthSubstring(test3) << endl;
    cout << "  Approach 2 (Array):      " << s2.maximumLengthSubstring(test3) << endl;
    cout << "  Approach 3 (Binary):     " << s3.maximumLengthSubstring(test3) << endl;
    cout << "  Approach 4 (Brute):      " << s4.maximumLengthSubstring(test3) << endl;

    return 0;
}