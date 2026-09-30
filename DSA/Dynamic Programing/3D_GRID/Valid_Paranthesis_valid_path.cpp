#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int len = m + n - 1;

        // Odd length can never form a valid parentheses string
        if (len % 2)
            return false;

        // First character must be '('
        if (grid[0][0] == ')')
            return false;

        vector<vector<vector<bool>>> dp(
            m,
            vector<vector<bool>>(n, vector<bool>(len + 1, false))
        );

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int balance = 0; balance <= len; balance++) {

                    // Current cell contributes to balance
                    int newBalance = balance;

                    if (grid[i][j] == '(')
                        newBalance++;
                    else
                        newBalance--;

                    if (newBalance < 0)
                        continue;

                    if (i > 0 && dp[i - 1][j][balance])
                        dp[i][j][newBalance] = true;

                    if (j > 0 && dp[i][j - 1][balance])
                        dp[i][j][newBalance] = true;
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};


class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool solve(int i, int j, int balance, vector<vector<char>>& grid) {

        // Balance can never be negative
        if (balance < 0)
            return false;

        // Reached outside grid
        if (i >= m || j >= n)
            return false;

        // Apply current cell
        if (grid[i][j] == '(')
            balance++;
        else
            balance--;

        // Invalid balance
        if (balance < 0)
            return false;

        // Remaining cells cannot possibly close the balance
        int remaining = (m - 1 - i) + (n - 1 - j);

        if (balance > remaining)
            return false;

        // Destination
        if (i == m - 1 && j == n - 1)
            return balance == 0;

        // Already calculated
        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        // Move down
        bool down = solve(i + 1, j, balance, grid);

        // Move right
        bool right = solve(i, j + 1, balance, grid);

        return dp[i][j][balance] = (down || right);
    }

    bool hasValidPath(vector<vector<char>>& grid) {

        m = grid.size();
        n = grid[0].size();

        int len = m + n - 1;

        // Valid parentheses string must have even length
        if (len % 2 == 1)
            return false;

        // First character must be '('
        if (grid[0][0] == ')')
            return false;

        dp.assign(m, vector<vector<int>>(n, vector<int>(len + 1, -1)));

        return solve(0, 0, 0, grid);
    }
};




int main(){
    return 0;
}