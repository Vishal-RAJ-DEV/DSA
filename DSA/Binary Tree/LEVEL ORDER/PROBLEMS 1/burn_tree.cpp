#include <bits/stdc++.h>
using namespace std;

// Definition of the binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    //time complexity : O(n)
    //space complexity : O(n)
    // Function to calculate minimum time to burn the entire tree from the target node
    int minTime(TreeNode* root, int target) {
        // Create an undirected graph using adjacency list
        unordered_map<int, vector<int>> graph;
        buildGraph(root, nullptr, graph);

        // Use a set to track visited (burned) nodes
        unordered_set<int> visited;

        // Use queue for BFS starting from the target node
        queue<int> q;
        q.push(target);
        visited.insert(target);

        // Track time taken to burn the tree
        int time = 0;

        // Perform level-order BFS to simulate the spread of fire
        while (!q.empty()) {
            int size = q.size();
            bool burned = false;

            // Process each node at the current level
            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();

                // Traverse all adjacent (connected) nodes
                for (int neighbor : graph[node]) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                        burned = true;
                    }
                }
            }

            // If fire spread to new nodes, increment time
            if (burned) time++;
        }

        // Return total time taken to burn the tree
        return time;
    }

private:
    //time complexity : O(n)
    //space complexity : O(n)
    //convert the tree intio an undirected graph 
    void buildGraph(TreeNode* node, TreeNode* parent, unordered_map<int, vector<int>>& graph) {
        // Base case: if node is null, return
        if (!node) return;

        // If parent exists, connect parent and node bidirectionally
        if (parent) {
            graph[node->val].push_back(parent->val);
            graph[parent->val].push_back(node->val);
        }

        // Recursively connect left and right children
        buildGraph(node->left, node, graph);
        buildGraph(node->right, node, graph);
    }
};

// Driver code
int main() {
    // Create the binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->left->right = new TreeNode(7);

    // Create solution object
    Solution sol;

    // Set target node to burn from
    int target = 1;

    // Print the minimum time to burn the tree
    cout << "Minimum time to burn the tree: " << sol.minTime(root, target) << endl;

    return 0;
}
