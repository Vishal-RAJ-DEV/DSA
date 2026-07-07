#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given two strings s1 and s2.
Return true if some permutation of s1 is present as a substring of s2.
Otherwise return false.

What does permutation mean?
- A permutation is a rearrangement of characters.
- Example:
  s1 = "ab"
  permutations are "ab" and "ba"

So if s2 contains "ab" or "ba" as a substring, the answer is true.

Example:
s1 = "ab"
s2 = "eidbaooo"

Substring "ba" exists in s2, and "ba" is a permutation of "ab".
So answer = true.

Main idea common to all 3 approaches:
- Any permutation of s1 must have the same length as s1.
- So we only need to check windows of length s1.size() inside s2.
- If one window has exactly the same character frequency as s1,
  then that window is a permutation of s1.

How sliding window works in this problem:
- Keep a window of fixed size = s1.size()
- Add one character from the right
- If the window becomes too large, remove one character from the left
- After every valid-size window, compare its frequency with s1

Below, all three approaches use this same idea,
but they differ in how they organize the window movement.
*/

/*
Approach 1: Standard left-right sliding window

How it works:
- Use two pointers l and r.
- r expands the window by adding a new character.
- If window size becomes larger than s1.size(),
  remove s2[l] and move l forward.
- Whenever window size becomes exactly s1.size(), compare frequency arrays.

Why this is useful:
- This is the most general sliding-window template.
- It is easy to reuse for many other fixed-size or variable-size window problems.

How it is different from the other two:
- It explicitly tracks the window size using l and r.
- It is very intuitive if you are learning sliding window for the first time.
*/
class SolutionApproach1 {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> freq(26, 0);
        vector<int> check(26, 0);

        if (s1.size() > s2.size()) return false;

        for (char ch : s1) {
            freq[ch - 'a']++;
        }

        int l = 0;
        int r = 0;

        while (r < s2.size()) {
            // Add the current right character into the window.
            check[s2[r] - 'a']++;

            /*
            If window size becomes bigger than s1.size(),
            remove the leftmost character and move l forward.
            */
            if (r - l + 1 > s1.size()) {
                check[s2[l] - 'a']--;
                l++;
            }

            // When the window size is exactly equal to s1.size(), compare counts.
            if (r - l + 1 == s1.size()) {
                if (freq == check) return true;
            }

            // Expand the window by moving right pointer.
            r++;
        }

        return false;
    }
};

/*
Approach 2: Pre-fill first window, then slide by one step

How it works:
- First build frequency for s1 and for the first window of s2 of size n1.
- Compare them once.
- Then from left to right:
  1. add the new incoming character
  2. remove the old outgoing character
  3. compare again

Why this is useful:
- This is a very clean fixed-size window pattern.
- Since the first window is already built, every next step is simply:
  add one, remove one.

How it is different from Approach 1:
- It does not use the "window too large, then shrink" style.
- Instead, it starts with a valid-size window from the beginning.
- This makes the loop shorter and often easier for fixed-size problems.
*/
class SolutionApproach2 {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n2 < n1) return false;

        vector<int> c1(26, 0), c2(26, 0);

        // Build frequency of s1 and of the first window of s2.
        for (int i = 0; i < n1; i++) {
            c1[s1[i] - 'a']++;
            c2[s2[i] - 'a']++;
        }

        // Check the very first window.
        if (c1 == c2) return true;

        /*
        Now slide the window one step at a time.
        Incoming character: s2[i]
        Outgoing character: s2[i - n1]
        */
        for (int i = n1; i < n2; i++) {
            c2[s2[i] - 'a']++;
            c2[s2[i - n1] - 'a']--;

            if (c1 == c2) return true;
        }

        return false;
    }
};

/*
Approach 3: Start-end index window with explicit shift

How it works:
- Build the frequency of s1 and the first window of s2.
- Use i as the start of the window.
- Use j as the next character that will enter the window.
- If current window is not a match:
  1. remove s2[i]
  2. add s2[j]
  3. move both i and j one step forward

Why this is useful:
- It clearly shows the idea that one character leaves and one character enters.
- Some people find this version easier to visualize than pointer-size formulas.

How it is different from Approach 2:
- Approach 2 uses a for-loop and derives the outgoing index as i - n1.
- Approach 3 directly keeps two moving indices: one leaving, one entering.
- Logic is almost the same, but the window shift is expressed more explicitly.

How it is different from Approach 1:
- Approach 1 manages window size dynamically with l and r.
- Approach 3 starts with a full valid window and only performs full-window shifts.
*/
class SolutionApproach3 {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
        }

        vector<int> mp(26, 0), temp(26, 0);

        // Build frequency for s1 and the first window of s2.
        for (int i = 0; i < s1.size(); i++) {
            mp[s1[i] - 'a']++;
            temp[s2[i] - 'a']++;
        }

        // i = start of current window, j = next incoming character.
        int i = 0, j = s1.size();

        while (j < s2.size()) {
            // If current window matches, we found a permutation.
            if (temp == mp) {
                break;
            } else {
                // Remove the leftmost character of current window.
                temp[s2[i] - 'a']--;

                // Add the next character to the right.
                temp[s2[j] - 'a']++;

                // Shift the whole window by one step.
                i++, j++;
            }
        }

        if (temp == mp) {
            return true;
        }
        return false;
    }
};

int main() {
    string s1 = "ab";
    string s2 = "eidbaooo";

    SolutionApproach1 a1;
    SolutionApproach2 a2;
    SolutionApproach3 a3;

    cout << a1.checkInclusion(s1, s2) << '\n';
    cout << a2.checkInclusion(s1, s2) << '\n';
    cout << a3.checkInclusion(s1, s2) << '\n';

    return 0;
}
