#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        long long a = -1, b = -1, c = -1;

        // Find first divisor
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                a = i;
                n /= i;
                break;
            }
        }

        // Find second divisor (different from a)
        if (a != -1) {
            for (long long i = a + 1; i * i <= n; i++) {
                if (n % i == 0) {
                    b = i;
                    n /= i;
                    break;
                }
            }
        }

        c = n;

        if (a != -1 && b != -1 && c > 1 && c != a && c != b) {
            cout << "YES\n";
            cout << a << " " << b << " " << c << "\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}

/*
================================================================
QUESTION:
Given a number n (1 <= n <= 1e9), determine if it can be expressed as
a product of three distinct integers a, b, c such that a, b, c > 1.
If yes, output "YES" followed by a, b, c. Otherwise output "NO".

================================================================
INTUITION:
We need to split n into 3 distinct factors > 1. The greedy approach
works: find the smallest divisor a (starting from 2), then find the
next smallest divisor b distinct from a from the quotient, and let
c = n / (a*b). Validate that all three are distinct and > 1.

Why greedy works: To maximize the chance of finding three distinct
factors, we want the first two factors as small as possible, leaving
the largest possible remainder for the third factor. Starting from
2 ensures we find the smallest possible divisor.

================================================================
ALGORITHM:
1. Find the first divisor a:
   For i = 2 to sqrt(n):
     if n % i == 0: set a = i, n /= i, break.
2. If a is found, find the second divisor b (must be > a to ensure
   distinctness):
   For i = a+1 to sqrt(n):
     if n % i == 0: set b = i, n /= i, break.
3. Set c = n (the remaining quotient after dividing by a and b).
4. Check conditions:
   - a != -1 (first divisor found)
   - b != -1 (second divisor found)
   - c > 1 (third divisor > 1)
   - c != a && c != b (all three distinct)
   If all satisfied, output YES with a, b, c. Else output NO.

Time Complexity: O(sqrt(n)) per test case.
Space Complexity: O(1)

================================================================
EXAMPLE:
n = 64
Find a: i=2, 64%2=0 => a=2, n=32
Find b: i=3..sqrt(32): 32%3!=0, 32%4=0 => b=4, n=8
c = 8
Check: a=2, b=4, c=8, all >1 and distinct => YES (2*4*8 = 64)

n = 12
Find a: i=2, 12%2=0 => a=2, n=6
Find b: i=3, 6%3=0 => b=3, n=2
c = 2
Check: a=2, b=3, c=2 => c == a (not distinct) => NO
(No other factorization of 12 into 3 distinct factors >1 exists)
*/