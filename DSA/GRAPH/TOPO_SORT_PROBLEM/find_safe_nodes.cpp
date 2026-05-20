#include <bits/stdc++.h>
using namespace std;

//this is the dfs approach for finding the safe nodes in the directed graph
//it uses the same approach as the cycle detection in the directed graph using dfs but here we are marking the node as safe node if there is no cycle in any of the paths from that node and if there is a cycle in any of the paths from that node then we will mark that node as not safe node
//time complexity: O(V + E) as we are traversing all the nodes and edges of the graph
//space complexity: O(V) for the visited and path visited array and O(V) for the recursive stack space in the worst case when there is a cycle in the graph

class Solution1 {
private:
    bool dfsCheck(int node, vector<vector<int>>& graph, vector<int>& vis, vector<int>& pathVis, vector<int>& check) {
		vis[node] = 1;
		pathVis[node] = 1;
        check[node] = 0;

		// traverse for adjacent nodes
		for (auto it : graph[node]) {
			// when the node is not visited
			if (!vis[it]) {
				if (dfsCheck(it, graph, vis, pathVis , check) == true){
                    check[node] = 0; //not safe node this one 
					return true;
                }
			}
			// if the node has been previously visited
			// but it has to be visited on the same path
			else if (pathVis[it]) {
                check[node] = 0; //mark 0 beacuse cycle is detected here 
				return true; //return true for node that lead to the cylce to mark that node 0 
			}
		}
        check[node] = 1; //if the loop complelte then node leads to the safe node 
		pathVis[node] = 0; //as we are backtracking we need to unmark the node in the path visited  array so that it can be used in other paths
		return false; //at last if there is no cycle in any of the paths then return false
	}
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int v = graph.size();
        vector<int>vis(v, 0); //check for the visited node
		vector<int>pathVis(v, 0);   //check for the node in the current path if we are visiting the same node in the same path then there is a cycle or else there is no cycle for that path 
        vector<int>check(v, 0); //mark 1 if find out that node/vertices is safe node 
        vector<int>safeNode; //contain all the safe nodes

        //loop for starting dfs call for the unvisited node
		for (int i = 0; i < v; i++) { 
			if (!vis[i]) {
				dfsCheck(i, graph, vis, pathVis , check);
			}
		}

        //loop for the push safe node in the safe vector if node is marked as the 1 
        for ( int i = 0 ; i<v;i++){
            if( check[i]== 1 )safeNode.push_back(i);
        }

        return safeNode;
    }
};

//using the bfs approach for finding the safe nodes in the directed graph
//time complexity: O(V + E) as we are traversing all the nodes and edges
//space complexity: O(V) for the indegree array and O(V) for the queue and O(V) for the reverse adjacency list
class Solution {
public:
    // Function to find all eventual safe nodes in a directed graph
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
        vector<int> adjRev[V];  // Reverse adjacency list
        int indegree[V] = {0};  // Indegree array to track nodes with no outgoing edges

        // Build the reverse graph and calculate indegrees
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                //it -> i is the original edge, so in the reverse graph we will have i -> it
                adjRev[it].push_back(i);  // Reverse the direction of edges
                indegree[i]++;  // Increment indegree for the current node
            }
        }

        queue<int> q;  // Queue to store nodes with no outgoing edges (safe nodes)
        vector<int> safeNodes;

        // Add all nodes with 0 indegree to the queue
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Process the queue to find all safe nodes
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);  // This node is safe
            for (auto it : adjRev[node]) {
                indegree[it]--;  // Decrease indegree of the parent nodes
                if (indegree[it] == 0) {
                    q.push(it);  // If indegree becomes 0, it is a safe node
                }
            }
        }

        sort(safeNodes.begin(), safeNodes.end());  // Sort the safe nodes
        return safeNodes;
    }
};

int main() {
    // Adjacency list representation of the graph
    vector<int> adj[12] = {{1}, {2}, {3, 4}, {4, 5}, {6}, {6}, {7}, {}, {1, 9}, {10},
                           {8}, {9}};
    int V = 12;  // Number of nodes in the graph

    Solution obj;
    vector<int> safeNodes = obj.eventualSafeNodes(V, adj);  // Call function to get safe nodes

    for (auto node : safeNodes) {
        cout << node << " ";  // Print the safe nodes
    }
    cout << endl;

    Solution1 obj1;
    vector<vector<int>> graph = {{1}, {2}, {3, 4}, {4, 5}, {6}, {6}, {7}, {}, {1, 9}, {10},
                                  {8}, {9}};
    vector<int> safeNodes1 = obj1.eventualSafeNodes(graph);  // Call function to get safe nodes
    for (auto node : safeNodes1) {
        cout << node << " ";  // Print the safe nodes
    }
    cout << endl;

    return 0;
}
