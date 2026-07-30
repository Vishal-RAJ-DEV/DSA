#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
                        TARJAN'S ALGORITHM - FINDING BRIDGES
================================================================================

INTUITION
---------

A bridge (critical connection) is an edge whose removal disconnects the graph.

The main idea is to determine whether there exists another path from a child's
subtree back to one of its ancestors.

If NO alternate path exists, then the only way to reach that subtree is through
the current edge, making that edge a bridge.

Example:

        0
       / \
      1---2
      |
      3

Edge (1,3) is a bridge because node 3 cannot reach any ancestor of node 1
without using edge (1,3).

However,

        0
       / \
      1---2

None of these edges are bridges because there is always another path.


================================================================================
WHY DO WE NEED TWO ARRAYS?
================================================================================

1) tin[] (Time of Insertion / Discovery Time)

tin[node] tells us:
"When was this node first visited during DFS?"

Example DFS order:

0 -> 1 -> 2 -> 3

Then

Node : 0 1 2 3
tin  : 1 2 3 4

This value NEVER changes.


------------------------------------------------------

2) low[] (Lowest Reachable Discovery Time)

low[node] tells us:

"What is the earliest discovered node that I can reach
from this node or any node inside my DFS subtree
using at most ONE back edge?"

Initially

low[node] = tin[node]

because every node can obviously reach itself.

Later, while returning from DFS,
low[] may become smaller if we discover a back edge.

Example

0
|\
| \
1  2
 \ |
  \|
   3

Suppose

tin

0 -> 1
1 -> 2
3 -> 3
2 -> 4

If node 3 has a back edge to node 0,

then

low[3] = tin[0] = 1

which means

"Although I entered node 3 at time 3,
I can still reach node 0 whose discovery time is 1."

Therefore low[] keeps propagating upward.


================================================================================
WHEN IS AN EDGE A BRIDGE?
================================================================================

Suppose

u -------- v

where u is parent and v is child.

After DFS(v) finishes,

if

low[v] > tin[u]

then

the subtree rooted at v CANNOT reach
u or any ancestor of u.

Therefore,

removing edge (u,v)

disconnects the graph.

Hence,

(u,v) is a bridge.


Why STRICTLY greater (>)

Suppose

0
/ \
1--2

Here

low[2] = tin[0]

There is another path.

So edge (1,2) is NOT a bridge.

Hence the condition is

low[child] > tin[parent]

NOT

>=


================================================================================
ALGORITHM
================================================================================

1. Build the adjacency list.

2. Maintain two arrays

       tin[]
       low[]

3. Start DFS from any node.

4. Whenever a node is visited

       tin[node] = low[node] = timer++

5. For every neighbour

   A) If neighbour is parent
      Ignore it.

   B) If neighbour is not visited

      DFS(neighbour)

      After returning

      low[node] = min(low[node], low[neighbour])

      If

      low[neighbour] > tin[node]

      then

      (node, neighbour)

      is a bridge.

   C) If neighbour is already visited

      It is a Back Edge.

      Update

      low[node] = min(low[node], tin[neighbour])

6. All collected edges are the bridges.


================================================================================
TIME COMPLEXITY
================================================================================

Building Graph : O(V + E)

DFS            : O(V + E)

Total          : O(V + E)


================================================================================
SPACE COMPLEXITY
================================================================================

Adjacency List : O(V + E)

DFS Stack      : O(V)

tin[]          : O(V)

low[]          : O(V)

Total          : O(V + E)

================================================================================
*/

class Solution {
private:
    int timer = 1; // Global timer to assign discovery times

    // Depth-First Search (DFS) to find bridges
    void dfs(int node, int parent, vector<int> &vis,
             vector<int> adj[], int tin[], int low[],
             vector<vector<int>> &bridges) {

        vis[node] = 1;                 // Mark current node as visited

        // Assign discovery time and initialize lowest reachable time
        tin[node] = low[node] = timer;
        timer++;

        // Traverse all adjacent vertices
        for (auto it : adj[node]) {

            // Ignore the edge back to parent
            if (it == parent) continue;

            // Tree Edge
            if (vis[it] == 0) {

                dfs(it, node, vis, adj, tin, low, bridges);

                // Child may have found a back edge to an ancestor,
                // so propagate that information upward.
                low[node] = min(low[node], low[it]);

                // If child cannot reach this node or any ancestor,
                // then removing this edge disconnects the graph.
                if (low[it] > tin[node]) {
                    bridges.push_back({it, node});
                }
            }

            // Back Edge
            else {

                // IMPORTANT:
                // We update using tin[it], NOT low[it].
                //
                // Reason:
                // This back edge directly reaches an already visited ancestor.
                // We only care about the ancestor's discovery time.
                //
                // Using low[it] here is incorrect because low[it] may include
                // information obtained from other DFS branches.
                low[node] = min(low[node], tin[it]);
                //OR 
                // low[node] = min(low[node], low[it]);
                //both are correct but using tin[it] is more precise for back edges.
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(
        int n,
        vector<vector<int>>& connections) {

        // Step 1: Build adjacency list
        vector<int> adj[n];

        for (auto it : connections) {
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Step 2: Initialize helper arrays
        vector<int> vis(n, 0);

        int tin[n]; // Discovery time of every node
        int low[n]; // Earliest discovery time reachable

        vector<vector<int>> bridges;

        // Step 3:
        // For this problem the graph is connected.
        // For a disconnected graph, run DFS for every unvisited node.
        dfs(0, -1, vis, adj, tin, low, bridges);

        return bridges;
    }
};

int main() {

    int n = 4;

    vector<vector<int>> connections = {
        {0,1},
        {1,2},
        {2,0},
        {1,3}
    };

    Solution obj;

    vector<vector<int>> bridges =
        obj.criticalConnections(n, connections);

    cout << "Critical Connections (Bridges): ";

    for (auto it : bridges) {
        cout << "[" << it[0] << ", " << it[1] << "] ";
    }

    cout << endl;

    return 0;
}