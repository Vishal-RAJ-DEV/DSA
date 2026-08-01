/*
Problem: LeetCode 1382 - Balance a Binary Search Tree
Given the root of a BST, return a balanced BST with the same
node values.

Balanced means: for every node, the height difference between
its left and right subtrees is at most 1.

Approach: Inorder → Sorted Array → Rebuild Balanced BST

Intuition:
1. Inorder traversal of a BST visits nodes in ASCENDING order.
   So it gives us the sorted sequence of ALL nodes.
2. In a balanced BST built from a sorted array, the middle element
   must be the root (half the elements go left, half go right).
3. Recursively repeat: middle of left half → left subtree root,
   middle of right half → right subtree root.

This guarantees every node splits its range in half, giving a
perfectly balanced tree of height O(log n).

Algorithm:
1. inorder(root) → collect all nodes in sorted order.
2. sortedArrayToBST(low, high) → recursively build tree:
   - Base case: low > high → empty subtree → return nullptr
   - mid = (low + high) / 2
   - root = sortedArray[mid]
   - root->left  = build(low, mid - 1)
   - root->right = build(mid + 1, high)

Time Complexity : O(n) — one inorder pass + one build pass,
                  each node visited twice
Space Complexity : O(n) — sorted array + recursion stack (O(log n) height)
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
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
    vector<TreeNode*> sortedArray;  // stores nodes in sorted order (by value)

    // Step 1: Inorder traversal — since it's a BST, this visits
    // nodes in ascending order of value.
    // Left → Node → Right
    void inorder(TreeNode* root) {
        if (root == nullptr) return;

        inorder(root->left);          // first all smaller values
        sortedArray.push_back(root);  // then the current node
        inorder(root->right);         // then all larger values
    }

    // Step 2: Recursively build a balanced BST from the sorted array.
    // Works exactly like binary search — always picking the middle
    // of the current range as the subtree root.
    TreeNode* sortedArrayToBST(int low, int high) {
        // Base case: empty range → no node exists here
        if (low > high) return nullptr;

        // Pick the middle element as the root of this subtree.
        // (low + high) / 2 avoided in favor of this form to
        // prevent integer overflow, and it picks the same node
        // for both even and odd ranges consistently.
        int mid = low + (high - low) / 2;
        TreeNode* root = sortedArray[mid];

        // Left half [low, mid-1] → left subtree (all smaller values)
        root->left = sortedArrayToBST(low, mid - 1);

        // Right half [mid+1, high] → right subtree (all larger values)
        root->right = sortedArrayToBST(mid + 1, high);

        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        // Step 1: collect nodes in sorted order
        inorder(root);

        // Step 2: rebuild balanced BST from the sorted array
        return sortedArrayToBST(0, sortedArray.size() - 1);
    }
};

/* Visual example:
Original (unbalanced):        Balanced result:
        10                           8
       /  \                         / \
      5   15                      5   15
     / \                           \    \
    3   7                          7    20
         \
          8                          (height = 2, balanced)

Inorder gives sorted order of nodes: 3, 5, 7, 8, 10, 15, 20
- mid = index 3 → root = 8
- left half [3, 5, 7] → mid = 5 → 5->left = 3, 5->right = 7
- right half [10, 15, 20] → mid = 15 → 15->left = 10, 15->right = 20
*/

int main() {
    return 0;
}
