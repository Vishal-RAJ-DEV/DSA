#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Longest Path in a Directed Acyclic Graph (DAG)
    Given a weighted DAG with V vertices, edges, and a source vertex,
    find the longest distance from source to all other vertices.

    Example:
    V = 6, edges = [[0,1,5], [0,2,3], [1,3,6], [1,2,2], [2,4,7], [3,5,1], [4,5,2]]
    src = 0
    Output: [0, 5, 5, 11, 12, 13]

    ================================================================
    WHY TOPOLOGICAL SORT + RELAXATION?
    ================================================================

    For LONGEST PATH in a DAG:
    1. Topological Sort ensures we process nodes in correct order
       (all dependencies processed before dependents)
    2. Relaxation finds the longest path by updating distances

    Key Insight:
    ───────────
    In a DAG, if we process nodes in topological order, when we
    reach node u, ALL paths to u have already been considered.

    This means dist[u] is FINAL when we process u!

    ================================================================
    WHAT IS RELAXATION?
    ================================================================

    Relaxation is the process of UPDATING distances when we find
    a BETTER (longer) path to a node.

    For edge u → v with weight w:
    ─────────────────────────────
    If dist[v] < dist[u] + w:
        dist[v] = dist[u] + w

    This means:
    - Current best path to v: dist[v]
    - New path through u: dist[u] + w
    - If new path is LONGER, update dist[v]

    VISUAL EXAMPLE:
    ───────────────
    0 ──5──▶ 1 ──6──▶ 3
    │        │
    3        2
    │        │
    ▼        ▼
    2 ──7──▶ 4 ──2──▶ 5

    Initially: dist = [0, -∞, -∞, -∞, -∞, -∞]

    Process node 0:
    - Relax 0→1: dist[1] = max(-∞, 0+5) = 5
    - Relax 0→2: dist[2] = max(-∞, 0+3) = 3
    dist = [0, 5, 3, -∞, -∞, -∞]

    Process node 1:
    - Relax 1→3: dist[3] = max(-∞, 5+6) = 11
    - Relax 1→2: dist[2] = max(3, 5+2) = 7
    dist = [0, 5, 7, 11, -∞, -∞]

    Process node 2:
    - Relax 2→4: dist[4] = max(-∞, 7+7) = 14
    dist = [0, 5, 7, 11, 14, -∞]

    Process node 3:
    - Relax 3→5: dist[5] = max(-∞, 11+1) = 12
    dist = [0, 5, 7, 11, 14, 12]

    Process node 4:
    - Relax 4→5: dist[5] = max(12, 14+2) = 16
    dist = [0, 5, 7, 11, 14, 16]

    Final: dist = [0, 5, 7, 11, 14, 16]

    ================================================================
    WHY PROCESS IN TOPOLOGICAL ORDER?
    ================================================================

    If we process nodes in WRONG order:
    - We might relax edges before all paths to a node are found
    - This gives INCORRECT results

    Topological Order guarantees:
    ────────────────────────────
    For every edge u→v, u comes BEFORE v in the order.

    So when we process u:
    - dist[u] is already the LONGEST path to u
    - We can safely relax all edges from u

    This is why we MUST use topological sort!

    ================================================================
    TWO APPROACHES TOPOLOGICAL SORT
    ================================================================

    1. DFS: Process nodes, push to stack after visiting all neighbors
    2. Kahn's (BFS): Use indegree, process nodes with indegree 0

    Both give valid topological order, but:
    - DFS: Recursive, uses call stack
    - Kahn's: Iterative, uses queue
*/

// ═══════════════════════════════════════════════════════════════════
// APPROACH 1: DFS TOPOLOGICAL SORT + RELAXATION
// Time: O(V + E) | Space: O(V + E)
// ═══════════════════════════════════════════════════════════════════
class DFS_Topological {
private:

    // DFS to find topological order
    void topoSort(int node,
                  vector<vector<pair<int, int>>>& adj,
                  vector<int>& visited,
                  stack<int>& st) {

        visited[node] = 1;

        // Visit all neighbors first (post-order traversal)
        for (auto it : adj[node]) {
            int next = it.first;
            // int weight = it.second;  // Not needed for topo sort

            if (!visited[next]) {
                topoSort(next, adj, visited, st);
            }
        }

        // Push node AFTER all neighbors are processed
        // This ensures topological order
        st.push(node);
    }

public:
    vector<int> longestPath(int V, vector<vector<int>>& edges, int src) {

        // ─────────────────────────────────────────────────────────
        // STEP 1: Build adjacency list
        // ─────────────────────────────────────────────────────────
        vector<vector<pair<int, int>>> adj(V);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});  // u → v with weight w
        }

        // ─────────────────────────────────────────────────────────
        // STEP 2: Find topological order using DFS
        // ─────────────────────────────────────────────────────────
        vector<int> visited(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topoSort(i, adj, visited, st);
            }
        }

        // ─────────────────────────────────────────────────────────
        // STEP 3: Initialize distances
        // ─────────────────────────────────────────────────────────
        // dist[i] = longest distance from source to vertex i
        vector<int> dist(V, INT_MIN);

        dist[src] = 0;  // Source to itself = 0

        // ─────────────────────────────────────────────────────────
        // STEP 4: RELAX edges in topological order
        // ─────────────────────────────────────────────────────────
        while (!st.empty()) {

            int node = st.top();
            st.pop();

            // Skip if node is unreachable from source
            if (dist[node] == INT_MIN) {
                continue;
            }

            // ─────────────────────────────────────────────────────
            // RELAXATION: Update distances to neighbors
            // ─────────────────────────────────────────────────────
            for (auto it : adj[node]) {
                int next = it.first;
                int weight = it.second;

                // If going through 'node' gives a LONGER path to 'next'
                // then update dist[next]
                dist[next] = max(
                    dist[next],           // Current best distance
                    dist[node] + weight   // New path through node
                );
            }
        }

        return dist;
    }
};

// ═══════════════════════════════════════════════════════════════════
// APPROACH 2: KAHN'S ALGORITHM (BFS) + RELAXATION
// Time: O(V + E) | Space: O(V + E)
// ═══════════════════════════════════════════════════════════════════
/*
    ================================================================
    HOW KAHN'S ALGORITHM WORKS
    ================================================================

    Kahn's algorithm uses BFS to find topological order:

    1. Calculate indegree for all nodes
    2. Add all nodes with indegree 0 to queue
    3. While queue is not empty:
       a. Remove node from queue
       b. Add it to topological order
       c. Decrease indegree of all neighbors
       d. If neighbor's indegree becomes 0, add to queue

    ================================================================
    VISUAL EXAMPLE
    ================================================================

    Graph:
    0 → 1 → 3
    ↓   ↓
    2 → 4 → 5

    Indegree: [0, 1, 1, 1, 1, 1]

    Step 1: Queue = [0] (only node with indegree 0)
    Step 2: Process 0, add to topo = [0]
            Update neighbors: 1 (indegree 0), 2 (indegree 0)
    Step 3: Queue = [1, 2]
    Step 4: Process 1, topo = [0, 1]
            Update neighbors: 3 (indegree 0), 4 (indegree 0)
    Step 5: Process 2, topo = [0, 1, 2]
            Update neighbors: 4 (already 0)
    Step 6: Process 3, topo = [0, 1, 2, 3]
    Step 7: Process 4, topo = [0, 1, 2, 3, 4]
    Step 8: Process 5, topo = [0, 1, 2, 3, 4, 5]

    Final topological order: [0, 1, 2, 3, 4, 5]

    ================================================================
    RELAXATION IN KAHN'S ALGORITHM
    ================================================================

    After finding topological order, we relax edges EXACTLY
    the same way as the DFS approach:

    for each node in topological order:
        if node is reachable:
            for each neighbor of node:
                dist[neighbor] = max(dist[neighbor],
                                     dist[node] + weight)

    The order is guaranteed to be topological, so relaxation
    gives correct longest paths.
*/
class Kahns_Algorithm {
public:
    vector<int> longestPath(int V, vector<vector<int>>& edges, int src) {

        vector<vector<pair<int, int>>> adj(V);
        vector<int> indegree(V, 0);

        // ─────────────────────────────────────────────────────────
        // STEP 1: Build adjacency list and calculate indegree
        // ─────────────────────────────────────────────────────────
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj[u].push_back({v, w});
            indegree[v]++;  // Count incoming edges to v
        }

        // ─────────────────────────────────────────────────────────
        // STEP 2: Find topological order using Kahn's algorithm
        // ─────────────────────────────────────────────────────────
        queue<int> q;

        // Add all nodes with indegree 0 to queue
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;  // Topological order

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            topo.push_back(node);

            // Decrease indegree of all neighbors
            for (auto it : adj[node]) {
                int next = it.first;

                indegree[next]--;

                // If indegree becomes 0, add to queue
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // ─────────────────────────────────────────────────────────
        // STEP 3: Initialize distances
        // ─────────────────────────────────────────────────────────
        vector<int> dist(V, INT_MIN);
        dist[src] = 0;

        // ─────────────────────────────────────────────────────────
        // STEP 4: RELAX edges in topological order
        // ─────────────────────────────────────────────────────────
        for (int node : topo) {

            // Skip unreachable nodes
            if (dist[node] == INT_MIN) {
                continue;
            }

            // ─────────────────────────────────────────────────────
            // RELAXATION: Update distances to neighbors
            // ─────────────────────────────────────────────────────
            for (auto it : adj[node]) {
                int next = it.first;
                int weight = it.second;

                // If going through 'node' gives a LONGER path to 'next'
                dist[next] = max(
                    dist[next],           // Current best
                    dist[node] + weight   // New path through node
                );
            }
        }

        return dist;
    }
};

/*
    COMPARISON OF APPROACHES:
    =========================

    Approach              Time        Space       Method
    ─────────────────────────────────────────────────────────────
    1. DFS + Topo Sort    O(V + E)    O(V + E)    Recursive
    2. Kahn's + Topo Sort O(V + E)    O(V + E)    Iterative (BFS)

    Both approaches are equivalent in complexity.
    The ONLY difference is how we find topological order.

    ════════════════════════════════════════════════════════════════
    DETAILED RELAXATION EXPLANATION
    ════════════════════════════════════════════════════════════════

    The relaxation step is the HEART of the algorithm:

    ┌─────────────────────────────────────────────────────────────┐
    │  dist[next] = max(dist[next], dist[node] + weight)        │
    └─────────────────────────────────────────────────────────────┘

    This single line does all the work:

    1. dist[node] + weight:
       - Calculate the distance to 'next' if we go through 'node'
       - This is the NEW candidate path

    2. max(dist[next], ...):
       - Compare with current best distance to 'next'
       - If new path is LONGER, update

    3. Why it works:
       - In topological order, when we process 'node', ALL paths
         to 'node' have been considered
       - So dist[node] is the LONGEST path to 'node'
       - Adding weight gives the LONGEST path through 'node'

    ════════════════════════════════════════════════════════════════
    EXAMPLE WALKTHROUGH
    ════════════════════════════════════════════════════════════════

    Graph:
    0 ──5──▶ 1 ──6──▶ 3 ──1──▶ 5
    │        │
    3        2
    │        │
    ▼        ▼
    2 ──7──▶ 4 ──2──▶ 5

    Topological Order: [0, 1, 2, 3, 4, 5]

    Step 1: dist = [0, -∞, -∞, -∞, -∞, -∞]

    Step 2: Process node 0 (dist[0] = 0)
            - Relax 0→1: dist[1] = max(-∞, 0+5) = 5
            - Relax 0→2: dist[2] = max(-∞, 0+3) = 3
            dist = [0, 5, 3, -∞, -∞, -∞]

    Step 3: Process node 1 (dist[1] = 5)
            - Relax 1→3: dist[3] = max(-∞, 5+6) = 11
            - Relax 1→2: dist[2] = max(3, 5+2) = 7  ← UPDATED!
            dist = [0, 5, 7, 11, -∞, -∞]

    Step 4: Process node 2 (dist[2] = 7)
            - Relax 2→4: dist[4] = max(-∞, 7+7) = 14
            dist = [0, 5, 7, 11, 14, -∞]

    Step 5: Process node 3 (dist[3] = 11)
            - Relax 3→5: dist[5] = max(-∞, 11+1) = 12
            dist = [0, 5, 7, 11, 14, 12]

    Step 6: Process node 4 (dist[4] = 14)
            - Relax 4→5: dist[5] = max(12, 14+2) = 16  ← UPDATED!
            dist = [0, 5, 7, 11, 14, 16]

    Step 7: Process node 5 (dist[5] = 16)
            - No outgoing edges

    Final: dist = [0, 5, 7, 11, 14, 16]

    Longest paths from vertex 0:
    0→0: 0
    0→1: 5
    0→2: 7 (via 1, not direct!)
    0→3: 11
    0→4: 14
    0→5: 16 (via 4, not 3!)
*/

int main(){
    return 0;
}
