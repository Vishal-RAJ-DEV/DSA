#include <bits/stdc++.h>
using namespace std;

  /*
    -------------------------------------------------------------------------
    Longest String Chain (LIS Pattern)
    You are given an array of words where each word consists of lowercase English letters.

    wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

    For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
    A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.

    Return the length of the longest possible word chain with words chosen from the given list of words.
    -------------------------------------------------------------------------

    This problem is solved using the exact same Dynamic Programming pattern as
    the Longest Increasing Subsequence (LIS).

    ------------------------- Mapping with LIS -------------------------

    LIS Problem:
        - We have numbers.
        - A number nums[i] can extend the subsequence ending at nums[j]
          if nums[j] < nums[i].

        Transition:
            dp[i] = max(dp[i], dp[j] + 1)

    Longest String Chain:
        - We have strings instead of numbers.
        - A string words[i] can extend the chain ending at words[j]
          only if words[j] is a valid predecessor of words[i].
        - A predecessor means:
              • words[i] has exactly one extra character.
              • Removing one character from words[i] makes words[j].

        Transition:
            dp[i] = max(dp[i], dp[j] + 1)

    --------------------------------------------------------------------

    Why do we sort?

    In LIS, smaller numbers naturally appear before larger numbers.

    Here, a predecessor must always have length exactly one less than the
    current word, so we first sort all strings by their length.

    After sorting:
        Every possible predecessor always appears before its successor,
        allowing us to apply the LIS DP transition.

    --------------------------------------------------------------------

    DP State:

        dp[i]
        = Length of the longest string chain ending at words[i].

    --------------------------------------------------------------------

    Transition:

        For every previous word j:

            If words[j] is a valid predecessor of words[i],

                dp[i] = max(dp[i], dp[j] + 1)

    --------------------------------------------------------------------

    Answer:

        The maximum value present in the dp[] array.

    --------------------------------------------------------------------

    Time Complexity:
        Sorting : O(n log n)
        DP       : O(n²)
        checkPossible() : O(L)

        Overall : O(n² × L)

        where L = maximum length of a word.

    Space Complexity:
        O(n)
    --------------------------------------------------------------------
    */
class Solution {
public:
    // Function to return the length of the longest string chain possible
    int longestStringChain(vector<string>& words) {

        int n = words.size(); // Size of the array

        sort(words.begin(), words.end(), compare);

        vector<int> dp(n, 1); // dp[i] stores the longest chain ending at words[i].

        // Stores the maximum chain length found so far.
        int maxLen = 0;

        // Computing the DP array
        for(int i = 0; i < n; i++) {

            // Check every previous word as a possible predecessor.
            for(int j = 0; j < i; j++) {

                /*
                 If words[j] is a valid predecessor of words[i],
                 try extending the chain ending at j.
                */
                if(checkPossible(words[i], words[j]) && dp[i] < dp[j] + 1) {

                    // Update the best chain ending at words[i].
                    dp[i] = dp[j] + 1;
                }
            }

            // Update the overall longest chain.
            if(dp[i] > maxLen)
                maxLen = dp[i];
        }

        return maxLen;
    }

private:

    // Sort strings in increasing order of their length.
    static bool compare(string &s, string &t) {
        return s.size() < t.size();
    }

    // Returns true if 't' is a predecessor of 's'.
    bool checkPossible(string &s, string &t) {

        // The larger string must contain exactly one extra character.
        if(s.size() != t.size() + 1)
            return false;

        int i = 0, j = 0; // Two pointers

        // Traverse the larger string.
        while(i < s.size()) {

            // Characters match -> move both pointers.
            if(j < t.size() && s[i] == t[j]) {
                i++;
                j++;
            }
            // Mismatch -> skip the extra character from the larger string.
            else {
                i++;
            }
        }

        // If every character of the smaller string was matched,
        // then 't' is a valid predecessor of 's'.
        if(i == s.size() && j == t.size())
            return true;

        return false;
    }
};

int main() {

    vector<string> words = {"a", "ab", "abc", "abcd", "abcde"};

    // Creating an object of Solution class
    Solution sol;

    int lengthOfLongestStringChain = sol.longestStringChain(words);

    cout << "The length of the Longest String Chain is: "
         << lengthOfLongestStringChain << endl;

    return 0;
}