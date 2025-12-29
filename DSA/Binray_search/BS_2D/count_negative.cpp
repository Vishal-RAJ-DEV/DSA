#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
leetcode :- 1351. Count Negative Numbers in a Sorted Matrix
Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, return the number of negative numbers in grid.
Example 1:

Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.
Example 2:

Input: grid = [[3,2],[1,0]]
Output: 0
*/
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int cnt = 0 ;
        for( int i = 0 ; i<m ; i++){
            int low = 0 ; int high = n - 1; //column size 
            int first_neg = n;

            while( low <= high){
                int mid  = low + ( high - low ) / 2;

                if(grid[i][mid] < 0 ){
                    first_neg = mid;
                    //so each column is sorted so may be in left there could be -1  so search in left side
                    high = mid - 1;
                }
                else low = mid + 1;
            }
            cnt += ( n - first_neg);
        }
        return cnt;
    }
};
int main(){
    return 0;
}