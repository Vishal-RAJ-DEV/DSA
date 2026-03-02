#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

class Solution {
public:
    TreeNode* build( vector<int>& preorder , int& idx , long long bound){
        if( idx == preorder.size() || preorder[idx] > bound)return nullptr;

        TreeNode* root = new TreeNode( preorder[idx++]); //increse the value of the idx 
        
        root->left = build( preorder , idx , root->val ); //pass the value of the root as the bound for the left subtree beacuse the value of the left subtree should be less than the value of the root
        root->right= build(preorder , idx , bound); //pass the value of the bound for the right subtree beacuse the value of the right subtree should be less than the value of the bound which is the value of the root in this case 
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int idx = 0 ;
        long long bound  = INT_MAX;
        return build( preorder , idx , bound) ;

    }
};

int main(){
    vector<int> preorder = {8,5,1,7,10,12};
    Solution sol;
    TreeNode* root = sol.bstFromPreorder(preorder);
    //preorder traversal to print the tree after construction
    function<void(TreeNode*)> preorder_traversal = [&](TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preorder_traversal(node->left);
        preorder_traversal(node->right);
    };

    preorder_traversal(root);

    return 0;
}
