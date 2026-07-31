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
    vector<TreeNode*>sortedArray;
    void inorder(TreeNode* root){
        if( root == nullptr){
            return;
        }

        inorder(root->left);
        sortedArray.push_back(root);
        inorder(root->right);
    }

    TreeNode * sortedArrayTO_bst(int low , int high){
        if( low > high)return nullptr;

        int mid = low + (high - low) / 2;
        TreeNode * root = sortedArray[mid];
        root->left = sortedArrayTO_bst(low , mid - 1);
        root->right = sortedArrayTO_bst(mid + 1 , high);

        return root;
    }
    TreeNode* balanceBST(TreeNode* root) {
        inorder(root);

        return sortedArrayTO_bst(0 , sortedArray.size() - 1);
    }
};


int main(){
    return 0;
}