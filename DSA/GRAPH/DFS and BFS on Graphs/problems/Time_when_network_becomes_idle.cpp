#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM: Time When the Network Becomes Idle
 *
 * We have n servers (0 to n-1) connected in an undirected graph.
 * Server 0 is the MASTER server. Every other server i periodically
 * sends a message to server 0, and server 0 immediately replies.
 *
 * RULES:
 * 1. Server i sends its FIRST message at time = patience[i].
 * 2. If no reply is received, server i RESENDS every patience[i] seconds
 *    (at times: patience[i], 2*patience[i], 3*patience[i], ...).
 * 3. Once server i receives ANY reply, it STOPS sending.
 * 4. Each edge takes 1 second to traverse (so round trip = 2 * distance).
 *
 * GOAL: Find the earliest time when ALL servers have stopped sending
 *       (i.e., every server has received its reply) — this is when
 *       the network "becomes idle".
 *
 * KEY FORMULA for server i:
 *   roundTrip     = 2 * dist[i]           (time for one round trip)
 *   lastSend      = floor((roundTrip-1) / patience[i]) * patience[i]
 *                   (largest multiple of patience[i] that is < roundTrip)
 *   lastReply     = lastSend + roundTrip   (arrival time of last reply)
 *   idle time     = max over all servers of (lastReply + 1)
 *
 * WHY +1? Because the network is idle AFTER the last reply arrives,
 * i.e., at the next second after the last reply.
 *
 * EXAMPLE:
 *   Server i with patience=2, dist=3 (roundTrip=6)
 *   Sends at times: 2, 4, 6, 8, ...
 *   Reply for msg at t=2 arrives at t=8  (after round trip)
 *   But server stops when FIRST reply arrives:
 *     msg sent at t=2 arrives at t=0+6=6, reply arrives at t=2+6=8
 *     Actually: msg sent at t=2 arrives at server 0 at t=2+3=5
 *     Reply sent at t=5 arrives back at t=5+3=8
 *     So server stops at t=8. lastSend=2, lastReply=8.
 *     idle contribution = 8+1 = 9
 */

class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges,
                           vector<int>& patience) {

        int n = patience.size();

        // Build undirected adjacency list from edges
        vector<vector<int>> adj(n);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // BFS from server 0 to find shortest distance to every server.
        // Distance = minimum number of edges from server 0.
        // Since each edge takes 1 second, dist[i] = travel time one-way.
        vector<int> dist(n, -1);
        queue<int> q;

        dist[0] = 0;   // Server 0 is at distance 0 from itself
        q.push(0);

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {

                // Unvisited neighbor — this is its shortest distance
                if (dist[neighbor] == -1) {

                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        // For each server i (1 to n-1), compute when its last reply arrives.
        // The answer is the maximum of all those times + 1.
        int ans = 0;

        for (int i = 1; i < n; i++) {

            // Round trip time: go to server 0 and come back
            int roundTrip = 2 * dist[i];

            // Server i sends messages at times: patience[i], 2*patience[i], ...
            // It stops sending once a reply arrives.
            // The LAST message it sends before a reply arrives is at time:
            //   lastSend = largest multiple of patience[i] that is < roundTrip
            //   = floor((roundTrip - 1) / patience[i]) * patience[i]
            //
            // WHY < roundTrip? Because the reply for a message sent at time t
            // arrives at t + roundTrip. For the server to still be "waiting"
            // when it sends, t + roundTrip must not have happened yet.
            int lastSend =
                ((roundTrip - 1) / patience[i]) * patience[i];

            // The reply to this last message arrives at: lastSend + roundTrip
            int lastReply = lastSend + roundTrip;

            // Network is idle AFTER this reply arrives, so +1 second
            ans = max(ans, lastReply + 1);
        }

        return ans;
    }
};


int main(){
    return 0;
}