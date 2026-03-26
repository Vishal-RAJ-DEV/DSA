#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// User function template for C++
class Solution {
  public:
    int rowWithMax1s(vector<vector<int>> &arr) {
                // Return -1 when matrix is empty.
                if (arr.empty() || arr[0].empty()) {
                        return -1;
                }

        int numRow = arr.size();
        int numCol = arr[0].size();
        
        int currRow = 0 ;
        int currcol = numCol - 1;
        
        int maxRowIDX = -1;
        
        while( currRow < numRow && currcol >= 0){
            if( arr[currRow][currcol] == 1){
                maxRowIDX = currRow ;
                currcol--;
            }
            else{
                currRow ++;
            }
        }
        
        return maxRowIDX;
    }
};


int main(){
    int rows, cols;
    cin >> rows >> cols;

    vector<vector<int>> arr(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }

    Solution obj;
    cout << obj.rowWithMax1s(arr) << "\n";

    return 0;
}
