#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
1373. Maximum Sum BST in Binary Tree
Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).

Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
*/
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
    int maxSum = 0;

    struct info
    { // class that will store the imformation of the node
        bool isBST = false;
        int maxVal;
        int minVal;
        int step;
    };

    info dfs(TreeNode *root)
    { // this is the method that will return the objectof type info
        if (root == NULL)
        {
            // NO nodes , so return 0 as the null value for the null
            return {true, INT_MIN, INT_MAX, 0};
        }

        // now go to the left and right
        info left = dfs(root->left);
        info right = dfs(root->right);

        if (left.isBST && right.isBST && left.maxVal < root->val && root->val < right.minVal)
        {
            // sum of alll node in the subtree
            int currsum = left.step + right.step + root->val;

            maxSum = max(maxSum, currsum);

            return {
                true,
                max(root->val, right.maxVal),
                min(root->val, left.minVal),
                currsum};
        }

        // nothing return then its not bst
        return {
            false,
            0,
            0,
            0};
    }

public:
    int maxSumBST(TreeNode *root)
    {
        dfs(root);
        return maxSum;
    }
};


int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(4);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(5);
    root->right->right->right = new TreeNode(6);

    Solution sol;
    int ans = sol.maxSumBST(root);
    cout << "The maximum sum of a BST in the given binary tree is: " << ans << endl;
    return 0;
}