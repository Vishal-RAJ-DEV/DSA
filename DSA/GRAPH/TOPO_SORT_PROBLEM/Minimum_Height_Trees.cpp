#include <bits/stdc++.h>
using namespace std;
/*
Step 1

Build adjacency list.

vector<vector<int>> graph(n);
Step 2

Calculate degree of every node.

degree[i] = graph[i].size();
Step 3

Put all leaves into queue.

if (degree[i] == 1)
    q.push(i);
Step 4

Remove leaves layer by layer.

For every leaf:

remove leaf
    ↓
decrease degree of its neighbor
    ↓
if neighbor becomes leaf
    ↓
put neighbor into queue
Step 5

Stop when:

remainingNodes <= 2
Step 6

The nodes left in the queue are the MHT roots.
*/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

        // If there is only one node,
        // that node itself is the center/root.
        if (n == 1) {
            return {0};
        }

        // Build adjacency list
        vector<vector<int>> graph(n);

        // degree[i] = number of current neighbors of node i
        vector<int> degree(n, 0);

        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);

            degree[u]++;
            degree[v]++;
        }

        // Queue contains all current leaf nodes
        queue<int> q;

        for (int i = 0; i < n; i++) {

            // A leaf has only one neighbor
            if (degree[i] == 1) {
                q.push(i);
            }
        }

        // Number of nodes that are still remaining
        int remainingNodes = n;

        // Remove leaves layer by layer
        while (remainingNodes > 2) {

            // Number of leaves in the current layer
            int leaves = q.size();

            // Remove this entire layer
            remainingNodes -= leaves;

            for (int i = 0; i < leaves; i++) {

                int leaf = q.front();
                q.pop();

                // Remove this leaf from the tree.
                // Its neighbors lose one connection.
                for (int neighbor : graph[leaf]) {

                    degree[neighbor]--;

                    // If neighbor now has only one
                    // remaining connection, it becomes a leaf.
                    if (degree[neighbor] == 1) {
                        q.push(neighbor);
                    }
                }
            }
        }

        // The remaining 1 or 2 nodes are the centers
        // and therefore the MHT roots.
        vector<int> answer;

        while (!q.empty()) {
            answer.push_back(q.front());
            q.pop();
        }

        return answer;
    }
};

/*
Brute Force idea

The simplest possible approach is:

Try every node as the root.

For each possible root:

Make that node the root.
Run BFS/DFS from that node.
Find the farthest node.
The distance to that farthest node = height.
Keep track of the minimum height.
Store every root having that minimum height.

So conceptually:

Root 0 → calculate height
Root 1 → calculate height
Root 2 → calculate height
Root 3 → calculate height
...
Root n-1 → calculate height

                    ↓

          Find minimum height

                    ↓

        Return all roots having it
*/
class Solution {
public:

    // DFS calculates the maximum distance
    // from 'node' to any node in its subtree/path
    int dfs(int node, int parent, vector<vector<int>>& graph) {

        int height = 0;

        for (int neighbor : graph[node]) {

            // Don't go back to the parent
            if (neighbor == parent)
                continue;

            // Distance from current node to this neighbor
            int childHeight = dfs(neighbor, node, graph);

            // Take the longest path
            height = max(height, 1 + childHeight);
        }

        return height;
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

        // Special case
        if (n == 1)
            return {0};

        // Build adjacency list
        vector<vector<int>> graph(n);

        for (auto& edge : edges) {

            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int minHeight = INT_MAX;

        vector<int> answer;

        // Try every node as root
        for (int root = 0; root < n; root++) {

            // Calculate height when 'root' is the root
            int height = dfs(root, -1, graph);

            // Found a smaller height
            if (height < minHeight) {

                minHeight = height;

                answer.clear();

                answer.push_back(root);
            }

            // Same minimum height
            else if (height == minHeight) {

                answer.push_back(root);
            }
        }

        return answer;
    }
};

int main(){
    return 0;
}