/*
 * Problem: Shortest Path in Binary Matrix/Maze
 * 
 * Two variations:
 * 1. Custom source/destination with 4-directional movement
 * 2. Fixed (0,0) to (n-1,m-1) with 8-directional movement
 * 
 * In a binary grid:
 * - 0 represents blocked cells (cannot move through)
 * - 1 represents open/valid cells (can move through) 
 * 
 * Goal: Find shortest path length using BFS (Breadth-First Search)
 * BFS guarantees shortest path in unweighted graphs
 * 
 * Time Complexity: O(n*m) where n=rows, m=columns
 * Space Complexity: O(n*m) for distance matrix and queue
 */

#include <bits/stdc++.h>
using namespace std;

// Solution 1: 4-directional movement with custom source and destination
class Solution {
public:
    // Find shortest path using BFS with 4-directional movement (up, down, left, right)
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) {
        
        // Edge Case: Source same as destination
        if (source.first == destination.first && source.second == destination.second)
            return 0;

        // BFS setup: Queue stores {distance, {row, col}}
        queue<pair<int, pair<int, int>>> q;
        int n = grid.size();    // Number of rows
        int m = grid[0].size(); // Number of columns

        // Distance matrix: Initialize all cells with infinity (unreachable)
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[source.first][source.second] = 0;  // Source distance is 0

        // Start BFS from source with distance 0
        q.push({0, {source.first, source.second}});

        // Direction vectors for 4-directional movement: up, right, down, left
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        // BFS traversal
        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            
            int dis = it.first;              // Current distance from source
            int r = it.second.first;         // Current row
            int c = it.second.second;        // Current column

            // Explore all 4 adjacent directions
            for (int i = 0; i < 4; i++) {
                int newr = r + dr[i];  // New row position
                int newc = c + dc[i];  // New column position

                // Check if new position is valid:
                // 1. Within grid bounds
                // 2. Cell value is 1 (passable)
                // 3. New path is shorter than previously found path
                if (newr >= 0 && newr < n && newc >= 0 && newc < m && 
                    grid[newr][newc] == 1 && dis + 1 < dist[newr][newc]) {
                    
                    dist[newr][newc] = dis + 1;  // Update shortest distance

                    // Check if we reached the destination
                    if (newr == destination.first && newc == destination.second)
                        return dis + 1;

                    // Add new cell to queue for further exploration
                    q.push({dis + 1, {newr, newc}});
                }
            }
        }

        // No path found from source to destination
        return -1;
    }
};

//when we have 8 direction then we can use the below code
//source is (0 , 0) and destination is ( n - 1 , m - 1)
class Solution1 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        //edges cases 
        if( grid[0][0] == 1 || grid[n -1][m - 1] == 1) return -1;

        //quque to store the '0'  and the corrdinate
        queue<pair<int , pair<int , int >>> q;

        //distance matrix to store the dist from the source node
        vector<vector<int>>dist( n , vector<int>(m  , 1e9));

        //here source is the (0 , 0) and destination  is ( n - 1 , m - 1)
        q.push({ 1 , { 0 , 0}});
        dist[0][0] = 1;
        //all the four direction in the row and col
        int delrow[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int delcol[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

        while( !q.empty() ){
            auto it = q.front(); q.pop();
            int dis = it.first;
            int row = it.second.first;
            int col = it.second.second;

            if( row == n - 1  && col == m - 1) return dis;

            for( int i = 0 ; i < 8  ; i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];

                if( nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && grid[nrow][ncol] == 0 && 
                dis + 1 < dist[nrow][ncol]){
                    dist[nrow][ncol] = dis + 1;
                    q.push({ dis + 1 , { nrow , ncol}});
                }
            }
        }

        return -1;

    }
};

int main() {
    // Test Case for Solution 1 (4-directional movement)
    pair<int, int> source = {0, 1};      // Starting position
    pair<int, int> destination = {2, 2}; // Target position

    // Grid definition: 1 = passable, 0 = blocked
    vector<vector<int>> grid = {{1, 1, 1, 1},
                                {1, 1, 0, 1},
                                {1, 1, 1, 1},
                                {1, 1, 0, 0},
                                {1, 0, 0, 1}};

    cout << "Grid (1=passable, 0=blocked):" << endl;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Source: (" << source.first << ", " << source.second << ")" << endl;
    cout << "Destination: (" << destination.first << ", " << destination.second << ")" << endl;

    Solution obj;
    int res = obj.shortestPath(grid, source, destination);

    if(res != -1) {
        cout << "Shortest path length (4-directional): " << res << endl;
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}