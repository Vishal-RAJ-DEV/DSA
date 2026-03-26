#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement: Given a 2D grid of integers and an integer k, find the minimum absolute difference between any two elements in each k x k submatrix of the grid. Return a 2D array where each element at position (i, j) contains the minimum absolute difference for the k x k submatrix starting at (i, j).
input : grid = [[1, 2, 3], [4, 5, 6], [7, 8, 9]], k = 2
output : [[1, 1], [1, 1]]

*/
class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        //res only store the abosolute diff of the submatrix of k * k 
        vector<vector<int>>res( n - k + 1 , vector<int>( m - k + 1));

        //loop all in the matix 
        //i will go till n - k , beacuse at every row we need the k * k submatrix , so it can't go beyond n - k 
        for( int i = 0 ; i <= n - k ; i++){
            for(int j = 0 ; j <= m - k ; j++){

                //store the all the element of the submatrix and in the sorted way 
                set<int>st;
                for( int _i = i ; _i <= i + k -1 ; _i++){
                    for ( int _j  = j ; _j <= j + k - 1 ; _j++){
                        st.insert( grid[_i][_j]);
                    }
                }

                //edge case 
                //if the set have only one elemenet , there will no differnce , it is last element
                if( st.size() == 1){
                    res[i][j] = 0;
                    continue;
                }

                //now traverse the submatrix element form the set which is sorted
                //adjacent element give the minimum difference so check on each adjacent 
                //and store the minimum form them
                int minVal  = INT_MAX;
                auto prev = st.begin();
                auto curr = next(prev);
                while( curr != st.end ()){
                    minVal = min( minVal , *curr - *prev);
                    prev = curr;
                    curr++;
                }
                //now minval have the minimum difference form the current submatrix 
                res[i][j] = minVal;
            }
        }
        return res;
        
    }
};

int main(){
    Solution sol;
    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int k = 2;
    vector<vector<int>> ans = sol.minAbsDiff(grid, k);
    cout<<"Minimum absolute difference for each 2x2 submatrix: "<<endl;
    for (const auto& row : ans) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}