#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Given n integers, check whether we can pick k numbers such that the difference
between ANY two of them is divisible by m. If yes, print "Yes" and any such
k numbers; otherwise print "No".

Key Insight (Math):
For two numbers a and b:
    (a - b) is divisible by m  <=>  (a - b) % m == 0  <=>  a % m == b % m
So to make differences divisible by m, all chosen numbers must have the SAME
remainder when divided by m.

Algorithm (Bucket / Counting by remainder):
1. Create m buckets (groups), one for each possible remainder 0 .. m-1.
2. Read each number x and put it into bucket (x % m).
3. Scan the buckets: if any bucket holds at least k numbers,
   pick any k of them (e.g. the first k) -> those k numbers have equal
   remainders, so all pairwise differences are divisible by m -> print "Yes".
4. If no bucket reaches size k -> print "No".

Time complexity : O(n + m)
Space complexity: O(n + m)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;   // n = count of numbers, k = how many we need to pick, m = divisor
    cin >> n >> k >> m;

    // groups[r] stores all input numbers whose remainder mod m equals r
    // There are exactly m possible remainders: 0, 1, ..., m-1
    vector<vector<int>> groups(m);

    // Phase 1: Read all numbers and bucket them by remainder (x % m)
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        groups[x % m].push_back(x);   // push x into its remainder bucket
    }

    // Phase 2: Find any remainder group that contains at least k numbers
    for (int r = 0; r < m; r++) {

        if ((int)groups[r].size() >= k) {
            // Found a bucket with >= k numbers -> those numbers all share
            // remainder r, so any two differ by a multiple of m
            cout << "Yes\n";

            // Print any k numbers from this group (first k is fine)
            for (int i = 0; i < k; i++) {
                cout << groups[r][i] << " ";
            }

            cout << "\n";
            return 0;   // answer found, stop
        }
    }

    // Phase 3: No remainder group has k or more numbers -> impossible
    cout << "No\n";

    return 0;
}