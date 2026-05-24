#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	/*  Function to implement Bellman Ford
	*   edges: vector of vectors which represents the graph
	*   S: source vertex to start traversing graph with
	*   V: number of vertices
	*
	*   Short Algorithm:
	*   - Initialize distance of source as 0 and all other nodes as infinity.
	*   - Relax every edge V - 1 times.
	*   - Relax means: if going through u gives a shorter distance to v,
	*     then update dist[v].
	*   - After V - 1 rounds, shortest distances are finalized if there is
	*     no negative cycle.
	*   - Do one extra round to check negative cycle.
	*
	*   Why loop goes V - 1 times:
	*   - In a graph with V vertices, the longest possible simple shortest path
	*     can contain at most V - 1 edges.
	*   - A shortest path never needs to repeat a vertex unless there is a cycle.
	*   - So after relaxing all edges V - 1 times, every shortest path has got
	*     enough chances to update its distance.
	*   - If distance still improves after that, it means a negative cycle exists.
	*/
	vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
		// Initially all nodes are unreachable, so distance is infinity.
		vector<int> dist(V, 1e8);

		// Distance from source to itself is always 0.
		dist[S] = 0;

		// Relax all edges V - 1 times.
		// This is enough because any shortest path can have at most V - 1 edges.
		for (int i = 0; i < V - 1; i++) {
			for (auto it : edges) {
				int u = it[0]; //Starting point of the edge
				int v = it[1]; //Ending point of the edge
				int wt = it[2]; //Edge weight

				// If u is reachable and going from u to v gives shorter distance,
				// update the distance of v.
				if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
					dist[v] = dist[u] + wt;
				}
			}
		}

		// Nth relaxation to check negative cycle.
		// If any distance still decreases now, a negative cycle is present.
		for (auto it : edges) {
			int u = it[0];
			int v = it[1];
			int wt = it[2];
			if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
				return { -1};
			}
		}


		return dist;
	}
};


int main() {

	int V = 6;
	vector<vector<int>> edges(7, vector<int>(3));
	edges[0] = {3, 2, 6};
	edges[1] = {5, 3, 1};
	edges[2] = {0, 1, 5};
	edges[3] = {1, 5, -3};
	edges[4] = {1, 2, -2};
	edges[5] = {3, 4, -2};
	edges[6] = {2, 4, 3};

	int S = 0;
	Solution obj;
	vector<int> dist = obj.bellman_ford(V, edges, S);
	for (auto d : dist) {
		cout << d << " ";
	}
	cout << endl;

	return 0;
}
