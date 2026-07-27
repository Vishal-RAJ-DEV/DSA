#include <bits/stdc++.h>
using namespace std;

/*
Approach:

1. Ensure A <= B
   - If A > B, swap(A, B).

2. Find the first multiple of X in the range [A, B]
   first = ((A + X - 1) / X) * X;

   Explanation:
   - (A + X - 1) / X gives the ceiling value of A/X.
   - Multiplying by X gives the smallest multiple of X that is >= A.

   Example:
   A = 7, X = 5
   first = ((7 + 5 - 1) / 5) * 5
         = (11 / 5) * 5
         = 2 * 5
         = 10

3. Find the last multiple of X in the range
   last = (B / X) * X;

   Explanation:
   - B / X gives the floor value of B/X.
   - Multiplying by X gives the largest multiple of X that is <= B.

   Example:
   B = 23, X = 5
   last = (23 / 5) * 5
        = 4 * 5
        = 20

4. Check if any multiple exists
   - If first > last, then no multiple of X exists in [A, B].
   - Answer = 0.

5. Count the number of multiples
   Sequence:
   first, first + X, first + 2X, ..., last

   Number of terms:
   n = (last - first) / X + 1;

   Example:
   5, 10, 15, 20

   n = (20 - 5) / 5 + 1
     = 4

6. Compute the sum using Arithmetic Progression (AP)

   AP Sum Formula:
   Sum = n * (first + last) / 2

   Use 'long long' because the answer can be much larger than the
   range of an int.

Time Complexity: O(1)
Space Complexity: O(1)
*/
void solve()
{
    long long A, B, X;
    cin >> A >> B >> X;

    if (A > B)
        swap(A, B);

    long long answer = 0;
    long long first = ((A + X - 1) / X) * X;
    long long last = (B / X) * X;

    if (first > last)
        answer = 0;
    else
    {
        long long n = (last - first) / X + 1;
        answer = n * (first + last) / 2;
    }

    cout << answer << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}