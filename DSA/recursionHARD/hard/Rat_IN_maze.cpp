#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool safe( int row , int col , vector<vector<int>> &maze , vector<vector<int>> &visited , int n , int m ){
    if( row >=0 && row < n && col >=0 && col < m && maze[row][col] == 1 && visited[row][col] == 0 ){
        return true ;
    }
    return false ;
}

//function to find all paths from top-left to bottom-right in the maze using delrow and delcol arrays
void ratINmaze_path( int row , int col , vector<vector<int>> &maze , vector<string> & path , string current , vector<vector<int>> &visited){
    int n = maze.size();
    int m = maze[0].size();
    
    if( row == n -1 && col == m -1 ){
        path.push_back( current );
        cout<< current << endl;
        return ;
    }
    
    visited[row][col] = 1 ; //mark as visited
    
    // Direction arrays: Down, Left, Right, Up
    int delrow[] = {1, 0, 0, -1};
    int delcol[] = {0, -1, 1, 0};
    char directions[] = {'D', 'L', 'R', 'U'};
    
    // Try all 4 directions
    for(int i = 0; i < 4; i++){
        int newrow = row + delrow[i];
        int newcol = col + delcol[i];
        
        if(safe(newrow, newcol, maze, visited, n, m)){
            ratINmaze_path(newrow, newcol, maze, path, current + directions[i], visited);
        }
    }
    
    //now when all the paths are explored and we are backtracking we need to unmark the cell as visited so that it can be used in other paths
    visited[row][col] = 0 ;
}

void ratINmaze_path( int row , int col , vector<vector<int>> &maze , vector<string> & path , string current , vector<vector<int>> &visited){
    int n = maze.size();
    int m = maze[0].size();
    if( row == n -1 && col == m -1 ){
        path.push_back( current );
        cout<< current << endl;
        return ;
    }
    visited[row][col] = 1 ; //mark as visited
    //down
    if( safe( row + 1 , col , maze , visited , n , m )){
        ratINmaze_path( row + 1 , col , maze , path , current + 'D' , visited );
    }
    //left
    if( safe( row , col - 1 , maze , visited , n , m )){
        ratINmaze_path( row , col - 1 , maze , path , current + 'L' , visited );
    }
    //right 
    if( safe( row , col + 1 , maze , visited , n , m )){
        ratINmaze_path( row , col + 1 , maze , path , current + 'R' , visited );
    }
    //up 
    if( safe( row - 1 , col , maze , visited , n , m )){
        ratINmaze_path( row - 1 , col , maze , path , current + 'U' , visited );
    }
    //now when all the paths are explored and we are backtracking we need to unmark the cell as visited so that it can be used in other paths
    visited[row][col] = 0 ;
}


int main(){
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {1, 1, 1, 1}
    };

    vector<string> path ;
    vector<vector<int>> visited ( maze.size() , vector<int> ( maze[0].size() , 0 )); //to mark visited cells 
    if( maze[0][0] == 0 ){
        cout<< " No paths exist " << endl;
        return 0;
    }
    ratINmaze_path( 0 , 0 , maze , path , "" ,visited );
    cout<< "All possible paths are: " << endl;
    for( auto i : path ){
        cout<< i << endl;
    }
    return 0;
}