#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM: Codeforces A. Cut Ribbon

APPROACH: BOTTOM-UP DYNAMIC PROGRAMMING (TABULATION)


1. INTUITION
-------------
We have a ribbon of length n and can cut pieces of length a, b, or c.

Our goal is to maximize the total number of pieces while using
the entire ribbon.

For every possible ribbon length i, we calculate the maximum
number of pieces we can obtain.

Instead of trying every possible combination of cuts separately,
we store answers to smaller ribbon lengths and reuse them.


2. DP STATE
------------
dp[i] = maximum number of pieces obtainable from a ribbon
        of length i.

For example:
dp[5] represents the maximum number of pieces we can obtain
from a ribbon of length 5 using only the allowed cuts.


3. BASE CASE
-------------
dp[0] = 0

Why?
A ribbon of length zero requires zero pieces.

All other states are initially set to -1e9, a very negative
number representing an impossible or not-yet-reachable length.

This prevents an impossible smaller length from being treated
as a valid solution.


4. TRANSITION
--------------
For every ribbon length i, we try all three possible cuts.

CHOICE 1: CUT A
If i >= a, we can use one piece of length a.
The remaining ribbon length is i - a.

Number of pieces = dp[i - a] + 1

Therefore:
dp[i] = max(dp[i], dp[i - a] + 1)


CHOICE 2: CUT B
If i >= b, we can use one piece of length b.
The remaining ribbon length is i - b.

Number of pieces = dp[i - b] + 1

Therefore:
dp[i] = max(dp[i], dp[i - b] + 1)


CHOICE 3: CUT C
If i >= c, we can use one piece of length c.
The remaining ribbon length is i - c.

Number of pieces = dp[i - c] + 1

Therefore:
dp[i] = max(dp[i], dp[i - c] + 1)


FINAL TRANSITION:
dp[i] = max(
    dp[i - a] + 1,
    dp[i - b] + 1,
    dp[i - c] + 1
)

We only consider a choice when its cut length does not exceed i.


5. HOW TABULATION WORKS
------------------------
We calculate dp values in increasing order, from i = 1 to i = n.

Why?
To calculate dp[i], we need previously calculated values:
dp[i - a], dp[i - b], and dp[i - c].

Because a, b, and c are positive, these smaller lengths are
processed before i.

Thus, we build the answer from smaller subproblems to larger ones.


6. DRY RUN
-----------
Suppose:
n = 5, a = 5, b = 3, c = 2

Initially:
dp[0] = 0
All other dp values are impossible.

For i = 1:
No cut of length 2, 3, or 5 fits.
dp[1] remains impossible.

For i = 2:
We can cut a piece of length 2.
dp[2] = dp[0] + 1 = 1

For i = 3:
We can cut a piece of length 3.
dp[3] = dp[0] + 1 = 1

For i = 4:
We can cut two pieces of length 2.
dp[4] = dp[2] + 1 = 2

For i = 5:
Option 1: Cut length 5.
          dp[5] = dp[0] + 1 = 1

Option 2: Cut length 3.
          dp[5] = dp[2] + 1 = 2

Option 3: Cut length 2.
          dp[5] = dp[3] + 1 = 2

The maximum is 2.

Answer = dp[5] = 2
One optimal cutting is 3 + 2.


7. WHY DO WE TAKE MAXIMUM?
---------------------------
We need the largest possible number of pieces, not the smallest.

Each transition represents a different possible first cut.
We calculate the answer for each choice and keep the maximum.


8. WHY IS THIS DYNAMIC PROGRAMMING?
------------------------------------
There are two important properties:

1. Optimal substructure:
   After choosing a piece, the remaining ribbon must also be cut
   optimally to maximize the total number of pieces.

2. Overlapping subproblems:
   The same smaller ribbon lengths can be needed by multiple states.
   Storing their answers avoids recalculating them.


9. FINAL ANSWER
----------------
After processing every length from 1 to n, dp[n] contains the
maximum number of pieces for the original ribbon.

We return dp[n].


10. COMPLEXITY
---------------
Time Complexity: O(n)

We process n ribbon lengths and check at most three cuts per length.

Space Complexity: O(n)

We store one DP value for every length from 0 to n.

IMPORTANT:
This solution uses O(n) space. A few variables are not sufficient
for general inputs because dp[i] may depend on earlier states
that are arbitrarily far apart.
*/


vector<int> dp;

int solve(int n, int a, int b, int c) {
    // Base case: exactly used the entire ribbon.
    if (n == 0) return 0;

    // Impossible to cut the remaining length.
    if (n < 0) return -1e9;

    // Return the previously calculated answer.
    if (dp[n] != -1) return dp[n];

    // Try cutting a piece of length a, b, or c.
    int cutA = 1 + solve(n - a, a, b, c);
    int cutB = 1 + solve(n - b, a, b, c);
    int cutC = 1 + solve(n - c, a, b, c);

    // Choose the option that produces the maximum pieces.
    return dp[n] = max({cutA, cutB, cutC});
}

int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    dp.assign(n + 1, -1);

    cout << solve(n, a, b, c) << '\n';

    return 0;
}


int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    // dp[i] = maximum number of pieces we can get
    // by cutting a ribbon of length i.
    vector<int> dp(n + 1, -1e9);

    // Base case: a ribbon of length 0 needs 0 pieces.
    dp[0] = 0;

    // Build answers for every length from 1 to n.
    for (int i = 1; i <= n; i++) {

        // Try cutting a piece of length a.
        if (i >= a)
            dp[i] = max(dp[i], dp[i - a] + 1);

        // Try cutting a piece of length b.
        if (i >= b)
            dp[i] = max(dp[i], dp[i - b] + 1);

        // Try cutting a piece of length c.
        if (i >= c)
            dp[i] = max(dp[i], dp[i - c] + 1);
    }

    // Maximum number of pieces for the complete ribbon.
    cout << dp[n] << '\n';

    return 0;
}


int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    // dp[i] = maximum pieces for ribbon length i.
    vector<int> dp(n + 1, -1e9);

    // Base case: zero length requires zero pieces.
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != -1e9)
            dp[i] = max(dp[i], dp[i - a] + 1);

        if (i >= b && dp[i - b] != -1e9)
            dp[i] = max(dp[i], dp[i - b] + 1);

        if (i >= c && dp[i - c] != -1e9)
            dp[i] = max(dp[i], dp[i - c] + 1);
    }

    cout << dp[n] << '\n';
    return 0;
}

int main(){
    return 0;
}