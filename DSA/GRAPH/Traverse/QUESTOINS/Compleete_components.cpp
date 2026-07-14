#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// =========================================================================
// PROBLEM: Count Complete Components (LeetCode 2685)
// A complete component = a connected component where every pair of vertices
// is directly connected by an edge (i.e., it forms a clique).
// For a component with V vertices, a complete graph has V*(V-1)/2 edges.
//
// Two approaches below:
//   1. DFS — visit each component, count vertices & edges, verify formula.
//   2. DSU — union all nodes, track degree of each node, then per component
//      check if every node's degree == component_size - 1.
// =========================================================================

// =========================================================================
// APPROACH 1: DFS (Depth-First Search)
// =========================================================================
// HOW IT WORKS:
//   1. Build an undirected adjacency list `graph` from the edge list.
//   2. Iterate over all n nodes. For each unvisited node, begin a DFS.
//   3. Inside the DFS, for each node visited:
//        - Increment `vertices` (count of nodes in this component).
//        - Add `graph[node].size()` to `edge` — this counts each edge
//          incident to the node. Since the graph is undirected, every
//          edge in this component will be counted TWICE (once from each
//          endpoint).
//   4. After the DFS for a component finishes:
//        - Divide `edge` by 2 → get the true number of undirected edges.
//        - Check if `edge == vertices * (vertices - 1) / 2`.
//          This is the formula for a complete graph (clique) with V vertices.
//        - If true → this component is "complete" → increment answer.
//
// WHY THE FORMULA WORKS:
//   In a complete undirected graph with V vertices, each vertex connects
//   to every other vertex → degree of each node = V-1.
//   Total edges = sum(degree) / 2 = V * (V-1) / 2.
//   Our DFS counts sum(degree) in `edge`, then we divide by 2.
//   If the result matches the formula, every possible edge exists.
//
// TIME:  O(n + e) for graph construction + DFS traversal
// SPACE: O(n + e) for adjacency list + visited array
// =========================================================================

class Solution {
public:
    vector<vector<int>> graph;
    vector<bool> visited;
    int edge;
    int vert;

    void dfs(int node) {
        visited[node] = true;
        vert++;

        edge += graph[node].size();

        for (int nei : graph[node]) {
            if (!visited[nei]) {
                dfs(nei);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        graph.assign(n, {});
        visited.assign(n, false);

        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;

            edge = 0;
            vert = 0;

            dfs(i);

            edge /= 2;   // each edge was counted twice (once per endpoint)

            if (edge == vert * (vert - 1) / 2)
                ans++;
        }

        return ans;
    }
};


// =========================================================================
// DSU (Disjoint Set Union / Union-Find) helper class
// =========================================================================
// Provides union-find with:
//   - Path compression in find() → nearly O(1) amortized.
//   - Union by size in unite() → ensures tree depth stays O(log n).
// Used by Approach 2 to group nodes into connected components.
// =========================================================================

class DSU {
public:
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);   // path compression
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;

        // union by size: attach smaller tree under larger tree
        if (sz[u] < sz[v])
            swap(u, v);

        parent[v] = u;
        sz[u] += sz[v];
    }

    int getSize(int x) {
        return sz[find(x)];
    }
};


// =========================================================================
// APPROACH 2: DSU (Disjoint Set Union) with per-node degree check
// =========================================================================
// HOW IT WORKS:
//   Step 1 — Union + Degree tracking:
//     For each edge (u, v):
//       - d.unite(u, v)      → merge the sets
//       - degree[u]++, degree[v]++ → track degree of each node
//
//   Step 2 — Group by component:
//     For each node i (0..n-1):
//       - mp[d.find(i)].push_back(i)
//         → mp maps root → list of all nodes in that component
//
//   Step 3 — Validate each component:
//     Initialize ans = mp.size() (assume all components are complete).
//     For each component (root → nodes list):
//       - sz = d.getSize(root)   → number of vertices in this component
//       - For every node in that component:
//           if degree[node] != sz - 1 → this component is NOT complete
//         Reason: In a complete component of size sz, every node must be
//         connected to ALL other sz-1 nodes in the same component → its
//         degree must be exactly sz-1.
//       - If any node fails, decrement ans.
//     Return ans.
//
// WHY THIS IS CORRECT:
//   A connected component is complete iff AND ONLY IF every node in it has
//   degree == (component_size - 1). This is because:
//     - If component is complete, each node connects to all sz-1 others.
//     - If each node has degree == sz-1, and edges don't go outside the
//       component (DSU guarantees internal connectivity), then every
//       possible internal edge that exists. But wait — degree counts ALL
//       incident edges. Could a node have degree == sz-1 but edges go to
//       nodes outside the component? No — DSU defines connectivity by
//       union operations. If a node u is in component A and has an edge
//       to node v in component B, then u and v would be in the SAME DSU
//       component (because they're connected via that edge). DSU groups
//       all connected nodes, so edges CANNOT cross DSU component boundaries.
//     Therefore, degree[node] == sz-1 ensures all sz-1 connections within
//       the component are present → complete.
//
// KEY DIFFERENCE from DFS:
//   - DFS approach counts TOTAL edges in the component and compares to
//     V*(V-1)/2 (global property of the component).
//   - DSU approach checks PER-NODE degree == sz-1 (local property of
//     each node). Both are equivalent mathematically, but DSU avoids
//     recursion and can handle dynamic edge additions more naturally.
//
// TIME:  O(n + e * α(n))   where α(n) is inverse Ackermann (≈ O(1))
// SPACE: O(n)              for DSU arrays, degree[], and hash map
// =========================================================================

class Solution2 {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        DSU d(n);
        vector<int> degree(n, 0);

        // Step 1: union all edges + track degrees
        for (auto &e : edges) {
            d.unite(e[0], e[1]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        // Step 2: group nodes by their DSU root
        unordered_map<int, vector<int>> comp;

        for (int i = 0; i < n; i++)
            comp[d.find(i)].push_back(i);

        // Step 3: check each component
        int ans = comp.size();

        for (auto &it : comp) {
            int sz = d.getSize(it.first);
            bool complete = true;

            for (int node : it.second) {
                if (degree[node] != sz - 1) {
                    complete = false;
                    break;
                }
            }

            if (!complete)
                ans--;
        }

        return ans;
    }
};


// =========================================================================
// MAIN — Test cases for both approaches
// =========================================================================
//
// Test 1: n=6, edges=[[0,1],[0,2],[1,2],[3,4]]
//   Components:
//     {0,1,2} → 3 verts, 3 edges = 3*2/2 = 3 ✓ (complete)
//     {3,4}   → 2 verts, 1 edge  = 2*1/2 = 1 ✓ (complete)
//     {5}     → 1 vert,  0 edges = 1*0/2 = 0 ✓ (trivially complete)
//   Answer: 3
//
// Test 2: n=6, edges=[[0,1],[0,2],[1,2],[3,4],[3,5]]
//   Components:
//     {0,1,2} → complete (3 edges)
//     {3,4,5} → 3 verts, 2 edges ≠ 3 (missing 4-5) ✗
//   Answer: 1
//
// Test 3: n=4, edges=[[0,1],[1,2],[2,3],[3,0]]
//   {0,1,2,3} → 4 verts, 4 edges ≠ 6 (not a clique) ✗
//   Answer: 0
//
// Test 4: n=5, edges=[[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
//   All 5 nodes form a single component.
//   5 verts → need 5*4/2 = 10 edges. We have 10 edges. ✓
//   Answer: 1
//
// Test 5: n=3, edges=[]
//   Three isolated nodes: each is trivially complete (1 vertex, 0 edges).
//   Answer: 3
// =========================================================================

int main() {

    cout << "=== APPROACH 1: DFS ===\n";

    Solution s1;

    // Test 1
    {
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{1,2},{3,4}};
        int res = s1.countCompleteComponents(n, edges);
        cout << "Test 1: " << res << " (expected: 3)\n";
    }

    // Test 2
    {
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{1,2},{3,4},{3,5}};
        int res = s1.countCompleteComponents(n, edges);
        cout << "Test 2: " << res << " (expected: 1)\n";
    }

    // Test 3
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,0}};
        int res = s1.countCompleteComponents(n, edges);
        cout << "Test 3: " << res << " (expected: 0)\n";
    }

    // Test 4
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
        int res = s1.countCompleteComponents(n, edges);
        cout << "Test 4: " << res << " (expected: 1)\n";
    }

    // Test 5
    {
        int n = 3;
        vector<vector<int>> edges = {};
        int res = s1.countCompleteComponents(n, edges);
        cout << "Test 5: " << res << " (expected: 3)\n";
    }

    cout << "\n=== APPROACH 2: DSU ===\n";

    Solution2 s2;

    // Test 1
    {
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{1,2},{3,4}};
        int res = s2.countCompleteComponents(n, edges);
        cout << "Test 1: " << res << " (expected: 3)\n";
    }

    // Test 2
    {
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{1,2},{3,4},{3,5}};
        int res = s2.countCompleteComponents(n, edges);
        cout << "Test 2: " << res << " (expected: 1)\n";
    }

    // Test 3
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,0}};
        int res = s2.countCompleteComponents(n, edges);
        cout << "Test 3: " << res << " (expected: 0)\n";
    }

    // Test 4
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
        int res = s2.countCompleteComponents(n, edges);
        cout << "Test 4: " << res << " (expected: 1)\n";
    }

    // Test 5
    {
        int n = 3;
        vector<vector<int>> edges = {};
        int res = s2.countCompleteComponents(n, edges);
        cout << "Test 5: " << res << " (expected: 3)\n";
    }

    return 0;
}
