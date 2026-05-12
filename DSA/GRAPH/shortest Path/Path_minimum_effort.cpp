#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
*/

class Solution {
public:
    //          {effort,{x1 , x2}}
    //store the distance with the corrdinates
    typedef pair<int , pair<int , int >>p;
    //store all the four direction coredinates
    vector<vector<int>> dirs ={{-1,0},{1,0},{0,1},{0,-1}};

    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        //this store the max effort to reach a cell
        vector<vector<int>>dist(n, vector<int>(m ,INT_MAX ));
        priority_queue<p , vector<p> , greater<p>> pq; 

        //store the source node which has the 0 effort since its a inital node
        pq.push({0 ,{0,0}});
        //store the source node in dist vector
        dist[0][0] = 0;
        
        //function to check the corrdinate in bounded or nor
        auto isSafe = [&](int x , int y){
            return x >=0 && y >= 0 && x<n && y<m;
        };

        //now pop the top of the pq and relax all node using that 
        while( !pq.empty()){
            int effort = pq.top().first;
            auto corrd = pq.top().second;
            pq.pop();

            int x = corrd.first;
            int y = corrd.second;

            //now go to all the direction 
            for(auto &dir : dirs){
                int newx = x + dir[0];
                int newy = y + dir[1];

                if( isSafe(newx , newy)){
                    int diff = abs( heights[x][y] - heights[newx][newy]);
                    int neweffort = max (effort , diff);//new effort to reach the currrent cell

                    //now check this effort is lesser than stored effort in dist
                    //if less than store it 
                    if( neweffort < dist[newx][newy]){
                        //put in the dist 
                        dist[newx][newy] = neweffort;
                        //now push in the pq
                        pq.push({neweffort,{newx , newy}});
                    }
                }
            }
        }

        return dist[n-1][m-1];
    }
};


int main(){
    Solution sol;
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    cout << sol.minimumEffortPath(heights) << endl; // Output the minimum effort required to reach the destination
    return 0;
}
