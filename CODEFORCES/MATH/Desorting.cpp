#include <bits/stdc++.h>
using namespace std;

/*
=============================================================
 PROBLEM: 1853A - Desorting (Codeforces)
=============================================================

 INTUITION (in simple words):

We have an array. One operation picks index i:
  - Add +1 to all elements from index 1 to i
  - Add -1 to all elements from index i+1 to n

The goal is to make the array NOT sorted (i.e., find some
adjacent pair where left > right) using minimum operations.

=============================================================

KEY OBSERVATION:

Only the adjacent pair (i, i+1) is affected when we operate
on index i. For all other pairs, both elements change by the
same amount (+1 or -1), so their relative difference stays
the same.

When we operate on index i:
  a[i]   → a[i]   + 1      (prefix gets +1)
  a[i+1] → a[i+1] - 1      (suffix gets -1)

So the difference (a[i] - a[i+1]) increases by exactly 2
per operation.

=============================================================

 MATHEMATICAL BREAKDOWN:

Let d = a[i+1] - a[i]   (the gap between adjacent elements)

If the array is sorted (non-decreasing), then d ≥ 0.

Our current state: a[i] - a[i+1] = -d

After k operations on index i:
  a[i] - a[i+1] = -d + 2k

We need this to become > 0 (i.e., left > right, breaking sort):
  -d + 2k > 0
  → 2k > d
  → k > d/2

Since k must be an integer, the smallest k that satisfies
k > d/2 is:
  k = floor(d/2) + 1   or equivalently   k = d/2 + 1

Examples:
  d=0 → need k > 0   → k=1  → 0/2+1 = 1
  d=1 → need k > 0.5 → k=1  → 1/2+1 = 0+1 = 1
  d=2 → need k > 1   → k=2  → 2/2+1 = 1+1 = 2
  d=3 → need k > 1.5 → k=2  → 3/2+1 = 1+1 = 2

=============================================================

WHY TAKE MINIMUM DIFFERENCE?

Each adjacent pair (i,i+1) has its own gap d.
The smaller the gap, the fewer operations needed to break it.
So we find the smallest d across all pairs — that's the
"weakest link" that will break first.

If any d < 0, the array is already unsorted → answer is 0.

=============================================================

 FINAL ANSWER:

answer = min_difference / 2 + 1

Where min_difference = smallest (a[i+1] - a[i]) across all i.
=============================================================
*/

void solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++){
        cin>>a[i];
    }

    // Find the minimum adjacent difference
    int min_diff = INT_MAX;
    for(int i = 0  ; i < n- 1 ; i++){
        int diff = a[i + 1] - a[i];

        // If any pair is already decreasing, array is already unsorted
        if( diff < 0){
            cout<<"0"<<endl;
            return;
        }
        min_diff = min(min_diff, diff);
    }

    // Minimum operations needed = smallest_gap / 2 + 1
    cout<<min_diff / 2 + 1<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}