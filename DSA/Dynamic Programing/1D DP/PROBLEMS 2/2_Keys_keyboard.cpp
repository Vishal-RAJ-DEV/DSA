#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
   QUESTION EXPLAINED : 2 KEYS KEYBOARD (LeetCode 650)
   ----------------------------------------------------------------------------
   Problem Statement:
     You start with ONE character 'A' on screen (count = 1).
     You have only 2 operations:
       1. Copy All  -> copy everything currently on screen into clipboard
                      (overwrites old clipboard).
       2. Paste     -> paste clipboard content, increasing screen count by
                      clipboard size.

     Given integer n, find MINIMUM number of operations (Copy + Paste steps)
     to get EXACTLY n 'A's on screen. You cannot do extra then delete.

   Examples:
     n = 1 -> 0 (already have 1 A, nothing to do)
     n = 3 -> 3 steps: (1)Copy [A], (2)Paste -> AA, (3)Paste -> AAA
     n = 4 -> 4 steps: Copy, Paste -> AA, Copy, Paste -> AAAA
              (making 2 then doubling is optimal here)
     n = 9 -> 6 steps: make AAA in 3 steps, then Copy(1)+Paste(1)+Paste(1)=3
              more -> total 6. Better than 9 times paste one by one.

   Key Observation (why divisors matter):
     Suppose screen has `d` chars and clipboard also somehow leads us to `n`.
     The ONLY way to grow from d to n using Copy/Paste is:
       - clipboard must hold exactly d (so Copy once when screen = d)
       - then Paste (n/d - 1) times, each adds d.
     So total extra cost after reaching d = 1 (Copy) + (n/d - 1) (Pastes)
                                            = n/d steps.
     And this is possible ONLY if n is a multiple of d (n % d == 0),
     otherwise you overshoot / never hit exactly n.

     Hence recurrence:
       f(1) = 0
       f(n) = min over all divisors d of n, d < n : f(d) + n/d
       Worst case d=1: f(n) <= f(1) + n/1 = n  (Copy once, Paste n-1 times).
       That is why code initializes ans = n.

   All 3 solutions below use this same idea, just implemented differently.
   ============================================================================ */


// ----------------------------------------------------------------------------
// APPROACH 1 : MEMOIZATION (Top-Down Recursion + DP)
// ----------------------------------------------------------------------------
// Logic / How this code works:
//   solve(n):
//     - Base: n==1 -> 0 steps.
//     - If dp[n] already computed, return it (avoid recomputation).
//     - Assume worst answer = n (make 1 -> n by 1 Copy + (n-1) Pastes).
//     - Try EVERY d from 1 to n-1:
//         if n % d == 0 (d can grow to n exactly):
//            candidate = solve(d) + n/d
//            // solve(d) = best way to build d from 1
//            // n/d     = 1 Copy at d + (n/d - 1) Pastes to reach n
//         keep minimum candidate.
//     - Store in dp[n] and return.
//
//   minSteps(n) creates dp array of size n+1 filled with -1 and calls solve(n).
//
// Example trace n=6, divisors d = 1,2,3:
//   d=1 -> solve(1)+6 = 0+6 = 6
//   d=2 -> solve(2)+3 ; solve(2)= solve(1)+2 = 2 -> total 2+3 = 5
//   d=3 -> solve(3)+2 ; solve(3)= solve(1)+3 = 3 -> total 3+2 = 5
//   answer = 5 (which equals 2+3, prime factors of 6).
//
// Time  : O(n^2) in this naive loop version (for each n, scan all d < n,
//         each solve(d) again scans). Can be optimized to O(n*sqrt(n)) by
//         checking divisors only, but this form is kept for teaching.
// Space : O(n) dp array + O(n) recursion stack worst case.
class SolutionMemo {
public:
    int solve(int n, vector<int>& dp) {
        if (n == 1) return 0; // base: 1 A needs 0 steps

        if (dp[n] != -1) return dp[n]; // memoized -> reuse

        int ans = n; // Worst case: Copy + Paste n-1 times

        for (int d = 1; d < n; d++) {
            if (n % d == 0) {
                // Build d first, then 1 Copy + (n/d - 1) Pastes = n/d steps
                ans = min(ans, solve(d, dp) + n / d);
            }
        }

        return dp[n] = ans;
    }

    int minSteps(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};


// ----------------------------------------------------------------------------
// APPROACH 2 : TABULATION (Bottom-Up 1D DP)
// ----------------------------------------------------------------------------
// Logic / How this code works:
//   Same recurrence as above, but built iteratively small -> large:
//     dp[1] = 0
//     for i = 2..n:
//       dp[i] = i (worst case)
//       for d = 1..i-1:
//         if i % d == 0:
//           dp[i] = min(dp[i], dp[d] + i/d)
//   When computing dp[i], all dp[d] for d < i are already known, so no
//   recursion is needed.
//
// Example n=9:
//   dp[1]=0
//   dp[2]=2, dp[3]=3,
//   dp[6]: divisors 1,2,3 -> min(6, 2+3=5, 3+2=5) = 5
//   dp[9]: divisors 1,3 -> min(9, 3+3=6) = 6 -> answer 6.
//
// Time  : O(n^2) (nested loops i and d).
// Space : O(n) for dp array, O(1) extra (no recursion stack).
// Use when you want to avoid recursion depth issues.
class SolutionTab {
public:
    int minSteps(int n) {
        if (n == 1) return 0;

        vector<int> dp(n + 1, 0);
        // dp[0], dp[1] stay 0; we fill from 2 upwards

        for (int i = 2; i <= n; i++) {
            dp[i] = i; // worst case: from 1 via Copy+Paste

            for (int d = 1; d < i; d++) {
                if (i % d == 0) {
                    // reach d first (dp[d]), then jump d -> i in i/d moves
                    dp[i] = min(dp[i], dp[d] + i / d);
                }
            }
        }

        return dp[n];
    }
};


// ============================================================================
// APPROACH 3 : OPTIMAL SOLUTION - PRIME FACTORIZATION (Greedy / Math)
// Time O(sqrt(n)), Space O(1). This is the BEST solution.
// ============================================================================
// LOGIC OF THIS CODE - DETAILED EXPLANATION:
//
//   Claim: Answer = SUM OF PRIME FACTORS of n (with multiplicity).
//     n = 12 = 2*2*3 -> answer = 2+2+3 = 7
//     n = 9  = 3*3   -> answer = 3+3   = 6
//     n = 7 (prime)  -> answer = 7
//
//   WHY is this true? Step-by-step reasoning:
//
//   Step 1: Any sequence of Copy/Paste can be viewed as FACTORIZATION.
//     Suppose final n is built in k stages with batch sizes:
//       n = k1 * k2 * k3 * ... * km   (each ki >= 2 is one Copy+Paste batch)
//     Example n=12 built as: 1 -> 3 (cost 3) -> 6 (cost 2) -> 12 (cost 2)
//       factors: 3*2*2 = 12, total cost = 3+2+2 = 7.
//     Cost of a batch of size k = k steps (1 Copy + (k-1) Pastes).
//     Total cost = k1 + k2 + ... + km.
//
//   Step 2: Splitting a COMPOSITE batch is always cheaper (or equal).
//     A batch of size k = a*b (a,b > 1) costs k = a*b steps if done at once.
//     If split into two batches a then b, cost = a + b.
//     Since a*b >= a+b for all a,b >= 2 (e.g. 2*4=8 > 2+4=6),
//     splitting NEVER increases cost, always decreases (except 2*2 = 2+2 tie).
//     Therefore an OPTIMAL solution never contains a composite batch;
//     every batch must be PRIME.
//
//   Step 3: So optimal cost = break n into PRIME factors, sum them.
//     Any order of prime factors gives same sum, so just find them.
//
//   Step 4: How the code finds them (trial division):
//     for (d = 2; d*d <= n; d++):
//       while (n % d == 0):   // d is a prime factor, possibly repeated
//         ans += d;           // one batch of size d costs d steps
//         n /= d;             // shrink n, continue factoring remainder
//     After loop, if n > 1, remaining n itself is prime (e.g. n=7, or
//     leftover like 12 -> after removing 2*2, n=3 remains) so ans += n.
//
//   Example dry run n = 12:
//     d=2: 12%2==0 -> ans=2, n=6; 6%2==0 -> ans=4, n=3; 3%2!=0 stop.
//     d=3: 3*3=9 > 3? loop condition d*d<=n -> 3*3<=3 false, loop ends.
//     n=3 > 1 -> ans = 4+3 = 7. Correct.
//
//   Example n = 18 = 2*3*3:
//     d=2 -> ans=2, n=9. d=3 -> ans=2+3=5, n=3 -> ans=5+3=8, n=1.
//     leftover n=1, no addition. Answer 8.
//     Check DP: 1->2 (2), 2->6 (3), 6->18 (3) = 8. Matches.
//
//   Complexity:
//     Trial division up to sqrt(n): Time O(sqrt(n)), Space O(1).
//     Beats both DP versions (O(n^2) time, O(n) space) by far.
//
//   Edge case: n=1 -> loop never runs, n>1 false, ans=0. Correct.
// ============================================================================
class SolutionOptimal {
public:
    int minSteps(int n) {
        int ans = 0;

        // Try every possible divisor d starting from smallest prime 2.
        // d*d <= n (not d <= n) because a larger factor would have a
        // complementary smaller factor already tested. n shrinks as we divide.
        for (int d = 2; d * d <= n; d++) {
            // While d divides n, d is a prime-factor batch:
            // pay d steps (1 Copy + d-1 Pastes), then remove it from n.
            while (n % d == 0) {
                ans += d;
                n /= d;
            }
        }

        // If n > 1 here, the remainder is itself prime (largest prime factor).
        // Example: original n=7 prime -> loop does nothing, ans = 0+7 = 7.
        if (n > 1) {
            ans += n;
        }

        return ans;
    }
};



int main(){
    // Quick demo: n = 9 -> expected 6 (3+3), n = 12 -> expected 7 (2+2+3)
    SolutionMemo s1;
    SolutionTab s2;
    SolutionOptimal s3;
    cout << "Memo n=9: " << s1.minSteps(9) << "\n";     // 6
    cout << "Tab  n=9: " << s2.minSteps(9) << "\n";     // 6
    cout << "Optimal n=9: " << s3.minSteps(9) << "\n";  // 6
    cout << "Optimal n=12: " << s3.minSteps(12) << "\n";// 7
    return 0;
}
