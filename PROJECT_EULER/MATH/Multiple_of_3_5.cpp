#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
For each test case, you are given a number n.
You have to find the sum of all natural numbers less than n
that are multiples of 3 or 5.

Constraints:
- 1 <= T <= 10^5
- 1 <= N <= 10^9

Important detail:
- We need numbers strictly less than n, not less than or equal to n.
- That is why the formula uses (n - 1).

Example:
If n = 10
Numbers less than 10 are: 1, 2, 3, 4, 5, 6, 7, 8, 9
Multiples of 3 or 5 are: 3, 5, 6, 9
Answer = 3 + 5 + 6 + 9 = 23

Constraint intuition:
- t can be very large, so using a loop from 1 to n for every test case would be too slow.
- We need a mathematical formula that gives the sum in constant time.

Main intuition of this code:
- First find the sum of multiples of 3 below n.
- Then find the sum of multiples of 5 below n.
- But multiples of 15 are counted in both sums, so subtract them once.
- This is the inclusion-exclusion principle.

How the formula works:
- Multiples of k below n are:
  k, 2k, 3k, ..., mk
- Here m = (n - 1) / k, which tells how many multiples of k are below n.
- Their sum is:
  k * (1 + 2 + 3 + ... + m)
- And:
  1 + 2 + 3 + ... + m = m * (m + 1) / 2
- So final sum becomes:
  k * m * (m + 1) / 2
*/
long long solve(int n, int k) {
    // m = count of multiples of k that are strictly less than n.
    long long m = (n - 1) / k;

    // Sum of k + 2k + 3k + ... + mk.
    return (k * m * (m + 1)) / 2;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        // Add multiples of 3 and 5, then subtract multiples of 15 counted twice.
        long long sum = solve(n, 3) + solve(n, 5) - solve(n, 15);

        cout << sum << endl;
    }
    return 0;
}
