#include <iostream>
#include <bits/stdc++.h>
using namespace std;


struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : data(val), left(NULL), right(NULL) {}
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        long long maxWidth = 0 ;
        queue<pair<TreeNode* , long long>> q;
        q.push({root , 0});


        while( !q.empty()){
            int size = q.size();
            long long  minimal = q.front().second; //first node in the level is minimum index value

            long long  first = 0;
            long long  last = 0;
            //loop in the level 
            for( int i = 0 ; i < size ; i++){
                TreeNode* node = q.front().first;
                long long curr_idx =  q.front().second - minimal;
                q.pop();
                if( i == 0 ) first = curr_idx;
                if( i == size - 1) last = curr_idx;
                
                //push all the children nodes for that node 
                if( node->left){
                    q.push({ node->left , 2 * curr_idx + 1});
                }
                if( node -> right ){
                    q.push({ node->right , 2 * curr_idx + 2});
                }


            }
            maxWidth = max(maxWidth , last - first + 1);

        }
        return maxWidth;
        
        
    }
};
int main(){
     // Construct a simple binary tree:
    //       3
    //      / \
    //     5   1
    //    / \ / \
    //   6  2 0  8
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    Solution solution;
    int result = solution.widthOfBinaryTree(root);
    cout << "Maximum width of the binary tree is: " << result << endl;
    
    return 0;
}
