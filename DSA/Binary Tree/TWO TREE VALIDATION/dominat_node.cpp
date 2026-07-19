/*
QUESTION: Count Dominant Nodes in a Binary Tree

A node is "dominant" if its value is ≥ every other node's value in its
entire subtree (i.e., it is the maximum value in its own subtree).

Count how many nodes in the tree are dominant.

Example:
        5
       / \
      3   7         → dominant nodes: 7 (subtree max=7), 3 (subtree max=3),
     / \                      5 is NOT dominant because 7 > 5
    1   9                    9 (subtree max=9), 1 (subtree max=1)
                              Output: 4
                              (only node 5 is not dominant since 7 > 5)

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ──────────────────────────────────────────────────────────────
// TREE NODE DEFINITION
// ──────────────────────────────────────────────────────────────
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// ──────────────────────────────────────────────────────────────
// SOLUTION
//
// INTUITION:
//   A node is dominant if its value is the maximum in the subtree
//   rooted at itself. We can compute this with a post-order DFS:
//
//     - Recursively get the maximum value from left and right subtrees.
//     - The subtree max = max(current node, left max, right max).
//     - If current node's value equals this subtree max → it dominates.
//
//   Why post-order?
//     We need both child subtree max values before we can determine
//     the max for the current subtree — classic bottom-up DP on a tree.
//
//   Edge: null children return INT_MIN so they never affect the max.
//
// ALGORITHM:
//   1. ans = 0
//   2. dfs(root):
//        if root is null → return INT_MIN
//        leftMax  = dfs(root.left)
//        rightMax = dfs(root.right)
//        subMax   = max(root.val, leftMax, rightMax)
//        if root.val == subMax → ans++
//        return subMax
//   3. Return ans
//
// TIME  : O(N) — visits every node once
// SPACE : O(H) — recursion stack = height of tree
// ──────────────────────────────────────────────────────────────

class Solution {
public:
    int ans;    // global counter (reset per call)

    // Returns the maximum value in the subtree rooted at root.
    // Also increments ans if root itself is the maximum.
    int dfs(TreeNode* root) {
        if (!root)
            return INT_MIN;     // neutral value for max comparison

        int leftMax  = dfs(root->left);
        int rightMax = dfs(root->right);

        // Maximum value in this entire subtree
        int subMax = max({root->val, leftMax, rightMax});

        if (root->val == subMax)
            ans++;              // this node is dominant

        return subMax;
    }

    int countDominantNodes(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};

/*
DRY RUN: Tree from the example above

        5
       / \
      3   7
     / \
    1   9

  dfs(1):  left=INT_MIN right=INT_MIN  subMax=1  1==1 → ans=1   return 1
  dfs(9):  left=INT_MIN right=INT_MIN  subMax=9  9==9 → ans=2   return 9
  dfs(3):  left=1 right=9             subMax=9  3!=9 → NOT     return 9
  dfs(7):  left=INT_MIN right=INT_MIN subMax=7  7==7 → ans=3   return 7
  dfs(5):  left=9 right=7             subMax=9  5!=9 → NOT     return 9

  ans = 3   (nodes 1, 9, 7 are dominant)
  Node 3 and 5 are NOT dominant because a descendant (9) has larger value.
*/

int main() {
    // Build the example tree:
    //         5
    //        / \
    //       3   7
    //      / \
    //     1   9
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n9 = new TreeNode(9);
    TreeNode* n3 = new TreeNode(3, n1, n9);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n5 = new TreeNode(5, n3, n7);

    Solution sol;
    cout << "Dominant nodes: " << sol.countDominantNodes(n5)
         << " (expected: 3)\n";

    // Edge case: empty tree
    cout << "Empty tree: " << sol.countDominantNodes(nullptr)
         << " (expected: 0)\n";

    // Edge case: single node
    TreeNode* single = new TreeNode(42);
    cout << "Single node: " << sol.countDominantNodes(single)
         << " (expected: 1)\n";

    // Cleanup (omitted for brevity — not required for competitive coding)

    return 0;
}
