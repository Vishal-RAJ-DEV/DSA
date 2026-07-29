#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
==========================================
        Prim's Algorithm (MST)
==========================================

Problem:
--------
We have 'n' points on a 2D plane.
The cost to connect two points is their Manhattan Distance:
|x1 - x2| + |y1 - y2|

We need to connect all points with the minimum possible total cost.

Observation:
------------
- Think of every point as a node in a graph.
- Every pair of points has an edge.
- Edge weight = Manhattan Distance.
- We need the Minimum Spanning Tree (MST).

Why Prim's Algorithm?
---------------------
Prim's algorithm builds the MST greedily.

Idea:
-----
1. Start from any node (here node 0).
2. Add it to the MST.
3. Push all edges from this node into a Min Heap.
4. Always choose the minimum-cost edge that connects
   a visited node to an unvisited node.
5. Repeat until all nodes are included.

Why Min Heap?
-------------
The heap always gives the smallest available edge first,
allowing us to greedily build the minimum spanning tree.

Time Complexity:
----------------
There are O(n²) edges.
Each edge may be pushed into the priority queue.

Time: O(n² log n)
Space: O(n²) (priority queue in the worst case)

==========================================
*/

class Solution {
public:

    // Returns Manhattan distance between two points.
    int manhattanDist(vector<int>& a, vector<int>& b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }

    int minCostConnectPoints(vector<vector<int>>& points) {

        int n = points.size();               // Number of points

        vector<bool> vis(n, false);          // Marks whether a point is already in MST

        int ans = 0;                         // Stores total minimum cost

        // Min Heap -> {edgeCost, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        pq.push({0, 0});                     // Start from node 0 with cost 0

        while (!pq.empty()) {

            auto it = pq.top();       // Get minimum cost edge
            pq.pop();

            int cost = it.first;
            int u = it.second;
            
            if (vis[u])                      // Skip if node already included
                continue;

            vis[u] = true;                   // Include node in MST

            ans += cost;                     // Add edge cost to answer

            // Explore all remaining nodes
            for (int v = 0; v < n; v++) {

                if (!vis[v]) {               // Ignore already visited nodes

                    // Push edge from current node to this node
                    pq.push({
                        manhattanDist(points[u], points[v]),
                        v
                    });
                }
            }
        }

        return ans;                          // Minimum cost to connect all points
    }
};


/*
Dry Run (Small Example)

Suppose:

points = [(0,0), (2,2), (3,10)]

Distance matrix:

       0   1   2
0      -   4   13
1      4   -   9
2      13  9   -

Initial state:

Heap:
(0,0)

Visited:
F F F

Answer = 0
Iteration 1

Pop:

(0,0)

Visit node 0.

Answer = 0

Push its edges:

(4,1)
(13,2)

Heap:

(4,1)
(13,2)
Iteration 2

Pop:

(4,1)

Visit node 1.

Answer = 4

Push:

(9,2)

Heap:

(9,2)
(13,2)
Iteration 3

Pop:

(9,2)

Visit node 2.

Answer = 13

All nodes are now visited, so the MST is complete.

Intuition

Think of Prim's algorithm as growing one connected network:

Start

0

↓

Pick cheapest edge

0 ----- 1

↓

Pick cheapest edge again

0 ----- 1
         |
         |
         2

At every step:

The visited nodes form the current MST.
The priority queue stores all possible edges leaving the MST.
We always choose the smallest edge that connects to an unvisited node, ensuring the total cost remains minimal.
*/


int main(){
    return 0;
}