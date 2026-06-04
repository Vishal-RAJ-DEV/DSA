#include <bits/stdc++.h>
using namespace std;

class MemoizationSolution {
  public:
    int solve(int ind, int length,
              vector<int>& price,
              vector<vector<int>>& dp) {

        /*
            Here index acts like rod length exactly like the item/weight relation
            in knapsack style questions.

            ind = 0 means we are standing at price[0].
            price[0] is the price of a rod piece of length 1.

            ind = 1 means price[1], which is rod length 2.
            ind = 2 means price[2], which is rod length 3.

            So in general:
                rodLength = ind + 1

            Just like knapsack:
                wt[ind] gives the weight of current item

            Here:
                ind + 1 gives the length of current rod piece.
        */

        /*
            Base case:
            When ind == 0, only rod piece of length 1 is available.

            If only length 1 pieces are allowed, then to make total rod length
            "length", we must cut the whole rod into "length" number of pieces
            of size 1.

            Example:
                length = 5
                only available piece length = 1

                Then we take 1, 1, 1, 1, 1
                total pieces = 5
                total price = 5 * price[0]

            So:
                answer = length * price[0]

            This works because piece of length 1 can always fit, and we can
            take it again and again just like unbounded knapsack.
        */
        if(ind == 0) {
            return length * price[0];
        }

        if(dp[ind][length] != -1) {
            return dp[ind][length];
        }

        // skip current rod piece length
        int notTake = solve(ind - 1, length, price, dp);

        // take current rod piece length
        int take = INT_MIN;
        int rodLength = ind + 1;

        /*
            If current rod length fits, we take it and stay on same index.

            Why stay on same index?
            Because rod cutting is an unbounded knapsack pattern.
            We are allowed to use the same piece length multiple times.
        */
        if(rodLength <= length) {
            take = price[ind] +
                   solve(ind, length - rodLength, price, dp);
        }

        return dp[ind][length] = max(take, notTake);
    }

    // Function to compute maximum price obtainable by cutting the rod
    int rodCutting(vector<int>& price, int n) {
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solve(n - 1, n, price, dp);
    }
};

class TabulationSolution {
  public:
    // Function to compute maximum price obtainable by cutting the rod
    int rodCutting(vector<int>& price, int n) {

        /*
            dp[i][length] means:
            maximum price we can get using rod pieces from index 0 to i
            to make total rod length = length

            Here:
                i = 0 means only rod length 1 is available
                i = 1 means rod lengths 1 and 2 are available
                i = 2 means rod lengths 1, 2 and 3 are available
        */
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        /*
            Base case conversion from memoization:

            In memoization we wrote:

                if(ind == 0) {
                    return length * price[0];
                }

            Meaning:
            when we are at row ind = 0, only rod piece of length 1 is allowed.

            So if total rod length is:
                0 -> answer = 0 * price[0]
                1 -> answer = 1 * price[0]
                2 -> answer = 2 * price[0]
                3 -> answer = 3 * price[0]
                ...

            Why?
            Because with only piece length 1 available, the only way to form
            total rod length = length is to take that piece exactly "length"
            times.

            In tabulation, ind == 0 means first row.
            So we fill the whole first row using:
                dp[0][length] = length * price[0]

            This is exactly the tabulation form of the memoization base case.
        */
        for(int length = 0; length <= n; length++) {
            // First row fill: only rod length 1 can be used again and again
            dp[0][length] = length * price[0];
        }

        // Iterate through each rod piece starting from index 1
        for(int i = 1; i < n; i++) {
            for(int length = 0; length <= n; length++) {

                // Option 1: Do not cut with this rod (copy from above)
                int notTake = dp[i - 1][length];

                // Option 2: Cut with current rod length (reuse allowed)
                int take = INT_MIN;
                int rodLength = i + 1;

                // Check if this rod fits in current length
                if(rodLength <= length) {
                    take = price[i] + dp[i][length - rodLength];
                }

                // Store the best value in the DP table
                dp[i][length] = max(take, notTake);
            }
        }

        // Return the answer from the last row and column (full rod length)
        return dp[n - 1][n];
    }
};



class SpaceOptimizedSolution {
public:
    // Function to solve the rod cutting problem
    int rodCutting(vector<int>& price, int n) {
        // Initialize DP table with dimensions [n + 1]
        vector<int> prev(n+1, 0), cur(n+1, 0);
        
        for(int length = 0; length <= n; length++){
            prev[length] = price[0]*length;
        }
        
        // Fill the DP table
        for (int ind = 1; ind < n; ++ind) { 
            for (int length = 1; length <= n; ++length) { 
                
                // Case when the piece is not taken
                int notTaken = 0+prev[length];
                
                // Case when the piece is taken
                int taken = INT_MIN;
                
                /* Length of the rod piece 
                corresponding to the current index*/
                int rodLength = ind + 1;
                
                // Check if the piece can be taken
                if (rodLength <= length) {
                    taken = price[ind] + cur[length - rodLength];
                }
                
                /* Update cur[length] with the maximum of 
                including or not including the current piece*/
                cur[length] = max(notTaken, taken);
            }
            prev = cur;
        }
        
        // Return the result 
        return prev[n];
    }
};


// Driver code
int main() {
    // Length of the rod
    int n = 8;

    // Price list where price[i] is the value of rod of length i+1
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};

    // Create object of Solution class
    MemoizationSolution memo;
    TabulationSolution tab;
    SpaceOptimizedSolution space;

    // Call rodCutting function and print the result
    cout << "Memoization: " << memo.rodCutting(price, n) << endl;
    cout << "Tabulation: " << tab.rodCutting(price, n) << endl;
    cout << "Space Optimized: " << space.rodCutting(price, n) << endl;

    return 0;
}
