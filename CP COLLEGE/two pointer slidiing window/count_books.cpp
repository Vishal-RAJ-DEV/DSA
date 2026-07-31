/*
Question: Codeforces 279B - Books
Given n books with reading times a[i] and free time t.
Find the maximum number of books you can read consecutively
such that the total reading time does not exceed t.

Approach: Sliding window (variable-length)
- r = right pointer expands window by adding a[r]
- When sum exceeds t, shrink from left by subtracting a[l] and moving l++
- At each step, ans = max(ans, window size = r - l + 1)
Every element is added once (by r) and removed at most once (by l), giving O(n) time.
Time: O(n), Space: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 0, sum = 0, ans = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > t) sum -= a[l++];
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';

    return 0;
}
