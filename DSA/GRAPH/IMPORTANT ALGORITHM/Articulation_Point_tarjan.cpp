#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
                    ARTICULATION POINTS (TARJAN'S ALGORITHM)
===============================================================================

INTUITION
---------
An articulation point (or cut vertex) is a vertex whose removal increases
the number of connected components in the graph.

Observation:
------------
While performing DFS, every node tries to know:

"Can my subtree reach any ancestor of mine without using me?"

If the answer is NO, then I am the only bridge between my subtree and
the remaining graph, therefore I am an articulation point.

To answer this efficiently, Tarjan's Algorithm maintains two arrays:

1. tin[node]
   = Discovery time of the node.
   = The time when the node is first visited.

2. low[node]
   = The minimum discovery time reachable from this node
     (using tree edges and at most one back edge).

----------------------------------------------------------------------------
Articulation Point Conditions
----------------------------------------------------------------------------

Case 1 : Root Node

If the root has more than one DFS child,
then removing the root disconnects those subtrees.

Condition:
child > 1

--------------------------------------------------

Case 2 : Non-root Node

Suppose

          node
          /
       child

If

low[child] >= tin[node]

then the child's subtree cannot reach any ancestor of node.

So removing node disconnects the child's subtree.

Hence node is an articulation point.

----------------------------------------------------------------------------
ALGORITHM
----------------------------------------------------------------------------

1. Build the adjacency list.

2. Initialize
      vis[]  -> visited array
      tin[]  -> discovery time
      low[]  -> lowest reachable discovery time
      timer  -> DFS timer

3. Run DFS from every unvisited node
   (graph may be disconnected).

4. During DFS

   • Mark node visited.

   • Store discovery time.

   • Initially
         low[node] = tin[node]

   • Traverse every neighbour.

       a) Parent
          Ignore.

       b) Back Edge
          Update

          low[node] = min(low[node], tin[neighbour])

       c) Tree Edge

          DFS(child)

          Update

          low[node] = min(low[node], low[child])

          Check articulation condition

          if(low[child] >= tin[node])
                node is articulation point

5. Handle root separately.

6. Return every marked node.

----------------------------------------------------------------------------
TIME COMPLEXITY
----------------------------------------------------------------------------

Building Graph : O(E)

DFS            : O(V + E)

Overall        : O(V + E)

----------------------------------------------------------------------------
SPACE COMPLEXITY
----------------------------------------------------------------------------

Adjacency List : O(V + E)

Arrays         : O(V)

DFS Stack      : O(V)

Overall        : O(V + E)

===============================================================================
*/

class Solution {
private:

    // DFS function to calculate tin[] and low[] and identify articulation points.
    void dfs(int node,                 // Current node
             int parent,               // Parent of current node in DFS tree
             int &timer,               // Global timer (passed by reference)
             vector<int> &vis,         // Visited array
             vector<int> &tin,         // Discovery time array
             vector<int> &low,         // Lowest reachable discovery time
             vector<int> &isArticulation, // Marks articulation points
             vector<vector<int>> &adj) // Adjacency list
    {
        vis[node] = 1;                 // Mark current node as visited

        // Assign discovery time and initialize low value.
        tin[node] = low[node] = timer++;

        // Counts DFS children (used only for root node).
        int child = 0;

        // Traverse all neighbours.
        for (auto it : adj[node]) {

            // Ignore the edge back to parent.
            if (it == parent)
                continue;

            // ---------------- BACK EDGE ----------------
            if (vis[it]) {

                // Update low using neighbour's discovery time.
                low[node] = min(low[node], tin[it]);
            }

            // ---------------- TREE EDGE ----------------
            else {

                // Explore neighbour.
                dfs(it, node, timer, vis, tin, low,
                    isArticulation, adj);

                // Update low after returning from child.
                low[node] = min(low[node], low[it]);

                /*
                   If child's subtree cannot reach an ancestor
                   of current node, then current node is an
                   articulation point.
                */
                if (low[it] >= tin[node] && parent != -1) {
                    isArticulation[node] = 1;
                }

                // Count DFS children.
                child++;
            }
        }

        /*
            Root node is articulation point only if
            it has more than one DFS child.
        */
        if (parent == -1 && child > 1) {
            isArticulation[node] = 1;
        }
    }

public:

    vector<int> articulationPoints(int V,
                                   vector<vector<int>>& edges)
    {
        // ---------------- Build Graph ----------------

        // Adjacency list representation.
        vector<vector<int>> adj(V);

        // Convert edge list into adjacency list.
        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // ---------------- Initialization ----------------

        vector<int> vis(V, 0);              // Visited array

        vector<int> tin(V, -1);             // Discovery time

        vector<int> low(V, -1);             // Lowest reachable time

        vector<int> isArticulation(V, 0);   // Marks articulation points

        int timer = 0;                      // DFS timer

        // Graph may contain multiple connected components.
        for (int i = 0; i < V; i++) {

            // Start DFS from every unvisited node.
            if (!vis[i]) {

                dfs(i,
                    -1,                    // Root has no parent
                    timer,
                    vis,
                    tin,
                    low,
                    isArticulation,
                    adj);
            }
        }

        // ---------------- Collect Answer ----------------

        vector<int> ans;

        for (int i = 0; i < V; i++) {

            // Store every articulation point.
            if (isArticulation[i]) {
                ans.push_back(i);
            }
        }

        // No articulation point exists.
        if (ans.empty())
            return {-1};

        return ans;
    }
};


int main(){
    return 0;
}