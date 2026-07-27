#include <bits/stdc++.h>
using namespace std;
/*
Approach: Prime Factorization (Trial Division)

1. Check every divisor from 2 to √N.
   - We only need to check up to √N because if a factor is greater than √N,
     the other factor must be smaller than √N.

2. If i divides N:
   - Count how many times it divides N.
   - Keep dividing N by i until it is no longer divisible.
   - Print (i^count).

3. After removing all occurrences of i, continue with the next divisor.

4. If after the loop N > 1, then N itself is a prime factor.
   - Print (N^1).

Why use i * i <= n?
- As we divide N, it becomes smaller.
- This reduces the number of iterations, making the algorithm faster.

Why use 'first'?
- To print '*' only between factors.
- Avoids printing an extra '*' before the first factor.

Example:
N = 1260

1260 = 2 × 2 × 3 × 3 × 5 × 7

Output:
(2^2)*(3^2)*(5^1)*(7^1)

Time Complexity: O(√N)
Space Complexity: O(1)
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    bool first = true;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }

            if (!first) cout << "*";
            cout << "(" << i << "^" << cnt << ")";
            first = false;
        }
    }

    if (n > 1) {
        if (!first) cout << "*";
        cout << "(" << n << "^1)";
    }

    cout << "\n";

    return 0;
}