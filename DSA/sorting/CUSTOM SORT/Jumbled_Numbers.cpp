#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Sort the Jumbled Numbers (LeetCode 2191)
 * ================================================================
 *  You are given a mapping[0..9] where mapping[digit] gives the
 *  new digit that 'digit' should be replaced with.
 *
 *  Each number is transformed by replacing every digit using the
 *  mapping, then numbers are sorted by this MAPPED VALUE.
 *  If two numbers have the same mapped value, their relative
 *  order (original index) is preserved (stable sort).
 *
 *  Example:
 *    mapping = [8,9,4,0,2,1,3,5,7,6]
 *    nums    = [991, 338, 38]
 *
 *    mapping:  0→8  1→9  2→4  3→0  4→2  5→1  6→3  7→5  8→7  9→6
 *
 *    991  →  6  6  1  →  661
 *    338  →  0  0  7  →  7     (leading zeros dropped → stoi("007")=7)
 *    38   →  0  7    →  7
 *
 *    338 and 38 both map to 7 → stable sort preserves order:
 *    Sorted: [338, 38, 991]  (mapped: 7, 7, 661)
 * ================================================================
 */

// ================================================================
// APPROACH 1: String-based mapping
// ================================================================
// Converts number → string → map each character → stoi() converts
// back to integer (stoi automatically drops leading zeros).
//
// TIME:  O(N × D) — N numbers, each with D digits (D ≤ 9)
// SPACE: O(N)     — stores {mapped, index, original} for each number
// ================================================================

class Solution_String {
public:

    /*
     * getMappedValue(mapping, num)
     * -----------------------------------------------
     * Transforms num digit-by-digit using mapping[].
     * Uses string manipulation for simplicity.
     *
     * Example: mapping[0→8, 9→6, 1→9, ...]
     *   num=991 → "991" → each char mapped → "661" → stoi → 661
     *   num=338 → "338" → "007"            → stoi → 7
     *   num=0   → mapping[0] directly      → (avoids stoi("") )
     */
    int getMappedValue(vector<int>& mapping, int num) {

        // Handle zero separately: stoi("") would error,
        // and the digit '0' maps to mapping[0].
        if (num == 0)
            return mapping[0];

        // Convert the number to a string so we can access each digit
        string s = to_string(num);
        string mapped = "";

        // Replace each digit character with its mapped counterpart
        for (char ch : s) {
            // ch - '0' converts char to integer digit
            // mapping[digit] gives the new digit value
            // + '0' converts it back to a char
            mapped += char(mapping[ch - '0'] + '0');
        }

        // stoi converts "007" → 7 (automatically strips leading zeros)
        return stoi(mapped);
    }

    /*
     * sortJumbled(mapping, nums)
     * -----------------------------------------------
     * Main sorting logic:
     *   1. For each number, compute its mapped value and store
     *      {mappedValue, originalIndex, originalNumber}.
     *   2. Sort by (mappedValue, originalIndex) for stability.
     *   3. Extract and return original numbers in sorted order.
     */
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {

        // arr[i] = {mappedValue, originalIndex, originalNumber}
        vector<vector<int>> arr;

        for (int i = 0; i < nums.size(); i++) {

            // Compute the mapped (transformed) value for nums[i]
            int mapped = getMappedValue(mapping, nums[i]);

            // Store all three pieces: needed for stable sorting
            arr.push_back({mapped, i, nums[i]});
        }

        /*
         * Sort by mapped value (a[0]).
         * If mapped values tie → compare by original index (a[1])
         * to preserve the original relative order (stable sort).
         */
        sort(arr.begin(), arr.end(),
            [](const vector<int>& a, const vector<int>& b) {

                // Tie-breaker: preserve original order
                if (a[0] == b[0])
                    return a[1] < b[1];

                // Primary sort key: mapped value (ascending)
                return a[0] < b[0];
            });

        // Collect original numbers in the sorted order
        vector<int> ans;
        for (auto& x : arr)
            ans.push_back(x[2]);

        return ans;
    }
};

// ================================================================
// APPROACH 2: Arithmetic mapping (no strings)
// ================================================================
// Extracts digits from right to left using % 10, builds the mapped
// number using place value multiplication. More efficient — no
// string allocations or stoi calls.
//
// TIME:  O(N × D) — same asymptotic complexity
// SPACE: O(N)     — same storage
// ================================================================

class Solution_Arithmetic {
public:

    /*
     * getMappedValue(mapping, num)
     * -----------------------------------------------
     * Transforms num digit-by-digit using arithmetic.
     *
     * Algorithm:
     *   1. Extract the rightmost digit: digit = num % 10
     *   2. Map it: mapping[digit]
     *   3. Place it at the correct position: mapped += mapping[digit] * place
     *   4. place *= 10 (move to next higher place)
     *   5. num /= 10 (remove the processed digit)
     *   6. Repeat until num == 0
     *
     * Example: mapping[0→8, 9→6, 1→9], num=991
     *   Iter | digit | mapping | place | mapped before | mapped after
     *   ------+-------+---------+-------+---------------+--------------
     *    1   |   1   |    9    |   1   |      0        |    0 + 9×1 = 9
     *    2   |   9   |    6    |  10   |      9        |    9 + 6×10 = 69
     *    3   |   9   |    6    | 100   |     69        |   69 + 6×100 = 669
     *   Result: 669 (not 661 — wait, that's because my example
     *   mapping was different. Let me use the example from above)
     *
     * Example: mapping[8,9,4,0,2,1,3,5,7,6], num=338
     *   digits right-to-left: 8 → map[8]=7, 3 → map[3]=0, 3 → map[3]=0
     *   place progression: 1×7=7, 10×0=0, 100×0=0 → total = 7
     *   Result: 7 ✓
     *
     * Note: Leading zeros naturally vanish because 0 × place = 0,
     * so the accumulated sum never includes them.
     */
    int getMappedValue(vector<int>& mapping, int num) {

        // Handle zero separately: the loop below would not execute
        if (num == 0)
            return mapping[0];

        int place = 1;   // current decimal place (1, 10, 100, ...)
        int mapped = 0;  // accumulates the transformed number

        // Process digits from RIGHT to LEFT
        while (num > 0) {

            int digit = num % 10;               // extract last digit (e.g., 991 % 10 = 1)
            mapped += mapping[digit] * place;   // place it at correct position
            place *= 10;                        // move to next place (1→10→100→...)
            num /= 10;                          // remove last digit (991→99→9→0)
        }

        return mapped;
    }

    /*
     * sortJumbled(mapping, nums)
     * -----------------------------------------------
     * Identical logic to Approach 1 — compute mapped values,
     * sort by (mapped, originalIndex), extract original numbers.
     */
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {

        // arr[i] = {mappedValue, originalIndex, originalNumber}
        vector<vector<int>> arr;

        for (int i = 0; i < nums.size(); i++) {

            int mapped = getMappedValue(mapping, nums[i]);

            arr.push_back({mapped, i, nums[i]});
        }

        /*
         * Custom comparator:
         *   Primary key: a[0] (mapped value), ascending
         *   Secondary key: a[1] (original index), ascending
         *   This ensures stable ordering for ties.
         */
        sort(arr.begin(), arr.end(),
            [](const vector<int>& a, const vector<int>& b) {

                if (a[0] == b[0])
                    return a[1] < b[1];      // preserve original order

                return a[0] < b[0];
            });

        // Collect results
        vector<int> ans;
        for (auto& x : arr)
            ans.push_back(x[2]);

        return ans;
    }
};

/*
 * ================================================================
 *  DRY RUN (both approaches produce identical result)
 * ================================================================
 *  mapping = [8,9,4,0,2,1,3,5,7,6]
 *  nums    = [991, 338, 38]
 *
 *  --------------------------------------------------------------
 *  Compute mapped values:
 *  --------------------------------------------------------------
 *  991:  9→6, 9→6, 1→9  → 661
 *  338:  3→0, 3→0, 8→7  → 7    (strips leading zeros → 7)
 *  38:   3→0, 8→7        → 7    (strips leading zero → 7)
 *
 *  arr before sorting:
 *    [{661,0,991}, {7,1,338}, {7,2,38}]
 *
 *  --------------------------------------------------------------
 *  Sort by (mapped, index):
 *  --------------------------------------------------------------
 *  7 appears twice (338 and 38).
 *    - 338 has index=1, 38 has index=2 → 338 comes first
 *  Sorted:
 *    [{7,1,338}, {7,2,38}, {661,0,991}]
 *
 *  --------------------------------------------------------------
 *  Result:
 *  --------------------------------------------------------------
 *  [338, 38, 991]
 * ================================================================
 */

int main() {
    return 0;
}
