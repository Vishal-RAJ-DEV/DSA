#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
For each test case, you are given a number n.
You have to find the sum of all even Fibonacci numbers that are less than or equal to n.

Constraints:
- 1 <= T <= 10
- 10 <= N <= 10^12

Input format:
- The first input is t, the number of test cases.
- For each test case, one number n is given.

What is the Fibonacci sequence?
- It starts as: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 ...
- Every next term is the sum of the previous two terms.

Example:
If n = 10
Fibonacci numbers up to 10 are: 0, 1, 1, 2, 3, 5, 8
Even Fibonacci numbers are: 2, 8
Answer = 2 + 8 = 10

Constraint intuition:
- t can contain multiple test cases, so the solution should be efficient for repeated queries.
- n can be large, so checking every number from 1 to n would be too slow.
- We only need to generate Fibonacci numbers until they become greater than n.
- This is efficient because Fibonacci numbers grow quickly.
- We do not need an array or extra storage for all terms.
- Keeping only the last two Fibonacci numbers is enough.

Main intuition of this code:
- Start from the first two Fibonacci values: 0 and 1.
- Generate the next Fibonacci term using:
  current = previous1 + previous2
- If the current Fibonacci number is even, add it to the answer.
- Stop when the Fibonacci number becomes greater than n.

Why does this work?
- The question only asks for Fibonacci terms up to n.
- So once a term becomes greater than n, no future term can be used.
- Since each Fibonacci term depends only on the previous two terms,
  we only track two variables instead of storing the whole sequence.
*/
long long solve(long n) {
    // If n is 0 or 1, there is no positive even Fibonacci number to add.
    if (n == 0 || n == 1) return 0;

    // sum stores the sum of even Fibonacci numbers found so far.
    long long sum = 0;

    // prev2 = 0, prev1 = 1 are the starting Fibonacci values.
    long long prev1 = 1;
    long long prev2 = 0;

    while (true) {
        // Generate the next Fibonacci number.
        long long curr = prev1 + prev2;

        // Stop once the Fibonacci term goes beyond the allowed limit n.
        if (curr > n) break;

        // Only even Fibonacci terms are included in the sum.
        if (curr % 2 == 0) sum += curr;

        /*
        Shift the two previous values forward.
        Example:
        if prev2 = 2 and prev1 = 3, then curr = 5
        for the next step we want the pair to become 3 and 5
        */
        prev2 = prev1;
        prev1 = curr;
    }

    return sum;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        long n;
        cin >> n;

        long long fib = solve(n);

        cout << fib << endl;
    }
    return 0;
}
