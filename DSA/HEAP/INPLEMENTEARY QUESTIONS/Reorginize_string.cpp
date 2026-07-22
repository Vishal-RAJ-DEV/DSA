#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* --------------------------------------------------------------------------
 *  Algorithm: Max-Heap (Greedy with "cool-off" for previous character)
 * --------------------------------------------------------------------------
 *  Problem (LeetCode 767): Reorganize String such that no two adjacent
 *  characters are the same. If impossible, return "".
 *
 *  Key Observation:
 *    If any character appears more than ceil(n/2) times, it is impossible
 *    to rearrange without adjacent duplicates. This algorithm will
 *    naturally detect that case.
 *
 *  Algorithm Steps:
 *    1. Count frequency of every character in the string.
 *    2. Push all characters into a Max Heap (ordered by frequency).
 *       The character with the highest remaining count is always on top.
 *    3. Maintain a "previous" pair `prev = {remainingCount, character}`.
 *       This holds the character we just placed — it cannot be placed
 *       again immediately (otherwise we'd get adjacent duplicates).
 *    4. In each iteration:
 *       a) Pop the most frequent character from the heap.
 *       b) Append it to the result string.
 *       c) Decrement its remaining frequency (we used one occurrence).
 *       d) Now push `prev` back into the heap (if it still has remaining
 *          count), because a different character has been placed in
 *          between, so `prev` is now safe to be picked again.
 *       e) Set `prev` to the current (decremented) character so it sits
 *          out for one turn.
 *    5. If the loop finishes AND the result length equals original length,
 *       return the result. Otherwise return "".
 *
 *  Why it works:
 *    - By always picking the most frequent character that isn't the one
 *      we just placed, we greedily avoid adjacent duplicates.
 *    - The `prev` variable acts as a mandatory one-turn delay:
 *      "you just got placed, now sit out for the next pick."
 *    - If a character is too frequent, eventually the heap will empty
 *      before all characters are placed, and the length check catches it.
 *
 *  Dry Run with "aab":
 *    freq: a->2, b->1
 *    heap: [{2,'a'}, {1,'b'}]
 *
 *    Iter 1: pop {2,'a'}, ans="a", freq-- => 1
 *            prev was {0,'#'}, skip push
 *            prev = {1,'a'}
 *    Iter 2: pop {1,'b'}, ans="ab", freq-- => 0
 *            push prev {1,'a'} back
 *            prev = {0,'b'}
 *    Iter 3: pop {1,'a'}, ans="aba", freq-- => 0
 *            prev {0,'b'} has no count, skip
 *            prev = {0,'a'}
 *    Done. ans.length() = 3 == s.length() => return "aba"
 *
 *  Time  Complexity: O(n log k) — n = string length, k = distinct chars
 *        Each push/pop on the heap costs O(log k) ≤ O(log 26) = O(1)
 *  Space Complexity: O(k) ≈ O(1) — since alphabet size is fixed (26)
 * -------------------------------------------------------------------------- */

class Solution {
public:
    string reorganizeString(string s) {

        /* ---- Step 1: Count character frequencies ---- */
        unordered_map<char, int> freq;
        for (char ch : s)
            freq[ch]++;

        /* ---- Step 2: Max Heap ordered by frequency ---- */
        priority_queue<pair<int, char>> pq;
        for (auto &it : freq)
            pq.push({it.second, it.first});

        string ans = "";

        /* ---- Step 3: Previous character (cool-off) ---- */
        pair<int, char> prev = {0, '#'};   // {remainingCount, character}

        /* ---- Step 4: Greedy placement loop ---- */
        while (!pq.empty()) {

            /* Pick the character with the highest remaining frequency */
            auto curr = pq.top();
            pq.pop();

            int frequency = curr.first;
            char ch       = curr.second;

            /* Place it in the result */
            ans += ch;
            frequency--;   // one occurrence consumed

            /* The previous character can now be used again because a
             * different character was just placed between them. */
            if (prev.first > 0)
                pq.push(prev);

            /* The current character must now sit out for one turn */
            prev = {frequency, ch};
        }

        /* ---- Step 5: Verify completeness ---- */
        if (ans.length() != s.length())
            return "";     // impossible to reorganize

        return ans;
    }
};


int main(){
    return 0;
}