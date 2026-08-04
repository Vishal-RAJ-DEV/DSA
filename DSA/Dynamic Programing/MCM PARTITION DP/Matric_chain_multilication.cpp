#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:
    // Recursive function with memoization
    int matrixMultiplication(vector<int>& arr, int i, int j, vector<vector<int>>& dp) {
        // Base case: only one matrix, no multiplication
        if (i == j) return 0;

        // If already computed, return from dp
        if (dp[i][j] != -1) return dp[i][j];

        // Initialize min cost as very large
        int minCost = INT_MAX;

        // Try every partition
        for (int k = i; k < j; k++) {
            int cost1 = matrixMultiplication(arr, i, k, dp);
            int cost2 = matrixMultiplication(arr, k + 1, j, dp);
            int costMultiply = arr[i - 1] * arr[k] * arr[j];

            int total = cost1 + cost2 + costMultiply;

            minCost = min(minCost, total);
        }

        // Store and return result
        return dp[i][j] = minCost;
    }

    // Function to start the memoization approach
    int matrixChainOrder(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return matrixMultiplication(arr, 1, n - 1, dp);
    }
};

class Tabulation {
public:
    int matrixMultiplication(vector<int> &arr) {

        int n = arr.size() - 1;      // number of matrices

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // length of matrix chain
        for(int len = 2; len <= n; len++){

            for(int i = 1; i <= n - len + 1; i++){

                int j = i + len - 1;

                dp[i][j] = INT_MAX;

                for(int k = i; k < j; k++){
                    
                    int left = dp[i][k]; // cost of multiplying matrices from i to k
                    int right = dp[k + 1][j]; // cost of multiplying matrices from k+1 to j
                    
                    int cost = left + right + arr[i - 1] * arr[k] * arr[j];

                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

    return dp[1][n];
    }
};
// Driver code
int main() {
    Memoization sol;
    vector<int> arr = {40, 20, 30, 10, 30};
    cout << "Minimum number of multiplications is: "
         << sol.matrixChainOrder(arr) << endl;
    return 0;
}
