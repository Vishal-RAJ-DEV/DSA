#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
For each test case, you are given a number n.
You have to find the largest prime factor of n.

Constraints:
- 1 <= T <= 10
- 10 <= N <= 10^12

What is a prime factor?
- A factor of n is a number that divides n exactly.
- A prime factor is a factor that is also a prime number.

Example:
n = 12
factors of 12 are 1, 2, 3, 4, 6, 12
prime factors are 2 and 3
largest prime factor is 3

Constraint intuition:
- n can be very large, so checking every number from 1 to n is too slow.
- A better idea is to try dividing n by small factors and remove them completely.
- We only need to check factors up to sqrt(n), because if n has a factor bigger than sqrt(n),
  then the matching pair factor must be smaller than sqrt(n).

Main intuition of this code:
- Start checking from the smallest prime factor, 2.
- If i divides n, then i is a factor.
- Keep dividing n by i until i no longer divides it.
- This removes all copies of that prime factor from n.
- The last factor removed during the process helps us track the largest prime factor.

Why does this work?
- When smaller factors are removed, the remaining n becomes smaller.
- After the loop, if n is still greater than 1, then that remaining n itself must be a prime factor,
  and it will be larger than every factor we already removed.
*/
long long solve(long n) {
    // largest stores the largest prime factor found so far.
    long long largest = LLONG_MIN;

    /*
    We test possible factors from 2 onward.
    Condition i * i <= n means we only check up to sqrt(n).
    */
    for (long long i = 2; i * i <= n; i++) {

        /*
        If i divides n, then i is a prime factor candidate.
        Keep dividing until all occurrences of i are removed.

        Example:
        n = 72, i = 2
        72 -> 36 -> 18 -> 9
        This means 2 was a prime factor and has been fully removed.
        */
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    /*
    If n is still greater than 1 here, then n itself is prime.

    Why?
    Because all smaller factors were already removed in the loop.
    So the leftover value cannot be broken into smaller unchecked factors.

    Example:
    n = 21
    divide by 3 => n becomes 7
    loop ends, and 7 is the largest prime factor.
    */
    if (n > 1) largest = n;

    return largest;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        long n;
        cin >> n;

        long long primefactor = solve(n);

        cout << primefactor << endl;
    }
    return 0;
}
