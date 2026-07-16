/*
    Problem: Convergence (Make all elements equal to middle element)

    Given array a of length n, find min operations to make all elements
    equal to a[mid] (the middle element), where one operation can change
    elements on only ONE side of mid (left side OR right side).

    Since left & right can be processed independently in parallel,
    answer = MAX of mismatches on left vs right (not the sum).
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define all(x) (x).begin(), (x).end()

// ----------------------------------------------------------------
// Approach 2: Sort first, then count per half
//
// Idea:
//   - Sort so that a[mid] is the median
//   - mid = n / 2
//   - Count elements in [0, mid-1] != a[mid]  -> leftcall
//   - Count elements in [mid+1, n-1] != a[mid] -> rightcall
//   - Answer = max(leftcall, rightcall)
//
// Time: O(n log n), Space: O(1)
// ----------------------------------------------------------------
int solve_approach2() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(all(a));

    int leftcall = 0;
    int rightcall = 0;
    int mid = n / 2;

    for (int i = 0; i < mid; i++) {
        if (a[i] != a[mid]) leftcall++;
    }
    for (int i = mid + 1; i < n; i++) {
        if (a[i] != a[mid]) rightcall++;
    }

    return max(leftcall, rightcall);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cout << solve_approach2() << '\n';
    }

    return 0;
}


