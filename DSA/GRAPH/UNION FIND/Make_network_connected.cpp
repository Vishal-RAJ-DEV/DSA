#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem:
-------------------------------------------------------------------------------
There are 'n' computers numbered from 0 to n-1 and some existing network
connections between them.

Each connection [u, v] means there is a cable directly connecting computer
'u' and computer 'v'.

You are allowed to:
1. Remove any existing cable.
2. Connect that cable between any two disconnected computers.

Return the minimum number of operations required to connect all computers
into one connected network.

If it is impossible to connect all computers, return -1.

-------------------------------------------------------------------------------
Example:

n = 6

Connections:
0-1
0-2
1-2
3-4
4-5

Graph:

      0
     / \
    1---2

      3
      |
      4
      |
      5

The edge (1,2) is redundant because 1 and 2 are already connected through 0.

We can remove that extra cable and connect:

2 -------- 3

Now the entire graph becomes connected.

Answer = 1

===============================================================================
Algorithm (Union Find / Disjoint Set Union)

1. A connected graph with 'n' nodes must contain at least (n-1) edges.
   If the given number of edges is less than (n-1), connecting all computers
   is impossible.

2. Create a Disjoint Set Union (DSU).

3. Traverse every edge.
   - If both nodes already belong to the same component,
     then this edge forms a cycle.
     This edge is called an EXTRA EDGE because it can be removed and reused.
   - Otherwise merge both components using Union By Size.

4. After processing all edges, count how many connected components exist.

5. If there are 'k' connected components,
   then exactly (k-1) cables are required to connect them.

6. If the number of extra cables is at least (components-1),
   return (components-1), otherwise return -1.

===============================================================================
Time Complexity:
O(E * α(N)) + O(N * α(N))
≈ O(E + N)

where
E = number of edges
N = number of computers

α(N) = Inverse Ackermann Function (almost constant)

Space Complexity:
O(N)
===============================================================================
*/

class DSU {
public:
    // parent[i] -> stores the parent (or leader) of node i
    // size[i] -> stores the size of the component whose leader is i
    vector<int> parent, size;

    // Constructor: Initialize DSU for n nodes
    DSU(int n) {

        // Allocate memory for parent array
        parent.resize(n);

        // Allocate memory for size array and initialize every size to 1
        size.resize(n, 1);

        // Initially every node is its own parent
        // Each node forms an independent component
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find the Ultimate Parent (Leader) of a node
    int findUPar(int node) {

        // Base Case:
        // If node is its own parent, it is the leader
        if (node == parent[node])
            return node;

        // Path Compression:
        // Store the ultimate parent directly to flatten the tree
        // This makes future find operations much faster
        return parent[node] = findUPar(parent[node]);
    }

    // Merge two components using Union by Size
    void unionBySize(int u, int v) {

        // Find the leaders of both nodes
        int pu = findUPar(u);
        int pv = findUPar(v);

        // If both nodes already belong to the same component,
        // no merging is required
        if (pu == pv) return;

        // Attach the smaller component under the larger component
        if (size[pu] < size[pv]) {

            // Make pv the new leader
            parent[pu] = pv;

            // Update the size of the merged component
            size[pv] += size[pu];
        }
        else {

            // Make pu the new leader
            parent[pv] = pu;

            // Update the size of the merged component
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {

        /*
        -----------------------------------------------------------------------
        Step 1:
        Check whether enough cables even exist.

        To connect 'n' computers into one connected network,
        at least (n-1) edges are required.

        Example:

        n = 5

        Minimum edges required = 4

        If only 3 cables are available,

            0----1

            2----3

            4

        No matter how we rearrange the cables,
        one computer will always remain disconnected.

        Therefore return -1 immediately.
        -----------------------------------------------------------------------
        */
        if (connections.size() < n - 1)
            return -1;

        /*
        -----------------------------------------------------------------------
        Step 2:
        Create the Disjoint Set Union.

        Initially every computer is an independent component.

        Example:

        0   1   2   3   4

        Components = 5
        -----------------------------------------------------------------------
        */
        DSU ds(n);

        /*
        extra = Number of redundant cables.

        A redundant cable is an edge whose both endpoints
        already belong to the same connected component.

        Such cables can be removed and used elsewhere.
        */
        int extra = 0;

        /*
        -----------------------------------------------------------------------
        Step 3:
        Traverse every edge.
        -----------------------------------------------------------------------
        */
        for (auto &edge : connections) {

            int u = edge[0];
            int v = edge[1];

            /*
            Find whether both nodes already belong to
            the same connected component.

            If yes:

                u ---- ... ---- v

            already has a path.

            Adding another edge creates a cycle.

            Example:

                  0
                 / \
                1---2

            Edge (1,2) is unnecessary because

            1 -> 0 -> 2

            already exists.

            Therefore this edge becomes an EXTRA cable.
            */
            if (ds.findUPar(u) == ds.findUPar(v))
                extra++;

            /*
            Otherwise,
            u and v belong to different components.
            Merge both components.

            Example:
            Component A

                 0
                 |
                 1

            Component B

                 2
                 |
                 3

            After Union:

                 0
                 |
                 1
                 |
                 2
                 |
                 3
            */
            else
                ds.unionBySize(u, v);
        }

        /*
        -----------------------------------------------------------------------
        Step 4:
        Count the number of connected components.

        Every component has exactly one Ultimate Parent.
        Therefore,
        if findUPar(i) == i,
        then 'i' is the leader of one connected component.
        Example:

              0
             / \
            1   2

              3
              |
              4

        Parent Array
        0 0 0 3 3

        Ultimate Parents:
        0
        3

        Therefore
        Components = 2
        -----------------------------------------------------------------------
        */
        int components = 0;

        for (int i = 0; i < n; i++) {

            if (ds.findUPar(i) == i)
                components++;
        }

        /*
        -----------------------------------------------------------------------
        Step 5:
        How many cables are needed?
        If there are
        k connected components,then  Minimum cables required = k-1
        Example:
        Component A
        Component B
        Component C

        Three components need only two cables.
        A ----- B ----- C
        Hence,
        Required cables = components - 1
        Now compare it with the number of extra cables.
        If
        extra >= components-1
        we can reconnect the network.
        Otherwise,
        it is impossible.
        -----------------------------------------------------------------------
        */

        return (extra >= components - 1) ? components - 1 : -1;
    }
};

///ANOTHER APPROCH USING THE DFS AND CONNECTED COMPONENTS

/*
===============================================================================
Problem:
-------------------------------------------------------------------------------
There are 'n' computers (0 to n-1) and some existing connections.

Each connection [u, v] represents a cable between computer u and v.

You can remove any existing cable and reconnect it between any two
disconnected computers.

Return the minimum number of operations required to connect all computers.

If it is impossible to connect all computers, return -1.

===============================================================================
Why DFS Works?
-------------------------------------------------------------------------------
The graph can have multiple disconnected components.

DFS is used to find all nodes belonging to one connected component.

Suppose we have:

      0 ----- 1

      2 ----- 3

      4

There are 3 connected components:
{0,1}, {2,3}, {4}

To connect 'k' connected components into one graph,
we always need exactly (k - 1) cables.

So the problem reduces to:
1. Count the number of connected components.
2. Return components - 1.

===============================================================================
Algorithm:
-------------------------------------------------------------------------------
1. If total edges are less than (n-1), return -1 because it is impossible
   to connect all computers.

2. Build an adjacency list from the given connections.

3. Create a visited array to keep track of visited nodes.

4. Traverse every node.
   - If the node is not visited,
     perform DFS from that node.
   - DFS visits every node in that connected component.
   - Increase the component count.

5. Finally return (components - 1).

===============================================================================
Time Complexity:
O(V + E)

V = Number of computers
E = Number of connections

Space Complexity:
O(V + E)
Adjacency List + Visited Array + DFS Recursion Stack
===============================================================================
*/

class Solution {

private:

    // DFS visits every node belonging to the same connected component.
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src)
    {
        // Mark current node as visited
        visited[src] = true;

        // Visit all unvisited neighbours
        for(int i : adj[src])
            if(!visited[i])
                dfs(adj, visited, i);
    }

public:

    int makeConnected(int n, vector<vector<int>>& connections) {

        // A connected graph with n nodes must have at least (n-1) edges.
        if(connections.size() < n - 1)
            return -1;

        // Adjacency list to represent the graph
        vector<vector<int>> adj(n);

        // Build the undirected graph
        for(auto v : connections)
        {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }

        // Tracks whether a computer has already been visited
        vector<bool> visited(n, false);

        // Stores the total number of connected components
        int components = 0;

        // Traverse every computer
        for(int i = 0; i < n; i++)

            // If this node belongs to a new component
            if(!visited[i])
            {
                // Visit the entire connected component
                dfs(adj, visited, i);

                // One complete connected component found
                components++;
            }

        // To connect 'components' groups together,
        // exactly (components - 1) cables are required.
        return components - 1;
    }
};
int main(){
    return 0;
}