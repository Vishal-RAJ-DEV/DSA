#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
====================================================================
Longest Cycle in a Directed Graph (LeetCode 2360)

Graph Property
--------------
Each node has AT MOST one outgoing edge.

Example

0 → 3
1 → 3
2 → 4
3 → 2
4 → 3

Since every node has only one outgoing edge,
DFS from any node always moves in ONE direction.

====================================================================

Algorithm
---------

We maintain three arrays.

1. visited[]

visited[node] = 1

Means:
This node has already been processed in some DFS.

Once a node becomes visited,
we never start DFS from it again.

--------------------------------------------------

2. pathVisited[]

pathVisited[node] = 1

Means:
This node is currently present in the recursion stack
(current DFS path).

Suppose current DFS path is

0 → 3 → 2 → 4

Then

pathVisited

0 = 1
3 = 1
2 = 1
4 = 1

When recursion returns,

pathVisited[node] = 0

because that node is no longer part of
the current DFS path.

--------------------------------------------------

3. depth[]

Stores the DFS level of each node
inside the current DFS.

Example

DFS

0 → 3 → 2 → 4

depth[]

0 = 0
3 = 1
2 = 2
4 = 3

Depth simply means

"How many edges have we travelled
from the starting node?"

====================================================================

Cycle Detection
---------------

Suppose

0 → 3 → 2 → 4
      ↑      |
      |______|

DFS path

0 → 3 → 2 → 4

depth

0 = 0
3 = 1
2 = 2
4 = 3

Now

4 → 3

When visiting 4,

visited[3] = true
pathVisited[3] = true

This means

3 is already present in the CURRENT DFS path.

Therefore

we found a cycle.

====================================================================

Why does the formula work?

Cycle

3 → 2 → 4 → 3

Depths

3 = 1
2 = 2
4 = 3

Current node = 4

Back edge goes to

3

Current depth

3

Depth of repeated node

1

Difference

3 - 1 = 2

This counts

4 → 2 → 3

We also need to include node 3 itself.

Therefore

Cycle Length

=

currentDepth - depth[next] + 1

=

3 - 1 + 1

=

3

Exactly

3 → 2 → 4 → 3

This is exactly the same idea as

Length of subarray

=

rightIndex - leftIndex + 1

====================================================================

Time Complexity

O(N)

Every node is visited only once.

Space Complexity

O(N)

====================================================================
*/

class Solution {
public:

    int ans = -1;

    vector<int> visited;
    vector<int> pathVisited;
    vector<int> depth;

    void dfs(int node,
             vector<int>& edges,
             int currentDepth) {

        // Mark current node as visited.
        visited[node] = 1;

        // Mark current node as part of
        // the current DFS path.
        pathVisited[node] = 1;

        // Store DFS level of this node.
        depth[node] = currentDepth;

        int next = edges[node];

        // Continue only if an outgoing edge exists.
        if (next != -1) {

            // Visit next node.
            if (!visited[next]) {

                dfs(next, edges, currentDepth + 1);
            }

            // A node already present in the current
            // DFS path means we found a cycle.
            else if (pathVisited[next]) {

                int cycleLength =
                    currentDepth - depth[next] + 1;

                ans = max(ans, cycleLength);
            }
        }

        // Backtrack:
        // Remove this node from the current DFS path.
        pathVisited[node] = 0;
    }

    int longestCycle(vector<int>& edges) {

        int n = edges.size();

        visited.assign(n, 0);
        pathVisited.assign(n, 0);
        depth.assign(n, 0);

        // Start DFS from every unvisited node.
        for (int i = 0; i < n; i++) {

            if (!visited[i]) {

                dfs(i, edges, 0);
            }
        }

        return ans;
    }
};


/*
====================================================================
Algorithm

Since every node has AT MOST one outgoing edge,

starting from any node, there is only ONE possible path to follow.

So instead of using recursive DFS, we simply keep moving
to the next node until

1. We reach -1 (no outgoing edge), OR
2. We reach a node that has already been visited.

--------------------------------------------------------------------

For every new traversal, we maintain

visited[]

Marks nodes that have already been processed.
A visited node is never processed again.

position[]

Stores the order (step number) in which every node
was visited in the CURRENT traversal.

Example

Traversal

0 → 3 → 2 → 4

position

0 → 0
3 → 1
2 → 2
4 → 3

Notice

position[] is created fresh for every starting node.

--------------------------------------------------------------------

Cycle Detection

Suppose

0 → 3 → 2 → 4
      ↑      |
      |______|

During traversal

Node        Position

0              0
3              1
2              2
4              3

After visiting 4,

step becomes 4.

Now

4 → 3

Since

3 already exists inside position[],

we know that 3 belongs to the CURRENT traversal.

Hence,

we found a cycle.

--------------------------------------------------------------------

Why does

cycleLength = step - position[node]

work?

Current traversal

Position

0     1     2     3

Node

0 --> 3 --> 2 --> 4
      ^            |
      |____________|

Current

step = 4

Repeated node

3

position[3] = 1

Cycle starts at position 1
and continues until position 3.

Length

4 - 1 = 3

Exactly

3 → 2 → 4 → 3

Unlike the DFS solution, no +1 is needed because

step always points to the NEXT free position
instead of the current node's position.

====================================================================

Time Complexity : O(N)

Every node is visited only once.

Space Complexity : O(N)

visited[] + temporary hashmap.
====================================================================
*/

class Solution {
public:

    int longestCycle(vector<int>& edges) {

        int n = edges.size();

        // Marks nodes that have already been processed.
        vector<int> visited(n, 0);

        int ans = -1;

        // Start a traversal from every unvisited node.
        for (int start = 0; start < n; start++) {

            if (visited[start])
                continue;

            // Stores the visiting order (step number)
            // of nodes in the CURRENT traversal only.
            unordered_map<int, int> position;

            int node = start;

            // Current traversal step.
            int step = 0;

            // Continue moving forward until
            // we either reach -1 or a previously visited node.
            while (node != -1 && !visited[node]) {

                // Mark node as processed.
                visited[node] = 1;

                // Store when this node was first visited
                // in the current traversal.
                position[node] = step++;

                // Move to the next node.
                node = edges[node];
            }

            // If node is not -1 and also exists inside
            // the current traversal,
            // then we have found a cycle.
            if (node != -1 && position.count(node)) {

                // Number of nodes in the cycle.
                int cycleLength = step - position[node];

                // Update the longest cycle found so far.
                ans = max(ans, cycleLength);
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}