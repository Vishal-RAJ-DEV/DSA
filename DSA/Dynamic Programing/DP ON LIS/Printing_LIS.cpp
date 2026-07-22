#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ==========================================================================
 *  PROBLEM: Print (Reconstruct) the Longest Increasing Subsequence
 *  ==========================================================================
 *  Given an array, return the actual LIS (not just its length).
 *
 *  Two approaches are provided:
 *    1. O(n²)  — Classic DP with parent tracking
 *    2. O(n log n) — Binary search + tailIndex + parent reconstruction
 * ========================================================================== */



/* ==========================================================================
 *  APPROACH 1 — O(n²) DP with Parent Tracking
 *  ==========================================================================
 *  Key Points to Remember:
 *    - dp[i] stores the LENGTH of the LIS that ENDS at index i.
 *    - parent[i] stores the PREVIOUS INDEX used to reach i in that LIS.
 *    - Whenever dp[i] is updated using j, set parent[i] = j.
 *    - After filling dp, find the index with the maximum dp value.
 *    - Follow the parent links BACKWARD to reconstruct the LIS (from last
 *      element to first).
 *    - Reverse the collected sequence because reconstruction starts from
 *      the last element of the LIS.
 *
 *  Intuition:
 *    Same as the standard LIS DP (dp[i] = 1 + max dp[j] for j < i and
 *    nums[j] < nums[i]). The extra `parent` array turns the "length only"
 *    DP into a full reconstruction by remembering the previous element in
 *    the optimal subsequence ending at each index.
 *
 *  Reconstruction:
 *    1. Find the index `lastIndex` with the largest dp[i].
 *    2. Walk backward: while parent[lastIndex] != lastIndex, add nums[lastIndex]
 *       to answer and set lastIndex = parent[lastIndex].
 *    3. Add the first element (where parent[lastIndex] == lastIndex).
 *    4. Reverse the answer (since we built it from last → first).
 *
 *  Time  Complexity: O(n²)  — two nested loops
 *  Space Complexity: O(n)   — dp + parent arrays
 * ========================================================================== */

class Solution {
public:
    vector<int> longestIncreasingSubsequence(vector<int>& nums) {

        int n = nums.size();

        /* dp[i] = length of LIS ending at index i (minimum = 1) */
        vector<int> dp(n, 1);

        /* parent[i] = previous index in the optimal LIS ending at i */
        vector<int> parent(n);

        int maxi = 1;         // maximum LIS length seen so far
        int lastIndex = 0;    // ending index of the overall LIS

        /* Initially every element points to itself (it's the start of its own LIS) */
        for (int i = 0; i < n; i++)
            parent[i] = i;

        /* ---------- Compute dp[i] for every index ---------- */
        for (int i = 0; i < n; i++) {

            /* Try to extend the LIS ending at any previous j */
            for (int j = 0; j < i; j++) {

                /* Condition 1: strictly increasing (nums[j] < nums[i])
                 * Condition 2: extending j gives a BETTER LIS than we already have at i */
                if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {

                    dp[i] = dp[j] + 1;

                    /* Remember which index we extended from */
                    parent[i] = j;
                }
            }

            /* Track the index where the overall LIS ends */
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastIndex = i;
            }
        }

        /* ---------- Reconstruct the LIS by following parent pointers ---------- */
        vector<int> ans;

        /* Walk backward until we hit the self-pointing start */
        while (parent[lastIndex] != lastIndex) {
            ans.push_back(nums[lastIndex]);
            lastIndex = parent[lastIndex];
        }

        /* Push the very first element of the LIS */
        ans.push_back(nums[lastIndex]);

        /* The above loop built the sequence backwards (from last → first) */
        reverse(ans.begin(), ans.end());

        return ans;
    }
};



/* ==========================================================================
 *  APPROACH 2 — O(n log n) Binary Search + Parent Reconstruction
 *  ==========================================================================
 *  Key Points to Remember (Must Know for Interviews):
 *    - tailIndex stores INDICES, not values.
 *    - tailIndex[len] = index of the SMALLEST POSSIBLE ENDING ELEMENT
 *      for an increasing subsequence of length (len + 1).
 *    - Binary search is performed on the VALUES nums[tailIndex[i]],
 *      not on the indices themselves.
 *    - If no larger/equal tail exists (x > all tails), APPEND the current
 *      index (LIS length increases by 1).
 *    - Otherwise, REPLACE the existing tail index with the current index
 *      (same LIS length, but a BETTER / SMALLER ending value).
 *    - parent[i] stores the PREVIOUS INDEX in the LIS ending at i.
 *    - When placing an element at position pos, set:
 *        parent[i] = tailIndex[pos - 1]   (if pos > 0)
 *    - The LAST ELEMENT of the final LIS is tailIndex.back().
 *    - Follow the parent pointers BACKWARD to reconstruct the sequence,
 *      then reverse it.
 *
 *  Intuition:
 *    This extends the classic O(n log n) LIS-length algorithm (tails array)
 *    to also RECONSTRUCT the actual sequence. The trick is:
 *      - Instead of storing values in `tails`, we store INDICES.
 *      - For each index i, when we place it at position `pos` in tailIndex,
 *        the element at tailIndex[pos - 1] is the PREVIOUS element in the
 *        optimal subsequence of length pos. We record this in parent[i].
 *      - At the end, tailIndex.back() points to the last element of the
 *        actual LIS, and parent pointers trace it back to the beginning.
 *
 *  Dry Run Example: nums = [10, 9, 2, 5, 3, 7, 101, 18]
 *
 *    i=0, x=10: tailIndex=[], pos=0 → append 0, parent[0] = (none)
 *               tailIndex = [0]   (represents value 10)
 *    i=1, x=9:  binary search on values [10] → first >= 9 is index 0 (10)
 *               pos=0, replace tailIndex[0]=1, parent[1] = (none, pos==0)
 *               tailIndex = [1]   (represents value 9)
 *    i=2, x=2:  binary search on values [9] → first >= 2 is index 0 (9)
 *               pos=0, replace tailIndex[0]=2, parent[2] = none
 *               tailIndex = [2]   (represents value 2)
 *    i=3, x=5:  binary search on values [2] → none >= 5
 *               pos=1, append 3, parent[3] = tailIndex[0] = 2
 *               tailIndex = [2, 3]   (represents values [2, 5])
 *    i=4, x=3:  binary search on values [2, 5] → first >= 3 is index 1 (5)
 *               pos=1, replace tailIndex[1]=4, parent[4] = tailIndex[0] = 2
 *               tailIndex = [2, 4]   (represents values [2, 3])
 *    i=5, x=7:  binary search on values [2, 3] → none >= 7
 *               pos=2, append 5, parent[5] = tailIndex[1] = 4
 *               tailIndex = [2, 4, 5]   (represents values [2, 3, 7])
 *    i=6, x=101: binary search on values [2,3,7] → none >= 101
 *               pos=3, append 6, parent[6] = tailIndex[2] = 5
 *               tailIndex = [2, 4, 5, 6]   (values [2, 3, 7, 101])
 *    i=7, x=18: binary search on values [2,3,7,101] → first >= 18 is 101 at idx 3
 *               pos=3, replace tailIndex[3]=7, parent[7] = tailIndex[2] = 5
 *               tailIndex = [2, 4, 5, 7]   (values [2, 3, 7, 18])
 *
 *    Reconstruction:
 *      cur = tailIndex.back() = 7 (nums[7] = 18)
 *      parent[7] = 5 (nums[5] = 7)
 *      parent[5] = 4 (nums[4] = 3)
 *      parent[4] = 2 (nums[2] = 2)
 *      parent[2] = -1 → stop
 *      ans = [18, 7, 3, 2] → reverse → [2, 3, 7, 18]  ✓
 *
 *  Time  Complexity: O(n log n)
 *  Space Complexity: O(n)
 * ========================================================================== */

class Solution2 {
public:
    vector<int> longestIncreasingSubsequence(vector<int>& nums) {

        int n = nums.size();

        /* tailIndex[pos] = index of the smallest ending element for a
         * subsequence of length (pos + 1). This is the O(n log n) LIS
         * length algorithm, but storing INDICES instead of values. */
        vector<int> tailIndex;

        /* parent[i] = index of the PREVIOUS element in the optimal LIS
         * ending at i. Used to reconstruct the full sequence. */
        vector<int> parent(n, -1);

        for (int i = 0; i < n; i++) {

            /* ----- Binary search on the VALUES stored at tailIndex -----
             * Find the first position where nums[tailIndex[pos]] >= nums[i].
             * The comparator: nums[tailIndex[index]] < value
             * This finds the first tail that is NOT < nums[i],
             * i.e. the first tail >= nums[i]. */
            auto it = lower_bound(
                tailIndex.begin(),
                tailIndex.end(),
                nums[i],
                [&](int index, int value) {
                    return nums[index] < value;
                });

            int pos = it - tailIndex.begin();   // position where i belongs

            if (it == tailIndex.end()) {
                /* nums[i] is larger than all tails → NEW longest LIS found */
                tailIndex.push_back(i);
            } else {
                /* Replace the existing tail with i (smaller ending value) */
                *it = i;
            }

            /* ----- Record parent link -----
             * The element at tailIndex[pos - 1] is the best predecessor
             * for an LIS of length (pos + 1) that ends at i. */
            if (pos > 0)
                parent[i] = tailIndex[pos - 1];
        }

        /* ---------- Reconstruct the LIS ----------
         * tailIndex.back() points to the LAST element of the overall LIS.
         * Follow parent pointers backward to get the full sequence. */
        vector<int> ans;
        int cur = tailIndex.back();

        while (cur != -1) {
            ans.push_back(nums[cur]);
            cur = parent[cur];
        }

        /* The while loop built the sequence backwards (last → first) */
        reverse(ans.begin(), ans.end());

        return ans;
    }
};



int main(){
    return 0;
}