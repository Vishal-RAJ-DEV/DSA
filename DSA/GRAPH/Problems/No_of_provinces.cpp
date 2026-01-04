
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

    //here we are giving the adjency matrix directly
    vector<vector<int>> adjMatrix = {{1,1,0},{1,1,0},{0,0,1}};

    int V = adjMatrix.size();
    // Step 1: Create adjacency list
    vector<vector<int>> adj(V);
    
    // Convert adjacency matrix to adjacency list
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjMatrix[i][j] == 1 && i != j) {  
                adj[i].push_back(j);
                adj[j].push_back(i); // for undirected graph
            }
        }
    }


    // Step 2: Visited array
    vector<bool> visited(V, false);

    // Step 3: Traverse all components
    int componentCount = 0;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            componentCount++; // this will count the number of provinces
            cout << "Component " << componentCount << ": ";
            dfs(i, adj, visited);
            cout << endl;
        }
    }

    return 0;
}

/*
Time Complexity: O(V²)
Breakdown:

Matrix to Adjacency List Conversion:

Nested loops: O(V × V) = O(V²)
This dominates the time complexity
DFS Traversal:

Each node is visited exactly once: O(V)
Each edge is traversed exactly once: O(E)
Total DFS: O(V + E)
For adjacency matrix: E ≤ V², so O(V + E) = O(V²)

Overall: O(V²) + O(V²) = O(V²)

Space Complexity: O(V²)
Breakdown:

Input Adjacency Matrix: O(V²)
Adjacency List: O(V + E) = O(V²) (worst case when graph is dense)
Visited Array: O(V)
DFS Recursion Stack: O(V) (worst case: linear chain)
*/
