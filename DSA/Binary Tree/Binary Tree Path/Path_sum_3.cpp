#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// TreeNode structure for the binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};


// Approach 1: Prefix Sum (Accumulative) Method
// Logic:
//   - 'solve' counts paths starting from the current node that sum to targetSum
//     by accumulating node values along the path and checking if sum == targetSum
//   - 'pathSum' tries EVERY node as a potential starting point via recursion,
//     so that all downward paths (any start → any end) are considered
//   - For each node, we count paths that begin at that node (via solve)
//     and add paths that don't include this node (via pathSum on left & right)
class PrefixSumSolution {
public:

    int solve(TreeNode* root, int targetSum, long long sum) {
        if (root == nullptr)
            return 0;

        sum += root->val;

        int ans = 0;

        if (sum == targetSum)
            ans++;

        ans += solve(root->left, targetSum, sum);
        ans += solve(root->right, targetSum, sum);

        return ans;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return 0;

        // Count paths starting at root + paths in left subtree + paths in right subtree
        return solve(root, targetSum, 0)
             + pathSum(root->left, targetSum)
             + pathSum(root->right, targetSum);
    }
};

// Approach 2: Remaining Sum (Subtractive) Method
// Logic:
//   - 'dfs' counts paths starting from the current node that sum to targetSum
//     by subtracting node values from the remaining target and checking if
//     root->val == remain (i.e., remaining target is exactly met at this node)
//   - 'pathSum' tries EVERY node as a potential starting point (same outer
//     recursion as Approach 1)
//   - Both approaches are equivalent; the difference is whether we "accumulate
//     towards" (sum going up) or "subtract from" (remain going down) the target
class RemainingSumSolution {
public:

    int dfs(TreeNode* root, long long remain) {
        if (!root)
            return 0;

        int ans = 0;

        if (root->val == remain)
            ans++;

        ans += dfs(root->left, remain - root->val);
        ans += dfs(root->right, remain - root->val);

        return ans;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (!root)
            return 0;

        return dfs(root, targetSum)
             + pathSum(root->left, targetSum)
             + pathSum(root->right, targetSum);
    }
};

int main(){
    return 0;
}
