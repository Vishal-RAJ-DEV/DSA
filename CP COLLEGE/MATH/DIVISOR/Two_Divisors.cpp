/*
 * Problem: Given the two largest proper divisors a and b (a < b < x) of
 * some unknown integer x, find x.
 *
 * Intuition:
 * - The largest divisor of x (other than itself) is x / p, where p is
 *   the smallest prime factor of x.  So b = x / p.
 * - The second largest divisor a = x / q, where q is the next factor
 *   (could be p again for a prime power, or a different prime).
 *
 * Two cases:
 *
 * 1) x has at least two distinct prime factors  (e.g. x = p^e * q^f * ...)
 *    Then b = x/p, a = x/q, and since p,q are coprime,
 *    lcm(a,b) = lcm(x/p, x/q) = x.  So output L = lcm(a,b) = x.
 *
 * 2) x is a prime power (x = p^k), or more generally a divides b:
 *    Then lcm(a,b) = b.  Here b/a = p (the smallest prime factor),
 *    so x = b * (b/a) = b * p = p^k.
 *    This also covers mixed cases like x = p^2 * q where q > p^2
 *    (e.g. x = 28 = 2^2 * 7: divisors are 1,2,4,7,14,28; a=7,b=14;
 *     a|b, b/a=2=p, 14*2=28=x).
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        ll a, b; // two largest divisors of x
        cin >> a >> b;

        ll L = lcm(a, b); // if x has >= 2 distinct primes, L = x

        // If a | b (i.e. lcm = b), x is a prime power (or a special
        // mixed case like p^2 * q with q > p^2) → recover x = b * (b/a).
        // Otherwise, x = lcm(a, b).
        // also can write
        /*
    if (b % a == 0)
        cout << b * (b / a);
    else
        cout << lcm(a, b);*/
        if (L == b)
            cout << b * (b / a) << '\n';
        else
            cout << L << '\n';
    }

    return 0;
}