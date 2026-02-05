
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

class Solution {
public:
    bool isValid(TreeNode* root , long long low , long long high ){
        if( root == nullptr) return true;
        //here opposite condition( ANY ONE OF THEM ) true then return false 
        if( root->val < low || root->val > high ) return false ;

        //change the range 
        //for left :- maxvalue = current root 
        //for right :- minvalue = current root
        return isValid( root->left , low , root->val) && 
               isValid( root->right , root->val , high);
    }
    bool isValidBST(TreeNode* root) {
        return isValid( root , LLONG_MIN , LLONG_MAX); //Initally range for the root node ;

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
    if(sol.isValidBST(root)){
        cout<<"The tree is a valid binary search tree"<<endl;
    }
    else{
        cout<<"The tree is not a valid binary search tree"<<endl;
    }



    return 0;
}