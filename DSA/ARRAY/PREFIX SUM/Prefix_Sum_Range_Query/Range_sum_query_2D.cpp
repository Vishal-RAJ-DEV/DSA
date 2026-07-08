#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class NumMatrix {
public:
    // prefix[i][j] stores sum of ALL elements in rectangle from (0,0) to (i,j)
    vector<vector<int>>prefix;

    /*
     * PREFIX BUILDING LOGIC:
     * =======================
     * We want prefix[i][j] = sum of matrix[0..i][0..j]
     *
     * The recurrence:
     *   prefix[i][j] = matrix[i][j]                 (current cell itself)
     *                + prefix[i-1][j]               (sum of rectangle above: rows 0..i-1, cols 0..j)
     *                + prefix[i][j-1]               (sum of rectangle on left: rows 0..i, cols 0..j-1)
     *                - prefix[i-1][j-1]             (subtract overlap counted twice)
     *
     * Visual of what each term contributes (i=2,j=2 as example):
     *   matrix[i][j]         ->  [X]              (just cell (2,2))
     *   prefix[i-1][j]       ->  rows 0..1, cols 0..2  (everything above (2,2))
     *   prefix[i][j-1]       ->  rows 0..2, cols 0..1  (everything left of (2,2))
     *   -prefix[i-1][j-1]    ->  subtract rows 0..1, cols 0..1  (diagonal overlap removed)
     *
     * Grid view of regions at (i=2, j=2):
     *
     *   (0,0) ──── (0,j-1) ── (0,j)
     *     │   A       │    B    │          A = prefix[i-1][j-1] (top-left overlap)
     *     │           │         │          B = prefix[i-1][j]   - A  (top-right portion)
     *   (i-1,0) ── (i-1,j-1) ─ (i-1,j)    C = prefix[i][j-1]   - A  (bottom-left portion)
     *     │   C       │    D    │          D = matrix[i][j]           (bottom-right single cell)
     *     │           │         │
     *   (i,0) ──── (i,j-1) ── (i,j)
     *
     *   prefix[i][j] = A + B + C + D
     *                = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + matrix[i][j]
     */
    NumMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        prefix.resize( n , vector<int>(m));

        for(int i = 0 ; i< n ; i++){
            for( int j = 0 ; j < m ; j++){
                prefix[i][j] = matrix[i][j];

                // add sum of rectangle from (0,0) to (i-1,j) — region above current cell
                if(i > 0){
                    prefix[i][j] += prefix[i - 1][j];
                }
                // add sum of rectangle from (0,0) to (i,j-1) — region left of current cell
                if( j > 0){
                    prefix[i][j] += prefix[i][j-1];
                }
                // subtract the doubly-counted top-left diagonal region (0,0) to (i-1,j-1)
                if( i > 0 && j > 0){
                    prefix[i][j] -= prefix[i-1][j-1];
                }
            }
        }
    }

    /*
     * RANGE QUERY LOGIC (sumRegion):
     * ===============================
     * We want sum of matrix elements inside rectangle (row1,col1) to (row2,col2).
     *
     * Using inclusion-exclusion on prefix sums:
     *
     *   result = prefix[row2][col2]             (entire rectangle from origin to (row2,col2))
     *          - prefix[row1-1][col2]           (remove rows above the region)
     *          - prefix[row2][col1-1]           (remove columns left of the region)
     *          + prefix[row1-1][col1-1]         (add back the corner subtracted twice)
     *
     * Grid view of query region (r1,c1) to (r2,c2):
     *
     *   (0,0) ─────── (0,c1-1) ──── (0,c2)
     *     │     Q        │     R       │       Q = area above row1, to left of col1  (subtracted twice → added back)
     *     │              │             │       R = area above row1, cols c1..c2       (subtracted once)
     *   (r1,0) ──── (r1,c1-1) ──── (r1,c2)    S = area rows r1..r2, to left of col1 (subtracted once)
     *     │     S        │   RESULT   │       RESULT = our desired answer
     *     │              │             │
     *   (r2,0) ──── (r2,c1-1) ──── (r2,c2)
     *
     *   prefix[row2][col2]           = Q + R + S + RESULT
     *   prefix[row1-1][col2]        = Q + R
     *   prefix[row2][col1-1]        = Q + S
     *   prefix[row1-1][col1-1]      = Q
     *
     *   RESULT = (Q+R+S+RESULT) - (Q+R) - (Q+S) + Q
     *          = prefix[row2][col2] - prefix[row1-1][col2] - prefix[row2][col1-1] + prefix[row1-1][col1-1]
     */
    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = prefix[row2][col2];

        if( row1 > 0){
            res -= prefix[row1 - 1][col2];
        }
        if( col1 > 0){
            res -= prefix[row2][col1 - 1];
        }
        if( row1 > 0 && col1 > 0){
            res += prefix[row1 - 1][col1 - 1];
        }

        return res;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */



int main(){
    
    return 0;
}

