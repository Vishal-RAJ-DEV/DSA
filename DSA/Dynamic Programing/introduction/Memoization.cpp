#include <bits/stdc++.h>
using namespace std;

/*
Steps to memoize a recursive solution:

Any recursive solution to a problem can be memoized using these three steps:

1.Create a dp[n+1] array initialized to -1.
2.Whenever we want to find the answer of a particular value (say n), we first check whether the answer is already calculated using the dp array. If yes, simply return the value from the dp array.
3.If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will store the solution in our dp array.
*/

//time complexity: O(n) as we are calculating the answer for each value from 0 to n only once and then storing it in the dp array so that we can use it later without recalculating it again
//space complexity: O(n) for the dp array and O(n) for the recursive stack space in the worst case when there is no overlapping subproblems and we are calculating the answer for each value from 0 to n in a linear manner 
class Solution {
public:
    // Function to calculate Fibonacci using memoization
    int fib(int n, vector<int>& dp) {
        // If base case return n
        if (n <= 1) return n;

        // If already computed, return stored value
        if (dp[n] != -1) return dp[n];

        // Otherwise compute and store
        dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
        return dp[n];
    }
};

int main() {
    int n = 10;
    vector<int> dp(n + 1, -1);
    Solution sol;
    cout << sol.fib(n, dp);
    return 0;
}
