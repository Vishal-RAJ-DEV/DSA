#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        //prefix sum approch
        int n = grid.size();
        int m = grid[0].size();

        //array to store the prefix sum of the x and y apperance in the matrix 
        vector<int>sumx(m , 0);
        vector<int>sumy(m , 0);

        int result = 0;

        //now traverse the thorough the array 
        //and calcualte the each cell prefix sum of the number of the X and Y 
        for ( int i = 0 ; i< n ; i++){
            //numbers of x and y count in the current row
            int rowX = 0 ;
            int rowY = 0;

            //check each col in the current row
            for (int j = 0;j< m ; j++){
                if( grid[i][j] == 'X') rowX++;
                else if(grid[i][j] == 'Y') rowY++;

                //add the these to the prefix sum to current cell
                sumx[j] += rowX;
                sumy[j] += rowY;

                //check for the current cell ,is it submatrix 
                //total sum of number of x should be greater than 0
                //and should be equal to sum of number of y
                if( sumx[j] > 0 && sumx[j] == sumy[j]) result++;
            }
        }

        return result;
    }
};

int main(){
    Solution sol;
    vector<vector<char>> grid = {
        {'X', 'Y', 'X'},
        {'Y', 'X', 'Y'},
        {'X', 'Y', 'X'}
    };
    int ans = sol.numberOfSubmatrices(grid);
    cout<<"Number of submatrices with equal frequency of X and Y: "<< ans << endl;

    return 0;
}