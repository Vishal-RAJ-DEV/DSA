#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Optimal Approach — BFS from Every Node

The most standard optimal solution is:

Run BFS starting from every vertex and detect a cycle while doing BFS.

The important observation is this:

Suppose BFS starts from node 0.

       0
      / \
     1   2
      \ /
       3

BFS distances:

dist[0] = 0
dist[1] = 1
dist[2] = 1
dist[3] = 2

When processing node 1, we see neighbor 3.

But:

dist[3] != -1

So 3 has already been visited.

However, we cannot simply say:

"Visited node means cycle."

Because in an undirected graph, we always see the edge back to our parent.

For example:

0 -- 1

While processing 1, we see 0.

0 is already visited, but this is not a cycle.

Therefore we need to remember the parent.
*/
class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {

        // Build adjacency list
        vector<vector<int>> graph(n);

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int ans = INT_MAX;

        // BFS from every node
        for (int start = 0; start < n; start++) {

            vector<int> dist(n, -1);
            vector<int> parent(n, -1);

            queue<int> q;

            dist[start] = 0;
            q.push(start);

            while (!q.empty()) {

                int node = q.front();
                q.pop();

                for (int neighbor : graph[node]) {

                    // First time visiting this node
                    if (dist[neighbor] == -1) {

                        dist[neighbor] = dist[node] + 1;
                        parent[neighbor] = node;

                        q.push(neighbor);
                    }

                    // Already visited and not our parent
                    else if (neighbor != parent[node]) {

                        int cycleLength =
                            dist[node] + dist[neighbor] + 1;

                        ans = min(ans, cycleLength);
                    }
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};


/*
Brute Force Approach

A very direct thought is:

For every edge (u, v), remove that edge and check whether u and v can still reach each other.

Why does this work?

Suppose:

u -------- v
 \        /
  \------/

If we remove the direct edge:

u -------- v

but there is still another path:

u → a → b → v

then adding the removed edge gives:

u → a → b → v → u

which is a cycle.

So:

For every edge (u, v):
Temporarily ignore (u, v).
Run BFS/DFS from u.
Check whether we can reach v.

If yes:

cycle length = distance(u, v) + 1
Take the minimum.
*/
class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {

        int ans = INT_MAX;

        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            // BFS after removing edge (u, v)
            vector<int> dist(n, -1);
            queue<int> q;

            dist[u] = 0;
            q.push(u);

            while (!q.empty()) {

                int node = q.front();
                q.pop();

                for (auto &e : edges) {

                    // Ignore the current edge
                    if ((e[0] == u && e[1] == v) ||
                        (e[0] == v && e[1] == u)) {
                        continue;
                    }

                    int a = e[0];
                    int b = e[1];

                    int next = -1;

                    if (a == node)
                        next = b;
                    else if (b == node)
                        next = a;

                    if (next != -1 && dist[next] == -1) {
                        dist[next] = dist[node] + 1;
                        q.push(next);
                    }
                }
            }

            // u can reach v after removing edge
            if (dist[v] != -1) {
                ans = min(ans, dist[v] + 1);
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};


int main(){
    return 0;
}