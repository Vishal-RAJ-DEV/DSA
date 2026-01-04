#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// Breadth-First Search (BFS) function
void BFS( int row , int col , vector<vector<int>> & grid , vector<vector<bool>> & visited){
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int,int>> q;
    q.push({row , col});
    visited[row][col] = true;

    while( !q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // Explore all 8 directions
        for( int delRow = -1 ; delRow <= 1 ; delRow++){
            for( int delCol = -1 ; delCol <= 1 ; delCol++){
                int nRow = r + delRow;
                int nCol = c + delCol;

                // Check if the new position is within bounds
                if( nRow >= 0 && nRow < n && nCol >= 0 && nCol < m){
                    // Check if it's land and not visited
                    if( grid[nRow][nCol] == 1 && !visited[nRow][nCol]){
                        visited[nRow][nCol] = true;
                        q.push({nRow , nCol});
                    }
                }
            }
        }
    }
}

// Depth-First Search (DFS) function
void DFS( int row , int col , vector<vector<int>> & grid , vector<vector<bool>> & visited){
    int n = grid.size();
    int m = grid[0].size();
    visited[row][col] = true;

    // Explore all 8 directions
    for( int delRow = -1 ; delRow <= 1 ; delRow++){
        for( int delCol = -1 ; delCol <= 1 ; delCol++){
            int nRow = row + delRow;
            int nCol = col + delCol;

            // Check if the new position is within bounds
            if( nRow >= 0 && nRow < n && nCol >= 0 && nCol < m){
                // Check if it's land and not visited
                if( grid[nRow][nCol] == 1 && !visited[nRow][nCol]){
                    DFS( nRow , nCol , grid , visited);
                }
            }
        }
    }
}


int main()
{
    vector<vector<int>> grid = {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 1},
    };
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int islandCount = 0;
    for( int i = 0 ; i < rows ; i++){
        for( int j = 0 ; j < cols ; j++){
            if( grid[i][j] == 1 && !visited[i][j]){
                islandCount ++;
                // BFS to mark all connected land cells
                BFS( i , j , grid , visited);
            }
        }
    }

    cout << "Number of islands (using BFS): " << islandCount << endl;
    return 0;
}

// Time Complexity: O(N*M) where N is the number of rows and M is the number of columns in the grid.
// Space Complexity: O(N*M) for the visited array and O(min(N,M)) for the BFS queue in the worst case.

/*
Time Complexity: O(N × M)
Breakdown:

Outer Nested Loops:

This visits every cell once: O(N × M)
BFS/DFS Traversal:

Each cell is visited at most once during all BFS/DFS calls combined
When a cell is visited, it's marked as visited[i][j] = true
Once visited, it's never processed again
Total cells processed across all BFS/DFS calls: O(N × M)
8-Direction Exploration:

For each cell, we check 8 neighbors: O(8) = O(1)
This doesn't add to the overall complexity
Overall: O(N × M) + O(N × M) = O(N × M)

Space Complexity: O(N × M)
Breakdown:

Input Grid: O(N × M) - given
Visited Array: O(N × M) - explicitly created
BFS Queue: O(N × M) - worst case when entire grid is one island
DFS Recursion Stack: O(N × M) - worst case when entire grid forms a long path
Overall: O(N × M)
*/