#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//using the bfs , priority queue and dijkstra to solve this problem
class Solution1 {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return 0;

        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        // Step 1: Multi-source BFS to calculate distance to nearest thief
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            auto it = q.front();
            int r = it.first, c = it.second;

            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Modified Dijkstra to find path with maximum minimum distance
        // {safeness, {r, c}} - we use a max-heap
        priority_queue<pair<int, pair<int, int>>> pq;
        vector<vector<int>> max_safe(n, vector<int>(n, -1));

        pq.push({dist[0][0], {0, 0}});
        max_safe[0][0] = dist[0][0];

        while (!pq.empty()) {
            int d = pq.top().first;
            auto it = pq.top().second;
            int r = it.first, c = it.second;
            pq.pop();

            if (r == n - 1 && c == n - 1) return d;

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    // The safeness of the new cell is the min of current path safeness 
                    // and the distance of the new cell to a thief
                    int new_safe = min(d, dist[nr][nc]);
                    if (new_safe > max_safe[nr][nc]) {
                        max_safe[nr][nc] = new_safe;
                        pq.push({new_safe, {nr, nc}});
                    }
                }
            }
        }

        return 0;
    }
};


//using the binary search and bfs to solve this problem

class Solution1 {
public:
    vector<int>rowDir = {-1, 1, 0, 0};
    vector<int>colDir = {0, 0, -1, 1};
    bool isValid(vector<vector<bool>>&visited, int i, int j)
    {
        if (i < 0 || j < 0 || i == visited.size() || j == visited[0].size() || visited[i][j])
            return false;
        return true;
    }
    //============================================================================================================
    bool isSafe(vector<vector<int>>&distToTheif, int safeDist) //check the validity of safenessFactor
    {
        int n = distToTheif.size();
        queue<pair<int, int>>q;
        if (distToTheif[0][0] < safeDist) return false;
        q.push({0, 0});
        vector<vector<bool>>visited(n, vector<bool>(n, false));
        visited[0][0] = true;
        while(!q.empty())
        {
            int currRow = q.front().first, currCol = q.front().second;
            q.pop();
            if (currRow == n - 1 && currCol == n - 1) return true;
            for (int dirIdx = 0; dirIdx < 4; dirIdx++)
            {
                int newRow = currRow + rowDir[dirIdx];
                int newCol = currCol + colDir[dirIdx];
                if (isValid(visited, newRow, newCol))
                {
                    if (distToTheif[newRow][newCol] < safeDist) continue;
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
        return false;
    }
    //===========================================================================================================
    int maximumSafenessFactor(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        queue<pair<int, int>>q;
        vector<vector<bool>>visited(n, vector<bool>(n, false));
        vector<vector<int>>distToTheif(n, vector<int>(n, -1));
        //========================================================================
        //Add all the theives in current queue
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1) 
                {
                    visited[i][j] = true;
                    q.push({i, j});
                }
            }
        }
        //=============================================================================
        //BFS to fill the "DistToTheif" 2D array
        int dist = 0;
        while(!q.empty())
        {
            int size = q.size();
            while(size--)
            {
                int currRow = q.front().first, currCol = q.front().second;
                q.pop();
                distToTheif[currRow][currCol] = dist;
                for (int dirIdx = 0; dirIdx < 4; dirIdx++)
                {
                    int newRow = currRow + rowDir[dirIdx], newCol = currCol + colDir[dirIdx];
                    if (!isValid(visited, newRow, newCol)) continue;
                    
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
            dist++;
        }
        //==================================================================================
        //BINARY SEARCH
        int low = 0, high = INT_MAX;
        int ans = 0;
        while(low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isSafe(distToTheif, mid))
            {
                ans = mid;
                low = mid + 1;
            }
            else high = mid - 1;
        }
        //=========================================================================================
        return ans;
        
    }
};



int main(){
        Solution1 sol;
        vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        cout << sol.maximumSafenessFactor(grid) << endl; // Output: 2
    return 0;
}
