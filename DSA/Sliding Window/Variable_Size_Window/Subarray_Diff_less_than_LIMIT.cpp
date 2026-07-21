#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Longest Continuous Subarray With Absolute Diff
 *           ≤ Limit  (LeetCode 1438)
 * ================================================================
 *  Given an array nums and a limit, find the length of the LONGEST
 *  contiguous subarray such that for every element in it:
 *    |max - min| ≤ limit
 *
 *  i.e., the absolute difference between ANY two elements in the
 *  subarray is ≤ limit.
 *
 *  Note: Since |max - min| ≤ limit captures the worst case (the
 *  farthest-apart pair), checking only max and min is sufficient.
 *
 *  Example:
 *    nums = [8, 2, 4, 7],  limit = 4
 *    Subarrays with |max-min|≤4:
 *      [8] → |8-8|=0 ✓
 *      [2] → 0 ✓
 *      [2,4] → |4-2|=2 ✓
 *      [2,4,7] → |7-2|=5 ✗
 *      [4,7] → |7-4|=3 ✓
 *    Longest = 2  ([2,4] or [4,7])
 *
 * ================================================================
 *  GENERAL STRATEGY: Variable-Size Sliding Window
 * ================================================================
 *  We maintain a window [left, right] that is always VALID
 *  (|max-min| ≤ limit). As we expand right, if the window becomes
 *  INVALID, we shrink left until it becomes valid again.
 *
 *  The key challenge is TRACKING the max and min of the current
 *  window efficiently as elements enter and leave.
 *
 *  Two solutions:
 *    1. Multiset (O(n log n)) — balanced BST gives O(log n) insert/erase
 *    2. Two Deques (O(n))     — monotonic deques give O(1) amortized
 * ================================================================
 */

// ================================================================
// APPROACH 1: Multiset (O(n log n))
// ================================================================
// INTUITION:
//   A multiset keeps elements in SORTED order.
//   - *window.rbegin() → maximum element  (largest)
//   - *window.begin()  → minimum element  (smallest)
//
//   When we add nums[right], we insert into the multiset.
//   If |max - min| > limit, we remove nums[left] and advance left.
//   We remove only ONE occurrence (multiset may have duplicates).
//
// HOW multiset WORKS HERE:
//   - window.insert(x)    → O(log n) — inserts x into sorted position
//   - window.find(x)      → O(log n) — returns iterator to first x
//   - window.erase(it)    → O(log n) — erases at iterator (only ONE x)
//   - window.rbegin()     → O(1)     — largest element
//   - window.begin()      → O(1)     — smallest element
//
// WHY multiset::find then erase instead of erase(x)?
//   window.erase(x) erases ALL occurrences of x. We only want to
//   erase one occurrence (the one leaving the window).
//   So we do: window.erase(window.find(x)) to remove just one.
//
// TIME:  O(n log n) — each element inserted and removed once
// SPACE: O(n)       — multiset holds at most n elements
// ================================================================

class Solution_Multiset {
public:
    int longestSubarray(vector<int>& nums, int limit) {

        // multiset stores all elements in the current window in
        // sorted order. Allows duplicates.
        multiset<int> window;

        int left = 0;          // left boundary of sliding window
        int ans = 0;           // longest valid window length found

        for (int right = 0; right < nums.size(); right++) {

            // --- EXPAND: Add nums[right] to the window ---
            // insert() places it in sorted position automatically.
            // After this, *window.rbegin() is max, *window.begin() is min.
            window.insert(nums[right]);

            // --- SHRINK: While window is INVALID ---
            // Condition: |max - min| > limit
            // Since window.rbegin() = max, window.begin() = min,
            // the diff is *window.rbegin() - *window.begin().
            //
            // We keep shrinking from the left until the condition
            // becomes false (|max-min| ≤ limit).
            while (*window.rbegin() - *window.begin() > limit) {

                // Remove nums[left] from the multiset.
                // window.find(nums[left]) gives an iterator to the
                // first occurrence of nums[left]. erase(it) removes
                // only that one occurrence.
                window.erase(window.find(nums[left]));

                left++;  // shrink window from left
            }

            // --- Window [left, right] is now VALID ---
            // Update answer with current window length.
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

// ================================================================
// APPROACH 2: Two Deques  (O(n))
// ================================================================
// INTUITION:
//   We avoid the O(log n) overhead of multiset by using TWO
//   monotonic deques to track max and min in O(1) amortized:
//
//     maxDeque  — stores elements in DECREASING order
//                 front → largest element in window
//     minDeque  — stores elements in INCREASING order
//                 front → smallest element in window
//
//   Both deques store the actual VALUES (not indices), but they
//   maintain monotonic properties by popping from the BACK when
//   a new element disrupts the order.
//
// HOW THE DEQUES WORK (detailed):
// ----------------------------------------------------------------
//  maxDeque (decreasing order: front = max):
//    When we add nums[right]:
//      - Pop from BACK while back < nums[right]
//        (smaller elements will never be max again since this
//         new larger element outlives them and is larger)
//      - Push nums[right] to back
//
//    When we remove nums[left] (shrink):
//      - If nums[left] == maxDeque.front(), pop_front()
//        (the max is leaving the window)
//
//    → After these operations, maxDeque.front() = current max
//
//  minDeque (increasing order: front = min):
//    When we add nums[right]:
//      - Pop from BACK while back > nums[right]
//        (larger elements will never be min again)
//      - Push nums[right] to back
//
//    When we remove nums[left] (shrink):
//      - If nums[left] == minDeque.front(), pop_front()
//        (the min is leaving the window)
//
//    → After these operations, minDeque.front() = current min
//
// WHY THIS IS O(n):
//   Each element is pushed to each deque at most once and popped
//   at most once. Total operations = O(n). This is the classic
//   "monotonic queue" / "sliding window maximum" pattern extended
//   to also track the minimum.
//
// TIME:  O(n) — each element enters/leaves each deque at most once
// SPACE: O(n) — deques hold at most n elements combined
// ================================================================

class Solution_Deque {
public:
    int longestSubarray(vector<int>& nums, int limit) {

        // maxDeque: front = MAX of current window (decreasing order)
        // minDeque: front = MIN of current window (increasing order)
        deque<int> maxDeque;
        deque<int> minDeque;

        int left = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); right++) {

            // ======================================================
            // EXPAND: Insert nums[right] into both deques
            // ======================================================

            // ---- Maintain maxDeque (decreasing order) ----
            // Remove smaller elements from the BACK because they
            // can NEVER become the maximum in this window
            // (nums[right] is larger and will outlast them).
            while (!maxDeque.empty() && maxDeque.back() < nums[right]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(nums[right]);

            // ---- Maintain minDeque (increasing order) ----
            // Remove larger elements from the BACK because they
            // can NEVER become the minimum in this window
            // (nums[right] is smaller and will outlast them).
            while (!minDeque.empty() && minDeque.back() > nums[right]) {
                minDeque.pop_back();
            }
            minDeque.push_back(nums[right]);

            // ======================================================
            // SHRINK: While |max - min| > limit
            // ======================================================
            // maxDeque.front() = current window maximum
            // minDeque.front() = current window minimum
            while (maxDeque.front() - minDeque.front() > limit) {

                // If the element LEAVING the window (nums[left])
                // happens to be the current max → pop it from maxDeque
                if (nums[left] == maxDeque.front())
                    maxDeque.pop_front();

                // If it's the current min → pop it from minDeque
                if (nums[left] == minDeque.front())
                    minDeque.pop_front();

                left++;  // shrink window from left
            }

            // --- Window [left, right] is now VALID ---
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

/*
 * ================================================================
 *  DRY RUN (both approaches give same result)
 * ================================================================
 *  nums = [8, 2, 4, 7],  limit = 4
 *
 *  --------------------------------------------------------------
 *  MULTISET APPROACH DRY RUN
 *  --------------------------------------------------------------
 *  right=0, x=8:
 *    window = {8}, max-min = 0 ≤ 4 ✓
 *    ans = max(0, 0-0+1) = 1
 *
 *  right=1, x=2:
 *    window = {2, 8}, max-min = 8-2 = 6 > 4
 *    → shrink: erase(find(8)), left=1, window = {2}, max-min = 0 ✓
 *    ans = max(1, 1-1+1) = 1
 *
 *  right=2, x=4:
 *    window = {2, 4}, max-min = 4-2 = 2 ≤ 4 ✓
 *    ans = max(1, 2-1+1) = 2
 *
 *  right=3, x=7:
 *    window = {2, 4, 7}, max-min = 7-2 = 5 > 4
 *    → shrink: erase(find(2)), left=2, window = {4, 7}, max-min = 3 ✓
 *    ans = max(2, 3-2+1) = 2
 *
 *  Result: 2
 *
 *  --------------------------------------------------------------
 *  DEQUE APPROACH DRY RUN
 *  --------------------------------------------------------------
 *  right=0, x=8:
 *    maxDeque: [8]     (back: none < 8 → push)
 *    minDeque: [8]     (back: none > 8 → push)
 *    diff = 8-8 = 0 ≤ 4 ✓
 *    ans = 1
 *
 *  right=1, x=2:
 *    maxDeque: [8]     back=8, 8<2? no → push → [8, 2]
 *    minDeque: [8]     back=8, 8>2? yes → pop → [] → push → [2]
 *    diff = 8-2 = 6 > 4
 *    → shrink left=0: nums[0]=8 == maxDeque.front → pop_front → [2]
 *                     nums[0]=8 == minDeque.front? (2) no
 *    left=1
 *    diff = 2-2 = 0 ≤ 4 ✓
 *    ans = 1
 *
 *  right=2, x=4:
 *    maxDeque: [2]     back=2, 2<4? yes → pop → [] → push → [4]
 *    minDeque: [2]     back=2, 2>4? no → push → [2, 4]
 *    diff = 4-2 = 2 ≤ 4 ✓
 *    ans = max(1, 2-1+1) = 2
 *
 *  right=3, x=7:
 *    maxDeque: [4]     back=4, 4<7? yes → pop → [] → push → [7]
 *    minDeque: [2,4]   back=4, 4>7? no → push → [2,4,7]
 *    diff = 7-2 = 5 > 4
 *    → shrink left=1: nums[1]=2 == maxDeque.front(7)? no
 *                     nums[1]=2 == minDeque.front(2)? yes → pop_front → [4,7]
 *    left=2
 *    diff = 7-4 = 3 ≤ 4 ✓
 *    ans = max(2, 3-2+1) = 2
 *
 *  --------------------------------------------------------------
 *  KEY VISUALIZATION OF MONOTONIC DEQUES
 *  --------------------------------------------------------------
 *  At right=3 (before shrinking):
 *    Window = [2, 4, 7] (indices 1,2,3)
 *
 *    maxDeque = [7]     ← front
 *      Why?  8 was too far left (out of window).
 *            When 7 came, 4 was popped from back (4<7).
 *            So only 7 remains.
 *
 *    minDeque = [2,4,7] ← front
 *      Why? 2 is min. 4 > 2 so stays (might be min if 2 leaves).
 *            7 > 4 so stays (might be min if 2 and 4 leave).
 *
 *    max-front - min-front = 7 - 2 = 5 > 4 → shrink needed.
 *    left=1 → nums[1]=2 leaves → 2 is minDeque.front → pop it.
 *    Now minDeque = [4,7], min=4, max-front=7, diff=3 ≤ 4 ✓
 *
 *  MENTAL MODEL:
 *    maxDeque stores "future maximum candidates" — it's always
 *    decreasing because a larger element at the RIGHT makes all
 *    smaller elements to its left irrelevant for max.
 *
 *    minDeque stores "future minimum candidates" — it's always
 *    increasing because a smaller element at the RIGHT makes all
 *    larger elements to its left irrelevant for min.
 * ================================================================
 */

int main() {
    return 0;
}
