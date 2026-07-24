#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Leetcode 112 - Path Sum):
Given the root of a binary tree and an integer targetSum,
return true if there exists a root-to-leaf path where the sum
of all node values along the path equals targetSum.

EXAMPLE:
        5
       / \
      4   8
     /   / \
    11  13  4
   /  \      \
  7    2      1

targetSum = 22
Path: 5 -> 4 -> 11 -> 2 sums to 22 -> return true.

ALGORITHM (DFS with subtraction):

Instead of accumulating a running sum and comparing at leaves,
we SUBTRACT the current node's value from targetSum as we go down.
At a leaf, we check if the remaining targetSum equals the leaf's value
(i.e., targetSum - leaf->val == 0).

This avoids needing an extra accumulator variable.

At each node:
1. If root is null -> no path possible, return false.
2. If root is a LEAF -> return (targetSum - root->val == 0).
3. Subtract root->val from targetSum.
4. Recurse on left OR right — if either returns true, we return true.

LOGIC:
- We DFS down each root-to-leaf path.
- targetSum is decremented by each node's value as we descend.
- At the leaf, if targetSum becomes 0, we found the path.
- Since we return true as soon as ANY path matches, we don't
  need to explore all paths.
- Time: O(n) — worst case we visit all nodes.
- Space: O(h) where h is tree height (recursion stack).
*/

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;

        // Leaf check: does remaining sum match leaf value?
        if (!root->left && !root->right) {
            return targetSum - root->val == 0;
        }

        // Subtract current node and recurse
        targetSum -= root->val;

        return hasPathSum(root->left, targetSum) ||
               hasPathSum(root->right, targetSum);
    }
};

int main(){
    return 0;
}