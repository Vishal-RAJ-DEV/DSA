/*
================================================================================
                            PERMUTATION SEQUENCE
================================================================================

PROBLEM STATEMENT:
------------------
Given two integers n and k, return the k-th permutation sequence of numbers
from 1 to n. All permutations are considered in lexicographic (dictionary) order.

Example:
    Input: n = 3, k = 3
    All permutations in lexicographic order:
        1. "123"
        2. "132"
        3. "213"  <-- k=3, this is our answer
        4. "231"
        5. "312"
        6. "321"

    Output: "213"

================================================================================
                    SOLUTION 1: BRUTE FORCE (BACKTRACKING)
================================================================================

APPROACH:
---------
Generate all permutations in lexicographic order using backtracking and count
them one by one until we reach the k-th permutation.

ALGORITHM:
----------
1. Use a boolean array 'used[]' to track which numbers are already placed.
2. At each recursive call, try every unused number from 1 to n.
3. When a complete permutation is formed (length == n), increment counter.
4. If counter equals k, store the result and stop.
5. Backtrack by removing the last number and marking it as unused.

TIME COMPLEXITY:  O(n! * n)
    - We generate up to n! permutations
    - Each permutation takes O(n) time to build

SPACE COMPLEXITY: O(n)
    - For recursion stack and auxiliary arrays

WHEN TO USE:
------------
- When n is small (n <= 9)
- When you need a simple, easy-to-understand solution
- NOT recommended for large n due to exponential time

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution_BruteForce {
public:
    vector<bool> used;  // tracks which numbers (1..n) are already used in current permutation

    /*
        RECURSIVE FUNCTION TO GENERATE PERMUTIONS
        -------------------------------------------
        n       = total numbers (1 to n)
        k       = we want the k-th permutation
        cnt     = reference to counter, tracks how many permutations we've generated so far
        res     = reference to result string, stores the k-th permutation when found
        curr    = current permutation being built

        INTUITION:
        ----------
        - We build permutations one character at a time.
        - At each position, we try all unused numbers in increasing order
          (this ensures lexicographic order).
        - When we complete a permutation, we increment counter.
        - If counter == k, we've found our answer.
        - Once found, we stop all further recursion using early termination.
    */
    void solve(int n, int k, int &cnt, string &res, string &curr) {

        // BASE CASE: A complete permutation of length n is formed
        if (curr.size() == n) {
            cnt++;  // Count this permutation

            // If this is the k-th permutation, save it
            if (cnt == k) {
                res = curr;
            }

            return;  // Go back to try next possibility
        }

        // RECURSIVE CASE: Try every number from 1 to n
        for (int i = 1; i <= n; i++) {

            // Skip if number i is already used in current permutation
            if (used[i])
                continue;

            // CHOOSE: Add number i to current permutation and mark as used
            curr.push_back('0' + i);  // Convert int to char
            used[i] = true;

            // EXPLORE: Recurse to fill next position
            solve(n, k, cnt, res, curr);

            // EARLY TERMINATION: If answer found in deeper recursion, stop immediately
            if (!res.empty())
                return;

            // BACKTRACK: Remove number i and mark as unused to try next number
            curr.pop_back();
            used[i] = false;
        }
    }

    /*
        MAIN FUNCTION: getPermutation (Brute Force)
        --------------------------------------------
        Initializes the backtracking process and returns the k-th permutation.
    */
    string getPermutation(int n, int k) {

        int cnt = 0;        // Counter to track permutations generated
        string curr = "";   // Current permutation being built
        string res = "";    // Final answer (k-th permutation)

        // Initialize used array: index 0 unused, indices 1..n for numbers 1..n
        used.resize(n + 1, false);

        // Start backtracking from empty permutation
        solve(n, k, cnt, res, curr);

        return res;
    }
};

/*
================================================================================
                SOLUTION 2: MATHEMATICAL / OPTIMAL APPROACH
================================================================================

APPROACH:
---------
Instead of generating all permutations, directly compute the k-th permutation
using factorial number system. This is based on the mathematical property that
for n numbers, exactly (n-1)! permutations start with each number.

ALGORITHM:
----------
1. Precompute factorials: factorial[i] = i!
2. Maintain a list of available numbers: [1, 2, 3, ..., n]
3. Convert k to 0-based index (k = k-1)
4. For each position from left to right:
   a. Calculate blockSize = factorial[remaining - 1]
      (how many permutations exist for each choice at this position)
   b. Find index = k / blockSize
      (which number block k falls into)
   c. Pick nums[index] as the current digit
   d. Remove nums[index] from available numbers
   e. Update k = k % blockSize
      (find position within the selected block)

TIME COMPLEXITY:  O(n^2)
    - We iterate n times
    - Each erase operation on vector takes O(n)

SPACE COMPLEXITY: O(n)
    - For factorial array and nums vector

WHEN TO USE:
------------
- Works for larger n values
- Much faster than brute force
- Optimal solution for this problem

================================================================================

EXAMPLE WALKTHROUGH (n=4, k=9):
---------------------------------
Step 0: k = 9 - 1 = 8 (convert to 0-based)
        nums = [1, 2, 3, 4]
        factorials: 0!=1, 1!=1, 2!=2, 3!=6

Step 1: remaining=4, blockSize = 3! = 6
        index = 8 / 6 = 1
        Pick nums[1] = 2       --> ans = "2"
        Remove 2 from nums     --> nums = [1, 3, 4]
        k = 8 % 6 = 2

Step 2: remaining=3, blockSize = 2! = 2
        index = 2 / 2 = 1
        Pick nums[1] = 3       --> ans = "23"
        Remove 3 from nums     --> nums = [1, 4]
        k = 2 % 2 = 0

Step 3: remaining=2, blockSize = 1! = 1
        index = 0 / 1 = 0
        Pick nums[0] = 1       --> ans = "231"
        Remove 1 from nums     --> nums = [4]
        k = 0 % 1 = 0

Step 4: remaining=1, blockSize = 0! = 1
        index = 0 / 1 = 0
        Pick nums[0] = 4       --> ans = "2314"
        Remove 4 from nums     --> nums = []

Answer: "2314" (9th permutation of 1,2,3,4)

================================================================================
*/

class Solution_Optimal {
public:
    /*
        MAIN FUNCTION: getPermutation (Optimal - Mathematical)
        -------------------------------------------------------
        Directly computes the k-th permutation using factorial number system.

        INTUITION:
        ----------
        For n numbers, permutations can be grouped into blocks:
        - First (n-1)! permutations start with 1
        - Next  (n-1)! permutations start with 2
        - Next  (n-1)! permutations start with 3
        - ...and so on

        So we can determine each digit by:
        1. Finding which block k falls into: index = k / (n-1)!
        2. Picking that number
        3. Recursing on remaining numbers with updated k = k % (n-1)!

        This avoids generating all permutations and directly jumps to the answer.
    */
    string getPermutation(int n, int k) {

        // Step 1: Store available numbers in a list
        vector<int> nums;
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }

        // Step 2: Precompute factorials: factorial[i] = i!
        vector<int> factorial(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        string ans = "";

        // Step 3: Convert k to 0-based index for easier math
        // k=1 means first permutation (index 0), k=2 means second (index 1), etc.
        k--;

        // Step 4: Build permutation digit by digit from left to right
        for (int remaining = n; remaining >= 1; remaining--) {

            // blockSize = number of permutations for each choice at this position
            // For 'remaining' numbers, each choice at current position gives (remaining-1)! permutations
            int blockSize = factorial[remaining - 1];

            // Determine which block k falls into
            // This tells us which available number to pick next
            int index = k / blockSize;

            // Pick the number at this index from available numbers
            ans += to_string(nums[index]);

            // Remove the picked number so it's not reused
            nums.erase(nums.begin() + index);

            // Update k to find position within the selected block
            // k % blockSize gives the offset within the current block
            k %= blockSize;
        }

        return ans;
    }
};

/*
================================================================================
                            COMPARISON
================================================================================

| Aspect            | Brute Force (Backtracking) | Optimal (Mathematical) |
|-------------------|----------------------------|------------------------|
| Time Complexity   | O(n! * n)                  | O(n^2)                 |
| Space Complexity  | O(n)                       | O(n)                   |
| Generates all?    | Yes (until k-th)           | No (direct computation)|
| Code Complexity   | Simple recursion           | Moderate math          |
| Best for          | Small n (<=9)              | Any n                  |

================================================================================
*/

int main(){
    return 0;
}



int main(){
    return 0;
}