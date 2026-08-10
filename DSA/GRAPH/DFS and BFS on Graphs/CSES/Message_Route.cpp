#include <bits/stdc++.h>
using namespace std;
/*
The pattern to remember

Whenever you see:

Unweighted graph + shortest path + need the actual path

Immediately think:

BFS
 ↓
visited[]
 ↓
parent[]
 ↓
reconstruct path

And the core template is:

q.push(start);
visited[start] = true;

while (!q.empty()) {

    int node = q.front();
    q.pop();

    for (int next : adj[node]) {

        if (!visited[next]) {

            visited[next] = true;
            parent[next] = node;
            q.push(next);
        }
    }
}

Then:

vector<int> path;

for (int cur = n; cur != -1; cur = parent[cur])
    path.push_back(cur);

reverse(path.begin(), path.end());

That BFS + parent[] pattern is very important for graph problems and will appear repeatedly in LeetCode, CSES, Codeforces, etc.
*/
class Solution {
public:
    void solve() {

        int n, m;
        cin >> n >> m;

        // Adjacency list
        vector<vector<int>> adj(n + 1);

        // Build the undirected graph
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // parent[x] tells us:
        // From which node did we reach x?
        vector<int> parent(n + 1, -1);

        // To know whether a node is already visited
        vector<bool> visited(n + 1, false);

        // BFS queue
        queue<int> q;

        // Start BFS from computer 1
        q.push(1);
        visited[1] = true;

        // BFS
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // Explore all neighbours
            for (int neighbor : adj[node]) {

                // If this computer is not visited
                if (!visited[neighbor]) {

                    // Mark it visited
                    visited[neighbor] = true;

                    // Store how we reached this node
                    parent[neighbor] = node;

                    // Add it to BFS queue
                    q.push(neighbor);
                }
            }
        }

        // If computer n was never visited,
        // there is no route from 1 to n.
        if (!visited[n]) {
            cout << "IMPOSSIBLE\n";
            return;
        }

        // ------------------------------------
        // Reconstruct the shortest path
        // ------------------------------------

        vector<int> path;

        int current = n;

        // Move backwards using parent[]
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        // Currently:
        // n -> ... -> 1
        // We need:
        // 1 -> ... -> n
        reverse(path.begin(), path.end());

        // Number of computers in the route
        cout << path.size() << '\n';

        // Print the route
        for (int node : path) {
            cout << node << " ";
        }

        cout << '\n';
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution obj;
    obj.solve();

    return 0;
}