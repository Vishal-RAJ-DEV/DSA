#include <bits/stdc++.h>
using namespace std;

/*
Tabulation
Tabulation is a ‘bottom-up’ approach where we start from the base case and reach the final answer that we want. Tabulation helps in optimizing the solution by preventing additional stack space used during recursion.

Steps to convert Recursive Solution to Tabulation one.

1.Declare a dp[] array of size n+1.
2.First initialize the base condition values, i.e i=0 and i=1 of the dp array as 0 and 1 respectively.
3.Set an iterative loop that traverses the array( from index 2 to n) and for every index set its value as dp[i-1] + dp[i-2]. 
*/

//time complexity: O(n) as we are filling the dp array of size n+1 once
//space complexity: O(n) for the dp array
class Solution {
public:
    // Function to calculate Fibonacci using tabulation
    int fib(int n) {
        // If n is 0 or 1, return n
        if (n <= 1) return n;

        // Create dp array
        vector<int> dp(n + 1, 0);

        // Initialize base cases
        dp[0] = 0;
        dp[1] = 1;

        // Fill dp array iteratively
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        // Return final answer
        return dp[n];
    }
};

int main() {
    int n = 10;
    Solution sol;
    cout << sol.fib(n);
    return 0;
}
