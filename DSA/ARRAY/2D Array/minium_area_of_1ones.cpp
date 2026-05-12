#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int minimumArea(vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int maxCol = -1;    // max col has taken as -1 because we want to find the rightmost column with 1
    int maxRow = -1;   // max row has taken as -1 because we want to find the bottommost row with 1
    int minCol = n;    // min col has taken as n because we want to find the leftmost column with 1
    int minRow = m;    // min row has taken as m because we want to find the topmost row with 1

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1)
            {
                maxCol = max(maxCol, j);   // find the right most column with 1
                maxRow = max(maxRow, i);   // find the bottom most row with 1
                minCol = min(minCol, j);   // find the left most column with 1
                minRow = min(minRow, i);   // find the top most row with 1
            }
        }
    }
    return (maxCol - minCol + 1) * (maxRow - minRow + 1); // here 1 is added to the area because the index is start with 0
}
    int main()
{
        vector<vector<int>> grid = {
            {0, 0, 1, 0},  //here the maximunm column is 2 
            {0, 1, 1, 0},  //and the maximnum row is 4 so the area is the 4 * 2 = 8   -> output
            {0, 0, 0, 0},
            {0, 1, 0, 0}
        };
        cout << minimumArea(grid) << endl;
        return 0;
    }