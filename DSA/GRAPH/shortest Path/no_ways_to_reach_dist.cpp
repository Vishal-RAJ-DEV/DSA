#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    const int mod = 1e9 + 7;
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        /*
            Algorithm: Number of Ways to Reach Destination

            Here we use Dijkstra's algorithm to find the minimum distance
            from 0th node to every other node.

            With that, we use ways array to store the number of shortest ways
            to go from 0th node to every node.

            Meaning:
            - dist[node] = shortest time found till now to reach node.
            - ways[node] = number of different paths that reach node
                           using exactly dist[node] shortest time.

            How ways array is filled:
            1. For source node 0:
               - dist[0] = 0
               - ways[0] = 1
               Because there is exactly one way to stand at the source:
               start from the source itself.

            2. If we find a smaller distance for nextnode:
                   currtime + time < dist[nextnode]

               This means we found a new better shortest path.
               So old ways of nextnode are no longer useful.

               Then:
                   dist[nextnode] = currtime + time
                   ways[nextnode] = ways[node]

               Why ways[nextnode] = ways[node]?
               Because every shortest way to reach node can now be extended
               through this edge to reach nextnode.

            3. If we find the same shortest distance again:
                   currtime + time == dist[nextnode]

               This means another shortest path is found for nextnode.
               So ways[nextnode] increases.

               Important:
               We do not do ways[nextnode] + 1.
               We add ways[node], because node itself may be reachable through
               multiple shortest paths.

               Then:
                   ways[nextnode] = ways[nextnode] + ways[node]

            Time Complexity: O((V + E) log V)
            Space Complexity: O(V + E)
        */

        // Build adjacency list for an undirected weighted graph.
        // adj[u] stores {v, time}, meaning u is connected to v with given time.
        vector<pair<int , int>> adj[n]; //0 to n - 1 index
        for( auto &it : roads){
            int u1 = it[0];
            int v1 = it[1];
            int time = it[2];

            // Road is bidirectional, so add edge in both directions.
            adj[u1].push_back({v1 , time});
            adj[v1].push_back({u1, time});
        }

        // Min heap stores {distance/time, node}.
        // Distance is first so the node with smallest time comes out first.
        priority_queue<pair<int , int> , vector<pair<int , int>> , greater<pair<int, int >>>pq;

        // dist[i] stores the shortest distance from source 0 to node i.
        vector<int>dist(n , INT_MAX);

        // ways[i] stores how many shortest paths reach node i.
        vector<int>ways( n , 0);

        //store the 0th src node in the pq and dist 
        pq.push({ 0 , 0});
        dist[0] = 0;
        ways[0] = 1;//initally there is one way for 0th node 

        while( !pq.empty()){
            auto it =pq.top();
            pq.pop();

            // currtime is the shortest known time for this pq entry.
            long long currtime = it.first;
            int node = it.second;

            // If this is an old entry and a better distance already exists,
            // skip it.
            if( currtime > dist[node]) continue;

            // Try to go from current node to all its neighbours.
            for( auto & neigh: adj[node]){
                int nextnode = neigh.first;
                long long time = neigh.second;

                // Case 1:
                // A strictly smaller shortest distance is found for nextnode.
                if( currtime + time < dist[nextnode]){
                    dist[nextnode] = currtime + time;
                    pq.push({dist[nextnode] , nextnode});

                    // Since this is a better distance, previous paths to
                    // nextnode are removed. Now the number of shortest ways
                    // to nextnode becomes the number of shortest ways to node.
                    ways[nextnode] = ways[node];//previous way count is for this node also 
                    //means only one way till now 
                }else if( currtime + time == dist[nextnode]){//here distance match with the old dist
                    // Case 2:
                    // We found one more shortest route to nextnode.
                    //we find another way to go nextnode through node
                    // Add all shortest ways of node, because each of them can
                    // be extended to nextnode using this edge.
                    ways[nextnode] = (ways[nextnode] + ways[node] )% mod;
                }
            }
        }

        // ways[n - 1] contains the number of shortest paths from 0 to n - 1.
        return ways[n-1] % mod;
    }
};

int main(){
    Solution s;
    int n = 7;
    vector<vector<int>> roads = {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}};
    cout << s.countPaths(n, roads) << endl;
    return 0;
}
