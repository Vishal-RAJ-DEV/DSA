#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 1524. Number of Sub-arrays With Odd Sum

    Given an array of integers arr, return the number of subarrays that have
    an odd sum. Since the answer can be very large, return it modulo 10^9 + 7.

    Example:
        Input: arr = [1,3,5]
        Output: 4
        Explanation: All subarrays are [1], [1,3], [1,3,5], [3], [3,5], [5].
                     Their sums are 1, 4, 9, 3, 8, 5.
                     Odd sums: 1, 9, 3, 5 -> 4 subarrays.

        Input: arr = [2,4,6]
        Output: 0
        Explanation: All subarray sums are even.

        Input: arr = [1,2,3,4,5,6,7]
        Output: 16

    KEY INSIGHT (Prefix Sum Parity):
        - The sum of subarray (l..r) = prefix[r] - prefix[l-1].
        - Sum is ODD iff prefix[r] and prefix[l-1] have OPPOSITE parity
          (one odd, one even).
        - Let prefix[-1] = 0 (even). We need to count pairs of prefix sums
          with opposite parity, where the earlier prefix serves as l-1.
        - If there are 'odd' odd prefix sums and 'even' even prefix sums
          (including the initial 0), then:
            Number of odd-sum subarrays = odd * even
*/


// =========================================================
// APPROACH 1: Mathematical Formula — O(n)
// =========================================================
/*
    LOGIC:
        1. Compute all prefix sums while counting how many are odd.
           (prefix variable tracks the running sum.)
        2. Let oddcnt = number of prefix sums (indices 0 to n-1) that are odd.
           Let n = arr.size().
        3. Number of even prefix sums among indices 0 to n-1 = n - oddcnt.
        4. Total even prefixes including the initial 0 = (n - oddcnt) + 1.
        5. Total odd-sum subarrays = oddcnt * ((n - oddcnt) + 1).
           Which simplifies to: oddcnt + (n - oddcnt) * oddcnt.

        Why this works:
        - Each subarray sum corresponds to a pair (i, j) with i < j,
          where prefix[i] and prefix[j] have opposite parity.
        - If we fix the "ending" prefix as odd, it can pair with any even
          prefix that comes before it (including the initial 0).
        - If we fix the "ending" prefix as even, it can pair with any odd
          prefix that comes before it.
        - Overall, this counts to oddPrefixes * evenPrefixes including
          the initial 0, i.e., oddcnt * (n - oddcnt + 1).

    TIME COMPLEXITY:
        - One pass through the array: O(n).
        - Constant time formula computation: O(1).
        - Overall: O(n).

    SPACE COMPLEXITY:
        - Only a few integer variables: O(1).
*/


class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int prefix = 0;
        long long oddcnt = 0;      // count of odd prefix sums

        // Count odd prefix sums among indices 0 to n-1
        for (int i : arr) {
            prefix += i;
            if (prefix % 2 != 0)
                oddcnt++;
        }

        int n = arr.size();
        // evenPrefixes (including initial 0) = n - oddcnt + 1
        // odd-sum subarrays = oddcnt * (n - oddcnt + 1)
        // Simplified: oddcnt + (n - oddcnt) * oddcnt
        oddcnt += (n - oddcnt) * oddcnt;

        return oddcnt % 1'000'000'007;
    }
};


/*
    NOTE: The above formula correctly handles negative numbers because
    in C++, -1 % 2 = -1 (not 1), but -1 != 0 is true, so negative odd
    prefix sums are correctly identified by `prefix % 2 != 0`.
    The parity addition rules (even+even=even, even+odd=odd, odd+odd=even)
    hold regardless of sign.
*/


// =========================================================
// APPROACH 2: Dynamic Counting (Standard DP) — O(n)
// =========================================================
/*
    LOGIC:
        1. Maintain count[0] = number of even prefix sums seen so far
           (starting with count[0] = 1 for the initial prefix sum 0).
           count[1] = number of odd prefix sums seen so far.
        2. Also maintain the current prefix sum parity.
        3. Iterate through arr:
            a. Add current element to prefix sum.
            b. Update current parity (prefix % 2).
            c. If current prefix is ODD, it pairs with all previous EVEN
               prefixes to create an odd-sum subarray.
               So add count[0] to the answer.
               Then increment count[1].
            d. If current prefix is EVEN, it pairs with all previous ODD
               prefixes. So add count[1] to the answer.
               Then increment count[0].
        4. Return answer % MOD.

        This is the most intuitive DP-like approach: at each step, we
        count how many new odd-sum subarrays end at the current index.

    TIME COMPLEXITY:
        - One pass through the array: O(n).
        - Constant work per element: O(1).
        - Overall: O(n).

    SPACE COMPLEXITY:
        - Only a few integer variables: O(1).
*/


class Solution2 {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1'000'000'007;
        int count[2] = {1, 0};  // count[0] = even prefixes (initially 0)
                                // count[1] = odd prefixes
        int prefix = 0;
        long long result = 0;

        for (int num : arr) {
            prefix += num;
            int parity = (prefix % 2 + 2) % 2;  // normalize to 0 or 1

            // Current prefix pairs with all prefixes of opposite parity
            result = (result + count[1 - parity]) % MOD;

            // Update count for this parity
            count[parity]++;
        }

        return (int)result;
    }
};


/*  COMPARISON OF APPROACHES:

    | Aspect              | Approach 1 (Formula) | Approach 2 (DP) |
    |---------------------|----------------------|-----------------|
    | Time Complexity     | O(n)                 | O(n)            |
    | Space Complexity    | O(1)                 | O(1)            |
    | Passes              | 1 pass + formula     | 1 pass          |
    | Readability         | Math-heavy           | Intuitive       |
    | Handles negatives   | Yes (via % 2 != 0)   | Yes (normalized)|

    Both are optimal O(n) time and O(1) space. Approach 2 is easier to
    understand and extend, while Approach 1 is more mathematically concise.
*/


int main(){
    return 0;
}

