// ============================================================
// PROBLEM: Subordinates (CSES 1674)
//
// STATEMENT:
//   A company has n employees numbered 1..n. Employee 1 is the
//   general manager (root). For each employee i (2..n), their
//   immediate boss b[i] is given (b[i] < i, so it's a tree rooted
//   at 1).
//
//   For each employee, output the number of subordinates they
//   have (direct + indirect).
//
// EXAMPLE:
//   Input:
//     n = 5
//     bosses: 1 1 2 3
//     (employee 2's boss=1, 3's boss=1, 4's boss=2, 5's boss=3)
//
//   Tree:
//         1
//        / \
//       2   3
//      /     \
//     4       5
//
//   Output: 4 1 1 0 0
//   (1 has 4 subordinates, 2 has 1, 3 has 1, 4 has 0, 5 has 0)
//
// ALGORITHM — DFS Subtree Size:
//
//   This is a classic subtree-size computation on a rooted tree.
//
//   1. Build an adjacency list: for each employee, store their
//      direct children (not parent).
//
//   2. Run DFS from root (1). For each node:
//        sub_size[node] = 1 + sum of sub_size[child] for all children
//      (The 1 counts the node itself; we subtract it at output.)
//
//   3. Print sub_size[i] - 1 for each employee i (exclude self).
//
// COMPLEXITY: O(n) time, O(n) space
// ============================================================

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;    // adjacency list: children of each node
vector<int> sub_size;       // subtree size (includes the node itself)

// DFS to compute subtree sizes
// Returns the size of the subtree rooted at 'node'
int dfs(int node) {
    sub_size[node] = 1;                     // count the node itself

    for (int child : adj[node]) {
        sub_size[node] += dfs(child);       // add size of each child's subtree
    }

    return sub_size[node];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.assign(n + 1, vector<int>());       // 1-indexed
    sub_size.assign(n + 1, 0);

    // Read the immediate boss for employees 2..n
    for (int i = 2; i <= n; i++) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);             // boss → child edge
    }

    // Compute subtree sizes starting from root (employee 1)
    dfs(1);

    // Output: subtract 1 to exclude the employee themself
    for (int i = 1; i <= n; i++) {
        cout << sub_size[i] - 1 << " \n"[i == n];
    }

    return 0;
}
