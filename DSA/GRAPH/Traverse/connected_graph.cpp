/*
connected graph is a type of graph in which there is a path between every pair of vertices. In other words, all the vertices in a connected graph are reachable from any other vertex in the graph.

Input:
the number of nodes and edges followed by the edges
numbere of nodes = 10 
number of edges = 8
edges:
components 1 :- 1-2 , 2-4 , 4-3 , 3-1
components 2 :- 5-6 , 6-7 , 7-5
components 3 :- 8-9 
components 4 :- 10

this is a single connected graph with 4 components
to traverse a connected graph we can use either DFS or BFS with the help of a visited array to keep track of visited nodes.

*/

#include <bits/stdc++.h>
using namespace std;

// DFS function
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

int main() {
    int V = 10;  // number of vertices

    // Step 1: Create adjacency list
    vector<vector<int>> adj(V + 1);

    //components 1 :- 1-2 , 2-4 , 4-3 , 3-1
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(4);
    adj[4].push_back(2);
    adj[4].push_back(3);
    adj[3].push_back(4);
    adj[3].push_back(1);
    adj[1].push_back(3);

    //components 2 :- 5-6 , 6-7 , 7-5
    adj[5].push_back(6);
    adj[6].push_back(5);
    adj[6].push_back(7);
    adj[7].push_back(6);
    adj[7].push_back(5);
    adj[5].push_back(7);

    //components 3 :- 8-9
    adj[8].push_back(9);
    adj[9].push_back(8);

    // Step 2: Visited array
    vector<bool> visited(V + 1, false);

    // Step 3: Traverse all components
    int componentCount = 0;
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            componentCount++;
            cout << "Component " << componentCount << ": ";
            dfs(i, adj, visited);
            cout << endl;
        }
    }

    return 0;
}
