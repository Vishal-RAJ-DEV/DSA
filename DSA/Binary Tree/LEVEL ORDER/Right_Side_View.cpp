#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// ============================================================
// PROBLEM: Binary Tree Right Side View (LeetCode 199)
//
// INTUITION:
//   Imagine standing to the RIGHT of a binary tree and looking at it.
//   You only see the RIGHTMOST node at each level — all other nodes
//   on that level are hidden behind it.
//
//   So the problem reduces to: for each level of the tree, pick the
//   LAST node (rightmost node) at that level.
//
// APPROACH (Level-Order BFS):
//   Perform a level-order traversal using a queue.
//   For each level, process all nodes at that level.
//   The LAST node we process at each level is the rightmost node
//   (since we push left→right, the last popped is rightmost).
//   Record its value.
//
//   Since we push children left-first and then right, within a level:
//     queue order = [leftmost ... rightmost]
//   The last node we pop at that level is the rightmost → that's our answer.
// ============================================================

// ── Implementation 1: size counter decrements to 0 ──
// Uses the fact that after popping, `size` holds how many NODES REMAIN
// in this level. When size == 0, the current node is the LAST one.
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {

        if(root == NULL)                     // Empty tree → nothing to see
            return {};

        vector<int> ans;                     // Stores the right-side view
        queue<TreeNode*> q;                  // Queue for level-order BFS
        q.push(root);                        // Start from the root

        while(!q.empty()) {

            int size = q.size();             // Number of nodes at the current level

            while(size--) {                  // Process all nodes at this level

                TreeNode* node = q.front();
                q.pop();

                if(size == 0)                // After popping, if size == 0, this was the
                    ans.push_back(node->val);// LAST node at this level → the rightmost one

                if(node->left)               // Enqueue left child for the next level
                    q.push(node->left);

                if(node->right)              // Enqueue right child (right comes after left)
                    q.push(node->right);
            }
        }

        return ans;
    }
};

// ── Implementation 2: for-loop with index counter ──
// Same logic, just uses an index i from 0 to n-1.
// The last index (i == n-1) corresponds to the rightmost node.
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {

        if(!root) return {};

        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {

            int n = q.size();                // Nodes in the current level

            for(int i = 0; i < n; i++) {     // Iterate over all nodes of this level

                TreeNode* node = q.front();
                q.pop();

                if(i == n - 1)               // Last index → rightmost node in this level
                    ans.push_back(node->val);

                if(node->left)               // Push children for next level
                    q.push(node->left);

                if(node->right)              // Right child pushed after left
                    q.push(node->right);
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}
