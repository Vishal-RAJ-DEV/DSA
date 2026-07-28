#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Recover Binary Search Tree
Solved
Companies
You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.*/
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
    TreeNode *first;
    TreeNode *middle;
    TreeNode *last;
    TreeNode *prev;

public:
    void inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;
        // go left of the tree
        inorder(root->left);
        if (prev != nullptr && prev->val > root->val)
        {

            if (first == nullptr)
            {                  // first violation
                first = prev;  // violeted node
                middle = root; // node after violted
            }
            else
            {
                last = root; // lase violation
            }
        }
        prev = root;          // store for traverse previous value
        inorder(root->right); // go right
    }
    void recoverTree(TreeNode *root)
    {
        first = middle = last = nullptr;
        // instailize the prev so it can store the prevoius value
        prev = new TreeNode(INT_MIN);
        inorder(root);
        if (first && last)
            swap(first->val, last->val);
        else if (first && middle)
            swap(first->val, middle->val);
    }
};

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->right = new TreeNode(2);

    Solution sol;
    sol.recoverTree(root);

    // Inorder traversal to verify the tree is recovered
    function<void(TreeNode *)> inorderPrint = [&](TreeNode *node) {
        if (node == nullptr)
            return;
        inorderPrint(node->left);
        cout << node->val << " ";
        inorderPrint(node->right);
    };

    cout << "Inorder traversal of the recovered BST: ";
    inorderPrint(root);
    cout << endl;

    return 0;
}