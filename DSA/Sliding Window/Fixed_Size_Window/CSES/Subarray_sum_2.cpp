/*
========================================================================================
 CSES: Subarray Sums II
 Problem: Count the number of subarrays whose sum is exactly X.
          (array can contain NEGATIVE numbers, so sliding window with
           two pointers does NOT work here -> use prefix sum + map)

 Key Idea:
   prefix[i] = sum of arr[0..i]
   Sum of subarray (j+1 .. i) = prefix[i] - prefix[j]

   For a subarray ENDING at index i to have sum X we need:
        prefix[i] - prefix[j] == X
     => prefix[j] == prefix[i] - X

   So for every i, count how many earlier prefix values equal (pref - X).
   That count is exactly the number of valid subarrays ending at i.

   cnt map stores: prefix value -> how many times it has appeared so far.
   cnt[0] = 1 is seeded because a subarray starting at index 0
   (i.e. j = -1, empty prefix) is valid when pref == X.

   Time: O(n log n) due to map operations.
========================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; long long x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    map<long long, long long> cnt;  // prefix sum -> frequency of its occurrences
    cnt[0] = 1;                     // empty prefix (before index 0) has sum 0
    long long pref = 0, ans = 0;    // current running prefix sum, answer counter

    for (int i = 0; i < n; i++) {
        pref += arr[i];             // prefix sum up to index i: pref = sum(arr[0..i])

        // Every earlier index j with prefix[j] == pref - X gives a subarray
        // (j+1..i) whose sum is exactly X. Add that many to the answer.
        ans += cnt[pref - x];       // subarrays ending at i with sum x

        cnt[pref]++;                // record this prefix sum for future indices
    }

    cout << ans << "\n";

}

int main() {
    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}