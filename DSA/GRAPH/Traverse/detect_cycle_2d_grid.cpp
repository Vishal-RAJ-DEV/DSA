#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/*

the question is to detect a cycle in a 2D grid of characters.
the approach is to use dfs to traverse the grid and check for the same character in the adjacent cells and if we find the same character in the adjacent cells then we will check for the visited array and if the visited array is true then there is a cycle in the grid and if the visited array is false then we will continue to traverse the grid until we find a cycle or we have traversed all the cells of the grid.

*/

//time complexity: O(n*m) as we are traversing all the cells of the grid
//space complexity: O(n*m) for the visited array and O(n*m) for the
//dfs recursive stack space in the worst case when there is a cycle in the grid
//dfs approach to detect cycle in a 2D grid of characters
class Solution {
public:
    //these are the direction in which we need to check 
    int dir[4][2] = {{0 ,1 } , { 0 , -1} , { 1  , 0 }  , { -1 , 0}};

    bool dfs( int r , int c , int pr , int pc ,vector<vector<bool>>&vis , vector<vector<char>>& grid){
        vis[r][c] = true;

        for( auto &d : dir){
            int nr = r + d[0];
            int nc = c + d[1];
            //index should be in the bound
            if(nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size()) continue;
            //skip the parent index 
            if( nr == pr && nc == pc)continue;

            //now check on the same character
            if( grid[nr][nc] == grid[r][c]){
                //same character with visted index means there is cycle 
                if(vis[nr][nc])return true;

                if(dfs(nr , nc , r , c, vis , grid)) return true;
            }
        }
        return false;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>>vis( n , vector<bool>(m , false));

        for( int i = 0 ; i < n ; i++){
            for( int j = 0 ;j< m ; j++){
                if( !vis[i][j]){
                    if( dfs( i , j , -1 , -1 , vis , grid)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

//bfs approach to detect cycle in a 2D grid of characters
class Solution {
public:
    bool bfs(int i, int j, vector<vector<char>>& grid,
             vector<vector<bool>>& visited) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int, int>, pair<int, int>>> q;
        q.push({{i, j}, {-1, -1}});
        visited[i][j] = true;

        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int x = curr.first.first;
            int y = curr.first.second;
            int px = curr.second.first;
            int py = curr.second.second;

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;

                if (grid[nx][ny] != grid[x][y])
                    continue;

                if (nx == px && ny == py)
                    continue;

                if (visited[nx][ny])
                    return true;

                visited[nx][ny] = true;
                q.push({{nx, ny}, {x, y}});
            }
        }
        return false;
    }

    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j]) {
                    if (bfs(i, j, grid, visited)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main(){
    vector<vector<char>> grid = {{'a','a','a','a'},
                                 {'a','b','b','a'},
                                 {'a','b','b','a'},
                                 {'a','a','a','a'}};
    Solution obj;
    bool ans = obj.containsCycle(grid);
    if(ans) cout<<"True\n";
    else cout<<"False\n";

    return 0;
}