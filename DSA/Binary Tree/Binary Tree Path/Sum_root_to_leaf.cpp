#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Leetcode 129 - Sum Root to Leaf Numbers):
Given a binary tree where each node contains a single digit (0-9),
each root-to-leaf path represents a number (digits concatenated).

Find the TOTAL SUM of all root-to-leaf numbers.

EXAMPLE:
    1
   / \
  2   3

Path 1→2 = number 12
Path 1→3 = number 13
Sum = 12 + 13 = 25

=========================================================
TWO WAYS TO WRITE THE SOLUTION:
=========================================================

Both use DFS. The key operation at each node:
  currentSum = currentSum * 10 + root->val

This builds the number by shifting digits left and adding the new digit.

APPROACH 1 — Using a reference variable (ans):
  1. Build currentSum = s * 10 + val.
  2. At leaf: add currentSum to ans (passed by reference).
  3. Recurse left and right.
  Pro: Explicit accumulation, easy to read.
  Con: Needs an extra reference parameter.

APPROACH 2 — Pure recursion (return sum):
  1. Build currentSum = currentSum * 10 + val.
  2. At leaf: return currentSum.
  3. Otherwise: return dfs(left) + dfs(right).
  Pro: Clean, no reference variables, pure functional style.
  Con: Slightly less obvious for beginners.
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
// APPROACH 1: Using a reference variable
// =========================================
class Solution1 {
public:
    void solve(TreeNode* root, int s, int& ans) {
        if (root == nullptr) return;

        s = s * 10 + root->val;

        // Leaf: add this path's number to total
        if (!root->left && !root->right) {
            ans += s;
            return;
        }

        solve(root->left, s, ans);
        solve(root->right, s, ans);
    }

    int sumNumbers(TreeNode* root) {
        int s = 0;
        int ans = 0;
        solve(root, s, ans);
        return ans;
    }
};

// =========================================
// APPROACH 2: Pure recursion (return sum)
// =========================================
class Solution2 {
public:
    int dfs(TreeNode* root, int currentSum) {
        if (!root) return 0;

        currentSum = currentSum * 10 + root->val;

        // Leaf: return this path's number
        if (!root->left && !root->right) {
            return currentSum;
        }

        // Sum of left and right subtree paths
        return dfs(root->left, currentSum) + dfs(root->right, currentSum);
    }

    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
};

int main(){
    return 0;
}