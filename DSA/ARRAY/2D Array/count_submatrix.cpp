#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//brute force approch using 4 loops

int countsubmatrix( vector<vector<int>>& grid , int k ){
    int n = grid.size();
    int m = grid[0].size();

    int cnt = 0 ;
    for ( int i = 0 ; i < n ;i++){
        for( int j = 0 ; j < m ; j++){

            
        }
    }
}

//optimal solution for the count submatrices with all ones less than or equal to k problem
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        int cnt = 0 ;
        for( int i = 0 ; i < n ;i++){
            for( int j = 0 ; j < m ; j++){

                if( i>0){
                    grid[i][j] += grid[i-1][j];
                }
                if(j > 0){
                    grid[i][j] += grid[i][j-1];
                }
                if( i >0 && j > 0){
                    grid[i][j] -= grid[i-1][j-1];
                }

                if( grid[i][j] <= k)cnt++;
            }
        }

        return cnt;
    }
};

int main(){
    vector<vector<int>> grid = {{1,1,1},{1,0,1},{1,1,1}};
    int k = 4;
    Solution s;
    cout << s.countSubmatrices(grid, k) << endl;
    return 0;
}
