#include <bits/stdc++.h>
using namespace std;

/* ====================================================================================
   KOSARAJU'S ALGORITHM — Strongly Connected Components (SCC) in a DIRECTED graph
   ====================================================================================

   WHAT IS AN SCC ?
   -----------------
   A Strongly Connected Component is a maximal set of nodes such that EVERY node in the
   set can reach EVERY OTHER node in the set, following the direction of the edges.
   i.e. there is a path from u -> v AND a path from v -> u for every pair (u, v).

   WHY IS IT TRICKY ?
   -------------------
   In a directed graph, connectivity is NOT symmetric. Example:
   edge 1 -> 0 exists, but 0 cannot go back to 1 via a single edge (may need a path).

   KEY INSIGHT / OBSERVATION
   -------------------------
   If we REVERSE all edges of the graph (make the TRANSPOSE graph), then the set of SCCs
   stays EXACTLY the same, only the direction of travel inside each SCC flips.
   WHY? Inside an SCC, if u can reach v, then v can reach u (that IS the definition),
   so reversing edges keeps every pair mutually reachable -> SCCs are unchanged.

   HOW DOES THE ALGORITHM WORK ? (3 STEPS)
   ---------------------------------------
   STEP 1 : Order the nodes by DFS "FINISHING TIME".
            Run DFS on the ORIGINAL graph. Push a node into a STACK only AFTER all
            its neighbours have been fully explored (post-order / finishing order).
            Result: nodes that "finish" later sit on TOP of the stack, i.e. we get a
            finishing-time order (nodes reachable first get popped last, and vice versa).
            This ordering guarantees that when we later process the TRANSPOSE graph,
            we always START from the node that belongs to a "source" SCC of the
            original graph (a component with no incoming edges from other components).

   STEP 2 : Build the TRANSPOSE graph.
            For every edge (u -> v) in the original graph, add edge (v -> u).

   STEP 3 : Count SCCs using the stack on the TRANSPOSE graph.
            Pop nodes one by one from the stack. If a popped node is not yet visited,
            start a DFS on the TRANSPOSE graph from it. Every such DFS visits exactly
            ONE complete SCC (and NOTHING outside it), so increment the SCC counter.
            Repeat until the stack is empty.

   WHY DOES STEP 1's ORDER + TRANSPOSE WORK (intuition) ?
   --------------------------------------------------------
   Consider the SCCs condensed into a DAG (each SCC = one super-node).
   Step 1 pushes a node of a "sink" SCC (no outgoing edges) into the stack LAST,
   so it comes out of the stack FIRST. On the TRANSPOSE graph this sink SCC becomes
   a SOURCE (no incoming edges), so a DFS started from it can NOT leak into any other
   SCC — it stays confined inside exactly one SCC. Hence each DFS = 1 SCC.      

   ====================================================================================
   WORKED EXAMPLE WITH DIAGRAM  (graph used in main())
   ====================================================================================

   Given edges (directed):  1→0 , 0→2 , 2→1 , 0→3 , 3→4

   ORIGINAL GRAPH:                              TRANSPOSE GRAPH (edges reversed):

              ┌──────────┐                            ┌──────────┐
              │          ▼                            │          ▼
          ┌───┴──┐     ┌───┴──┐ 2→1              ┌───┴──┐     ┌───┴──┐ 1→2
          │  1   │     │  2   │                  │  1   │     │  2   │
          └───▲──┘     └──────┘                  └───▲──┘     └──────┘
        1→0    │                                      │ 0→1     ▲
               │  0→2                                 │         │ 2→0
          ┌────┴────┐                            ┌────┴────┐
          │    0    │                            │    0    │
          └────┬────┘                            └────▲────┘
               │ 0→3                                 │ 3→0
               ▼                                     │
          ┌────┴────┐                            ┌────┴────┐
          │    3    │                            │    3    │
          └────┬────┘                            └────▲────┘
               │ 3→4                                 │ 4→3
               ▼                                     │
          ┌────┴────┐                            ┌────┴────┐
          │    4    │                            │    4    │
          └─────────┘                            └─────────┘

   SCCs present:  {0, 1, 2}  (cycle: 0→2→1→0  => every node reaches every other)
                  {3}        (alone — no way back from 3 to 0)
                  {4}        (alone — no outgoing edge at all)
   Total = 3 SCCs   ==>  expected answer: 3

   ====================================================================================
   STEP-BY-STEP TRACE OF THE CODE ON THIS EXAMPLE
   ====================================================================================

   STEP 1 — DFS on ORIGINAL graph, push by finishing time (post-order):
     start dfs(0): visit 0
       → neighbour 2: visit 2
         → neighbour 1: visit 1 → its only neighbour 0 already visited
           push 1                      (1 finishes first)
         push 2
       → neighbour 3: visit 3
         → neighbour 4: visit 4 → no unvisited neighbours
           push 4
         push 3
     push 0
     STACK (bottom→top): [ 1 , 2 , 4 , 3 , 0 ]      (0 finished LAST → on top)

   STEP 2 — Transpose: adjT[0]={1,3}, adjT[1]={2}, adjT[2]={0}, adjT[3]={4}, adjT[4]={}

   STEP 3 — Pop from stack, DFS on TRANSPOSE graph:
     pop 0  : not visited  → scc = 1 → dfs3(0): visits 0 → 1 → 2    {0,1,2}  = SCC #1
     pop 3  : not visited  → scc = 2 → dfs3(3): visits 3 (3→0 goes to visited 0) {3} = SCC #2
     pop 4  : not visited  → scc = 3 → dfs3(4): visits 4 (4→3 goes to visited 3) {4} = SCC #3
     pop 2,1: already visited → skip
   ANSWER: 3  ✔

   TIME COMPLEXITY : O(V + E)     (3 linear traversals of graph)
   SPACE COMPLEXITY: O(V + E)     (visited array, stack, transpose adjacency list)
   ==================================================================================== */

class Solution {
private:
    /* STEP 1 DFS: runs on the ORIGINAL graph.
       - Marks the current node as visited.
       - Recursively explores ALL unvisited neighbours FIRST.
       - Only AFTER the whole subtree (reachable part) is explored, we PUSH the node
         into the stack. This is POST-ORDER traversal => nodes are pushed in order of
         their FINISHING TIME. The node that finishes LAST (the one that can reach the
         most others) ends up on TOP of the stack and will be popped FIRST in Step 3.
       NOTE: This is the standard Topological-Sort-style DFS ordering. */
    void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &st) {
        vis[node] = 1;                       // mark current node as visited
        for (auto it : adj[node]) {          // visit every neighbour in original graph
            if (!vis[it]) {
                dfs(it, vis, adj, st);       // recursively finish neighbour's subtree first
            }
        }
        // Push the node into stack only after ALL its neighbours have finished
        // => stack top = most recently finished node = node of a SINK SCC of original graph
        st.push(node);
    }

    /* STEP 3 DFS: runs on the TRANSPOSED graph.
       - This DFS can ONLY travel along REVERSED edges (v -> u).
       - Because we start from a node of a SINK-SCC (popped first from stack) and the
         transpose graph turns that sink into a SOURCE, the DFS CANNOT escape into any
         other SCC. Whatever it visits belongs to ONE and ONLY ONE SCC.
       - We only count (increment scc counter) when this DFS is started on an
         unvisited node; we do NOT need to store the SCC members here. */
    void dfs3(int node, vector<int> &vis, vector<int> adjT[]) {
        vis[node] = 1;                       // mark node as visited (belongs to current SCC)
        for (auto it : adjT[node]) {         // travel along REVERSED edges only
            if (!vis[it]) {
                dfs3(it, vis, adjT);         // stay inside the same SCC
            }
        }
    }

public:
    // Function to find number of strongly connected components
    int kosaraju(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);   // visited array, all nodes initially unvisited
        stack<int> st;           // stack to store nodes in DECREASING finishing time

        /* ===== STEP 1 =====
           Run DFS on the ORIGINAL graph for every unvisited node and fill the stack
           in post-order (finishing time order). The loop also handles DISCONNECTED
           components: even if some nodes are not reachable from node 0, each of them
           gets its own DFS and still lands in the stack with correct ordering. */
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }

        /* ===== STEP 2 =====
           Build the TRANSPOSE graph: for every edge u -> v in original graph,
           add reverse edge v -> u. SCCs remain identical in the transpose graph.
           We also reset the visited array here so it can be reused in Step 3. */
        vector<int> adjT[V];                 // adjacency list of transpose graph
        for (int i = 0; i < V; i++) {
            vis[i] = 0;                      // reset visited for Step 3
            for (auto it : adj[i]) {
                adjT[it].push_back(i);       // reverse edge: it -> i (was i -> it)
            }
        }

        /* ===== STEP 3 =====
           Pop nodes from the stack (in finishing-time order, i.e. sink-SCC nodes first)
           and run DFS on the TRANSPOSE graph. Every new DFS started on an unvisited
           node discovers EXACTLY one SCC, so increment the counter each time. */
        int scc = 0;                         // strongly connected component counter
        while (!st.empty()) {
            int node = st.top();             // take the node that finished LAST in Step 1
            st.pop();                        // remove it from the stack
            if (!vis[node]) {                // if not yet visited by any earlier DFS
                scc++;                       // found a brand new SCC
                dfs3(node, vis, adjT);       // visit the WHOLE SCC on transpose graph
            }
        }
        return scc;                          // total number of strongly connected components
    }
};

int main() {
    // Example graph: 5 nodes (0..4)
    // Edges: 1->0 , 0->2 , 2->1 , 0->3 , 3->4   (see the diagram in the header comment)
    // Expected SCCs = 3  =>  {0,1,2} , {3} , {4}
    int n = 5;
    int edges[5][2] = {
        {1, 0}, {0, 2},
        {2, 1}, {0, 3},
        {3, 4}
    };

    // Build the ORIGINAL directed graph adjacency list from the edge list
    vector<int> adj[n];
    for (int i = 0; i < 5; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }

    Solution obj;
    int ans = obj.kosaraju(n, adj);
    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}
