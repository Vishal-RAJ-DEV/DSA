/*
 * ================================================================
 *  PROBLEM: Exciting Bets (Codeforces 1543A)
 * ================================================================
 *
 *  QUESTION:
 *  ---------
 *  Given two integers a and b. In one move, you can:
 *    - Increase both a and b by 1, OR
 *    - Decrease both a and b by 1 (they must stay non-negative).
 *
 *  Find the MAXIMUM possible GCD(a, b) you can achieve, and the
 *  MINIMUM number of moves required to reach that GCD.
 *
 *  If there is no limit (GCD can be arbitrarily large), output "0 0".
 *
 *  Example:
 *    a = 8, b = 3
 *    Output: 5 1
 *    Explanation:
 *      - |8-3| = 5, so max GCD = 5.
 *      - To make both divisible by 5: add 2 → (10,5) or subtract 1 → (7,2) ... actually:
 *        a % 5 = 3 → prev multiple at 3 (dist=3), next multiple at 8 (dist=2).
 *        Min moves = min(3, 5-3) = 2. So output: 5 2.
 *      Wait, let me recheck: 8 % 5 = 3, prev multiple = 5 (dist 3), next = 10 (dist 2) → min=2.
 *      Let me verify: (8+2, 3+2) = (10,5), gcd=5. Yes, 2 moves to increase.
 *      Or (8-1, 3-1) = (7,2), gcd=1 — not good.
 *      So min moves = 2.
 *
 *  INTUITION:
 *  ----------
 *  KEY OBSERVATION: Any common divisor of two numbers MUST divide
 *  their difference.
 *
 *  Proof: If d | a and d | b, then d | (a - b).
 *
 *  Therefore, no matter what operations we perform, the GCD can NEVER
 *  exceed |a - b| because:
 *    - Let d = gcd(a + k, b + k) after k moves.
 *    - d | (a + k) - (b + k) = a - b.
 *    - So d ≤ |a - b|.
 *
 *  And we CAN achieve GCD = |a - b| by making both numbers divisible
 *  by |a - b|. Since the difference is exactly |a - b|, making ONE
 *  number divisible by |a - b| automatically makes the other divisible
 *  too (because if g | (a + k) and g | (a - b), then g | (a + k) - (a - b) = b + k).
 *
 *  So:
 *    1. If a == b → |a - b| = 0 → GCD can be arbitrarily large → "0 0"
 *    2. Otherwise:
 *         g = |a - b| is the maximum achievable GCD.
 *         We need the min moves to make one number a multiple of g.
 *
 *  MINIMUM MOVES:
 *  --------------
 *  Let g = |a - b|.
 *  We need to find the smallest k ≥ 0 such that g divides (a + k)
 *  OR g divides (a - k) (keeping a - k ≥ 0).
 *
 *  a % g gives the remainder when a is divided by g:
 *    - a % g is the distance from a DOWN to the previous multiple of g
 *    - g - (a % g) is the distance from a UP to the next multiple of g
 *
 *  The minimum of these two is the minimum moves.
 *  (Provided a - (a % g) ≥ 0, which it always is since a % g ≤ a.)
 *
 *  ALGORITHM:
 *  ----------
 *  1. Read a, b.
 *  2. Compute g = |a - b|.
 *  3. If g == 0 (a == b):
 *       Print "0 0" → infinite GCD, 0 moves.
 *  4. Else:
 *       moves_prev = a % g          (distance down to prev multiple)
 *       moves_next = g - (a % g)    (distance up to next multiple)
 *       minMoves = min(moves_prev, moves_next)
 *       Print g, minMoves.
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(1) per test case
 *  Space → O(1)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;              // number of test cases
    cin >> t;

    while (t--) {
        long long a, b; // the two input numbers
        cin >> a >> b;

        /*
         * g = |a - b| is the UPPER BOUND for any achievable GCD.
         * Proof: Any common divisor d of (a+k) and (b+k) must divide
         * their difference: (a+k) - (b+k) = a - b. So d ≤ |a - b|.
         * And this bound IS achievable (by making both numbers divisible
         * by |a - b|).
         */
        long long g = abs(a - b);

        /*
         * If a == b, their difference is 0.
         * Any positive integer divides 0, so the GCD can be made
         * arbitrarily large. The problem specifies "0 0" for this case.
         */
        if (g == 0) {
            cout << 0 << " " << 0 << endl;
            continue;
        }

        /*
         * To achieve GCD = g, we need both numbers to be divisible by g.
         * Since a - b = g, making ONE number divisible by g automatically
         * makes the other divisible as well:
         *   If g | (a + k) and g | (a - b), then g | (a + k) - (a - b) = b + k.
         *
         * So we just need to find the minimum k to make 'a' divisible by g.
         *
         *   a % g  → distance DOWN to the previous multiple of g
         *   g - (a % g) → distance UP to the next multiple of g
         *
         * The smaller of these two is the minimum moves.
         */
        long long downMoves = a % g;        // move DOWN by this amount
        long long upMoves = g - downMoves;  // move UP by this amount
        long long minMoves = min(downMoves, upMoves);

        cout << g << " " << minMoves << endl;
    }

    return 0;
}
