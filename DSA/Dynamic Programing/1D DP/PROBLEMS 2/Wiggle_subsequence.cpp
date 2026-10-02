// ============================================================================
// QUESTION: Wiggle Subsequence (LeetCode 376)
// ----------------------------------------------------------------------------
// A sequence is a WIGGLE sequence if the differences between successive
// elements strictly alternate between positive and negative.
// (The first difference may be either; equal neighbours are NOT allowed.)
//
//   [1, 7, 4, 9, 2, 5] -> 1 < 7 > 4 < 9 > 2 < 5  -> wiggle, length 6
//   [1, 17, 5, 10, 15, 16] -> 1 < 17 > 5 < 10 (10 < 15 fails) -> length 4
//   [1, 2, 3, 4, 5, 6, 7, 8, 9] -> all increasing -> longest wiggle = 2
//
// Given nums, return the LENGTH of the longest wiggle SUBSEQUENCE
// (not substring - you may skip elements, but keep their order).
//
// ----------------------------------------------------------------------------
// INTUITION - why two DP arrays?
// ----------------------------------------------------------------------------
// A wiggle sequence is just: up, down, up, down, ... (or down, up, down, ...).
// The NEXT step depends only on how the sequence ENDED:
//   - if it ended going DOWN, we may only append a number that goes UP
//   - if it ended going UP,   we may only append a number that goes DOWN
//
// So for every index i we record the two best answers that end AT nums[i]:
//   up[i]   = longest wiggle subsequence ending at i whose LAST step is UP
//             (nums[prev] < nums[i], i.e. a "valley -> peak" move)
//   down[i] = longest wiggle subsequence ending at i whose LAST step is DOWN
//             (nums[prev] > nums[i], i.e. a "peak -> valley" move)
//
// Transition: try every earlier index j as the previous element.
//   nums[i] > nums[j] : this step is an UP step  -> attach it to a DOWN-ending
//                       sequence at j:  up[i] = max(up[i], down[j] + 1)
//   nums[i] < nums[j] : this step is a DOWN step -> attach it to an UP-ending
//                       sequence at j:  down[i] = max(down[i], up[j] + 1)
//   nums[i] == nums[j] : skip - a wiggle needs STRICT differences.
//
// Both arrays start at 1 because any single element is itself a wiggle
// subsequence of length 1 (no step yet - it can grow either way next).
//
// The answer is the max entry of BOTH arrays, since the optimal sequence
// may end with either an up step or a down step.
//
// ----------------------------------------------------------------------------
// DRY RUN: nums = [1, 7, 4, 9, 2, 5]
// ----------------------------------------------------------------------------
//   i=1 (7):  7>1  -> up[1]   = down[0]+1 = 2        (1 < 7)
//   i=2 (4):  4>1  -> up[2]   = 2 ; 4<7 -> down[2] = up[1]+1 = 3 (1<7>4)
//   i=3 (9):  9>4  -> up[3]   = down[2]+1 = 4        (1<7>4<9)
//   i=4 (2):  2<9  -> down[4] = up[3]+1 = 5          (1<7>4<9>2)
//   i=5 (5):  5>2  -> up[5]   = down[4]+1 = 6        (1<7>4<9>2<5)
//   answer = max(up, down) = 6
//
// Complexity:
//   Time  : O(n^2) - two nested loops
//   Space : O(n)   - two arrays of size n
//   (There is an O(n) time / O(1) space greedy version that keeps only two
//    running variables `up`/`down`, but this is the classic DP form.)
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();

        // 0 or 1 elements -> the whole array is already a wiggle of that size.
        if (n <= 1) return n;

        // up[i] / down[i] = best wiggle length ending exactly at index i
        //                   with last step up / down. Start at 1 (just nums[i]).
        vector<int> up(n, 1);
        vector<int> down(n, 1);

        // Build answers for i = 1..n-1 using all previously computed j < i.
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {

                if (nums[i] > nums[j]) {
                    // Step j -> i is UP, so it can only EXTEND a sequence
                    // that was going DOWN at j (down -> up alternation).
                    up[i] = max(up[i], down[j] + 1);
                }
                else if (nums[i] < nums[j]) {
                    // Step j -> i is DOWN, so it can only EXTEND a sequence
                    // that was going UP at j (up -> down alternation).
                    down[i] = max(down[i], up[j] + 1);
                }
                // nums[i] == nums[j]: equal values can never sit next to each
                // other in a wiggle, so do nothing (both values stay as-is).
            }
        }

        // Optimal wiggle may end with an up step OR a down step -> take both maxima.
        return max(*max_element(up.begin(), up.end()),
                   *max_element(down.begin(), down.end()));
    }
};


int main(){
    return 0;
}
