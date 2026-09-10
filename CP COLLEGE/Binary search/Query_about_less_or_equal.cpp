// ═══════════════════════════════════════════════════════════════
// PROBLEM: Queries about less than or equal elements
//          (Codeforces 990B / similar)
// ═══════════════════════════════════════════════════════════════
//
// You are given two arrays:
//
//   a → of size n  (the data array)
//   b → of size m  (the query array)
//
// For EACH element b[i], you need to answer:
//
//   "How many elements in array a are LESS THAN OR EQUAL TO b[i]?"
//
// ─────────────────────────────────────────────────────────────
// EXAMPLE:
//   n = 5, m = 4
//   a = [1, 3, 5, 7, 9]
//   b = [6, 4, 8, 2]
//
//   For b[0] = 6 → elements in a <= 6 are {1,3,5}   → count = 3
//   For b[1] = 4 → elements in a <= 4 are {1,3}     → count = 2
//   For b[2] = 8 → elements in a <= 8 are {1,3,5,7} → count = 4
//   For b[3] = 2 → elements in a <= 2 are {1}       → count = 1
//
//   Output: 3 2 4 1
// ═══════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    vector<long long> b(m);

    // Input array a
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Input array b
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    // ─────────────────────────────────────────────────────────
    // STEP 1: Sort array a
    // ─────────────────────────────────────────────────────────
    // Sorting is essential because binary search only works
    // on sorted data. After sorting, all elements are in
    // ascending order, so we can use upper_bound to find
    // how many elements are <= a given value.
    //
    // Example:
    //   Before sort: a = [7, 1, 9, 3, 5]
    //   After sort:  a = [1, 3, 5, 7, 9]
    // ─────────────────────────────────────────────────────────
    sort(a.begin(), a.end());

    // ─────────────────────────────────────────────────────────
    // STEP 2: Answer each query using binary search
    // ─────────────────────────────────────────────────────────
    for (int i = 0; i < m; i++) {

        // ─────────────────────────────────────────────────────
        // WHAT IS upper_bound?
        // ─────────────────────────────────────────────────────
        // upper_bound(begin, end, value) returns an iterator
        // to the FIRST element in the sorted array that is
        // STRICTLY GREATER than value.
        //
        // Since the array is sorted in ascending order:
        //   - All elements BEFORE this position are <= value
        //   - All elements FROM this position onward are > value
        //
        // So the COUNT of elements <= value is simply:
        //   (position of upper_bound) - (start of array)
        //   = upper_bound(...) - a.begin()
        //
        // ─────────────────────────────────────────────────────
        // VISUAL EXAMPLE (a = [1, 3, 5, 7, 9]):
        // ─────────────────────────────────────────────────────
        //   Query: b[i] = 6
        //
        //   a: [1, 3, 5, 7, 9]
        //           ↑
        //     upper_bound points here (first element > 6)
        //     Position = 3 (0-indexed)
        //
        //   Elements at index 0,1,2 → {1, 3, 5} are all <= 6
        //   Count = 3  ✓
        //
        // ─────────────────────────────────────────────────────
        // WHY NOT lower_bound?
        // ─────────────────────────────────────────────────────
        // lower_bound finds the first element >= value.
        // If there are duplicate values equal to b[i],
        // lower_bound would INCLUDE them in the count,
        // but we need <= (less than OR equal).
        //
        // Actually both work for <=, but upper_bound is more
        // natural here: it gives the count of elements <= b[i]
        // directly as (iterator - begin).
        // ─────────────────────────────────────────────────────

        int count = upper_bound(a.begin(), a.end(), b[i]) - a.begin();

        cout << count << " ";
    }

    cout << endl;

    return 0;
}