#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Leetcode 113 - Path Sum II):
Given the root of a binary tree and an integer targetSum,
return ALL root-to-leaf paths where the sum of node values
equals targetSum.

EXAMPLE:
        5
       / \
      4   8
     /   / \
    11  13  4
   /  \    / \
  7    2  5   1

targetSum = 22
Output: [[5,4,11,2], [5,8,4,5]]

=========================================================
TWO WAYS TO WRITE THE SOLUTION:
=========================================================

Both use DFS + Backtracking. The difference is HOW we track the sum.

APPROACH 1 — Using a running SUM variable:
  1. Add root->val to sum.
  2. Push root->val to path.
  3. At leaf: if sum == targetSum, record path.
  4. Recurse left and right.
  5. Backtrack: subtract root->val from sum, pop from path.

  Pro: Explicit — you see the sum accumulating and reverting.
  Con: Needs an extra class-level 'sum' variable.

APPROACH 2 — Using target SUBTRACTION (cleaner):
  1. Push root->val to path.
  2. Subtract root->val from target (target -= val).
  3. At leaf: if target == 0, record path.
  4. Recurse left and right with updated target.
  5. Backtrack: pop from path.

  Pro: No extra sum variable — target itself tracks what's left.
  Con: Slightly less obvious to beginners.

Both are functionally identical. Approach 2 is preferred
because it's cleaner and is the standard Leetcode style.
*/

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x){
        val = x;
        left = right = nullptr;
    }
};

// =========================================
// APPROACH 1: Using a running SUM variable
// =========================================
class Solution1 {
public:
    vector<vector<int>> ans;
    vector<int> path;
    int sum = 0;

    void solve(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return;

        sum += root->val;
        path.push_back(root->val);

        // At leaf: check if running sum matches target
        if (!root->left && !root->right) {
            if (sum == targetSum)
                ans.push_back(path);
        }

        solve(root->left, targetSum);
        solve(root->right, targetSum);

        // Backtrack
        sum -= root->val;
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return {};

        solve(root, targetSum);
        return ans;
    }
};

// =========================================
// APPROACH 2: Using target SUBTRACTION
// =========================================
class Solution2 {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void dfs(TreeNode* root, int target) {
        if (!root) return;

        path.push_back(root->val);
        target -= root->val;  // reduce target instead of adding sum

        // At leaf: check if target reached exactly 0
        if (!root->left && !root->right && target == 0) {
            ans.push_back(path);
        }

        dfs(root->left, target);
        dfs(root->right, target);

        // Backtrack (only path needs popping; target is passed by value)
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum);
        return ans;
    }
};

int main(){
    return 0;
}