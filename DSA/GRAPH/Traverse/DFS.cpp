#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public :

    void dfs( int node , vector<int>  adj[] , vector<int> &visited , vector<int> & result){
        visited[node] = 1 ;
        result.push_back(node);

        for( auto neighbor : adj[node]){
            if( !visited[neighbor]){
                dfs( neighbor , adj , visited , result); //send the neighbor as the next node to visit and push it into result 
                //and backtrack when all its neighbors are visited and go to the unvisited neighbor of the previous node
            }
        }
    }
};

//time complexity : O( V + E)  where V is the number of vertices and E is the number of edges
//space complexity : O( V) for visited array and O( V) for recursion stack
int main(){
     // Number of vertices
    int V = 5;

    // Adjacency list
    vector<int> adj[V]; //size of 5 because vertices are 0,1,2,3,4 - 0 based indexing
    adj[0] = {1, 2};  // edges from vertex 0 to 1 and 2 like neighboring nodes
    adj[1] = {0, 3};
    adj[2] = {0, 4};
    adj[3] = {1};
    adj[4] = {2};

    // Visited array
    vector<int> visited(V, 0);

    // Result vector
    vector<int> result;

    // Create object
    Solution sol;

    // Run DFS from node 0
    sol.dfs(0, adj, visited, result);

    // Print traversal
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;



    return 0;
}