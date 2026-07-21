#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// LeetCode 220: Contains Duplicate III
// ============================================================
//
// Problem:
//   Given nums[], return true if there exist two distinct indices
//   i and j such that:
//     1) |i - j| <= indexDiff    (indices are close enough)
//     2) |nums[i] - nums[j]| <= valueDiff   (values are close enough)
//
// ============================================================
// Intuition
// ============================================================
//
// A brute force would check all pairs (i,j) with |i-j| <= indexDiff:
// O(n * indexDiff) — too slow when indexDiff is large.
//
// We can do better with a sliding window of size indexDiff plus
// a data structure that can quickly tell us if a value close to
// nums[right] exists in the window.
//
// Core trick:
//   |nums[right] - x| <= valueDiff
//   →  nums[right] - valueDiff <= x <= nums[right] + valueDiff
//
// So from the window, we just need to know if ANY value falls
// inside this interval [L, R]. If we keep the window sorted,
// we can binary search for L and check if that element ≤ R.
//
// ============================================================
// Approach 1 — Sliding Window + Ordered Set (BST)  [used here]
// ============================================================
//
// Data structure:
//   std::set<ll> — a balanced BST that keeps elements sorted.
//   It stores the last 'indexDiff' elements (sliding window).
//
// Algorithm:
//   1. For each element nums[right]:
//      a) Compute L = nums[right] - valueDiff
//      b) Use lower_bound(L) to find the smallest x >= L in window.
//      c) If x exists AND x <= nums[right] + valueDiff → return true.
//      d) Insert nums[right] into window.
//      e) If window.size() > indexDiff, erase nums[left] and left++.
//   2. Return false if no pair found.
//
// How the range check works:
//   lower_bound(L) returns the FIRST element >= L.
//   Since the set is sorted, if that element is > R, then ALL
//   elements in the set are > R — no candidate exists.
//   If that element is ≤ R then it's inside [L, R] → valid pair.
//
// Example:
//   nums = [1,5,9,13], indexDiff=2, valueDiff=3
//   Window = {1,5}  (indices 0,1)
//   right=2, nums[2]=9, L=6, R=12
//   lower_bound(6) → points to 5? No, 5 < 6, so first >= 6 is... wait
//   Actually the window is {1,5}. lower_bound(6) returns end()
//   because 6 > 5. So no candidate → insert 9.
//
// Time: O(n log k)   — n = |nums|, k = indexDiff
//   Each right: lower_bound + insert + (occasional erase) = O(log k)
// Space: O(k) for the set
//
// Constraint note:
//   Using long long because nums[i] +/- valueDiff can overflow int.

class Solution {
public:
    typedef long long ll;

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        set<ll> window;
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {
            // Search for any x in window such that:
            //   nums[right] - valueDiff <= x <= nums[right] + valueDiff
            //
            // lower_bound(L) gives the smallest element >= L.
            auto it = window.lower_bound((ll)nums[right] - valueDiff);

            // If that element also satisfies the upper bound → found
            if (it != window.end() && *it <= (ll)nums[right] + valueDiff) {
                return true;
            }

            window.insert(nums[right]);

            // Keep window size ≤ indexDiff
            if (window.size() > indexDiff) {
                window.erase(nums[left]);
                left++;
            }
        }

        return false;
    }
};

// ============================================================
// Approach 2 — Sliding Window + Bucketing (O(n))
// ============================================================
//
// Intuition:
//   If we divide numbers into buckets of size (valueDiff + 1),
//   then any two numbers in the SAME bucket automatically have
//   difference ≤ valueDiff. Two numbers in ADJACENT buckets
//   might also be within valueDiff and need a direct check.
//
// Bucket id = nums[i] / (valueDiff + 1)
//   (adjusted for negatives: shift to floor division)
//
// Algorithm:
//   1. For each nums[right], compute its bucket id.
//   2. If the bucket already has an element → duplicate within
//      valueDiff (same bucket) → return true.
//   3. Check adjacent buckets (id-1, id+1) — if any element
//      in those has |value diff| ≤ valueDiff → return true.
//   4. Insert nums[right] into its bucket.
//   5. If window size > indexDiff, erase the leftmost element's
//      bucket.
//
// Time: O(n) — each operation is O(1) on average (unordered_map).
// Space: O(k) for the map.
//
// This is faster than the BST approach but requires careful
// handling of negative numbers.

class Solution2 {
public:
    typedef long long ll;

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (valueDiff < 0) return false;

        unordered_map<ll, ll> bucket;  // bucket_id → value stored
        int left = 0;

        auto getBucketId = [&](ll num) -> ll {
            // Floor division for negatives:
            // In C++, -3 / 5 = 0 (truncates toward zero), but we
            // need -3/5 = -1 for bucketing to work correctly.
            // Adding valueDiff shifts negatives properly.
            return (num + (ll)valueDiff + 1) / ((ll)valueDiff + 1) - 1;
            // Simpler alternative:
            // return num < 0 ? (num + 1) / ((ll)valueDiff + 1) - 1
            //                : num / ((ll)valueDiff + 1);
        };

        for (int right = 0; right < nums.size(); right++) {
            ll id = getBucketId(nums[right]);

            // Same bucket → diff guaranteed ≤ valueDiff
            if (bucket.count(id)) return true;

            // Adjacent bucket — check explicitly
            if (bucket.count(id - 1) &&
                abs(nums[right] - bucket[id - 1]) <= valueDiff)
                return true;
            if (bucket.count(id + 1) &&
                abs(nums[right] - bucket[id + 1]) <= valueDiff)
                return true;

            bucket[id] = nums[right];

            if (right - left >= indexDiff) {
                ll leftId = getBucketId(nums[left]);
                bucket.erase(leftId);
                left++;
            }
        }

        return false;
    }
};

// ============================================================
// Approach 3 — Brute Force (for comparison)
// ============================================================
//
// Check all pairs (i, j) with |i - j| <= indexDiff.
// Time: O(n * indexDiff) — often O(n²) in worst case.

class Solution3 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size() && j - i <= indexDiff; j++) {
                if (abs((long long)nums[i] - nums[j]) <= valueDiff)
                    return true;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}
