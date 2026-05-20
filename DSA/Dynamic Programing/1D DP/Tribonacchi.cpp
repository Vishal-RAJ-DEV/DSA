#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:

    int solve(int n, vector<int>& dp) {

        // base case
        if(n == 0) return 0;
        if(n == 1 || n == 2) return 1;

        // already computed
        if(dp[n] != -1) {
            return dp[n];
        }

        // store and return
        return dp[n] =
               solve(n-1, dp) +
               solve(n-2, dp) +
               solve(n-3, dp);
    }

    int tribonacci(int n) {

        vector<int> dp(n + 1, -1);

        return solve(n, dp);
    }
};

class Tabulation {
public:
    int tribonacci(int n) {

        // base cases
        if(n == 0) return 0;
        if(n == 1 || n == 2) return 1;

        vector<int> dp(n + 1);

        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for(int i = 3; i <= n; i++) {

            dp[i] =
                dp[i-1] +
                dp[i-2] +
                dp[i-3];
        }

        return dp[n];
    }
};
class SpaceOptimized {
public:
    int tribonacci(int n) {
        if( n == 0) return 0;
        if( n == 1 || n == 2) return 1;
        int first = 0 ;
        int second = 1;
        int third = 1;
        for( int i = 3 ; i<=n ; i++){
            int curr = first + second + third;
            first = second ;
            second = third;
            third = curr;
        }

        return third;
    }
};

/*Approach	Time	Space
Recursion	Exponential	O(n) stack
Memoization	O(n)	O(n)
Tabulation	O(n)	O(n)
Space Optimized	O(n)	O(1)
*/


int main(){
    return 0;
}

