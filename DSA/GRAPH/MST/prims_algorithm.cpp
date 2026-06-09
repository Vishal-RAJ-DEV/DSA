#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int prims(int V, vector<vector<pii>>& adj) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    vector<bool> visited(V, false);

    // {weight, node}
    pq.push({0, 0});

    int totalWeight = 0;

    while (!pq.empty()) {
        auto it = pq.top();
        int wt = it.first;
        int node = it.second;
        pq.pop();

        if (visited[node]) continue;

        visited[node] = true;
        totalWeight += wt;

        for (auto &neighbor : adj[node]) {
            int adjNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (!visited[adjNode]) {
                pq.push({edgeWeight, adjNode});
            }
        }
    }

    return totalWeight;
}

int main() {
    int V = 5;

    vector<vector<pii>> adj(V);

    // u, v, weight
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    cout << "Minimum Spanning Tree Weight: " << prims(V, adj) << endl;

    return 0;
}

//time complexity: O(E log V) where E is the number of edges and V is the number of vertices in the graph. This is because each edge is processed at most once and each operation on the priority queue takes O(log V) time.
//space complexity: O(V) for the visited array and O(V) for the priority queue in the worst case, leading to O(V) overall space complexity.

/*

Operation	       Count	Cost-per-op	   Total
Push into heap	    O(E)	O(log E)	   O(E log E)
Pop from heap	    O(E)	O(log E)	   O(E log E)
Adjacency traversal	O(E)	O(1)	       O(E)
*/
// 👉 Final:  O(E log E) → O(E log V)