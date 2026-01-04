#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// Breadth-First Search (BFS) function
void BFS( int row , int col ,vector<vector<int>> &ans, int initalcolor , int newcolor ,  int delrow[] , int delcol[] , vector<vector<int>>& image){
    int m = image.size();
    int n = image[0].size();
    queue<pair<int,int>> q;
    q.push({row , col});
    ans[row][col] = newcolor;

    while( !q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for( int i = 0 ; i< 4 ; i++){
            int nrow = r + delrow[i];
            int ncol = c + delcol[i];

            if( nrow >= 0 && nrow < m && ncol >= 0 && ncol < n && image[nrow][ncol] == initalcolor && ans[nrow][ncol] != newcolor){
                ans[nrow][ncol] = newcolor;
                q.push({nrow , ncol});
            }
        }
    }
}

// Depth-First Search (DFS) function
void DFS( int row , int col ,vector<vector<int>> &ans, int initalcolor , int newcolor ,  int delrow[] , int delcol[] , vector<vector<int>>& image){
    ans[row][col] = newcolor;
    int m = image.size();
    int n = image[0].size();

    for( int i = 0 ; i< 4 ; i++){
        // here we are adding the direction values to the current row and col to get the new row and col
        int nrow = row + delrow[i]; 
        int ncol = col + delcol[i];

        if( nrow >= 0 && nrow < m && ncol >= 0 && ncol < n && image[nrow][ncol] == initalcolor && ans[nrow][ncol] != newcolor){
            DFS( nrow , ncol , ans , initalcolor , newcolor , delrow , delcol , image);
        }
    }
}

vector<vector<int>> floodFill( vector<vector<int>> & image , int sr , int sc , int newcolor){
    int initalcolor = image[sr][sc];
    vector<vector<int>> ans = image ;

    int delrow[] = { -1 , 0 , 1 , 0 } ;
    int delcol[] = { 0 , 1 , 0 , -1 } ;
    DFS(sr , sc, ans , initalcolor , newcolor , delrow , delcol , image);
    return ans ;
}


int main()
{
    vector<vector<int>> image= {{1,1,1},{1,1,0},{1,0,1}};
    int newcolor = 2 ;
    int sr = 1 ;
    int sc = 1 ;
    vector<vector<int>> result = floodFill( image , sr , sc , newcolor);
    for( int i = 0 ; i< result.size() ; i++){
        for( int j = 0 ; j< result[0].size() ; j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}