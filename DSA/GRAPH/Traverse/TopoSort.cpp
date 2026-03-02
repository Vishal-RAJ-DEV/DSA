#include <bits/stdc++.h>
using namespace std;


//kahn's algorithm for topological sort
//time complexity: O(V + E) as we are traversing all the nodes and edges of the graph
//space complexity: O(V) for the in-degree array and O(V) for the queue
// Creating a class named Solution
class Solution1 {
public:
    // Function to perform BFS-based Topological Sort
    vector<int> topologicalSort(int V, vector<int> adj[]) {
        // Create a vector to store the in-degree of each vertex
        vector<int> indegree(V, 0);
        
        // Loop through all vertices to calculate in-degree
        for (int i = 0; i < V; i++) {
            // Traverse all adjacent vertices of the current vertex
            for (auto it : adj[i]) {
                // Increase in-degree of the connected vertex
                indegree[it]++;
            }
        }
        
        // Create a queue to store vertices with in-degree zero
        queue<int> q;
        
        // Loop through all vertices
        for (int i = 0; i < V; i++) {
            // If in-degree is zero, add to queue
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Vector to store the topological order
        vector<int> topo;
        
        // Process until queue is empty
        while (!q.empty()) {
            // Get the front vertex from the queue
            int node = q.front();
            q.pop();
            
            // Add it to the topological order
            topo.push_back(node);
            
            // Reduce in-degree of its adjacent vertices
            for (auto it : adj[node]) {
                indegree[it]--;
                // If in-degree becomes zero, push it into queue
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }
        
        // Return the topological ordering
        return topo;
    }
};

//using the dfs approach for topological sort
//time complexity: O(V + E) as we are traversing all the nodes and edges
//space complexity: O(V) for the visited array and O(V) for the recursive stack space in the worst case when there is a cycle in the graph
// Class containing the solution logic
class Solution {
public:
    // Function to perform DFS
    void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        // Mark the current node as visited
        vis[node] = 1;

        // Explore all neighbors of this node
        for (auto it : adj[node]) {
            // If the neighbor is not visited, recursively perform DFS
            if (!vis[it]) {
                dfs(it, adj, vis, st);
            }
        }

        // After visiting all neighbors, push this node into the stack
        //so in the back track element which is the last element will be the first element in the topological sort and the first element which is the starting node will be the last element in the topological sort
        st.push(node);
    }

    // Function to perform Topological Sort
    vector<int> topoSort(int V, vector<int> adj[]) {
        // Create a visited array to mark visited vertices
        vector<int> vis(V, 0);

        // Stack to store vertices in finishing order
        stack<int> st;

        // Perform DFS from each unvisited vertex
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, st);
            }
        }

        // Prepare the result array
        vector<int> ans;
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        // Return the topological ordering
        return ans;
    }
};

// Driver code
int main() {
    // Number of vertices and edges
    int V = 6, E = 6;

    // Adjacency list representation of the graph
    vector<int> adj[V];
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    // Create an object of Solution
    Solution obj;

    // Get the topological order
    vector<int> res = obj.topoSort(V, adj);

    // Print the result
    cout << "Topological Sort: ";
    for (auto it : res) {
        cout << it << " ";
    }
    cout << endl;

    return 0;
}
