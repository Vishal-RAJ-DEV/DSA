#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1e9 + 7;
    int m, n;
    int dp[50][50][51];

    int solve(int r, int c, int moves) {
        if (moves == 0)
            return 0;

        if (dp[r][c][moves] != -1)
            return dp[r][c][moves];

        long long ans = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Ball goes outside the grid
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                ans++;
            }
            // Ball remains inside
            else {
                ans += solve(nr, nc, moves - 1);
            }

            ans %= MOD;
        }

        return dp[r][c][moves] = ans;
    }

    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        this->m = m;
        this->n = n;

        memset(dp, -1, sizeof(dp));

        return solve(startRow, startColumn, maxMove);
    }
};


class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = 1e9 + 7;

        vector<vector<vector<int>>> dp(
            maxMove + 1,
            vector<vector<int>>(m, vector<int>(n, 0))
        );

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int moves = 1; moves <= maxMove; moves++) {

            for (int r = 0; r < m; r++) {

                for (int c = 0; c < n; c++) {

                    long long ways = 0;

                    for (int d = 0; d < 4; d++) {

                        int nr = r + dr[d];
                        int nc = c + dc[d];

                        // Moving outside the grid
                        if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                            ways++;
                        }
                        // Moving inside the grid
                        else {
                            ways += dp[moves - 1][nr][nc];
                        }

                        ways %= MOD;
                    }

                    dp[moves][r][c] = ways;
                }
            }
        }

        return dp[maxMove][startRow][startColumn];
    }
};

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = 1e9 + 7;

        vector<vector<int>> prev(m, vector<int>(n, 0));
        vector<vector<int>> curr(m, vector<int>(n, 0));

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int moves = 1; moves <= maxMove; moves++) {

            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {

                    long long ways = 0;

                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];

                        // Moving outside the grid
                        if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                            ways++;
                        }
                        // Moving inside the grid
                        else {
                            ways += prev[nr][nc];
                        }

                        ways %= MOD;
                    }

                    curr[r][c] = ways;
                }
            }

            // Current becomes previous for next iteration
            prev = curr;
        }

        return prev[startRow][startColumn];
    }
};




int main(){
    return 0;
}