#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void bfs( int row , int col ,vector<vector<int>>& grid , vector<vector<int>>& vis){
        int n = grid.size();
        int m = grid[0].size();
        //four direction 
        int delrow[] = { -1 , 0 , 1 , 0};
        int delcol[] = { 0 , 1 , 0 , -1};
        queue<pair<int, int >> q ;
        q.push({row , col}); //push in the queue
        vis[row][col] = 1;//mark visitd 
        while( !q.empty()){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for ( int i = 0 ; i< 4; i++){
                int nrow = r + delrow[i];
                int ncol = c + delcol[i];

                if(nrow >= 0 && nrow < n && ncol >=0 && ncol< m && !vis[nrow][ncol] && grid[nrow][ncol] == 1){
                    vis[nrow][ncol] = 1 ;
                    q.push({nrow, ncol});
                }
            }
        }
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if( n == 0 || m == 0 ) return 0;
        vector<vector<int>> vis ( n , vector<int>(m , 0));
        //search for the 1 in the boundary 
        for ( int i = 0 ;i< n ; i++){
            for ( int j = 0 ; j <m ; j++){
                //first row and col  and last row last col 
                if( i == 0 || j == 0 || i == n -1 || j == m - 1){
                    if( grid[i][j] == 1 && !vis[i][j]){
                        bfs( i , j , grid , vis);
                    }
                }
            }
        }

        //now all the boundary 1's is mark visited 
        //and left 1's are the enclaves , we count that 
        int enclaves = 0 ;
        for ( int i= 0 ; i < n ; i++){
            for ( int j = 0; j < m; j++){
                if( !vis[i][j] && grid[i][j] == 1){
                    enclaves ++;
                }
            }
        }
        return enclaves;
    }
};

int main() {
    // Define the grid
    vector<vector<int>> grid{
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    // Create Solution instance
    Solution obj;

    // Compute and print the number of enclaves
    cout <<" number of enclaves: "<<obj.numEnclaves(grid) << endl; // Expected: 3
    return 0;
}
