/******************************************************************************
 * FILE    : kthPositve_misssing_no.cpp
 * PROBLEM : LeetCode 1539 — Kth Missing Positive Number  (Easy)
 * TECHNIQUE : BINARY SEARCH ON ANSWER-SPACE (search on index, not on value)
 *
 * ============================ PROBLEM STATEMENT ============================
 * arr is a SORTED array of DISTINCT positive integers (strictly increasing).
 * Return the k-th missing positive integer that is NOT present in arr.
 *
 * Example : arr = [2, 3, 4, 7, 11],  k = 5
 *   Present     : 2, 3, 4, 7, 11, ...
 *   Missing     : 1, 5, 6, 8, 9, 10, 12, ...
 *   1st missing = 1
 *   2nd missing = 5
 *   3rd missing = 6
 *   4th missing = 8
 *   5th missing = 9   <-- answer
 *
 * ===================== APPROACH 1 : BRUTE FORCE (O(answer)) ================
 * Start from x = 1 and keep checking "is x present in arr?".
 * Count how many numbers are missing; when the count reaches k, x is the
 * answer.  Works but can be very slow when the answer is huge (e.g. 10^6).
 *
 * ===================== APPROACH 2 : PREFIX-COUNT + BINARY SEARCH (O(log n))
 *
 * THE KEY INSIGHT
 * ---------------
 * In a PERFECT sequence with NO missing numbers, at 0-based index i the
 * value would be exactly (i + 1):
 *        index :  0  1  2  3  4  5 ...
 *        value :  1  2  3  4  5  6 ...
 *
 * But in OUR array at index `mid` the actual value is arr[mid].
 * So the number of positive integers that actually EXIST up to the value
 * arr[mid] is exactly (mid + 1)   →   those are arr[0..mid] themselves.
 *
 * Therefore:
 *        MISSING COUNT up to value arr[mid]
 *          = (how many positives SHOULD exist up to arr[mid]) - (how many DO)
 *          = arr[mid] - (mid + 1)
 *
 *   missing = arr[mid] - (mid + 1)
 *
 * HOW THE DECISION IS MADE
 * ------------------------
 * We want the k-th missing number, call it `x`.
 * Let missing(v) = number of missing positives that are <= v.
 *
 *   • if missing(arr[mid]) <  k   →  even at arr[mid] we haven't seen k
 *                                    missing numbers, so the answer lies
 *                                    somewhere ABOVE arr[mid]  → go RIGHT
 *                                    (low = mid + 1)
 *
 *   • if missing(arr[mid]) >= k   →  the k-th missing number is at or below
 *                                    arr[mid], answer lies in LEFT half
 *                                    (high = mid - 1)
 *
 *   This monotonic property ("missing(v)" only grows as v grows) is exactly
 *   what makes binary search valid.
 *
 * WHY THE FINAL FORMULA `high + 1 + k` ( == `low + k`) IS CORRECT
 * ---------------------------------------------------------------
 * Let `x` be the answer (the k-th missing positive).
 *   • Every array element STRICTLY SMALLER than x is "occupying" one of the
 *     positive-integer slots before x.
 *   • Let p = number of array elements < x.
 *   • Positives before x          = x - 1        (i.e. 1, 2, ... , x-1)
 *   • Of those, the present ones  = p            (the array elements < x)
 *   • Of those, the missing ones  = (x - 1) - p
 *   • By definition this must equal (k - 1)      (x is the k-th missing,
 *     so there are k-1 missing numbers strictly before x)
 *         => (x - 1) - p = k - 1   =>   x = p + k
 *
 * After the binary search loop ends:
 *   • low  = first index where missing >= k
 *   • high = low - 1  (last index where missing <  k)
 *   • All elements arr[0..high] are < x, and arr[low] >= x
 *     => p (count of elements < x) = high + 1 = low
 *   =>  x = p + k = (high + 1) + k = low + k      <-- both forms are equal!
 *
 * ========================= DRY RUN (arr = {2,3,4,7,11}, k = 5) =============
 *  n = 5,  low = 0,  high = 4
 *
 *  Iteration 1:
 *      mid = (0 + 4) / 2 = 2
 *      arr[mid] = arr[2] = 4
 *      missing = arr[mid] - (mid + 1) = 4 - 3 = 1        (only `1` is missing)
 *      missing(1) < k(5)  →  answer is above 4  →  low = mid + 1 = 3
 *      state: low = 3, high = 4
 *
 *  Iteration 2:
 *      mid = (3 + 4) / 2 = 3
 *      arr[mid] = arr[3] = 7
 *      missing = 7 - (3 + 1) = 7 - 4 = 3      (missing 1, 5, 6 up to 7)
 *      missing(3) < k(5)  →  answer is above 7  →  low = mid + 1 = 4
 *      state: low = 4, high = 4
 *
 *  Iteration 3:
 *      mid = (4 + 4) / 2 = 4
 *      arr[mid] = arr[4] = 11
 *      missing = 11 - (4 + 1) = 11 - 5 = 6    (missing 1,5,6,8,9,10 up to 11)
 *      missing(6) >= k(5)  →  answer is <= 11  →  high = mid - 1 = 3
 *      state: low = 4, high = 3
 *
 *  Loop ends because low(4) > high(3).
 *
 *  Answer = high + 1 + k = 3 + 1 + 5 = 9
 *        (equivalently low + k = 4 + 5 = 9)
 *
 *  Verify: missing positives = 1, 5, 6, 8, 9, ...  →  5th is 9.  ✔
 *
 * ========================= COMPLEXITY ======================================
 *   Time  : O(log n)  — binary search halves the range every step.
 *   Space : O(1)      — only a few integer variables.
 *****************************************************************************/

#include <iostream>       // for cout / endl
#include <bits/stdc++.h>  // grabs the whole C++ standard library at once
using namespace std;

// ---------------------------------------------------------------------------
// findKthPositive(arr, k)
//   arr : strictly increasing sorted vector of distinct positive integers
//   k   : we want the k-th positive integer that is MISSING from arr
//   returns the k-th missing positive number
// ---------------------------------------------------------------------------
int findKthPositive(vector<int> &arr, int k)
{
    int n = arr.size();              // total number of elements in arr.
                                     // Used to set the initial search range.

    int low = 0;                     // LEFT boundary of the search window.
                                     // = first index that is still a candidate
                                     // for "first index with missing >= k".

    int high = n - 1;                // RIGHT boundary of the search window.
                                     // = last index that still has
                                     //   missing < k (answer is beyond it).

    // Standard binary search loop. It keeps shrinking [low, high] until the
    // pointers cross (low > high), which pins down the exact boundary index.
    while (low <= high)              // Run while the window is non-empty.
    {
        int mid = (low + high) / 2;  // Middle index of the current window.
                                     // (= safe here since indices are small;
                                     //  (low + (high - low) / 2) also works)

        // KEY FORMULA: how many positive numbers are missing BEFORE/at arr[mid]?
        //   • In a complete sequence, index i would hold value (i + 1).
        //   • So (mid + 1) elements SHOULD exist up to arr[mid].
        //   • But only (mid + 1) elements really DO exist there (arr[0..mid]).
        //   • Difference = numbers that were skipped = missing count.
        int missing = arr[mid] - (mid + 1);

        if (missing < k)             // Not enough missing numbers yet at
                                     // arr[mid] → the k-th missing must be a
                                     // LARGER value, so discard left half
                                     // (including mid).
            low = mid + 1;           // Move the left pointer past mid.

        else                         // missing >= k → the k-th missing number
                                     // is at or before arr[mid] → discard
                                     // right half (including mid).
            high = mid - 1;          // Move the right pointer before mid.
    }

    // Loop finished ⇒ low = high + 1 = first index whose missing count >= k.
    //   p = count of array elements that are < answer = high + 1
    //   answer = p + k
    return high + 1 + k;             // Formula derived in the header block.
    //or we can write here, low + k, because after the loop, low = high + 1
    //  Both give the SAME result: (high + 1) + k  ==  low + k.
}

int main()
{
    vector<int> arr = {2, 3, 4, 7, 11};  // sorted array with gaps (1,5,6,8,9,10 missing)
    int k = 5;                           // we want the 5th missing positive
    cout << findKthPositive(arr, k) << endl;   // prints 9  (1,5,6,8,9 → 5th = 9)
    return 0;                            // normal program exit
}
