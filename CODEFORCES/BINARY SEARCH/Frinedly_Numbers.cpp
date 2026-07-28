// ============================================================
// PROBLEM: Friendly Numbers
//
// For a given integer x, count how many integers y satisfy:
//       y - d(y) = x
// where d(y) = sum of digits of y.
//
// Example: x = 9
//   y = 10 → d(10) = 1+0 = 1 → 10 - 1 = 9 ✓
//   y = 11 → d(11) = 1+1 = 2 → 11 - 2 = 9 ✓
//   No other y works, so answer = 2.
//
// WHY left = x?
//
//   We are looking for y such that:
//       y - digitSum(y) = x   →   y = x + digitSum(y)
//
//   Since digitSum(y) ≥ 0 (sum of digits is never negative):
//       y ≥ x
//
//   No answer can ever be smaller than x.
//   Example: x = 100
//     y = 95 → 95 - digitSum(95) = 95 - 14 = 81 ≠ 100
//     y = 99 → 99 - digitSum(99) = 99 - 18 = 81 ≠ 100
//     No y < 100 can ever reach 100 because f(y) = y - d(y) ≤ y.
//
//   Therefore the search starts at left = x.
//
// WHY right = x + 90?
//
//   From y = x + digitSum(y), the maximum y depends on the
//   largest possible digitSum(y). What is that maximum?
//
//   For this problem, y ≤ 10¹⁰ (based on constraints).
//   A number up to 10¹⁰ has at most 10 digits.
//
//   The largest possible digit sum for a 10-digit number is:
//       9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 = 90
//
//   So digitSum(y) ≤ 90 for all y in the relevant range.
//   Therefore:
//       y = x + digitSum(y)  ≤  x + 90
//
//   Every possible answer must lie inside [x, x+90].
//
//   Visual picture for x = 100:
//       100 ------------------------------------ 190
//       ^                                        ^
//      left                                    right
//
//   The binary search only looks inside this tiny 91-element window.
//   Without this bound, we'd have to search to infinity.
//
// PROPERTY OF f(y) = y - d(y) (MONOTONICITY):
//
//   Is f always increasing? Let's check the difference:
//     f(y+1) - f(y) = (y+1 - d(y+1)) - (y - d(y))
//                    = 1 - (d(y+1) - d(y))
//
//   What is d(y+1) - d(y)?
//     If y has k trailing 9s (k ≥ 0):
//       - Those k 9s become 0 (sum drops by 9k)
//       - The digit before them increments by 1 (sum increases by 1)
//       - So d(y+1) - d(y) = 1 - 9k
//
//   Therefore:
//     f(y+1) - f(y) = 1 - (1 - 9k) = 9k  (always ≥ 0)
//
//   So f is NON-DECREASING.
//   When k = 0 (no trailing 9): f(y+1) = f(y)  [plateau]
//   When k ≥ 1: f(y+1) > f(y)               [strict increase]
//
//   Since f is non-decreasing, all y values satisfying f(y) = x
//   form a SINGLE CONTIGUOUS block. We just need to find its
//   start and count how long it lasts.
//
// ALGORITHM (Binary Search):
//   1. Binary search in [x, x+90] for the FIRST y where f(y) ≥ x
//      (lower bound of the block)
//   2. From there, count consecutive y where f(y) == x
//   3. Output the count
//
// COMPLEXITY: O(log 90 + 90) ≈ O(1) per test case
//
// ============================================================
// OPTIMAL APPROACH — Direct Iteration:
//
//   Since the search space is only 91 values (x to x+90), binary
//   search is unnecessary overhead. The simplest and fastest way
//   is to just iterate through every y in [x, x+90] and check
//   y - digitSum(y) == x directly.
//
// WHY DIRECT LOOP IS MORE EFFICIENT THAN BINARY SEARCH:
//
//   1. Binary search calls digitSum during the SEARCH phase AND
//      again during the COUNTING phase — many y values get their
//      digitSum computed TWICE (once in BS, once in the while loop).
//
//   2. Binary search uses a lambda + function call overhead per
//      check; the loop calls digitSum directly with zero indirection.
//
//   3. Worst-case digitSum calls per test case:
//        Binary search: 7 (BS) + up to 90 (counting) = ~97 calls
//        Direct loop:   91 calls (exactly one per y, never redundant)
//
//   4. Binary search has pointer arithmetic, mid calculations, and
//      extra branching — all unnecessary when 91 elements is the max.
//
//   5. The counting phase in BS re-evaluates f(left) == x on y
//      values that were already evaluated during the BS phase,
//      doing redundant digitSum computations.
//
//   BOTTOM LINE: Same O(1) asymptotically, but direct loop does
//   strictly fewer operations — fewer digitSum calls, no lambda
//   overhead, no redundant computations. Simpler = faster.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// Returns the sum of digits of n
int digitSum(long long n) {
    int sum = 0;
    while (n) {
        sum += n % 10;      // Extract last digit and add to sum
        n /= 10;            // Remove last digit
    }
    return sum;
}

// ── APPROACH 1: Direct iteration (optimal & simplest) ──
// Since y ∈ [x, x+90] (only 91 values), just loop and count.
void solve_optimal() {
    long long x;
    cin >> x;

    int ans = 0;

    // Every possible y lies in [x, x+90] — check all 91 values
    for (long long y = x; y <= x + 90; y++) {
        if (y - digitSum(y) == x)
            ans++;
    }

    cout << ans << "\n";
}

// ── APPROACH 2: Binary search (educational but unnecessary) ──
// Uses the non-decreasing property of f(y) to find the solution block.
void solve_bs() {
    long long x;
    cin >> x;

    // f(y) = y - digitSum(y)
    auto f = [&](long long y) {
        return y - digitSum(y);
    };

    // Search range: y must be in [x, x+90]
    long long left = x;
    long long right = x + 90;

    // Binary search: find the FIRST y where f(y) >= x
    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (f(mid) >= x)
            right = mid - 1;
        else
            left = mid + 1;
    }

    int ans = 0;

    // Count consecutive y where f(y) == x
    while (left <= x + 90 && f(left) == x) {
        ans++;
        left++;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve_optimal();    // Using the optimal direct approach
}
