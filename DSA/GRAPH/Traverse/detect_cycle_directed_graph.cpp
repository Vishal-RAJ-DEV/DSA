#include <bits/stdc++.h>
using namespace std;


//time complexity: O(V + E) as we are traversing all the nodes and edges of the graph
//space complexity: O(V) for the visited and path visited array and O(V) for the recursive stack space in the worst case when there is a cycle in the graph
class Solution {
private:
	bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]) {
		vis[node] = 1;
		pathVis[node] = 1;

		// traverse for adjacent nodes
		for (auto it : adj[node]) {
			// when the node is not visited
			if (!vis[it]) {
				if (dfsCheck(it, adj, vis, pathVis) == true)
					return true;
			}
			// if the node has been previously visited
			// but it has to be visited on the same path
			else if (pathVis[it]) {
				return true;
			}
		}

		pathVis[node] = 0; //as we are backtracking we need to unmark the node in the path visited array so that it can be used in other paths
		return false; //at last if there is no cycle in any of the paths then return false
	}
public:
	// Function to detect cycle in a directed graph.
	bool isCyclic(int V, vector<int> adj[]) {
		int vis[V] = {0}; //check for the visited node
		int pathVis[V] = {0};   //check for the node in the current path if we are visiting the same node in the same path then there is a cycle or else there is no cycle for that path 

		for (int i = 0; i < V; i++) { //check for the cycle in the graph for all the nodes as there can be disconnected components in the graph
			if (!vis[i]) {
				if (dfsCheck(i, adj, vis, pathVis) == true) return true;
			}
		}
		return false;
	}
};


int main() {

	// V = 11, E = 11;
	vector<int> adj[11] = {{}, {2}, {3}, {4, 7}, {5}, {6}, {}, {5}, {9}, {10}, {8}};
	int V = 11;
	Solution obj;
	bool ans = obj.isCyclic(V, adj);

	if (ans)
		cout << "True\n";
	else
		cout << "False\n";

	return 0;
}
