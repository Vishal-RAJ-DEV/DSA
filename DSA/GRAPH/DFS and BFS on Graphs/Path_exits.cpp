#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        unordered_map<int, vector<int>> graph;
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        queue<int> queue;
        unordered_set<int> visited;
        
        queue.push(source);
        visited.insert(source);
        
        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();
            if (node == destination) {
                return true;
            }
            for (int neighbor : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        
        return false;
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        unordered_map<int, vector<int>> graph;
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        unordered_set<int> visited;
        return dfs(source, destination, graph, visited);
    }
    
    bool dfs(int node, int destination, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
        if (node == destination) {
            return true;
        }
        visited.insert(node);
        for (int neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                if (dfs(neighbor, destination, graph, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};
int main(){
    return 0;
}

/*
================================================================
WHY unordered_set INSTEAD OF A VISITED ARRAY?

The visited tracker uses unordered_set<int> rather than a
vector<bool> visited(n, false). Here is the reasoning:

1. NODE LABELS MAY NOT BE CONTIGUOUS FROM 0 TO n-1
   The adjacency list is stored as unordered_map<int, vector<int>>,
   meaning the graph keys can be ARBITRARY integers (e.g. 100, 200,
   300). A vector<bool> of size n would fail if a node label
   exceeds n-1, or is negative, or is non-contiguous.
   An unordered_set handles any integer label correctly.

2. MEMORY EFFICIENCY FOR SPARSE TRAVERSAL
   If n is large (e.g. 10^6) but BFS/DFS only visits a few nodes,
   vector<bool> still allocates O(n) memory upfront.
   unordered_set only stores the nodes actually visited — O(V_visited).

3. SAME STYLE AS THE ADJACENCY LIST
   Since the graph uses unordered_map for flexibility, using
   unordered_set for visited maintains consistency — both are
   hash-based structures that don't assume contiguous indexing.

4. NO PERFORMANCE PENALTY
   insert() and find() are O(1) average, same as array lookup.

WHEN WOULD vector<bool> BE PREFERRED INSTEAD?
   If the problem guarantees nodes are labeled 0 to n-1 AND the
   graph is stored as vector<vector<int>> adj(n), then vector<bool>
   visited(n) is simpler and cache-friendlier. But the code here
   is written to be more general, so unordered_set is the right
   choice for consistency with unordered_map<int, vector<int>>.

================================================================
*/

