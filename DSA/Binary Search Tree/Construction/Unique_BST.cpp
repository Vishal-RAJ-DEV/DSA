/*
Problem: LeetCode 96 - Unique Binary Search Trees
Given an integer n, return the number of structurally unique BST's
(binary search trees) which have exactly n nodes with values 1 to n.

Key insight (Catalan Number):
For a given root i, the left subtree uses nodes [1..i-1] (i-1 nodes)
and the right subtree uses nodes [i+1..n] (n-i nodes).
So total BSTs with root i = BSTs(i-1) * BSTs(n-i).

Recurrence: G(n) = sum_{i=1}^{n} G(i-1) * G(n-i),  G(0) = G(1) = 1
This is the Catalan number C_n = (2n)! / ((n+1)! * n!)

The file contains THREE different approaches.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Top-down DP (Memoized Recursion)
Algorithm:
- Recurrence: Catalan(n) = sum_{i=1}^{n} Catalan(i-1) * Catalan(n-i)
- Base cases: Catalan(0) = Catalan(1) = 1
- For each root position i (1..n):
    leftSubTrees = solve(i-1)   → nodes smaller than root
    rightSubTrees = solve(n-i)  → nodes larger than root
    ans += leftSubTrees * rightSubTrees (Cartesian product)
- Memoize results in dp[] to avoid recomputation.

Why this works:
When we pick root = i, the left subtree must contain {1..i-1}
and right subtree must contain {i+1..n}. Since all values are
distinct and ordered, the structure only depends on COUNT,
not actual values. So left = solve(i-1), right = solve(n-i).

Time: O(n^2) — n choices for root, each does O(n) work across all calls
Space: O(n) — dp array + recursion stack
*/
class SolutionMemo {
public:
    vector<int> dp;

    int solve(int n) {
        if (n <= 1) return 1;
        if (dp[n] != -1) return dp[n];

        int ans = 0;

        // Try each node from 1..n as the root
        for (int root = 1; root <= n; root++) {
            int left = solve(root - 1);
            int right = solve(n - root);
            ans += left * right;
        }

        return dp[n] = ans;
    }

    int numTrees(int n) {
        dp.resize(n + 1, -1);
        return solve(n);
    }
};

/*
Approach 2: Bottom-up DP (Tabulation)
Algorithm:
- dp[i] = number of unique BSTs with exactly i nodes
- Base: dp[0] = dp[1] = 1
- For nodes = 2 .. n:
    For root = 1 .. nodes:
        left = root - 1      // nodes in left subtree
        right = nodes - root // nodes in right subtree
        dp[nodes] += dp[left] * dp[right]

Same recurrence as Approach 1 but computed iteratively
from bottom up. No recursion overhead.

Time: O(n^2)
Space: O(n)
*/
class SolutionDP {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);

        dp[0] = 1;  // Empty tree
        dp[1] = 1;  // Single node

        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                int leftNodes = root - 1;
                int rightNodes = nodes - root;
                dp[nodes] += dp[leftNodes] * dp[rightNodes];
            }
        }

        return dp[n];
    }
};

/*
Approach 3: Catalan Number Formula (Mathematical)
The recurrence G(n) = sum G(i-1)*G(n-i) generates Catalan numbers.
The closed form is:
    C_n = (1 / (n+1)) * C(2n, n)
    where C(2n, n) = binomial(2n, n) = (2n)! / (n! * n!)

Algorithm:
- Compute binomial coefficient C(2n, n) iteratively:
    result = 1
    For i = 0 .. n-1:
        result = result * (2n - i) / (i + 1)
- Then Catalan = result / (n + 1)

Why this works:
The formula directly computes the n-th Catalan number
using the multiplicative formula for binomial coefficients.
This avoids O(n^2) DP and is O(n).

Time: O(n)
Space: O(1)
*/
class SolutionCatalan {
public:
    int numTrees(int n) {
        long long catalan = 1;

        // Compute binomial(2n, n) iteratively
        // catalan = product_{i=0}^{n-1} (2n - i) / (i + 1)
        for (int i = 0; i < n; i++) {
            catalan = catalan * (2LL * n - i) / (i + 1);
        }

        // Divide by (n+1) to get the Catalan number
        return catalan / (n + 1);
    }
};

/* Summary:
   Approach    | Technique       | Time    | Space
   ------------+-----------------+---------+------
   Memoization | Top-down DP     | O(n^2)  | O(n)
   Tabulation  | Bottom-up DP    | O(n^2)  | O(n)
   Catalan     | Math formula    | O(n)    | O(1)
*/

int main() {
    return 0;
}
