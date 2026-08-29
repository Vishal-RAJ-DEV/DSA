#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// 1. Traverse the grid.
//    - Whenever an unvisited land (1) is found:
//        - Run DFS/BFS.
//        - Paint the island with a unique ID (2, 3, 4, ...).
//        - Count its area.
//        - Store: islandID → area.

// 2. Traverse the grid again.
//    - For every water cell (0):
//        - Check its 4 neighbors.
//        - Collect unique island IDs in a set.
//        - New area = 1 + sum(area of unique neighboring islands).
//        - Update the maximum answer.

// 3. If no 0 exists (the grid is already all land),
//    return the size of the largest island computed in step 1.

// 4. Otherwise, return the maximum area found.


class Solution {
public:
    int n;

    // Directions: Up, Down, Left, Right
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    // DFS to mark the entire island with a unique ID
    // and return its area.
    int dfs(vector<vector<int>>& grid, int row, int col, int islandId) {

        // Boundary check
        if (row < 0 || row >= n || col < 0 || col >= n)
            return 0;

        // Only visit unvisited land
        if (grid[row][col] != 1)
            return 0;

        // Mark this cell with island ID
        grid[row][col] = islandId;

        int area = 1;

        // Visit all 4 directions
        for (auto it : directions) {
            int dx = it.first;
            int dy = it.second;
            area += dfs(grid, row + dx, col + dy, islandId);
        }

        return area;
    }

    int largestIsland(vector<vector<int>>& grid) {

        n = grid.size();

        // islandArea[id] = size of island
        unordered_map<int, int> islandArea;

        int islandId = 2;      // Start from 2 because
                               // 0 = water
                               // 1 = unvisited land

        int answer = 0;

        // -----------------------------
        // Step 1 : Find all islands
        // -----------------------------
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {

                    int area = dfs(grid, i, j, islandId);

                    islandArea[islandId] = area;

                    answer = max(answer, area);

                    islandId++;
                }
            }
        }

        // -----------------------------
        // Step 2 : Try converting every
        //          0 into 1
        // -----------------------------
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 0) {

                    unordered_set<int> uniqueIslands;

                    int newArea = 1;   // Current flipped cell

                    // Check all 4 neighbours
                    for (auto it: directions) {
                        int dx =  it.first;
                        int dy = it.second;


                        int newRow = i + dx;
                        int newCol = j + dy;

                        if (newRow < 0 || newRow >= n ||
                            newCol < 0 || newCol >= n)
                            continue;

                        int id = grid[newRow][newCol];

                        // Ignore water
                        if (id == 0)
                            continue;

                        // Add area only once
                        if (uniqueIslands.insert(id).second) {
                            newArea += islandArea[id];
                        }
                    }

                    answer = max(answer, newArea);
                }
            }
        }

        return answer;
    }
};


class DSU {
public:
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int u, int v) {

        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return;

        // Union by size
        if (size[pu] < size[pv])
            swap(pu, pv);

        parent[pv] = pu;
        size[pu] += size[pv];
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {

        int n = grid.size();

        DSU dsu(n * n);

        vector<pair<int,int>> dir = {
            {-1,0},
            {1,0},
            {0,-1},
            {0,1}
        };

        // -------------------------------
        // Step 1 : Union all land cells
        // -------------------------------

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 0)
                    continue;

                int node = i * n + j;

                for (auto it : dir) {

                    int nr = i + it.first;
                    int nc = j + it.second;

                    if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                        continue;

                    if (grid[nr][nc] == 0)
                        continue;

                    int neighbour = nr * n + nc;

                    dsu.unite(node, neighbour);
                }
            }
        }

        int answer = 0;

        // Existing largest island
        for (int i = 0; i < n * n; i++) {

            if (grid[i / n][i % n] == 1) {

                int leader = dsu.find(i);

                answer = max(answer, dsu.size[leader]);
            }
        }

        // ---------------------------------
        // Step 2 : Convert every 0
        // ---------------------------------

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1)
                    continue;

                unordered_set<int> leaders;

                int area = 1;

                for (auto it : dir) {
                    int dx = it.first;
                    int dy = it.second;

                    int nr = i + dx;
                    int nc = j + dy;

                    if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                        continue;

                    if (grid[nr][nc] == 0)
                        continue;

                    int node = nr * n + nc;

                    leaders.insert(dsu.find(node));
                }

                for (int leader : leaders)
                    area += dsu.size[leader];

                answer = max(answer, area);
            }
        }

        return answer;
    }
};


int main(){
    return 0;
}