#include <bits/stdc++.h>
using namespace std;

int solve(int row, int col, int n, vector<vector<int>>& grid,
          vector<vector<int>>& dp) {

    // Base case: all rows have been processed.
    if (row == 2 * n - 1) return 0;

    // Return the previously calculated answer.
    if (dp[row][col] != -1) return dp[row][col];

    // Bananas collected from the current cell.
    int ans = grid[row][col];

    // Calculate the length of the next row.
    int nextRowSize = grid[row + 1].size();

    // Option 1: Move to the cell directly below, if it exists.
    int left = 0;
    if (col < nextRowSize) {
        left = solve(row + 1, col, n, grid, dp);
    }

    // Option 2: Move diagonally down-right, if that cell exists.
    int right = 0;
    if (col + 1 < nextRowSize) {
        right = solve(row + 1, col + 1, n, grid, dp);
    }

    // Add the current bananas to the maximum of the two paths.
    return dp[row][col] = ans + max(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;

        int rows = 2 * n - 1;
        vector<vector<int>> grid(rows);

        // Read the upper half: row lengths increase from 1 to n.
        for (int i = 0; i < n; i++) {
            grid[i].resize(i + 1);
            for (int j = 0; j <= i; j++) {
                cin >> grid[i][j];
            }
        }

        // Read the lower half: row lengths decrease from n-1 to 1.
        for (int i = n; i < rows; i++) {
            grid[i].resize(rows - i);
            for (int j = 0; j < grid[i].size(); j++) {
                cin >> grid[i][j];
            }
        }

        // Initialize all DP states as uncomputed.
        vector<vector<int>> dp(rows);
        for (int i = 0; i < rows; i++) {
            dp[i].assign(grid[i].size(), -1);
        }

        // Start at the top cell of the diamond.
        int ans = solve(0, 0, n, grid, dp);

        cout << "Case " << tc << ": " << ans << '\n';
    }

    return 0;
}