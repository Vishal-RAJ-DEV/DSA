#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Breadth-First Search (BFS) function
void BFS(int row, int col, vector<vector<int>> &grid, vector<vector<bool>> &visited, vector<pair<int, int>> &cells, int baseRow, int baseCol)
{
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int, int>> q;
    q.push({row, col}); //this store original cell of the island
    visited[row][col] = true;
    cells.push_back({row - baseRow, col - baseCol}); // store the cell relative to the base cell of the island

    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // explore 4 directions (up, down, left, right)
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++)
        {
            int nRow = r + dRow[i];
            int nCol = c + dCol[i];

            // Check if the new position is within bounds
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m)
            {
                // Check if it's land and not visited
                if (grid[nRow][nCol] == 1 && !visited[nRow][nCol])
                {
                    visited[nRow][nCol] = true;
                    q.push({nRow, nCol});
                    cells.push_back({nRow - baseRow, nCol - baseCol}); // store the cell relative to the base cell of the island
                }
            }
        }
    }
}

// Depth-First Search (DFS) function
void dfs( int row, int col, vector<vector<int>> &grid, vector<vector<bool>> &visited, vector<pair<int, int>> &cells, int baseRow, int baseCol)
{
    int n = grid.size();
    int m = grid[0].size();
    visited[row][col] = true;
    cells.push_back({row - baseRow, col - baseCol}); // store the cell relative to the base cell of the island

    // explore 4 directions (up, down, left, right)
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        int nRow = row + dRow[i];
        int nCol = col + dCol[i];

        // Check if the new position is within bounds
        if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m)
        {
            // Check if it's land and not visited
            if (grid[nRow][nCol] == 1 && !visited[nRow][nCol])
            {
                dfs(nRow, nCol, grid, visited, cells, baseRow, baseCol);
            }
        }
    }
}
int main()
{
    vector<vector<int>> grid = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {1, 1, 0, 1},
    };
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    set<vector<pair<int, int>>> uniqueIslands; // to store unique island shapes
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {

                // DFS to mark all connected land cells
                vector<pair<int, int>> cells; // to store the cells of the current island
                dfs(i, j, grid, visited, cells, i, j);
                uniqueIslands.insert(cells); // insert the shape of the current island into the set
            }
        }
    }

    cout << "Number of distinct islands: " << uniqueIslands.size() << endl;

    return 0;
}