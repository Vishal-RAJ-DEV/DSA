#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges,
                          vector<double>& succProb,
                          int start_node, int end_node) {

        // Adjacency list
        vector<vector<pair<int, double>>> adj(n);

        for (int i = 0; i < edges.size(); i++) {

            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];

            // Undirected graph
            adj[u].push_back({v, prob});
            adj[v].push_back({u, prob});
        }

        // Maximum probability found for each node
        vector<double> prob(n, 0.0);

        // Start node has probability 1
        prob[start_node] = 1.0;

        // Max heap: {probability, node}
        priority_queue<pair<double, int>> pq; //because in this question we have to find the maximum probability so we will use max heap 

        pq.push({1.0, start_node});

        while (!pq.empty()) {

            double currProb = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            // If we reached the destination
            if (u == end_node) {
                return currProb;
            }

            // Explore neighbours
            for (auto& edge : adj[u]) {

                int v = edge.first;
                double edgeProb = edge.second;

                // Probability of reaching v through u
                double newProb = currProb * edgeProb;

                // Found a better probability
                if (newProb > prob[v]) {

                    prob[v] = newProb;

                    pq.push({newProb, v});
                }
            }
        }

        // No path exists
        return 0.0;
    }
};



int main(){
    return 0;
}