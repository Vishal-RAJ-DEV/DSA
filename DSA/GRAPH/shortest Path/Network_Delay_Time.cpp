#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Algorithm: Network Delay Time using Dijkstra's Algorithm

        We are given directed weighted edges:
            times[i] = {source, destination, time}

        We need to find how long it takes for the signal from node k
        to reach every node. That means:
        - Find the shortest time from k to every node.
        - The final answer is the maximum shortest time among all nodes.
        - If any node is unreachable, return -1.

        Why Dijkstra?
        - Edge weights are positive.
        - We need shortest path from one source to all nodes.
        - Dijkstra always processes the currently smallest known distance first.

        Why put distance first in priority_queue?
        - pq stores pairs like {distance, node}.
        - C++ compares pair values by first element, then second element.
        - Since we use greater<pair<int,int>>, the smallest distance comes on top.
        - If we stored {node, distance}, the pq would sort by node number,
          which would break Dijkstra's logic.

        Why not use a max variable during pq traversal?
        - During traversal, a node may first be reached with a bigger time,
          then later updated with a smaller shortest time.
        - If we update max too early, it may store an old non-final distance.
        - After Dijkstra finishes, dist contains final shortest times.
        - So we calculate max from dist at the end.

        Time Complexity: O((V + E) log V)
        Space Complexity: O(V + E)
    */
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        // adj[u] stores all outgoing edges from node u.
        // Each pair is {destination node, time taken}.
        vector<pair<int,int>> adj[n + 1];

        // Build the directed graph from the given edge list.
        for(int i = 0; i < times.size(); i++) {

            int src = times[i][0];
            int dest = times[i][1];
            int time = times[i][2];

            // Signal can travel from src to dest in 'time' units.
            adj[src].push_back({dest, time});
        }

        // Min priority queue.
        // Pair format: {current shortest time, node}.
        // Distance is first because priority_queue compares the first value first.
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        // dist[i] stores the shortest known time to reach node i from k.
        // Initially every node is unreachable, so distance is INT_MAX.
        vector<int> dist(n + 1, INT_MAX);

        // Source node k takes 0 time to reach itself.
        pq.push({0, k});
        dist[k] = 0;

        // Process the node with the smallest current time first.
        while(!pq.empty()) {

            auto top = pq.top();
            pq.pop();

            // currtime is the shortest time taken to reach src from k.
            int currtime = top.first;
            int src = top.second;

            // If this pq entry is old and we already found a better distance,
            // skip it. This happens because the same node can be pushed multiple times.
            if(currtime > dist[src]) continue;

            // Try to relax all neighbours of src.
            for(auto &it : adj[src]) {

                int nextnode = it.first;
                int timetaken = it.second;

                // If going through src gives a shorter time to nextnode,
                // update the shortest time.
                if(currtime + timetaken < dist[nextnode]) {

                    dist[nextnode] = currtime + timetaken;

                    // Push updated shortest time first so pq sorts by time.
                    pq.push({dist[nextnode], nextnode});
                }
            }
        }

        // Now all shortest distances are final.
        // The network delay is the largest shortest time among all nodes.
        // We calculate it at the end instead of tracking max during traversal,
        // because earlier values in pq may not be final shortest distances.
        int maxtime =
            *max_element(dist.begin() + 1, dist.end());

        // If any node still has INT_MAX, it was not reachable from k.
        return maxtime == INT_MAX ? -1 : maxtime;
    }
};

class DFS_Solution {
public:
    /*
        DFS Approach for Network Delay Time

        This is another way to solve the problem for learning purposes.

        Idea:
        - Build the same directed weighted graph.
        - dist[node] stores the best time found so far to reach that node.
        - Start DFS from k with time 0.
        - Whenever DFS reaches a node with a smaller time than before,
          update dist[node] and continue exploring its neighbours.
        - If DFS reaches a node with time >= dist[node], stop that path
          because we already have a better or equal route.

        Important:
        - Dijkstra is preferred for this problem because it processes shortest
          distances in sorted order using a priority queue.
        - DFS can revisit nodes many times when it finds better paths later,
          so it is usually less efficient than Dijkstra for weighted graphs.

        Time Complexity: Can be worse than Dijkstra because nodes may be
        revisited multiple times.
        Space Complexity: O(V + E) for graph and recursion stack.
    */

    void dfs(int node,
             int currtime,
             vector<vector<pair<int,int>>>& adj,
             vector<int>& dist) {

        // If this path is not better than the best known time,
        // no need to continue from here.
        if(currtime >= dist[node]) return;

        // Store the best time found so far for this node.
        dist[node] = currtime;

        // Explore all outgoing edges from the current node.
        for(auto &it : adj[node]) {

            int nextnode = it.first;
            int timetaken = it.second;

            // Move to nextnode and add the edge time to current time.
            dfs(nextnode, currtime + timetaken, adj, dist);
        }
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        // adj[u] stores {v, w}, meaning u -> v takes w time.
        vector<vector<pair<int,int>>> adj(n + 1);

        // Build the graph.
        for(int i = 0; i < times.size(); i++) {

            int src = times[i][0];
            int dest = times[i][1];
            int time = times[i][2];

            adj[src].push_back({dest, time});
        }

        // Optional but useful for DFS:
        // visiting smaller edges first may help find good distances earlier.
        for(int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end(),
                 [](pair<int,int>& a, pair<int,int>& b) {
                     return a.second < b.second;
                 });
        }

        // dist[i] stores the best time found by DFS to reach node i.
        vector<int> dist(n + 1, INT_MAX);

        // Start signal from node k at time 0.
        dfs(k, 0, adj, dist);

        // Final answer is the maximum time among all shortest times found.
        int maxtime =
            *max_element(dist.begin() + 1, dist.end());

        // If some node is still INT_MAX, it cannot receive the signal.
        return maxtime == INT_MAX ? -1 : maxtime;
    }
};


int main(){
    Solution obj;
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4, k = 2;
    int ans = obj.networkDelayTime(times, n, k);
    cout << "The time taken for all nodes to receive the signal is: " << ans << "\n";
    return 0;
}
