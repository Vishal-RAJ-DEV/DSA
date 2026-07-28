// ============================================================
// PROBLEM: Sushi for Two (Codeforces 1138A)
//
// Given an array of 1s (tuna) and 2s (eel), find the longest
// contiguous segment where one half is all 1s and the other
// half is all 2s, and both halves have EQUAL length.
//
// In other words: find a subarray of the form:
//   k ones followed by k twos,  OR  k twos followed by k ones
// Maximize 2*k (the total length).
//
// Example:
//   arr = [2, 2, 2, 1, 1, 2, 2]
//   Groups:   3 twos | 2 ones | 2 twos
//   Adjacent: 3 & 2 → 2*2 = 4 (2 twos + 2 ones → [2,2,1,1])
//             2 & 2 → 2*2 = 4 (2 ones + 2 twos → [1,1,2,2])
//   Answer = 4
//
// ALGORITHM:
//   1. Scan the array, tracking current run length (curr) and
//      previous run length (prev) of the opposite value.
//   2. At each boundary where the value changes, evaluate
//      2 * min(prev, curr) and update the answer.
//   3. Answer is the maximum over all boundaries.
//
// WHY THIS WORKS:
//   Any valid segment spans exactly ONE boundary where the value
//   changes. It takes as many elements as possible from each side,
//   limited by the shorter group. We don't need to store all groups
//   — just the previous and current counts at each boundary.
//
// COMPLEXITY: O(n) time, O(1) space
// ============================================================
// APPROACH 2 — Group vector: O(n) time, O(n) space
//
//   Stores all run-lengths in a vector, then iterates adjacent pairs.
//   Simpler to understand but uses extra memory.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ── APPROACH 1: O(1) space (optimal) ──
// Only tracks prev and curr counts, updates answer at each boundary.
void solve_optimal() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;
    int prev = 0;        // count of the previous group (different value)
    int curr = 1;        // count of the current group we're building

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i-1]) {
            curr++;                     // extend current group
        } else {
            // Boundary found: evaluate best segment with prev group
            ans = max(ans, 2 * min(prev, curr));
            prev = curr;                // current group becomes prev for next boundary
            curr = 1;                   // start counting new group
        }
    }
    // Check the last boundary
    ans = max(ans, 2 * min(prev, curr));

    cout << ans << "\n";
}

// ── APPROACH 2: O(n) space (educational) ──
// Stores all group counts in a vector, then scans adjacent pairs.
void solve_vector() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> groups;
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i-1]) {
            count++;
        } else {
            groups.push_back(count);
            count = 1;
        }
    }
    groups.push_back(count);

    int ans = 0;
    for (int i = 0; i + 1 < groups.size(); i++) {
        ans = max(ans, 2 * min(groups[i], groups[i+1]));
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve_optimal();    // Using the O(1) space version
    }

    return 0;
}
