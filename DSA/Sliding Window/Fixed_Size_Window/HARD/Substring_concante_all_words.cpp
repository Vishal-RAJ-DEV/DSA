/*
 * ================================================================
 *  PROBLEM: Substring with Concatenation of All Words (Leetcode 30)
 * ================================================================
 *
 *  QUESTION:
 *  ---------
 *  You are given a string s and an array of words (all of the SAME length).
 *  Find ALL starting indices of substring(s) in s that is a concatenation
 *  of EACH word in words EXACTLY ONCE, in ANY order, with NO intervening
 *  characters.
 *
 *  Example:
 *    s = "barfoothefoobarman"
 *    words = ["foo", "bar"]
 *    Output: [0, 9]
 *    Explanation:
 *      - Index 0: "barfoo" → "bar" + "foo"
 *      - Index 9: "foobar" → "foo" + "bar"
 *
 *  INTUITION:
 *  ----------
 *  Let wordLen = length of each word, wordCount = number of words.
 *  A valid substring has length = wordLen * wordCount.
 *
 *  Since all words have the SAME length, the problem transforms into:
 *    "Find windows where each word occurs exactly the required frequency."
 *
 *  KEY INSIGHT — Offset-based sliding window:
 *  ------------------------------------------
 *  Because every word is wordLen long, the word boundaries in a valid
 *  substring are aligned at positions that differ by wordLen.
 *
 *  A brute-force approach would check every possible start index (0..n-1)
 *  and extract wordLen * wordCount windows — O(n * wordLen * wordCount).
 *
 *  Instead, we use a SLIDING WINDOW that slides by wordLen steps, but we
 *  must run it wordLen times, starting at offsets 0, 1, ..., wordLen-1.
 *
 *  Why multiple offsets?
 *    - Suppose wordLen = 3.
 *      A valid window might begin at index 0 ("barfoo").
 *      If we slide only from offset 0 (indices 0,3,6,...), we catch
 *      windows starting at 0,3,6,...
 *      But a valid window might start at index 9 ("foobar") = 0 mod 3,
 *      so offset 0 catches that too.
 *    - However, consider s = "abfoo", words = ["foo"].
 *      wordLen = 3. Valid start = 2.
 *      Offset 0: checks positions 0,3 → misses index 2.
 *      So we need offset = 2 to catch it.
 *    - In general, a valid start can be anywhere from 0 to n-1.
 *      By trying offsets 0, 1, ..., wordLen-1, we ensure that EVERY
 *      possible start position is aligned to one of these offset
 *      sequences.
 *    - For a given offset, the window slides by wordLen and only
 *      visits indices ≡ offset (mod wordLen), which is fine because
 *      once we find the right offset, word boundaries match perfectly.
 *
 *  ALGORITHM OVERVIEW:
 *  -------------------
 *  1. Build a frequency map "need" of the required words.
 *  2. For each offset in [0, wordLen-1]:
 *       a. Initialize an empty "window" map, left = offset, count = 0.
 *       b. Slide right by wordLen from offset:
 *            i.   Extract the word at right.
 *            ii.  If word NOT in need → reset window, move left past right.
 *            iii. Add word to window, increment count.
 *            iv.  If word appears too many times → shrink from left
 *                 until excess is removed.
 *            v.   If count == wordCount → valid window found.
 *                 Record left, then slide left forward by one word
 *                 to look for the next overlapping valid window.
 *  3. Return all recorded indices.
 *
 *  VISUAL WALKTHROUGH:
 *  -------------------
 *  s = "lingmindraboofooowingdingbarrwingmonkeypoundcake"
 *  words = ["fooo","barr","wing","ding","wing"]
 *
 *  wordLen = 4, wordCount = 5, totalLen = 20
 *  need = {fooo:1, barr:1, wing:2, ding:1}
 *
 *  We try offset = 0..3:
 *
 *  offset = 0:
 *    right slides: 0,4,8,12,16,20,24,28,32,36,40,44,48
 *    Check substrings of length 4 at each position.
 *    (This would eventually find the valid window at index 13)
 *
 *  For a detailed trace, the key operations per step are:
 *    - Word matches? Yes → add to window
 *    - Frequency exceeded? Yes → shrink left
 *    - count == wordCount? Yes → save left, shrink left
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(wordLen * (n / wordLen)) = O(n)  — each character visited
 *           roughly once per offset, total ~ O(n * wordCount) worst case,
 *           but practically O(n) since the inner while loop moves left
 *           forward across the whole string amortized.
 *  Space → O(wordCount) for the hash maps.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;

        int wordLen = words[0].size();        // length of each word (all same)
        int wordCount = words.size();          // total number of words
        int totalLen = wordLen * wordCount;    // length of concatenated substring

        if (s.size() < totalLen)               // impossible to find any match
            return ans;

        unordered_map<string, int> need;       // frequency required for each word

        // Build the frequency map of required words
        for (string &word : words)
            need[word]++;

        /*
         * Try every possible starting offset modulo wordLen.
         * This ensures we cover all alignment cases.
         */
        for (int offset = 0; offset < wordLen; offset++) {

            unordered_map<string, int> window; // frequency of words currently in our window

            int left = offset;                 // left boundary of the sliding window
            int count = 0;                     // number of valid words in current window

            /*
             * Slide right pointer one word at a time (step = wordLen)
             * Each iteration processes a single word starting at 'right'.
             */
            for (int right = offset; right + wordLen <= s.size(); right += wordLen) {

                string word = s.substr(right, wordLen);  // extract the current word

                /*
                 * CASE 1: This word is NOT in our required list.
                 * The entire window up to this point is invalid.
                 * Reset everything and start fresh after this word.
                 */
                if (!need.count(word)) {
                    window.clear();
                    count = 0;
                    left = right + wordLen;              // move left past the invalid word
                    continue;
                }

                /*
                 * CASE 2: This word IS required.
                 * Add it to the current window.
                 */
                window[word]++;
                count++;

                /*
                 * CASE 2a: Too many copies of this word in the window.
                 * Shrink from the left (one word at a time) until
                 * the excess is removed.
                 *
                 * Example:
                 *   need = {wing:2, ...}
                 *   window has "wing" 3 times
                 *   We remove the leftmost word repeatedly until
                 *   window["wing"] <= 2.
                 */
                while (window[word] > need[word]) {
                    string leftWord = s.substr(left, wordLen); // word at left boundary
                    window[leftWord]--;                         // remove it from window
                    left += wordLen;                            // advance left boundary
                    count--;                                    // one less valid word
                }

                /*
                 * CASE 3: We have exactly wordCount valid words in the window.
                 * This means all required words are present with correct frequencies.
                 * Record the starting index (left), then slide left forward by one
                 * word to keep looking for more possible windows.
                 *
                 * Example:
                 *   s = "barfoofoobarthefoobarman"
                 *   At some point, left=0, window has {bar,foo,foo,bar} = 4 words
                 *   and wordCount=4 → valid! Save 0, then remove "bar" from left
                 *   and continue searching.
                 */
                if (count == wordCount) {
                    ans.push_back(left);                     // record valid start index

                    string leftWord = s.substr(left, wordLen); // slide window forward
                    window[leftWord]--;
                    left += wordLen;
                    count--;
                }
            }
        }

        return ans;
    }
};

int main() {
    return 0;
}
