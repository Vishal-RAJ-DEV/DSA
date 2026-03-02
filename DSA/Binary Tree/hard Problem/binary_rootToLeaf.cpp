#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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
public:
    int solve(TreeNode *root, int Valsum)
    {
        if (root == nullptr)
            return 0;

        Valsum = (2 * Valsum) + (1 * root->val); // here 1 indicates the 2^0

        // for the  leaf node return the valsum for the that path

        if (root->left == nullptr && root->right == nullptr)
            return Valsum;

        // now get the path sum for both left and right
        return solve(root->left, Valsum) + solve(root->right, Valsum);
    }
    int sumRootToLeaf(TreeNode *root)
    {
        return solve(root, 0);
    }
};
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);
    
    Solution obj;
    cout << obj.sumRootToLeaf(root) << endl;
    
    return 0;
}