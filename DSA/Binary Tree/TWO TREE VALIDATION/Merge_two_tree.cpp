#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
? PROBLEM: Merge Two Binary Trees (LeetCode 617)
?
? You are given two binary trees root1 and root2.
? Merge them into one binary tree:
?   - If two nodes overlap (same position), sum their values.
?   - If one node is null and the other is not, the non-null node
?     becomes the merged node (no sum needed).
?   - If both are null, the merged node is null.
?
? Return the root of the merged tree. You can create a new tree or
? modify one of the existing trees in-place. This solution creates
? a brand new tree.
?
? EXAMPLE:
?   Tree1:        Tree2:        Merged:
?      1             2            3
?     / \           / \          / \
?    3   2         1   3        4   5
?   /               \   \      / \   \
?  5                 4   7    5   4   7
?
?
? INTUITION — Recursive Pre-order Traversal:
?   At every corresponding pair of nodes (one from each tree):
?     1. If both are null → stop (return null).
?     2. If one is null  → take the other node's value.
?     3. If both exist   → sum the values.
?   Then recursively merge the left children and right children.
?
?   This is a textbook tree recursion problem. Since both trees are
?   traversed simultaneously, the time is O(min(n1, n2)) — we only
?   go as deep as the smaller tree.
*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /*
     * Recursively merge two nodes (one from each tree).
     *
     * - If both are nullptr   → no node here, return nullptr.
     * - If exactly one exists  → the sum is just that node's value.
     * - If both exist          → sum = node1->val + node2->val.
     *
     * After setting the current node's value, recursively merge
     * the left and right children. If a node is nullptr, we pass
     * nullptr for its side.
     */
    TreeNode* solve(TreeNode* node1, TreeNode* node2) {
        // Base case: both positions are empty
        if (!node1 && !node2) return nullptr;

        // Compute merged value for the current position
        int sum = 0;
        if (!node1) {
            // Only node2 exists → take its value
            sum = node2->val;
        } else if (!node2) {
            // Only node1 exists → take its value
            sum = node1->val;
        } else {
            // Both exist → sum them
            sum = node1->val + node2->val;
        }

        // Create the merged node for this position
        TreeNode* root = new TreeNode(sum);

        // Recursively merge left and right subtrees.
        // If a node is null, its left/right child contributes nullptr.
        root->left  = solve(node1 ? node1->left  : nullptr,
                            node2 ? node2->left  : nullptr);
        root->right = solve(node1 ? node1->right : nullptr,
                            node2 ? node2->right : nullptr);

        return root;
    }

    /*
     * Wrapper called by LeetCode.
     * Delegates to solve() which already handles both-null,
     * so the explicit check here is redundant but kept for clarity.
     */
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return solve(root1, root2);
    }
};

int main() {
    return 0;
}
