
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
 };


 //usig the recursion and finding the inorder successor
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        
        //search for the node to be deleted
        if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;

            TreeNode* cur = root->right;
            while (cur->left) { //go to the leftmost node in the right subtree
                cur = cur->left;
            }
            cur->left = root->left; //connect left subtree to the leftmost node
            TreeNode* res = root->right;  //new root will be the right child
            delete root;  //delete the current node
            return res; 
        }

        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    int key = 3;

    Solution sol;
    TreeNode* newRoot = sol.deleteNode(root, key);
    //preorder traversal to print the tree after deletion
    function<void(TreeNode*)> preorder = [&](TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    };
    preorder(newRoot);


    return 0;
}