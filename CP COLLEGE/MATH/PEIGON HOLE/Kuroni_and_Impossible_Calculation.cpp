#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);

    // Read all the numbers
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    /*
    ------------------------------------------------------------------------
    Pigeonhole Principle Observation

    There are only 'm' possible remainders when a number is divided by 'm'.

    Possible remainders:
        0, 1, 2, ..., m-1

    If n > m:
        - We have more numbers than possible remainders.
        - By the Pigeonhole Principle, at least two numbers must have
          the same remainder modulo m.

        Suppose:
            ai % m = aj % m

        Then:
            ai = k1 * m + r
            aj = k2 * m + r

        Subtracting,

            ai - aj
            = (k1 * m + r) - (k2 * m + r)
            = (k1 - k2) * m

        Hence,

            (ai - aj) % m = 0

        Therefore, one factor |ai - aj| is divisible by m.

        Since the final answer is the product of all differences,

            Product = ... * |ai-aj| * ...

        and

            |ai-aj| % m = 0

        the whole product also becomes

            Product % m = 0

        So we can immediately print 0 without any computation.
    ------------------------------------------------------------------------
    */

    if (n > m) {
        cout << 0 << '\n';
        return 0;
    }

    /*
    Since n <= m and m <= 1000,

        n <= 1000

    Therefore, O(n²) is fast enough.

    We simply calculate the absolute difference for every pair,
    multiply it into the answer, and continuously take modulo m
    to keep the numbers small.
    */

    long long ans = 1;

    // Generate every pair (i, j) where i < j
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            // Absolute difference of the current pair
            long long diff = abs(a[i] - a[j]);

            // Multiply into the answer while taking modulo
            ans = (ans * (diff % m)) % m;
        }
    }

    cout << ans << '\n';

    return 0;
}

/*
==============================================================================
ALGORITHM
==============================================================================

1. Read n, m and the array.

2. Check whether n > m.

   If YES:
      • There are only m possible remainders modulo m.
      • Since there are more than m numbers,
        two numbers must have the same remainder
        (Pigeonhole Principle).

      • Their difference is divisible by m.

      • Hence one factor of the product is 0 modulo m,
        making the entire product equal to 0 modulo m.

      • Print 0 and terminate.

3. Otherwise (n <= m):

      • Initialize answer = 1.

      • Iterate over every pair (i, j) such that i < j.

      • Compute
            diff = |a[i] - a[j]|

      • Update
            answer = (answer × (diff % m)) % m

4. Print the final answer.

==============================================================================
TIME COMPLEXITY
==============================================================================

Case 1:
    n > m

    O(1)

Case 2:
    n <= m <= 1000

    Two nested loops generate all pairs.

    Number of pairs = n(n-1)/2

    Time Complexity:
        O(n²)

    Maximum operations:
        1000 × 1000 = 10⁶

==============================================================================
SPACE COMPLEXITY
==============================================================================

O(n)

for storing the input array.

==============================================================================
KEY OBSERVATION
==============================================================================

Whenever:

    • Answer is required modulo m.
    • m is very small.
    • n > m.

Think about the Pigeonhole Principle.

Duplicate remainders imply:

    (ai - aj) % m = 0

which immediately makes the entire product equal to 0 modulo m.
==============================================================================
*/