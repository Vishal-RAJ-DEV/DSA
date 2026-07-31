#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
Problem: LeetCode 863 - All Nodes Distance K in Binary Tree
Given a binary tree, a target node, and an integer k.
Find all nodes that are exactly k distance away from the target node.

Intuition:
In a binary tree, you can only move downward (parent -> child).
But to reach nodes at distance K, we may need to go UP from the target
(to its parent), then down another branch, or sideways via a sibling.
Essentially, we need to treat the tree as an undirected graph.

Approach:
1. Build a parent pointer map — This gives us the "upward" edge
   that the tree doesn't natively provide, effectively converting
   the tree into an undirected graph.
2. BFS from the target node — Since distance in an unweighted graph
   is just the number of edges traversed, BFS level-order gives us
   all nodes at exactly K hops away.

Step-by-step working:
- mapParentNodes() runs a level-order traversal and records each
  node's parent in an unordered_map. Now each node can go:
  left, right (children), or parentMap[node] (parent).
- bfsFromTarget() starts BFS from target, expanding to left child,
  right child, and parent at each step. A visited set prevents
  cycles (going back to where we came from).
- We track currentLevel. When currentLevel reaches k, all nodes in
  the BFS queue are exactly k distance away from target. We collect
  their values and return them.

Time Complexity: O(n) — each node visited once in parent mapping + once in BFS
Space Complexity: O(n) — parent map, visited set, and queue
*/



class Solution {
public:
    // Main function to find all nodes at distance K from the target node
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root) return {};

        // Step 1: Build parent mapping for each node using BFS
        unordered_map<TreeNode*, TreeNode*> parentMap;
        mapParentNodes(root, parentMap);

        // Step 2: Perform BFS from target to find nodes at distance K
        return bfsFromTarget(target, parentMap, k);
    }

private:
    // Builds a mapping from each node to its parent to simulate undirected graph
    void mapParentNodes(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parentMap) {
        queue<TreeNode*> q;
        q.push(root);

        // Level-order traversal to map parent of each node
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // If left child exists, record its parent and add it to queue
            if (node->left) {
                parentMap[node->left] = node;
                q.push(node->left);
            }

            // If right child exists, record its parent and add it to queue
            if (node->right) {
                parentMap[node->right] = node;
                q.push(node->right);
            }
        }
    }

    // BFS starting from target node to find all nodes exactly K distance away
    vector<int> bfsFromTarget(TreeNode* target, unordered_map<TreeNode*, TreeNode*>& parentMap, int k) {
        queue<TreeNode*> q;
        unordered_set<TreeNode*> visited; 

        // Start BFS from the target node
        q.push(target);
        visited.insert(target);

        int currentLevel = 0;

        // Perform level-order BFS until we reach level K
        while (!q.empty()) {
            int size = q.size();

            // If we've reached level k, break out and collect the result
            if (currentLevel++ == k) break;

            // Explore all nodes at current level
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                // Explore left child if not already visited
                if (node->left && visited.find(node->left) == visited.end()) {
                    visited.insert(node->left);
                    q.push(node->left);
                }

                // Explore right child if not already visited
                if (node->right && visited.find(node->right) == visited.end()) {
                    visited.insert(node->right);
                    q.push(node->right);
                }

                // Explore parent from parentMap if not already visited
                // Only proceed if the current node has a parent in the map
                // This avoids inserting a null parent for the root node (which has no parent)
                // and prevents accidental segfaults from accessing nullptr
                if (parentMap.count(node) && visited.find(parentMap[node]) == visited.end()) {
                    visited.insert(parentMap[node]);
                    q.push(parentMap[node]);
                }
            }
        }

        // All nodes in queue are now at distance K from the target
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()->val);
            q.pop();
        }

        return result;
    }
};

// --- Driver Code ---
int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

     // Node with value 5
    TreeNode* target = root->left;
    int k = 2;

    Solution sol;
    vector<int> result = sol.distanceK(root, target, k);

    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
