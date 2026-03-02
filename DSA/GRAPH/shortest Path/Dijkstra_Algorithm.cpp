#include <bits/stdc++.h>
using namespace std;


//this is using the set data structure to store the nodes in the order of their distance from the source node. The set will automatically sort the nodes based on their distance, allowing us to efficiently retrieve the node with the smallest distance at each step of the algorithm. The algorithm iteratively updates the distances to adjacent nodes and continues until all reachable nodes have been processed, ultimately returning a list of shortest distances from the source node to all other nodes in the graph.
class Solution
{
    public:
        // Function to find the shortest distance of all the vertices
        // from the source vertex S.
        vector<int> dijkstraUsingSet(int V, vector<vector<int>> adj[], int S)
        {
            // Create a set ds for storing the nodes as a pair {dist,node}
            // where dist is the distance from source to the node.
            // set stores the nodes in ascending order of the distances.
            set<pair<int, int>> st; 

            // Initialising dist list with a large number to
            // indicate the nodes are unvisited initially.
            // This list contains distance from source to the nodes.
            vector<int> dist(V, 1e9); 

            // Insert the source node with a distance of 0.
            st.insert({0, S}); 

            // Source initialised with dist = 0
            dist[S] = 0;

            // Traverse the graph until the set is empty
            while(!st.empty()) {
                // Extract the node with the minimum distance
                auto it = *(st.begin()); 
                int node = it.second; 
                int dis = it.first; 
                st.erase(it); 

                // Check for all adjacent nodes of the extracted node
                for(auto it : adj[node]) {
                    int adjNode = it[0];  // Adjacent node
                    int edgW = it[1];     // Weight of the edge
                    
                    // If the new distance is smaller, update it
                    if(dis + edgW < dist[adjNode]) {
                        // Erase the previous entry of the adjacent node
                        // if it was visited previously with a larger cost.
                        if(dist[adjNode] != 1e9) 
                            st.erase({dist[adjNode], adjNode}); 

                        // Update the distance for the adjacent node
                        dist[adjNode] = dis + edgW; 

                        // Insert the adjacent node with the updated distance into the set
                        st.insert({dist[adjNode], adjNode}); 
                    }
                }
            }

            // Return the list containing shortest distances
            // from source to all the nodes.
            return dist; 
        }
};

// Optimal approach : using priority queue (min heap)
//time complexity : O(E log V) and space complexity : O(V) where E is the number of edges and V is the number of vertices in the graph
class Solution1 {
public:
    // Function to implement Dijkstra's Algorithm
    vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
        // Distance array initialized to large value
        vector<int> dist(V, 1e9);

        // Min-heap storing {distance, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, 
                       greater<pair<int,int>>> pq;

        // Distance to source is 0
        dist[src] = 0;

        // Push source into heap
        pq.push({0, src});

        // Process nodes until heap is empty
        while (!pq.empty()) {
            // Extract node with minimum distance
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip if this distance is outdated
            if (d > dist[node]) continue;

            // Traverse all adjacent neighbors
            for (auto it : adj[node]) {
                int next = it.first;
                int wt = it.second;

                // Relaxation check
                if (dist[node] + wt < dist[next]) {
                    // Update distance
                    dist[next] = dist[node] + wt;

                    // Push updated distance into heap
                    pq.push({dist[next], next});
                }
            }
        }
        return dist;
    }
};


int main()
{
    // Driver code.
    int V = 3, E = 3, S = 2;  // Number of vertices, edges, and source vertex
    vector<vector<pair<int,int>>> adj(V); // Adjacency list representation of the graph

    // Example graph with edges and weights
    vector<int> v1{1, 1}, v2{2, 6}, v3{2, 3}, v4{0, 1}, v5{1, 3}, v6{0, 6};
    adj[0].push_back({v1[0], v1[1]});
    adj[0].push_back({v2[0], v2[1]});
    adj[1].push_back({v3[0], v3[1]});
    adj[1].push_back({v4[0], v4[1]});
    adj[2].push_back({v5[0], v5[1]});
    adj[2].push_back({v6[0], v6[1]});

    Solution1 obj;
    // Call dijkstra function and store the result
    vector<int> res = obj.dijkstra(V, adj, S);

    // Output the shortest distance from source to all nodes
    for (int i = 0; i < V; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}
