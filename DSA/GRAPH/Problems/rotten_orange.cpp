#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int rottenOrange1(vector<vector<int>>& orange) {
    int n = orange.size();
    int m = orange[0].size();
    
    queue<pair<pair<int, int>, int>> q; // {{row, col}, time}
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    int fresh_oranges = 0;
    
    // Step 1: Find all initially rotten oranges and count fresh ones
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (orange[i][j] == 2) {
                q.push({{i, j}, 0}); // Push all rotten oranges with time 0
                visited[i][j] = true;
            } else if (orange[i][j] == 1) {
                fresh_oranges++;
            }
        }
    }
    
    // If no fresh oranges, return 0
    if (fresh_oranges == 0) return 0;
    
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};
    int maxTime = 0;
    
    // Step 2: BFS to rot oranges level by level
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        
        int row = current.first.first;
        int col = current.first.second;
        int time = current.second;
        
        maxTime = max(maxTime, time);
        
        // Check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            
            // Check bounds and if it's a fresh orange
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && 
                !visited[nrow][ncol] && orange[nrow][ncol] == 1) {
                
                visited[nrow][ncol] = true;
                q.push({{nrow, ncol}, time + 1});
                fresh_oranges--;
            }
        }
    }
    
    // If there are still fresh oranges, return -1
    return (fresh_oranges == 0) ? maxTime : -1;
}
// Breadth-First Search (BFS) function
int BFS(vector<vector<int>> & orange , vector<vector<bool>> & visited){
    int n = orange.size();
    int m = orange[0].size();
    queue<pair<int , int>> q;

    int total_oranges = 0 ;
    int rotten_oranges = 0 ;
    for( int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if( orange[i][j] != 0){
                total_oranges++;
            }
            if( orange[i][j] == 2){
                rotten_oranges++;
                q.push({i , j});
                visited[i][j] = true;
            }
        }
    }

    int time = 0 ;
    int delrow[] = { -1 , 0 , 1 , 0 } ;
    int delcol[] = { 0 , 1 , 0 , -1 };

    while(!q.empty()){
        int size = q.size();
        bool rotten_added = false ;

        for( int i = 0 ; i<size ; i++){
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for(int i = 0 ; i < 4 ;i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];

                if( nrow >= 0 && ncol >= 0 && nrow < n && ncol < m && orange[nrow][ncol] == 1 && !visited[nrow][ncol]){
                    visited[nrow][ncol] = true;
                    orange[nrow][ncol] = 2; // make the orange rotten
                    q.push({nrow , ncol}); // push the newly rotten orange into the queue so that it can rot the adjacent oranges in the next time frame
                    rotten_oranges++;
                    rotten_added = true ; //the moment we rot an orange we set this to true
                    
                }
            }
        }
        if( rotten_added ){
            time++;
        }
    }

    return ( total_oranges == rotten_oranges ) ? time : -1;


}

int rottenOrange( vector<vector<int>> & orange){
    int n = orange.size();
    int m = orange[0].size();

    vector<vector<bool>> visited( n , vector<bool>( m , false));

    return BFS( orange , visited); // first rotten orange at (0,0) 
}
int main(){
    vector< vector<int>> oragne = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };

    int result= rottenOrange1(oragne);
    cout << " Minimum time required to rot all oranges is : " << result << endl;

    return 0;
}
