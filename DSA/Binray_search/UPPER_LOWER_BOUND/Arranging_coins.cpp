/*
QUESTION (LeetCode 441 — Arranging Coins):
You have n coins, and you want to build a staircase where row k has
exactly k coins. Find the maximum number of COMPLETE rows you can form.

Example:
  n = 5
  row 1: ●          1 coin  (total = 1)
  row 2: ● ●        2 coins (total = 3)
  row 3: ● ● ●      3 coins (total = 6) → need 3 more, only 2 left
  Output: 2

  n = 8
  Output: 3  (rows 1+2+3 = 6 ≤ 8, row 4 needs 4 more > 2 remaining)

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // ────────────────────────────────────────────────────────────
    // INTUITION:
    //   The total coins needed for k complete rows is the sum
    //   of the first k natural numbers:
    //
    //              total(k) = k * (k + 1) / 2
    //
    //   We need the LARGEST k such that total(k) ≤ n.
    //
    //   This is monotonic:
    //     k1 < k2  ⇒  total(k1) < total(k2)
    //
    //   So we can binary search for k ∈ [1, n].
    //
    // WHY BINARY SEARCH?
    //   n can be up to 2³¹−1. Linear search (building row by row)
    //   is O(√n) which is ~46340 iterations — acceptable but not
    //   optimal. Binary search O(log n) ≈ 31 iterations is better.
    //
    // WHERE WE SEARCH:
    //   Search space = [1, n] — the possible number of complete rows.
    //   For each candidate mid:
    //     - total(mid) ≤ n  → feasible, try more rows (left = mid + 1)
    //     - total(mid) > n  → too many coins, try fewer rows (right = mid - 1)
    //
    // WHY answer is at right (not left):
    //   The binary search finds the boundary:
    //     T T T ... T F F F ... F
    //                ↑
    //              answer (last T)
    //
    //   - left moves past feasible ks   (left = mid + 1 when feasible)
    //   - right moves below infeasible  (right = mid - 1 when infeasible)
    //
    //   When loop exits (left > right):
    //     right = last k where total(k) ≤ n  ← the answer
    //     left  = first k where total(k) > n
    //
    //   So right is the largest complete row count.
    //
    // ALGORITHM:
    //   1. left = 1, right = n
    //   2. while left ≤ right:
    //        mid = left + (right - left) / 2
    //        coins = mid * (mid + 1) / 2
    //        if coins ≤ n  → left = mid + 1
    //        else          → right = mid - 1
    //   3. Return right
    //
    // TIME  : O(log n)
    // SPACE : O(1)
    // ────────────────────────────────────────────────────────────

    int arrangeCoins(int n) {

        long long left  = 1;    // search range: [1, n]
        long long right = n;    // use long long to avoid overflow in mid

        while (left <= right) {

            long long mid = left + (right - left) / 2;

            // Total coins needed for 'mid' complete rows
            long long totalCoins = mid * (mid + 1) / 2;

            if (totalCoins <= n) {
                left = mid + 1;      // feasible → try a larger k
            } else {
                right = mid - 1;     // too many coins → try smaller k
            }
        }

        // right = last k that satisfied total(k) ≤ n
        return right;
    }
};

/*
DRY RUN:

  n = 5
  left=1, right=5

  mid=3: total = 3·4/2 = 6 > 5 → right=2
  mid=1: total = 1·2/2 = 1 ≤ 5 → left=2
  mid=2: total = 2·3/2 = 3 ≤ 5 → left=3
  left=3 > right=2 → exit

  return right = 2  ✓


  n = 8
  left=1, right=8

  mid=4: total = 4·5/2 = 10 > 8 → right=3
  mid=2: total = 2·3/2 = 3 ≤ 8 → left=3
  mid=3: total = 3·4/2 = 6 ≤ 8 → left=4
  left=4 > right=3 → exit

  return right = 3  ✓
*/

int main() {
    Solution sol;

    cout << "n=5 → " << sol.arrangeCoins(5) << " (expected: 2)\n";
    cout << "n=8 → " << sol.arrangeCoins(8) << " (expected: 3)\n";
    cout << "n=1 → " << sol.arrangeCoins(1) << " (expected: 1)\n";
    cout << "n=3 → " << sol.arrangeCoins(3) << " (expected: 2)\n";
    cout << "n=10 → " << sol.arrangeCoins(10) << " (expected: 4)\n";

    return 0;
}
