#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM: Find All Ancestors of Each Node in a DAG
 *
 * Given a Directed Acyclic Graph (DAG) with n nodes (0 to n-1)
 * and a list of directed edges, for EACH node return a sorted
 * list of ALL its ancestors (nodes that have a path TO it).
 *
 * Example:
 *   Edges: 0->1, 0->2, 1->3, 2->3, 3->4
 *
 *   0 → 1 → 3 → 4
 *   0 → 2 ↗
 *
 *   ancestors[0] = []
 *   ancestors[1] = [0]
 *   ancestors[2] = [0]
 *   ancestors[3] = [0, 1, 2]
 *   ancestors[4] = [0, 1, 2, 3]
 *
 * WHY TOPOLOGICAL SORT (Kahn's BFS)?
 *   - Topological order guarantees that when we process node u,
 *     ALL of u's ancestors have ALREADY been processed.
 *   - This means ancestors[u] is COMPLETE when we use it.
 *   - Without topo sort, we might process u before its ancestors
 *     are fully computed, giving wrong/incomplete results.
 *
 * WHY SET (not vector)?
 *   - A node can have MULTIPLE parents, and those parents may
 *     share common ancestors.
 *   - Example: ancestors[3] gets ancestors from both 1 and 2.
 *     Both 1 and 2 have ancestor 0. Without set, 0 appears twice.
 *   - Set AUTOMATICALLY deduplicates AND keeps elements sorted.
 *   - This avoids manual sorting and duplicate filtering at the end.
 *
 * HOW ANCESTOR PROPAGATION WORKS:
 *   When processing edge u -> v:
 *     1. u itself is an ancestor of v  →  insert u into ancestors[v]
 *     2. All ancestors of u are ALSO ancestors of v (transitive)
 *        →  insert every node in ancestors[u] into ancestors[v]
 *
 *   This is the TRANSITIVE CLOSURE: if a->b and b->c, then a is
 *   an ancestor of c. We propagate this information forward.
 *
 * TIME COMPLEXITY:
 *   Let V = n (number of nodes), E = number of edges.
 *
 *   Building graph:        O(V + E)
 *   Topological sort BFS:  O(V + E)
 *   For each edge (u, v):  we iterate over ancestors[u] and insert
 *                          each into ancestors[v] (set insert = O(log V))
 *                          ancestors[u] has at most V-1 elements
 *                          → O(V) per edge for the propagation loop
 *                          → O(V * E) total for all edges
 *   Converting set→vector: O(total ancestors stored) ≤ O(V²)
 *
 *   TOTAL: O(V * E) time, O(V²) space
 *
 *   Worst case (dense DAG): E = V², so O(V³)
 *   Typical case: much less since DAGs are often sparse.
 *
 * SPACE COMPLEXITY:
 *   - adj: O(V + E)
 *   - ancestors: O(V²) in worst case (each node stores up to V-1 ancestors)
 *   - queue: O(V)
 *   TOTAL: O(V²)
 */

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {

        // Step 1: Build adjacency list and compute indegree for each node.
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);   // u has a directed edge to v
            indegree[v]++;         // v has one more incoming edge
        }

        // Step 2: For each node, maintain a SET of its ancestors.
        // Set is used because:
        //   (a) A node can be reached via multiple paths → duplicates possible.
        //   (b) Set auto-deduplicates and keeps elements sorted (ascending).
        // This avoids manual sorting and duplicate removal later.
        vector<set<int>> ancestors(n);

        // Step 3: Kahn's algorithm — BFS-based topological sort.
        // Start by enqueueing all nodes with indegree 0 (no dependencies).
        queue<int> q;

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 4: Process nodes in topological order.
        // KEY INVARIANT: When we pop node u from the queue,
        // ancestors[u] is FULLY COMPUTED (all its ancestors already processed).
        while (!q.empty()) {

            int u = q.front();
            q.pop();

            // For each neighbor v that u points to (edge u -> v):
            for (int v : adj[u]) {

                // (a) u is a DIRECT ancestor of v → add u to ancestors[v]
                ancestors[v].insert(u);

                // (b) TRANSITIVE CLOSURE: all ancestors of u are also
                //     ancestors of v. If a->...->u->v, then a is ancestor of v.
                //     We copy ALL ancestors of u into ancestors[v].
                for (int x : ancestors[u]) {
                    ancestors[v].insert(x);
                }

                // (c) Reduce indegree of v. When indegree hits 0,
                //     ALL its parents have been processed → safe to process v.
                indegree[v]--;

                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Step 5: Convert set<int> → vector<int> for the required return type.
        // Since set is already sorted, the output is automatically sorted.
        vector<vector<int>> ans(n);

        for (int i = 0; i < n; i++) {
            for (int x : ancestors[i]) {
                ans[i].push_back(x);
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}