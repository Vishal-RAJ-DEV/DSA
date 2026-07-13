#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: Longest Happy String (LeetCode 1405)
    Given three integers a, b, c representing counts of 'a', 'b', 'c',
    build the longest possible string such that no three consecutive
    characters are the same.

    ================================================================
    APPROACH 1: Max-Heap (Priority Queue) - Greedy with Frequency
    ================================================================

    INTUITION:
    - We always want to use the character with the highest remaining count
      to maximize the string length.
    - However, if a character has already been used twice consecutively,
      we must skip it and use the next most frequent character instead.
    - This is exactly like scheduling: prioritize the most "available"
      resource, but avoid putting the same resource 3 times in a row.

    ALGORITHM:
    1. Push all characters with count > 0 into a max-heap (ordered by count).
    2. While heap is not empty:
       a. Pop the character with highest remaining frequency (char1, cnt1).
       b. If the last two characters in result are both char1:
          - We cannot use char1 now -> pop the second highest (char2, cnt2).
          - If no second char exists, break (cannot extend further).
          - Append char2 to result, decrement its count.
          - Push char2 back if still remaining.
          - Push char1 back (it will be available next round).
       c. Else (no triple constraint):
          - Append char1 to result, decrement its count.
          - Push char1 back if still remaining.
    3. Return result.

    TIME COMPLEXITY: O((a+b+c) * log(3)) ≈ O(N) where N = a+b+c
    SPACE COMPLEXITY: O(1) — heap stores at most 3 elements
*/

class Solution1_Heap {
public:
    string longestDiverseString(int a, int b, int c) {
        // Max-heap: ordered by character frequency (largest first)
        priority_queue<pair<int, char>> pq;

        if (a > 0) pq.push(make_pair(a, 'a'));
        if (b > 0) pq.push(make_pair(b, 'b'));
        if (c > 0) pq.push(make_pair(c, 'c'));

        string res = "";

        while (!pq.empty()) {
            pair<int, char> top1 = pq.top();
            pq.pop();
            int cnt1 = top1.first;
            char char1 = top1.second;

            // Check if adding char1 would create "xxx" (three same chars)
            if (res.size() >= 2 && res.back() == char1 && res[res.size() - 2] == char1) {
                // We need to use the next best character to break the streak
                if (pq.empty()) break;

                pair<int, char> top2 = pq.top();
                pq.pop();
                int cnt2 = top2.first;
                char char2 = top2.second;

                res += char2;
                cnt2--;

                if (cnt2 > 0) pq.push(make_pair(cnt2, char2));
                pq.push(make_pair(cnt1, char1));
            } else {
                res += char1;
                cnt1--;

                if (cnt1 > 0) pq.push(make_pair(cnt1, char1));
            }
        }

        return res;
    }
};

/*
    ================================================================
    APPROACH 2: Greedy without Heap — Direct Comparison
    ================================================================

    INTUITION:
    - At each step, pick the character with the highest remaining count
      that does not violate the "no three consecutive" rule.
    - We track consecutive counts (currA, currB, currC) for each char.
    - Pick a character if:
        (a) Its consecutive count < 2 AND it has the highest remaining count, OR
        (b) The other two characters have already reached 2 consecutive
            (so we must use this one to prevent them from forming a triplet).
    - This is a deterministic greedy: at every position, there is exactly
      one correct character to pick (or none → termination).

    ALGORITHM:
    1. Initialize currA=currB=currC=0 (consecutive counters).
    2. Loop maxLen = a+b+c times (or until no character can be placed):
       a. Check conditions for 'a':
          - (currA != 2 && a >= b && a >= c) → 'a' is the most available
            and hasn't been used twice consecutively.
          - OR (a > 0 && (currB == 2 || currC == 2)) → must use 'a' to
            prevent 'b' or 'c' from forming a triplet.
       b. Same logic for 'b' and 'c'.
       c. Append chosen char, update counters:
          - Increment chosen char's consecutive counter.
          - Reset the other two counters to 0.
          - Decrement the remaining count of chosen char.
    3. Return result string.

    TIME COMPLEXITY: O(N) where N = a+b+c
    SPACE COMPLEXITY: O(1)

    WHY THIS WORKS:
    - At each step, we either pick the globally most frequent character
      (that still allows a valid sequence) or the character forced by
      the "anti-triplet" rule.
    - This ensures we always maximise length without ever making a
      choice that would cause early termination.
*/

class Solution2_Greedy {
public:
    string longestDiverseString(int a, int b, int c) {
        int currA = 0, currB = 0, currC = 0; // consecutive counts
        int maxLen = a + b + c;
        string result;

        for (int i = 0; i < maxLen; i++) {
            // Try to place 'a'
            if ((currA != 2 && a >= b && a >= c) ||
                (a > 0 && (currB == 2 || currC == 2))) {
                result += 'a';
                currA++;
                currB = currC = 0; // reset others
                a--;
            }
            // Try to place 'b'
            else if ((currB != 2 && b >= a && b >= c) ||
                     (b > 0 && (currA == 2 || currC == 2))) {
                result += 'b';
                currB++;
                currA = currC = 0;
                b--;
            }
            // Try to place 'c'
            else if ((currC != 2 && c >= a && c >= b) ||
                     (c > 0 && (currA == 2 || currB == 2))) {
                result += 'c';
                currC++;
                currA = currB = 0;
                c--;
            }
            // If no character satisfies conditions → break
            else {
                break;
            }
        }

        return result;
    }
};

/*
    COMPARISON OF BOTH APPROACHES:
    ---------------------------------------
    | Aspect           | Approach 1 (Heap) | Approach 2 (Greedy)  |
    |------------------|-------------------|----------------------|
    | Data Structure   | priority_queue    | variables + checks   |
    | Logic            | avoid triple by   | avoid triple by      |
    |                  | skipping char     | conditional checks   |
    | Time Complexity  | O(N log 3) ≈ O(N) | O(N)                 |
    | Code Complexity  | Slightly complex  | Simple & direct      |
    | Intuition        | Scheduling with   | Decision at each     |
    |                  | cooldown of 2     | position             |
    ---------------------------------------

    Both produce the same result. The heap approach generalises better
    to k distinct characters (just push all into heap). The greedy
    approach is optimal when the alphabet size is fixed (here 3).
*/

int main() {
    // Test cases
    Solution1_Heap s1;
    Solution2_Greedy s2;

    cout << "Approach 1 (Heap): " << s1.longestDiverseString(1, 1, 7) << endl;
    cout << "Approach 2 (Greedy): " << s2.longestDiverseString(1, 1, 7) << endl;

    cout << "Approach 1 (Heap): " << s1.longestDiverseString(2, 4, 1) << endl;
    cout << "Approach 2 (Greedy): " << s2.longestDiverseString(2, 4, 1) << endl;

    cout << "Approach 1 (Heap): " << s1.longestDiverseString(7, 1, 0) << endl;
    cout << "Approach 2 (Greedy): " << s2.longestDiverseString(7, 1, 0) << endl;

    return 0;
}
