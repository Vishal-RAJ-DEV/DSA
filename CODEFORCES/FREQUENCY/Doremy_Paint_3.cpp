#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// =========================================================================
// PROBLEM: Doremy's Paint 3 (Codeforces Round 1790, Problem B)
// =========================================================================
//
// Given an array of n integers, you can rearrange it in ANY order.
// Determine if it's possible to arrange the array such that the sums
// of every pair of ADJACENT elements are ALL EQUAL.
//
// i.e., after rearrangement:
//   a1 + a2 == a2 + a3 == a3 + a4 == ... == a_{n-1} + an
//
// If possible → print "YES", otherwise → print "NO".
//
// Constraints: n up to 100 or 2e5 depending on version
// =========================================================================

// =========================================================================
// INTUITION & APPROACH
// =========================================================================
//
// Let's analyze what the condition a1+a2 == a2+a3 implies:
//
//   a1 + a2 == a2 + a3
//   => a1 == a3
//
// Similarly:
//   a2 + a3 == a3 + a4
//   => a2 == a4
//
//   a3 + a4 == a4 + a5
//   => a3 == a5
//
// PATTERN: All odd-indexed positions must have the SAME value, and all
// even-indexed positions must have the SAME value.
//
// So the array MUST alternate between exactly TWO values:
//   [x, y, x, y, x, y, ...]
//
// where x = value at odd positions, y = value at even positions.
//
// Now, depending on the length n:
//
//   n EVEN:  positions: x y x y x y ... x y
//            → count(x) == count(y) == n/2
//
//   n ODD:   positions: x y x y x y ... x
//            → count(x) == count(y) + 1
//            (since odd positions have one extra)
//
// Since x and y are just the two distinct values in the array,
// we can restate this as:
//
//   Let the array have k distinct values.
//
//   Case 1: k > 2  → impossible (need at most 2 distinct numbers)
//   Case 2: k == 1 → always possible (all elements same)
//   Case 3: k == 2 → possible iff |count(v1) - count(v2)| <= 1
//
// WHY k == 2 condition works:
//   - If n is even: we need equal counts → diff = 0 ✓
//   - If n is odd: we need one element to appear once more → diff = 1 ✓
//   - If diff > 1: impossible to alternate properly
//
// =========================================================================
// VISUAL EXAMPLE
// =========================================================================
//
// n = 4, array = [1, 2, 3, 4]
//   k = 4 (too many distinct) → NO
//
// n = 5, array = [2, 2, 2, 2, 2]
//   k = 1 (all same) → YES
//   Arrange: [2, 2, 2, 2, 2]
//   Sums: 2+2=4, 2+2=4, ... all equal ✓
//
// n = 4, array = [1, 2, 1, 2]
//   k = 2, count(1)=2, count(2)=2, diff=0 → YES
//   Already in alternating form ✓
//
// n = 3, array = [1, 2, 1]
//   k = 2, count(1)=2, count(2)=1, diff=1 → YES
//   Already: 1+2=3, 2+1=3 ✓
//
// n = 4, array = [1, 1, 1, 2]
//   k = 2, count(1)=3, count(2)=1, diff=2 > 1 → NO
//   Can't arrange to have all adjacent sums equal
//   Try: [1, 2, 1, 1] → 1+2=3, 2+1=3, 1+1=2 ✗
// =========================================================================

void solve() {
    int n;
    cin >> n;

    map<int, int> freq;     // frequency of each value

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    // If there are more than 2 distinct numbers, impossible
    if (freq.size() > 2) {
        cout << "NO\n";
        return;
    }

    // If there is exactly 1 distinct number, always possible
    if (freq.size() == 1) {
        cout << "YES\n";
        return;
    }

    // Exactly 2 distinct numbers: check count difference
    auto it = freq.begin();
    int cnt1 = it->second;
    ++it;
    int cnt2 = it->second;

    if (abs(cnt1 - cnt2) <= 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
