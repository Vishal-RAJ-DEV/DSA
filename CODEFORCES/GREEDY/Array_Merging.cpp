#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Algorithm
===============================================================================

Observation:
------------
For every value x, we only care about:

1. Longest consecutive block of x in array A.
2. Longest consecutive block of x in array B.

Suppose

A : 2 2 2        -> longest block = 3
B : 2 2          -> longest block = 2

During merge, we can always place the block from B immediately before
(or after) the block from A.

Result:

2 2 | 2 2 2

Maximum consecutive block = 2 + 3 = 5.

Therefore,

answer = max(bestA[x] + bestB[x])

for every possible value x.

-------------------------------------------------------------------------------
Steps
-------------------------------------------------------------------------------

1. Traverse array A.
   - Count every consecutive run.
   - Store the maximum run length for every value.

2. Traverse array B.
   - Do the same.

3. Iterate over every possible value (1 ... 2*n).
   - Compute bestA[value] + bestB[value].
   - Keep the maximum.

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(2*n) = O(n)
===============================================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {

        int n;
        cin >> n;

        vector<int> a(n), b(n);

        for (int i = 0; i < n; i++)
            cin >> a[i];

        for (int i = 0; i < n; i++)
            cin >> b[i];

        // Since values are in the range [1, 2*n]
        vector<int> bestA(2 * n + 1, 0);
        vector<int> bestB(2 * n + 1, 0);

        // ---------------------------------------------------------
        // Find longest consecutive block in array A
        // ---------------------------------------------------------

        int i = 0;

        while (i < n) {

            int value = a[i];
            int cnt = 0;

            // Count length of current consecutive block
            while (i < n && a[i] == value) {
                cnt++;
                i++;
            }

            // Store the maximum block length for this value
            bestA[value] = max(bestA[value], cnt);
        }

        // ---------------------------------------------------------
        // Find longest consecutive block in array B
        // ---------------------------------------------------------

        i = 0;

        while (i < n) {

            int value = b[i];
            int cnt = 0;

            while (i < n && b[i] == value) {
                cnt++;
                i++;
            }

            bestB[value] = max(bestB[value], cnt);
        }

        // ---------------------------------------------------------
        // Compute answer
        // ---------------------------------------------------------

        int ans = 0;

        for (int value = 1; value <= 2 * n; value++) {
            ans = max(ans, bestA[value] + bestB[value]);
        }

        cout << ans << '\n';
    }

    return 0;
}


/*
Dry Run
Input
n = 5

A = [1 2 2 2 2]

B = [2 1 1 1 1]


Step 1 (Process A)
Runs are:
1         length = 1
2 2 2 2   length = 4
So
bestA[1] = 1
bestA[2] = 4

Step 2 (Process B)
Runs are:
2         length = 1
1 1 1 1   length = 4
So
bestB[1] = 4
bestB[2] = 1

Step 3
For every value:
value = 1
bestA[1] + bestB[1]
= 1 + 4
= 5
---------------------

value = 2
bestA[2] + bestB[2]
= 4 + 1
= 5

Maximum

5
Interview Question

Why do we store only the longest run for each value?

Suppose

A = [2 2 1 2]

There are two runs of 2:

2 2      length = 2

2        length = 1

The 1 between them can never be removed because the relative order inside an array must remain unchanged during a merge. Therefore, those two runs can never become one continuous block. Only the largest run (length 2) can contribute to the optimal answer, which is why we store only the maximum run length for each value.*/