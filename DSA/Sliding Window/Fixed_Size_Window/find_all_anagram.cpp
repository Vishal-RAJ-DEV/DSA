#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given two strings s and p.
You have to return all starting indices in s where the substring is an anagram of p.

What is an anagram?
- Two strings are anagrams if they contain the same characters
  with the same frequencies, only the order may be different.

Example:
s = "cbaebabacd"
p = "abc"

Substrings of length 3 in s are checked because p has length 3.
- "cba" -> anagram of "abc"
- "bac" -> anagram of "abc"

So the answer is [0, 6]

Main intuition:
- Any anagram of p must have the same length as p.
- So we only need to check substrings of s whose size is exactly p.size().
- Instead of sorting every substring again and again, we use character frequency counts.

Approach:
- Store the frequency of characters of p in an array called freq.
- Maintain a sliding window of size p.size() over s.
- Store the frequency of characters inside the current window in another array called check.
- If both frequency arrays are equal, then the current window is an anagram of p.

Why frequency comparison works:
- Order does not matter in an anagram.
- Only character counts matter.
- So if the window and p have the same count for every character,
  then they contain the same letters and the window is a valid anagram.

Why sliding window is efficient:
- When the window moves by one step, we do not rebuild the whole frequency array.
- We only:
  1. add the new right character
  2. remove the old left character
- This makes the process much faster than checking every substring from scratch.
*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size();

        // If s is smaller than p, no substring of required size can exist.
        if (n < p.size()) return {};

        // freq stores the character count of pattern p.
        vector<int> freq(26, 0);

        // check stores the character count of the current sliding window in s.
        vector<int> check(26, 0);

        for (char ch : p) {
            freq[ch - 'a']++;
        }

        int r = 0;
        int l = 0;
        vector<int> ans;

        while (r < n) {
            // Include the current right character into the window.
            check[s[r] - 'a']++;

            /*
            This is a fixed-size sliding window.
            If the window becomes larger than p.size(),
            remove the leftmost character and shrink it.
            */
            if (r - l + 1 > p.size()) {
                check[s[l] - 'a']--;
                l++;
            }

            /*
            When window size becomes exactly equal to p.size(),
            compare frequencies.

            If both arrays are equal, it means:
            - same letters are present
            - same number of times
            So this window is an anagram of p.
            */
            if (r - l + 1 == p.size()) {
                if (freq == check) {
                    ans.push_back(l);
                }
            }

            // Move the right pointer to expand the window forward.
            r++;
        }

        return ans;
    }
};

int main() {
    string s = "cbaebabacd";
    string p = "abc";
    Solution obj;
    vector<int> ans = obj.findAnagrams(s, p);

    cout << "The starting indices of the anagrams of p in s are: ";
    for (int index : ans) {
        cout << index << " ";
    }

    return 0;
}
