#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given a string s and three integers:
- maxLetters
- minSize
- maxSize

You need to find the maximum number of occurrences of any substring such that:
- substring length is between minSize and maxSize
- the number of distinct characters in that substring is at most maxLetters

Return the highest frequency among all valid substrings.

Example idea:
s = "aababcaab"
maxLetters = 2
minSize = 3
maxSize = 4

Possible valid substrings must:
- have length 3 or 4
- contain at most 2 distinct characters

We count how many times each valid substring appears,
and return the maximum count.

Important intuition:
Why is checking only minSize enough in the optimized approach?
- If a larger substring is valid, then its smaller minSize-length pieces are easier to repeat.
- Longer substrings are harder to repeat because they are more specific.
- So the maximum frequency will always come from a substring of length minSize.

That is the key optimization of this problem.
*/

/*
Brute Force Approach:

Logic:
- Try every substring length from minSize to maxSize.
- For each length, generate every substring.
- Count distinct characters in that substring.
- If distinct characters <= maxLetters, count its frequency.
- Track the maximum frequency.

Why this is expensive:
- We check many substring lengths.
- For every substring, we build a fresh frequency map.
- So a lot of repeated work is done.

Time idea:
- This becomes too slow for large strings because substring creation
  and distinct-character counting happen again and again.
*/
class SolutionBruteForce {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        unordered_map<string, int> occur;
        int ans = 0;

        // Try every possible length from minSize to maxSize.
        for (int len = minSize; len <= maxSize; len++) {
            // Generate every substring of current length.
            for (int start = 0; start + len <= n; start++) {
                string sub = s.substr(start, len);

                // Count distinct characters inside this substring.
                unordered_map<char, int> mpp;
                for (char ch : sub) {
                    mpp[ch]++;
                }

                // If valid, store its frequency.
                if (mpp.size() <= maxLetters) {
                    occur[sub]++;
                    ans = max(ans, occur[sub]);
                }
            }
        }

        return ans;
    }
};

/*
Optimized Sliding Window Approach:

Main logic:
- We only check substrings of length minSize.
- Maintain a sliding window of fixed size minSize.
- Maintain a frequency map of characters inside the current window.
- If the window has at most maxLetters distinct characters,
  count that substring in occur map.
- Track the maximum frequency.

How sliding window works here:
- Expand window by adding s[r]
- If window size becomes greater than minSize, remove s[l] and move l forward
- When window size becomes exactly minSize, check distinct character count

Why this is better:
- We avoid checking all sizes from minSize to maxSize
- We avoid rebuilding the character frequency map from scratch for every substring
- We reuse the previous window information by adding one char and removing one char

Window intuition:
Suppose minSize = 3 and current window is "aab"
Next window might be "aba"
Instead of recounting everything:
- remove old left char
- add new right char
This is the power of sliding window.
*/
class SolutionSlidingWindow {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();

        // occur counts how many times each valid substring appears.
        unordered_map<string, int> occur;

        // mpp stores frequency of characters in the current window.
        unordered_map<char, int> mpp;

        int ans = 0;
        int l = 0;

        for (int r = 0; r < n; r++) {
            // Add the new right character into the window.
            mpp[s[r]]++;

            /*
            Keep the window size fixed at minSize.
            If it becomes too large, remove the leftmost character.
            */
            if (r - l + 1 > minSize) {
                mpp[s[l]]--;
                if (mpp[s[l]] == 0) mpp.erase(s[l]);
                l++;
            }

            /*
            Now the window size is exactly minSize.
            If the number of distinct characters is within limit,
            count this substring.
            */
            if (r - l + 1 == minSize && mpp.size() <= maxLetters) {
                string sub = s.substr(l, minSize);
                occur[sub]++;
                ans = max(ans, occur[sub]);
            }
        }

        return ans;
    }
};

int main() {
    string s = "aababcaab";
    int maxLetters = 2;
    int minSize = 3;
    int maxSize = 4;

    SolutionBruteForce brute;
    SolutionSlidingWindow optimal;

    cout << brute.maxFreq(s, maxLetters, minSize, maxSize) << '\n';
    cout << optimal.maxFreq(s, maxLetters, minSize, maxSize) << '\n';

    return 0;
}
