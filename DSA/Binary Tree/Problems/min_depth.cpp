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
    //Minimum depth = shortest path from root to a LEAF node
    //(a leaf has NO children — both left and right are null)
    int minDepth(TreeNode* root) {
        //BASE CASE 1: empty node contributes 0
        if(!root) return 0;

        //BASE CASE 2: leaf node → depth is 1 (just this node)
        if(root && !root->left && !root->right) return 1;

        //initialize both depths as INFINITY (we only consider real child paths)
        int left  = INT_MAX;
        int right = INT_MAX;

        //recurse only if the child actually exists
        if(root->left)  left  = 1 + minDepth(root->left);
        if(root->right) right = 1 + minDepth(root->right);

        //pick the shorter valid leaf path
        //(if one child is null, its INT_MAX is ignored by min())
        return min(left, right);
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
        Shortest leaf path: 3->9 (leaf 9) → depth = 2
    */
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    cout << "minDepth (test1): " << sol.minDepth(root1) << " (expected: 2)" << endl;

    /* Test case 2: single node
            1
        Leaf = root itself → depth = 1
    */
    TreeNode* root2 = new TreeNode(1);
    cout << "minDepth (test2): " << sol.minDepth(root2) << " (expected: 1)" << endl;

    /* Test case 3: empty tree
        Depth = 0
    */
    cout << "minDepth (test3): " << sol.minDepth(nullptr) << " (expected: 0)" << endl;

    /* Test case 4: skewed tree (only left children)
            1
           /
          2
         /
        3
        Only leaf is 3 → path 1->2->3 → depth = 3
    */
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->left->left = new TreeNode(3);
    cout << "minDepth (test4): " << sol.minDepth(root4) << " (expected: 3)" << endl;

    /* Test case 5: node with only one child
            1
             \
              2
        Only leaf is 2 → depth = 2
        (IMPORTANT: root(1) is NOT a leaf since it has a right child)
    */
    TreeNode* root5 = new TreeNode(1);
    root5->right = new TreeNode(2);
    cout << "minDepth (test5): " << sol.minDepth(root5) << " (expected: 2)" << endl;

    return 0;
}
