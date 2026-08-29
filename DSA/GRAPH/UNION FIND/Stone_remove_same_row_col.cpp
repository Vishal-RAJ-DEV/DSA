// ============================================================
// PROBLEM: Most Stones Removed with Same Row or Column (LeetCode 947)
//
// STATEMENT:
//   You have n stones placed on a 2D grid. In one move, you can
//   remove a stone if it shares the SAME ROW or SAME COLUMN with
//   ANY other stone that is STILL PRESENT.
//
//   Goal: Return the MAXIMUM number of stones that can be removed.
//
// KEY INSIGHT — Connected Components:
//
//   Imagine each stone is a node. Draw an edge between two stones
//   if they share the same row OR the same column. This forms a
//   graph where stones are grouped into CONNECTED COMPONENTS.
//
//   Within a connected component of size k, you can ALWAYS remove
//   (k-1) stones, leaving exactly ONE stone behind. Why?
//
//     - Pick any stone in the component. Since it's connected,
//       there is always another stone sharing its row/col (unless
//       it's the last one).
//     - Remove stones one by one; the last one in each component
//       cannot be removed because no other stone shares its row/col.
//
//   Therefore:
//     Max stones removable = sum over all components of (size - 1)
//                          = (sum of sizes) - (number of components)
//                          = n - components
//
//   So the problem reduces to: COUNT THE NUMBER OF CONNECTED
//   COMPONENTS in the graph where edges = "same row or same column".
//
// EXAMPLE:
//   stones = [[0,0], [0,1], [1,0], [1,2], [2,1], [2,2]]
//
//   Connections:
//     [0,0] — same row → [0,1]; same col → [1,0]
//     [0,1] — same row → [0,0]; same col → [2,1]
//     [1,0] — same row → [1,2]; same col → [0,0]
//     [1,2] — same row → [1,0]; same col → [2,2]
//     [2,1] — same row → [2,2]; same col → [0,1]
//     [2,2] — same row → [2,1]; same col → [1,2]
//
//   All 6 stones are ONE component. So components = 1.
//   Answer = n - components = 6 - 1 = 5.
//   (Remove 5 stones, keep 1)
// ============================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// APPROACH 1: DFS (Depth-First Search)
//
// Build the graph IMPLICITLY: for each node, we scan ALL other
// nodes to find neighbors. No explicit adjacency list needed.
//
// LOGIC:
//   1. Start DFS from an unvisited node.
//   2. Mark it visited.
//   3. For every other unvisited node, if it shares row OR col,
//      recursively DFS into it (they're in the same component).
//   4. After DFS finishes, we've traversed one full component.
//   5. Count components. Answer = n - components.
//
// COMPLEXITY: O(n²) time, O(n) space
// ============================================================
class Solution {
public:
    // DFS to mark all stones in the same component as 'node'
    // stones[node][0] = row, stones[node][1] = column
    void dfs(int node, vector<vector<int>>& stones, vector<bool>& vis) {

        vis[node] = true;                // Mark current stone as visited

        // Scan ALL other stones to find those connected to 'node'
        for (int i = 0; i < stones.size(); i++) {

            if (vis[i]) continue;        // Already visited → skip

            // Check if stone i shares the SAME ROW or SAME COLUMN with stone 'node'
            // If yes, they are in the same connected component
            if (stones[node][0] == stones[i][0] ||
                stones[node][1] == stones[i][1]) {

                dfs(i, stones, vis);     // Recursively visit the connected stone
            }
        }
    }

    int removeStones(vector<vector<int>>& stones) {

        int n = stones.size();

        vector<bool> vis(n, false);      // Track visited stones
        int components = 0;              // Count of connected components

        for (int i = 0; i < n; i++) {

            if (!vis[i]) {               // Found a new component
                dfs(i, stones, vis);
                components++;            // Increment component count
            }
        }

        // Each component of size k can remove (k-1) stones
        // Total removable = sum(k-1) = n - components
        return n - components;
    }
};

// ============================================================
// DSU (Disjoint Set Union / Union-Find) Data Structure
//
// Supports:
//   - find(x): find the root/representative of the set containing x
//     (with path compression for O(α(n)) amortized)
//   - unite(u, v): merge the sets containing u and v
//     (union by size for O(α(n)) amortized)
// ============================================================
class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);

        // Each node is its own parent initially (singleton sets)
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find the root of the set containing x
    // Uses PATH COMPRESSION: after finding root, set parent[x] = root
    // This flattens the tree for future O(1) lookups
    int find(int x) {
        if (parent[x] == x)
            return x;                     // x is the root of its set

        return parent[x] = find(parent[x]);  // Path compression
    }

    // Merge the sets containing u and v
    // Uses UNION BY SIZE: attach smaller tree under larger tree
    // to keep tree depth O(log n)
    void unite(int u, int v) {

        u = find(u);                      // Find root of u's set
        v = find(v);                      // Find root of v's set

        if (u == v)
            return;                       // Already in the same set

        // Ensure u is the root of the LARGER set
        if (size[u] < size[v])
            swap(u, v);

        parent[v] = u;                    // Attach v's tree under u's tree
        size[u] += size[v];               // Update size of the merged set
    }
};

// ============================================================
// APPROACH 2: DSU (Disjoint Set Union)
//
// LOGIC:
//   1. Initialize DSU with n nodes (each stone is its own component).
//   2. For EVERY pair of stones (i, j), if they share row OR column,
//      UNITE them into the same set.
//   3. After all unions, count distinct roots (find(i) == i).
//      This is the number of connected components.
//   4. Answer = n - components.
//
// HOW "SAME ROW OR SAME COLUMN" UNITES THEM:
//   If stone i = (r1, c1) and stone j = (r2, c2) with r1 == r2,
//   then they lie in the same ROW. They are DIRECTLY connected.
//   Similarly if c1 == c2, they are DIRECTLY connected.
//
//   Transitivity: If stone A connects to B (same row), and B
//   connects to C (same column), then A, B, C are all in one
//   component even though A and C share neither row nor col.
//   DSU handles this automatically via unite(A,B) then unite(B,C).
//
// COMPLEXITY: O(n² × α(n)) time, O(n) space
//   (α(n) = inverse Ackermann, nearly constant)
//
// NOTE: There is a more efficient O(n) approach using unordered_map
// to union by row/column indices, but this O(n²) version is the
// most intuitive translation of the graph idea.
// ============================================================
class UsingDSU_findRemoveStones {
public:
    int removeStones(vector<vector<int>>& stones) {

        int n = stones.size();

        DSU dsu(n);                       // Initialize DSU with n stones

        // Check every pair of stones and unite if they share row/col
        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                // If same row OR same column → they're connected
                if (stones[i][0] == stones[j][0] ||
                    stones[i][1] == stones[j][1]) {

                    dsu.unite(i, j);      // Merge them into one component
                }
            }
        }

        // Count distinct components: roots are nodes where find(i) == i
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == i)
                components++;
        }

        // Each component of size k can remove (k-1) stones
        return n - components;
    }
};


int main() {
    return 0;
}
