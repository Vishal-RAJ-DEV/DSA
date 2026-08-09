#include <bits/stdc++.h>
using namespace std;
/*
============================================================
PROBLEM: Partition Array for Maximum Sum
============================================================

Given an array and an integer k:

- Partition the array into contiguous groups.
- Each group can have length at most k.
- For every group:
      contribution = maximum_element_in_group * group_length
- We need the maximum possible total sum.

Example:
arr = [1, 15, 7, 9, 2, 5, 10], k = 3

One optimal partition is:

    [1, 15, 7] | [9] | [2, 5, 10]

For [1, 15, 7]:
    max = 15
    length = 3
    contribution = 15 * 3 = 45

For [9]:
    max = 9
    length = 1
    contribution = 9

For [2, 5, 10]:
    max = 10
    length = 3
    contribution = 30

Total = 45 + 9 + 30 = 84


============================================================
IMPORTANT IDEA: WHERE DOES PARTITIONING HAPPEN?
============================================================

We DON'T actually create/store partitions.

Suppose we are at index i.

We try:

    length = 1
    length = 2
    length = 3
    ...
    length = k

For example, at i = 0 and k = 3:

    length = 1:
        [1]

    length = 2:
        [1, 15]

    length = 3:
        [1, 15, 7]

Each choice represents a possible place where we make
the FIRST partition.

For example:

    [1, 15, 7] | remaining array

means the partition is made after index 2.

Then we solve the remaining array recursively / using DP.


============================================================
DP STATE
============================================================

dp[i] / helper(i) means:

    "What is the maximum sum we can obtain
     from index i until the end?"

So:

    dp[0] = answer for the entire array

    dp[3] = best answer for:
            [9, 2, 5, 10]

    dp[4] = best answer for:
            [2, 5, 10]

This is why we don't need to remember the actual partitions.


============================================================
HOW DO WE CALCULATE A PARTITION?
============================================================

While increasing length:

    maxElem = max(maxElem, arr[i + length - 1])

This continuously maintains the maximum element
of the current partition.

Example:

arr = [1, 15, 7]
i = 0

length = 1:
    partition = [1]
    maxElem = 1
    contribution = 1 * 1

length = 2:
    partition = [1, 15]
    maxElem = 15
    contribution = 15 * 2

length = 3:
    partition = [1, 15, 7]
    maxElem = 15
    contribution = 15 * 3


============================================================
MEMOIZATION LOGIC
============================================================

helper(i) tries every possible first partition.

For every partition:

    current sum =
        maximum of current partition * its length
        +
        best answer for remaining array

Formula:

    helper(i) =
        max over length 1...k of
        (maxElem * length + helper(i + length))


============================================================
TABULATION LOGIC
============================================================

Tabulation does exactly the same thing as memoization,
but instead of recursion, we calculate dp[] iteratively.

Meaning:

    dp[i] = best answer from index i to n-1

Since dp[i] depends on:

    dp[i + length]

we calculate from RIGHT TO LEFT.

Therefore:

    i = n-1
    i = n-2
    ...
    i = 0

Example:

For i = n-1:

    only one possible partition:
    [arr[n-1]]

So dp[n-1] is calculated first.

Then dp[n-2] can use dp[n-1].

Then dp[n-3] can use dp[n-2], dp[n-1], etc.

Finally:

    dp[0] = answer for the entire array.


============================================================
TIME AND SPACE COMPLEXITY
============================================================

There are n DP states.

For every state we try at most k partition lengths.

Time:
    O(n * k)

Space:
    O(n)

Memoization additionally uses recursion stack:
    O(n) worst case.


============================================================
*/



// ============================================================
// MEMOIZATION
// ============================================================

class Memoization {
private:

    // helper(start) = maximum sum obtainable
    // from index 'start' to the end.
    int helper(const vector<int>& arr, int k,
               int start, vector<int>& memo) {

        int n = arr.size();

        // No elements remaining.
        // Therefore, no more contribution.
        if (start == n)
            return 0;

        // Already calculated.
        if (memo[start] != -1)
            return memo[start];

        int maxSum = 0;
        int maxElem = 0;

        // Try every possible partition length.
        // This is where we conceptually make partitions.
        for (int length = 1;
             length <= k && start + length <= n;
             length++) {

            // Add the new element to the current partition
            // and update its maximum.
            maxElem = max(maxElem,
                          arr[start + length - 1]);

            // Current partition contribution:
            //
            // maximum element * length
            //
            // Then add the best answer for the remaining array.
            int currentSum =
                maxElem * length +
                helper(arr, k, start + length, memo);

            maxSum = max(maxSum, currentSum);
        }

        // Store answer for this starting index.
        return memo[start] = maxSum;
    }

public:

    int maxSumAfterPartitioning(vector<int>& arr, int k) {

        int n = arr.size();

        vector<int> memo(n, -1);

        return helper(arr, k, 0, memo);
    }
};


// ============================================================
// TABULATION
// ============================================================

class Tabulation {
public:

    int maxSumAfterPartitioning(vector<int>& arr, int k) {

        int n = arr.size();

        /*
        dp[i] = maximum sum obtainable from index i
                until the end.

        dp[n] = 0

        Because there are no elements after index n.
        */

        vector<int> dp(n + 1, 0);

        /*
        We calculate from RIGHT -> LEFT.

        Why?

        dp[i] depends on:

            dp[i + 1]
            dp[i + 2]
            ...
            dp[i + k]

        Therefore those states must already be calculated.
        */

        for (int i = n - 1; i >= 0; i--) {

            int maxElem = 0;
            int maxSum = 0;

            /*
            Try every possible partition starting at i.

            length = 1:

                [arr[i]] | remaining

            length = 2:

                [arr[i], arr[i+1]] | remaining

            length = 3:

                [arr[i], arr[i+1], arr[i+2]] | remaining

            and so on up to k.
            */

            for (int length = 1;
                 length <= k && i + length <= n;
                 length++) {

                /*
                Expand the current partition by one element.

                Example:

                [1]
                [1,15]
                [1,15,7]

                maxElem becomes:

                1 -> 15 -> 15
                */

                maxElem = max(
                    maxElem,
                    arr[i + length - 1]
                );

                /*
                Current partition:

                    maxElem * length

                Remaining array:

                    dp[i + length]

                Therefore:

                    currentSum =
                        maxElem * length
                        + dp[i + length]
                */

                int currentSum =
                    maxElem * length +
                    dp[i + length];

                // Choose the best partition.
                maxSum = max(maxSum, currentSum);
            }

            // Store the best answer for this starting index.
            dp[i] = maxSum;
        }

        /*
        dp[0] represents the best answer
        for the complete array.
        */

        return dp[0];
    }
};

// The most important thing to remember
// The partition is happening conceptually inside this loop:
// for (int length = 1; length <= k; length++)

// For i = 0:

// length = 1    → [1] | [15,7,9,2,5,10]
// length = 2    → [1,15] | [7,9,2,5,10]
// length = 3    → [1,15,7] | [9,2,5,10]

// We don't actually split the vector. We simply calculate the score for each possible split and let DP choose the best one.

// The core formula is:
// dp[i] = max(
//     maxElement(i...i+length-1) * length
//     + dp[i+length]
// )
// for length = 1 ... k.
int main() {

    vector<int> arr = {
        1, 15, 7, 9, 2, 5, 10
    };

    int k = 3;

    Tabulation tab;

    cout << "Maximum sum after partitioning: "
         << tab.maxSumAfterPartitioning(arr, k)
         << "\n";

    return 0;
}