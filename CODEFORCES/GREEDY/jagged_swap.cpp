/*
 * =============================================================
 *  PROBLEM: Jagged Swaps (Codeforces Round 1896A)
 * =============================================================
 *
 *  QUESTION:
 *  ---------
 *  You are given a permutation of numbers from 1 to n.
 *  You can perform the following operation any number of times:
 *      Choose an index i (1 <= i < n). If a[i] < a[i+1], swap them.
 *  Determine whether you can sort the array in ascending (non-decreasing) order.
 *
 *  INTUITION:
 *  ----------
 *  Key insight → The operation swaps a[i] and a[i+1] ONLY when a[i] < a[i+1].
 *
 *  What does this mean for element movement?
 *    - If a[i] < a[i+1], swapping puts the LARGER value at position i (left)
 *      and the SMALLER value at position i+1 (right).
 *    - So LARGER numbers can ONLY move LEFT.
 *    - SMALLER numbers can ONLY move RIGHT.
 *
 *  Now consider element '1' — the smallest number in the permutation.
 *    - Since 1 is the absolute minimum, it is smaller than every other element.
 *    - Therefore, 1 can NEVER trigger a swap from a position i to i-1
 *      (because that would require a[i-1] < a[i], i.e., the element BEFORE
 *      1 would need to be smaller than 1 — impossible).
 *    - In other words, 1 can ONLY move RIGHTWARD, never leftward.
 *
 *  If 1 is already at position 0 (a[0] == 1):
 *    - It's already at the leftmost spot where it belongs in a sorted array.
 *    - For the remaining elements (2, 3, ..., n), we can always sort them:
 *      since larger values can bubble left and smaller values can bubble right,
 *      effectively we can rearrange any suffix into sorted order.
 *    - → Answer = YES
 *
 *  If 1 is NOT at position 0 (a[0] != 1):
 *    - Since 1 can never move left, it can NEVER reach position 0.
 *    - But in a sorted permutation, the smallest element MUST be at index 0.
 *    - Therefore, sorting is impossible.
 *    - → Answer = NO
 *
 *  That's it. The entire problem reduces to: "Is a[0] == 1?"
 *
 *  ALGORITHM:
 *  ----------
 *  1. Read number of test cases t.
 *  2. For each test case:
 *       a. Read n and the array a[0..n-1].
 *       b. If a[0] == 1 → print "YES", else print "NO".
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(n) per test case (just reading input + one comparison)
 *  Space → O(n) for storing the array (though we only really need a[0])
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;            // number of test cases
    cin >> t;         // read test cases
    while (t--)       // iterate over each test case
    {
        long long n;  // size of the permutation
        cin >> n;     // read size
        long long a[n]; // array to store the permutation

        // read the permutation elements
        for (int i = 0; i < n; i++)
            cin >> a[i];

        /*
         * Core check: is the first element the minimum element '1'?
         *   YES → the array can be sorted
         *   NO  → sorting is impossible
         */
        if (a[0] == 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
