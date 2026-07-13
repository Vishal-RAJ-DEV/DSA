#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
? PROBLEM: Print all divisors of a given integer N.
?
? A divisor (or factor) of N is a positive integer that divides N
? completely (remainder = 0).
?
? EXAMPLE: N = 36
?   Divisors: 1, 2, 3, 4, 6, 9, 12, 18, 36
?
?
? INTUITION — Divisor pairs & the sqrt(n) trick:
?   Divisors always come in pairs: if i divides N, then N/i also divides N.
?   e.g. 3 × 12 = 36 → both 3 and 12 are divisors.
?
?   The two numbers in a pair meet at the square root:
?     i ≤ sqrt(N) ≤ N/i
?
?   So we only need to check i from 1 to sqrt(N) (i.e. while i*i ≤ N).
?   For each i that divides N:
?     - Add i
?     - Add N/i  (unless i == N/i, i.e. the perfect square case)
?
?   This reduces O(N) → O(√N).
?
?
? WHY STOP WHEN i*i > n?
?
?   Key observation: divisors come in pairs (d, n/d).
?   The smaller divisor d always satisfies d ≤ √n.
?   The larger divisor n/d always satisfies n/d ≥ √n.
?
?   If i*i > n, then i > √n.  At this point:
?     - Every divisor pair (d, n/d) has already been discovered
?       when checking the smaller half (d ≤ √n).
?     - The larger half was added via n/i in the inner condition.
?     - Checking beyond √n would only rediscover the same pairs
?       in reverse order — wasted work.
?
?   Example with n = 36:
?     i = 1 → pair (1, 36)   added
?     i = 2 → pair (2, 18)   added
?     i = 3 → pair (3, 12)   added
?     i = 4 → pair (4, 9)    added
?     i = 5 → 5 ∤ 36         skip
?     i = 6 → pair (6, 6)    added (i == n/i, so only once)
?     i = 7 → 7*7 = 49 > 36  STOP
?
?   If we continued to i = 9, we'd find 9|36 and add (9, 4) —
?   but 4 and 9 were already added from i=4. Just duplicate work.
*/

void printdivisor(int n) {
    vector<int> list;

    // Only go up to sqrt(n). i*i <= n  ⇔  i <= sqrt(n)
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {           // i divides n → i is a divisor
            list.push_back(i);      // add the smaller divisor

            // Add the paired larger divisor, unless it's the same
            // (i == n/i happens for perfect squares like 36 → i=6)
            if ((n / i) != i) {
                list.push_back(n / i);
            }
        }
    }

    // Sort because we collected unordered pairs
    sort(list.begin(), list.end());

    cout << "Divisors of " << n << ":" << endl;
    for (auto it : list) cout << it << "\t";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter your number: ";
    cin >> n;
    printdivisor(n);
    return 0;
}
