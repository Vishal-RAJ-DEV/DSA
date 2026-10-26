#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dirrow[4] = {-1, 0, 1, 0};
    int dircol[4] = {0, 1, 0, -1};

    bool dfs(int row, int col, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        if (row < 0 || row >= n || col < 0 || col >= m)
            return false;

        if (grid[row][col] == 1)
            return true;

        grid[row][col] = 1;

        bool closed = true;

        for (int i = 0; i < 4; i++) {
            int newrow = row + dirrow[i];
            int newcol = col + dircol[i];

            if (!dfs(newrow, newcol, grid)) {
                closed = false;
            }
        }

        return closed;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    if (dfs(i, j, grid)) {
                        cnt++;
                    }
                }
            }
        }

        return cnt;
    }
};

class Solution {
public:
    int dirrow[4] = {-1, 0, 1, 0};
    int dircol[4] = {0, 1, 0, -1};

    bool bfs(int row, int col, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        q.push({row, col});
        grid[row][col] = 1;

        bool closed = true;

        while (!q.empty()) {
            auto it = q.front();
            int r = it.first;
            int c = it.second;
            q.pop();

            if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
                closed = false;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dirrow[i];
                int nc = c + dircol[i];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < m &&
                    grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }

        return closed;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    if (bfs(i, j, grid)) {
                        cnt++;
                    }
                }
            }
        }

        return cnt;
    }
};



int main(){
    return 0;
}