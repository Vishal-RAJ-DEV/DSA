#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : data(val), left(NULL), right(NULL) {}
};

class Solution
{
public:
/*🧠 Core Idea (1-Line)
Recursively search for p and q in left and right subtrees.
If a node finds one target in each subtree, it becomes the LCA.
If it finds only one target, pass it upward.
If it finds none, return NULL.
*/
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // Base case 1: If we reach a null node, return null (not found in this path)
        // Base case 2: If current node is either p or q, return this node
        // This works because we're looking for the first occurrence of p or q from root
        if (root == nullptr || root == p || root == q)
            return root;

        // Recursively search in left subtree for p and q
        // This will return:
        // - null if neither p nor q is found in left subtree
        // - p or q if one of them is found in left subtree
        // - LCA if both p and q are found in left subtree
        TreeNode *left = lowestCommonAncestor(root->left, p, q);

        // Recursively search in right subtree for p and q
        // Same return logic as left subtree search
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        // Case 1: If left subtree returns null, it means both p and q are in right subtree
        // So the LCA must be whatever the right subtree returned
        if (left == nullptr)
            return right;

        // Case 2: If right subtree returns null, it means both p and q are in left subtree
        // So the LCA must be whatever the left subtree returned
        else if (right == nullptr)
            return left;

        // Case 3: If both left and right subtrees return non-null values,
        // it means p is in one subtree and q is in the other subtree
        // Therefore, the current root is the Lowest Common Ancestor
        else
            return root;
    }
};

int main()
{
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
    TreeNode *p = root->left;  // Node with value 5
    TreeNode *q = root->right; // Node with value 1

    // Find LCA of nodes 5 and 1
    // Expected output: 3 (root is the LCA since 5 and 1 are in different subtrees)
    TreeNode *lca = solution.lowestCommonAncestor(root, p, q);
    cout << "Lowest Common Ancestor: " << lca->data << endl;

    return 0;
}