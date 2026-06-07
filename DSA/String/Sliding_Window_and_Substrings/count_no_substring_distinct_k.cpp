#include <bits/stdc++.h>
using namespace std;

// Function to count substrings with at most k distinct characters
int atMostKDistinct(string s, int k) {
    // Left pointer and result
    int left = 0, res = 0;
    // Frequency map to track occurrences of each character in current window
    unordered_map<char, int> freq;

    // Iterate through string with right pointer
    for (int right = 0; right < s.size(); right++) {
        // Add current character to frequency map
        freq[s[right]]++;

        // Shrink window if distinct characters exceed k
        while (freq.size() > k) {
            // Decrement frequency of left character
            freq[s[left]]--;
            // Remove character completely if frequency becomes 0
            if (freq[s[left]] == 0) freq.erase(s[left]);
            // Move left pointer to shrink window
            left++;
        }

        // Count substrings in current window
        // For each new position of right pointer, 
        // we add all possible substrings ending at 'right'
        res += (right - left + 1);
    }
    return res;
}

// Function to count substrings with exactly k distinct characters
int countSubstrings(string s, int k) {
    // Mathematical trick: exactly k = atMost(k) - atMost(k-1)
    return atMostKDistinct(s, k) - atMostKDistinct(s, k - 1);
}

int main() {
    // Sample test
    string s = "pqpqs";
    int k = 2;

    // Output the result
    cout << "Count: " << countSubstrings(s, k) << endl; // Output: 7
    return 0;
}
/*
🧠 Intuitive Explanation

Imagine you counted all substrings that have at most 2 distinct characters:

👉 That includes:

substrings with 1 distinct character

substrings with 2 distinct characters

Now, if you remove all substrings that have at most 1 distinct character,
what’s left must be exactly 2 distinct characters.

It’s just like this analogy:

Category	Meaning
“At most 2”	{ 1-char substrings, 2-char substrings }
“At most 1”	{ 1-char substrings }
Subtract them	Left with only 2-char substrings ✅
*/