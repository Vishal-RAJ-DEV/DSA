#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:

    vector<int> bfs( int v , vector<vector<int>> &adj ){
        vector<bool> visited( v + 1 , false);
        visited[0] = true;
        queue<int> q;
        q.push(0);

        vector<int> bfs_traversal;

        while( !q.empty()){
            int node = q.front();
            q.pop();
            bfs_traversal.push_back(node);

            for( auto it : adj[node]){
                if( !visited[it]){
                    visited[it] = true;
                    q.push(it);
                }
            }
        }
        return bfs_traversal;
    }
    
};

//time complexity : o(v) + o( 2e)  where v is the number of vertices and e is the number of edges , since we are using adjacency list so we are traversing all the vertices and all the edges 
// 2e for undirected graph each edge is counted twice
//space complexity : o(v) for visited array + o(v) for queue + o(v) for bfs_traversal

void addedge(vector<vector<int>> &adj, int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u); // for undirected graph
}
int main(){
    int v = 4 ;  // number of vertices
    // Step 1: Create adjacency list
    vector<vector<int>> adj(v + 1);  // here total 5 are  0 , 1 , 2 , 3 , 4 vertices so v + 1 beacuse we are starting from 0 - 0 based indexing
    addedge(adj, 0, 1);
    addedge(adj, 1, 2);
    addedge(adj, 1, 3);
    addedge(adj, 0, 4);

    // Step 2: BFS Traversal
    Solution obj;
    vector<int> result = obj.bfs( v , adj);

    for(int i : result){
        cout << i << " ";
    }


    return 0;
}
