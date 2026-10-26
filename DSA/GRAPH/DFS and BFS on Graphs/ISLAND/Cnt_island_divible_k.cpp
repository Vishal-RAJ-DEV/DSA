#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dirrow[4] = {-1, 0, 1, 0};
    int dircol[4] = {0, 1, 0, -1};

    bool check(int row, int col, int n, int m,
               vector<vector<int>>& vis,
               vector<vector<int>>& grid) {
        return row >= 0 && row < n &&
               col >= 0 && col < m &&
               grid[row][col] != 0 &&
               vis[row][col] == 0;
    }

    long long dfs(int row, int col, int n, int m,
            vector<vector<int>>& grid,
            vector<vector<int>>& vis) {
        vis[row][col] = 1;
        long long sum = grid[row][col];

        for (int i = 0; i < 4; i++) {
            int newrow = row + dirrow[i];
            int newcol = col + dircol[i];

            if (check(newrow, newcol, n, m, vis, grid)) {
                sum += dfs(newrow, newcol, n, m, grid, vis);
            }
        }

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        if (n == 0) return 0;

        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));

        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 0 && vis[i][j] == 0) {
                    long long sum = dfs(i, j, n, m, grid, vis);

                    if (sum % k == 0) {
                        cnt++;
                    }
                }
            }
        }

        return (int)cnt;
    }
};


class Solution {
public:
    int dirrow[4] = {-1, 0, 1, 0};
    int dircol[4] = {0, 1, 0, -1};

    bool check(int row, int col, int n, int m,
               vector<vector<int>>& vis,
               vector<vector<int>>& grid) {
        return row >= 0 && row < n &&
               col >= 0 && col < m &&
               grid[row][col] != 0 &&
               vis[row][col] == 0;
    }

    int bfs(int row, int col, int n, int m,
            vector<vector<int>>& grid,
            vector<vector<int>>& vis) {

        queue<pair<int, int>> q;
        q.push({row, col});
        vis[row][col] = 1;

        int sum = 0;

        while (!q.empty()) {
            auto it = q.front();
            int r = it.first;
            int c = it.second;
            q.pop();

            sum += grid[r][c];

            for (int i = 0; i < 4; i++) {
                int newrow = r + dirrow[i];
                int newcol = c + dircol[i];

                if (check(newrow, newcol, n, m, vis, grid)) {
                    vis[newrow][newcol] = 1;
                    q.push({newrow, newcol});
                }
            }
        }

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        if (n == 0) return 0;

        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));

        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 0 && vis[i][j] == 0) {
                    int sum = bfs(i, j, n, m, grid, vis);

                    if (sum % k == 0) {
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