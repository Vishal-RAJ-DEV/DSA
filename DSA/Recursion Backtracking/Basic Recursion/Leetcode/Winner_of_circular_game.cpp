#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
              WINNER OF CIRCULAR GAME - JOSEPHUS PROBLEM
================================================================================

PROBLEM:
  n friends stand in a circle. Starting from friend 1, we count k friends
  clockwise. The k-th friend is eliminated. The next friend after the
  eliminated one starts counting again. This repeats until 1 friend remains.
  Return the 1-indexed position of the winner.

EXAMPLE: n=5, k=2
  Circle: 1 2 3 4 5
  Round 1: count 2 from 1 -> eliminate 2   -> [1, 3, 4, 5]
  Round 2: count 2 from 3 -> eliminate 4   -> [1, 3, 5]
  Round 3: count 2 from 5 -> eliminate 1   -> [3, 5]
  Round 4: count 2 from 3 -> eliminate 5   -> [3]
  Winner: 3

================================================================================
          APPROACH 1: ITERATIVE JOSEPHUS FORMULA  (lines below)
================================================================================

MATHEMATICAL FORMULA:
  f(1, k) = 0                          (base case: with 1 person, index 0 wins)
  f(n, k) = (f(n-1, k) + k) % n       (recursive relation)

WHY THIS FORMULA WORKS:
  When we eliminate one person from a circle of n people, the problem reduces
  to a circle of n-1 people. The key insight is that after removing one person,
  the "starting point" for the next round shifts by k positions. The modulo
  operation wraps around the circle.

  Think of it as: if we know the winner's position in a circle of (n-1) people
  (0-indexed), then in a circle of n people, that winner is shifted k positions
  ahead because k people were counted before elimination.

ITERATIVE BUILDUP (bottom-up):
  We start with the base case f(1,k) = 0 and iteratively compute f(2,k),
  f(3,k), ..., f(n,k) using the formula.

  Example trace: n=5, k=2

  i=2: ans = (0 + 2) % 2 = 0       // f(2,2) = 0  (0-indexed: winner at index 0)
  i=3: ans = (0 + 2) % 3 = 2       // f(3,2) = 2  (0-indexed: winner at index 2)
  i=4: ans = (2 + 2) % 4 = 0       // f(4,2) = 0  (0-indexed: winner at index 0)
  i=5: ans = (0 + 2) % 5 = 2       // f(5,2) = 2  (0-indexed: winner at index 2)

  Final: ans + 1 = 2 + 1 = 3       // convert to 1-indexed

VISUAL TRACE of the formula building up:
  -----------------------------------------------------------------------
  i=2 (2 people in circle, 0-indexed positions: 0,1)
    Previous winner (from i=1) was at index 0.
    After eliminating one person from 2, we add k=2 and mod by 2.
    New winner index = (0 + 2) % 2 = 0
    Meaning: in a circle of 2, the person at index 0 survives.

  i=3 (3 people, 0-indexed: 0,1,2)
    Previous winner (from i=2) was at index 0.
    New winner index = (0 + 2) % 3 = 2
    Meaning: in a circle of 3, the person at index 2 survives.

  i=4 (4 people, 0-indexed: 0,1,2,3)
    Previous winner (from i=3) was at index 2.
    New winner index = (2 + 2) % 4 = 0
    Meaning: in a circle of 4, the person at index 0 survives.

  i=5 (5 people, 0-indexed: 0,1,2,3,4)
    Previous winner (from i=4) was at index 0.
    New winner index = (0 + 2) % 5 = 2
    Meaning: in a circle of 5, the person at index 2 survives.
  -----------------------------------------------------------------------
  Final answer (1-indexed) = 2 + 1 = 3

COMPLEXITY: Time O(n), Space O(1)
  - Single loop from 2 to n, constant work per iteration.
  - No extra memory beyond a few variables.
================================================================================
*/

class Solution {
public:
    int findTheWinner(int n, int k) {
        // ans = 0 represents the winner's 0-indexed position when there is
        // only 1 person in the circle (base case f(1, k) = 0).
        //
        // We iteratively build up from 2 people to n people.
        // At each step i, we are computing f(i, k) = (f(i-1, k) + k) % i.
        //
        // WHY start from i=2:
        //   - i=1 is already handled by ans=0 (base case).
        //   - We need to compute f(2,k), f(3,k), ..., f(n,k) in order.
        //
        // WHY (ans + k) % i:
        //   - ans is the winner's index in a circle of (i-1) people.
        //   - When we add one more person (going from i-1 to i people),
        //     the elimination order shifts by k positions.
        //   - % i wraps around the circle (indices go from 0 to i-1).
        int ans = 0;

        for (int i = 2; i <= n; i++) {
            // Formula: f(i, k) = (f(i-1, k) + k) % i
            // ans currently holds f(i-1, k), update it to f(i, k)
            ans = (ans + k) % i;
        }

        // ans is 0-indexed. Convert to 1-indexed for the final answer.
        return ans + 1;
    }
};

/*
================================================================================
          APPROACH 2: RECURSIVE JOSEPHUS FORMULA  (lines below)
================================================================================

This is the direct recursive translation of the same mathematical formula.

RECURSION TREE for n=5, k=2:

  solve(5, 2)
  = (solve(4, 2) + 2) % 5
  |
  +-- solve(4, 2)
      = (solve(3, 2) + 2) % 4
      |
      +-- solve(3, 2)
          = (solve(2, 2) + 2) % 3
          |
          +-- solve(2, 2)
              = (solve(1, 2) + 2) % 2
              |
              +-- solve(1, 2)
                  = 0    <-- BASE CASE (n==1, return 0)

  UNWINDING THE STACK (computing values bottom-up):

  solve(1, 2) = 0                          (base case)
  solve(2, 2) = (0 + 2) % 2 = 0
  solve(3, 2) = (0 + 2) % 3 = 2
  solve(4, 2) = (2 + 2) % 4 = 0
  solve(5, 2) = (0 + 2) % 5 = 2

  Final answer = 2 + 1 = 3

STACK SPACE ANALYSIS:
  Maximum recursion depth = n (one call per person).
  For n=5: 5 stack frames alive at peak.
  Frame 5 (solve(5,2)) waits for Frame 4, which waits for Frame 3, etc.
  After reaching the base case, the stack unwinds and computes values.

  STACK AT PEAK (n=5):
  -------------------
  | solve(5,2) | waiting for solve(4,2)
  | solve(4,2) | waiting for solve(3,2)
  | solve(3,2) | waiting for solve(2,2)
  | solve(2,2) | waiting for solve(1,2)
  | solve(1,2) | BASE CASE, returns 0
  -------------------

  After base case returns, each frame computes and returns:
  Frame 4: (0+2)%2 = 0, pops
  Frame 3: (0+2)%3 = 2, pops
  Frame 2: (2+2)%4 = 0, pops
  Frame 1: (0+2)%5 = 2, pops

COMPARISON: ITERATIVE vs RECURSIVE
  -----------------------------------------------------------------------
  Aspect              | Iterative        | Recursive
  ------------------- | ---------------- | ---------------------------
  Time Complexity     | O(n)             | O(n)
  Space Complexity    | O(1)             | O(n) - recursion stack
  Risk                | None             | Stack overflow for large n
  Code clarity        | Compact          | Matches formula directly
  -----------------------------------------------------------------------

  Both produce the SAME answer because they use the SAME formula.
  The iterative version builds bottom-up (like filling a table).
  The recursive version goes top-down then unwinds (like a DFS).
================================================================================
*/

class SolutionRecursive {
public:
    // Recursive helper that computes the 0-indexed winner position.
    //
    // PARAMETER MEANING:
    //   n = current number of people in the circle
    //   k = step count (every k-th person is eliminated)
    //
    // RETURNS: 0-indexed position of the winner among n people.
    //
    // FORMULA: f(n, k) = (f(n-1, k) + k) % n
    // BASE CASE: f(1, k) = 0
    int solve(int n, int k) {
        // Base case: when there's only 1 person left, they are the winner.
        // Their 0-indexed position is always 0 (only person in the circle).
        if (n == 1)
            return 0;

        // Recursive case:
        //   - solve(n-1, k) gives us the winner's index in a circle of (n-1) people.
        //   - Adding k accounts for the shift in starting position after one elimination.
        //   - % n wraps around the circle.
        //
        // Visual: imagine we removed one person. The circle now has n-1 people.
        // The winner from that smaller circle is at index solve(n-1, k).
        // But in the ORIGINAL circle of n people, that position is shifted by k.
        // So the winner in the original circle = (solve(n-1, k) + k) % n.
        return (solve(n - 1, k) + k) % n;
    }

    int findTheWinner(int n, int k) {
        // solve(n, k) returns 0-indexed. Add 1 for 1-indexed answer.
        return solve(n, k) + 1;
    }
};

/*
================================================================================
                            VERIFICATION EXAMPLE
================================================================================

n=6, k=2  (simulate manually)

  Circle: 1 2 3 4 5 6
  Elimination order:
    Round 1: start at 1, count 2 -> eliminate 2  -> [1,3,4,5,6]
    Round 2: start at 3, count 2 -> eliminate 4  -> [1,3,5,6]
    Round 3: start at 5, count 2 -> eliminate 6  -> [1,3,5]
    Round 4: start at 1, count 2 -> eliminate 3  -> [1,5]
    Round 5: start at 5, count 2 -> eliminate 1  -> [5]
    Winner: 5

  Formula check:
    f(1,2) = 0
    f(2,2) = (0+2)%2 = 0
    f(3,2) = (0+2)%3 = 2
    f(4,2) = (2+2)%4 = 0
    f(5,2) = (0+2)%5 = 2
    f(6,2) = (2+2)%6 = 4

    Answer = 4 + 1 = 5  ✓  (matches manual simulation!)
================================================================================
*/

int main(){
    return 0;
}