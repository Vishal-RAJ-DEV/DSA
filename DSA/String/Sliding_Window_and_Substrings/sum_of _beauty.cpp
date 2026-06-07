#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int beautySum(string s) {
    /*
    Question:
    For every substring of the string, find its "beauty" and return the total sum.

    Beauty of a substring =
    (highest frequency of any character in that substring)
    -
    (lowest frequency of any character in that substring)

    Important:
    We consider only the characters that are present in the current substring.

    Example:
    substring = "aabcb"
    frequencies:
    a -> 2
    b -> 2
    c -> 1
    max frequency = 2
    min frequency = 1
    beauty = 2 - 1 = 1

    Algorithm:
    1. Fix the starting index i of the substring.
    2. Expand the ending index j from i to n-1.
    3. While expanding, keep updating the frequency of s[j].
    4. For the current substring s[i...j]:
       - find the maximum frequency
       - find the minimum frequency
       - add (maxi - mini) to the final answer
    5. Repeat for all starting positions.

    Intuition:
    We generate all substrings, but instead of rebuilding the frequency
    map from scratch every time, we grow the substring one character at a time.

    For a fixed i:
    - j = i gives first substring
    - j = i+1 extends it by one character
    - j = i+2 extends it again

    So the map always represents the frequency of the current substring.

    Time Complexity:
    - Outer loop over i -> O(n)
    - Inner loop over j -> O(n)
    - For each substring, scanning map to get max/min frequency -> O(26) for lowercase letters
      or O(k) for distinct characters in general
    - Overall: O(n^2 * alphabet) which is commonly treated as O(n^2) for lowercase English letters

    Space Complexity:
    - O(alphabet) for the frequency map
    */

    int n = s.size();
    int sum = 0;

    // Choose the starting index of the substring.
    for (int i = 0; i < n; i++) {
        unordered_map<char, int> mpp;

        // Extend the substring one character at a time.
        for (int j = i; j < n; j++) {
            mpp[s[j]]++;  // include current character in substring s[i...j]

            int maxi = 0;
            int mini = INT_MAX;

            // Find highest and lowest frequencies in the current substring.
            for (auto &p : mpp) {
                maxi = max(maxi, p.second);
                mini = min(mini, p.second);
            }

            // Add beauty of current substring to total answer.
            sum += (maxi - mini);
        }
    }

    return sum;
}

int main(){
    string s = "aabcb";
    cout << beautySum(s) << endl; // Output: 5
    cout << endl;
    return 0;
}
