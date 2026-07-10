#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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
    //POST-ORDER traversal (left -> right -> root)
    int maxDepth(TreeNode* root) {
        //BASE CASE: empty node contributes 0 to depth
        if(root == nullptr) return 0;

        //RECURSIVE CASE: compute depth of left and right subtrees
        int lh = maxDepth(root->left);      // left subtree depth
        int rh = maxDepth(root->right);     // right subtree depth

        //add 1 for the current node and take max of both sides
        return 1 + max(lh, rh);
    }
};

int main() {
    Solution sol;

    /* Test case 1:
            3
           / \
          9  20
             / \
            15  7
        Expected maxDepth = 3
    */
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    cout << "maxDepth (test1): " << sol.maxDepth(root1) << " (expected: 3)" << endl;

    /* Test case 2: single node
            1
        Expected maxDepth = 1
    */
    TreeNode* root2 = new TreeNode(1);
    cout << "maxDepth (test2): " << sol.maxDepth(root2) << " (expected: 1)" << endl;

    /* Test case 3: empty tree
        Expected maxDepth = 0
    */
    cout << "maxDepth (test3): " << sol.maxDepth(nullptr) << " (expected: 0)" << endl;

    /* Test case 4: skewed tree
            1
           /
          2
         /
        3
        Expected maxDepth = 3
    */
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->left->left = new TreeNode(3);
    cout << "maxDepth (test4): " << sol.maxDepth(root4) << " (expected: 3)" << endl;

    return 0;
}
