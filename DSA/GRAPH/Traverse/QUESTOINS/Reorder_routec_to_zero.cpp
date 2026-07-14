#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// =========================================================================
// QUESTION: Reorder Routes to Make All Paths Lead to the City Zero
// (LeetCode 1466)
//
// There are n cities numbered from 0 to n-1 and n-1 roads such that there
// is exactly one way to travel between any two cities (a tree structure).
// Each road is initially directed (one-way). We need to change the
// direction of some roads so that EVERY city can reach city 0.
// Find the MINIMUM number of road reversals needed.
//
// Constraint: The graph is a TREE (connected, n nodes, n-1 edges).
// =========================================================================

// =========================================================================
// INTUITION & ALGORITHM (DFS Approach)
// =========================================================================
//
// PROBLEM VISUALIZATION:
//   We have a tree with directed edges. City 0 is the capital/target.
//   We need ALL paths to eventually lead TO city 0.
//   Some edges already point towards 0, some point away — we need to
//   reverse the ones pointing away.
//
// KEY INSIGHT:
//   Since the graph is a TREE, there is exactly one path between any two
//   cities. To make every city reach 0, ALL edges along the unique path
//   from each city to 0 must be directed TOWARD 0.
//
//   -> If an edge on the path from a city to 0 points AWAY from 0,
//      it must be reversed.
//   -> The minimum number of reversals = number of edges that are
//      currently pointing AWAY from city 0 along their tree path.
//
// HOW WE SOLVE IT:
//   We cannot traverse a directed tree from city 0 because edges may
//   point away from 0, blocking traversal. So we:
//
//   1. BUILD AN UNDIRECTED GRAPH for traversal, but store a "direction
//      flag" on each edge:
//        dir = 1  → This IS the original direction of the road.
//                    Original: u ──→ v
//                    Stored as: graph[u] -> (v, 1)  [original direction]
//                               graph[v] -> (u, 0)  [helper edge for traversal]
//        dir = 0  → This is a HELPER/REVERSE edge we added only for
//                    traversal. The original road goes the opposite way.
//
//   2. START BFS/DFS FROM CITY 0.
//      Since we made the graph undirected (by adding helper edges with
//      dir=0), we can visit every city from 0.
//
//   3. COUNT REVERSALS:
//      Whenever we traverse from a parent to a child through an edge:
//        - If dir == 1: We used the ORIGINAL edge direction.
//          Original road: parent ──→ child
//          Since we started from 0 and are moving OUTWARD, this means
//          the road is pointing AWAY from city 0 → needs reversal.
//          ans += 1
//
//        - If dir == 0: We used the HELPER edge.
//          Original road: child ──→ parent  (points TOWARD 0)
//          The road is already correct → no reversal needed.
//          ans += 0
//
// EASY WAY TO REMEMBER (from city 0 perspective):
//   "Whenever I walk from city 0 to another city:
//    - If the road goes in the same direction I'm walking (dir = 1),
//      it's pointing away from 0 → reverse it.
//    - If the road goes opposite to my walking direction (dir = 0),
//      it's already pointing towards 0 → leave it."
//
// VISUALIZATION:
//
//   Original road:  0 ──→ 1
//   Stored as:
//     0 -> (1, 1)     ← original direction, points AWAY from 0
//     1 -> (0, 0)     ← helper edge (only for traversal)
//   BFS/DFS from 0:
//     0 → 1  using dir = 1  → REVERSAL NEEDED
//
//   Original road:  1 ──→ 0
//   Stored as:
//     1 -> (0, 1)     ← original direction
//     0 -> (1, 0)     ← helper edge (only for traversal)
//   BFS/DFS from 0:
//     0 → 1  using dir = 0  → ALREADY CORRECT, no reversal
//
// ONE-LINE INTERVIEW EXPLANATION:
//   "I treat the tree as an undirected graph for traversal. For each edge,
//    I store whether it's in its original direction (1) or a helper reverse
//    edge (0). While traversing from city 0, every time I use an original
//    edge (dir = 1), it means that edge points away from the capital and
//    must be reversed, so I increment the answer. If dir = 0, the original
//    edge already points toward the capital, so no change is needed."
// =========================================================================

// =========================================================================
// APPROACH 1: DFS (Recursive)
// =========================================================================

class Solution {
public:
    // graph[node] = list of {neighbor, direction}
    // direction: 1 = original edge in this direction
    //            0 = helper edge (original goes opposite way)
    vector<vector<pair<int,int>>> graph;
    vector<bool> visited;
    int changes = 0;

    void dfs(int node) {
        visited[node] = true;               // mark current city as visited

        for (auto &it : graph[node]) {      // explore all neighbors
            int nei = it.first;             // neighboring city
            int dir = it.second;            // direction flag (1 or 0)

            if (!visited[nei]) {            // if neighbor not visited yet
                changes += dir;             // dir==1 → need reversal; dir==0 → no change
                dfs(nei);                   // recursively visit the neighbor
            }
        }
    }

    int minReorder(int n, vector<vector<int>>& connections) {

        graph.resize(n);                    // initialize adjacency list for n cities

        // Build undirected graph with direction flags
        for (auto &e : connections) {
            int u = e[0];
            int v = e[1];

            // Original edge: u ──→ v
            // Store in u's list with dir = 1 (this IS the original direction)
            graph[u].push_back({v, 1});

            // For traversal: add reverse edge with dir = 0 (helper only)
            // The original road goes v ←── u, so if we travel v→u,
            // it's already pointing toward the "parent" (toward 0).
            graph[v].push_back({u, 0});
        }

        visited.assign(n, false);           // no city visited yet

        dfs(0);                             // start DFS from city 0

        return changes;                     // total reversals needed
    }
};


// =========================================================================
// APPROACH 2: BFS (Iterative using Queue)
// =========================================================================
// This uses the exact same logic as DFS, but iteratively with a queue.
// The traversal order differs (level-by-level vs depth-first), but the
// reversal counting logic is identical: dir == 1 → reverse, dir == 0 → skip.
// =========================================================================

class Solution2 {
public:
    int minReorder(int n, vector<vector<int>>& connections) {

        // graph[node] = list of {neighbor, direction}
        // dir = 1 → original edge direction, dir = 0 → helper edge for traversal
        vector<vector<pair<int, int>>> graph(n);

        // Build undirected graph with direction flags
        for (auto &e : connections) {
            int u = e[0];
            int v = e[1];

            // Original direction: u ──→ v
            graph[u].push_back({v, 1});     // this IS the original road direction

            // Helper edge (only for traversal): v ──→ u
            // Original road goes u ──→ v, so traversing v→u means the
            // original road was already pointing toward the parent (toward 0).
            graph[v].push_back({u, 0});     // dir = 0 → helper edge
        }

        vector<bool> visited(n, false);     // track visited cities
        queue<int> q;                       // BFS queue

        q.push(0);                          // start from city 0
        visited[0] = true;                  // mark it visited

        int ans = 0;                        // count of reversals needed

        // BFS traversal
        while (!q.empty()) {
            int node = q.front();           // get the front city
            q.pop();                        // remove it from queue

            // Visit all neighbors of current city
            for (auto &it : graph[node]) {
                int nei = it.first;         // neighboring city
                int dir = it.second;        // direction flag

                if (!visited[nei]) {        // if neighbor not visited yet

                    ans += dir;             // dir==1 → reversal needed, dir==0 → skip

                    visited[nei] = true;    // mark as visited
                    q.push(nei);            // enqueue for later processing
                }
            }
        }

        return ans;                         // minimum number of reorders
    }
};


// =========================================================================
// MAIN — Test Cases
// =========================================================================
// Test 1: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
//   Tree:
//     0 ──→ 1 ──→ 3 ←── 2
//     ↑
//     4 ──→ 5
//   From 0: edges pointing away: 0→1, 1→3, 4→5  (3 reversals)
//   Answer: 3
//
// Test 2: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
//   Tree:
//     0 ←── 1 ──→ 2 ←── 3 ──→ 4
//   From 0: edges pointing away: 1→2, 3→4  (2 reversals)
//   Answer: 2
//
// Test 3: n = 3, connections = [[1,0],[2,0]]
//   Tree:
//     1 ──→ 0 ←── 2
//   From 0: no edges point away (both already toward 0)
//   Answer: 0
// =========================================================================

int main() {

    cout << "=== APPROACH 1: DFS ===\n";

    // Test 1
    {
        Solution s;
        int n = 6;
        vector<vector<int>> conn = {{0,1},{1,3},{2,3},{4,0},{4,5}};
        int res = s.minReorder(n, conn);
        cout << "Test 1: " << res << " (expected: 3)\n";
    }

    // Test 2
    {
        Solution s;
        int n = 5;
        vector<vector<int>> conn = {{1,0},{1,2},{3,2},{3,4}};
        int res = s.minReorder(n, conn);
        cout << "Test 2: " << res << " (expected: 2)\n";
    }

    // Test 3
    {
        Solution s;
        int n = 3;
        vector<vector<int>> conn = {{1,0},{2,0}};
        int res = s.minReorder(n, conn);
        cout << "Test 3: " << res << " (expected: 0)\n";
    }

    cout << "\n=== APPROACH 2: BFS ===\n";

    // Test 1
    {
        Solution2 s;
        int n = 6;
        vector<vector<int>> conn = {{0,1},{1,3},{2,3},{4,0},{4,5}};
        int res = s.minReorder(n, conn);
        cout << "Test 1: " << res << " (expected: 3)\n";
    }

    // Test 2
    {
        Solution2 s;
        int n = 5;
        vector<vector<int>> conn = {{1,0},{1,2},{3,2},{3,4}};
        int res = s.minReorder(n, conn);
        cout << "Test 2: " << res << " (expected: 2)\n";
    }

    // Test 3
    {
        Solution2 s;
        int n = 3;
        vector<vector<int>> conn = {{1,0},{2,0}};
        int res = s.minReorder(n, conn);
        cout << "Test 3: " << res << " (expected: 0)\n";
    }

    return 0;
}
