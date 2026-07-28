#include <bits/stdc++.h>
using namespace std;

// Definition of TreeNode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        val = data;
        left = right = nullptr;
    }
};

class Solution
{
public:
    // Function to search for a node with given key in BST
    TreeNode *searchBST(TreeNode *root, int target)
    {
        TreeNode* ceilNode = nullptr;
        // Traverse until we reach a null node or the target is found
        while (root != nullptr)
        {
            if( root->val == target){
                ceilNode = root;
                return ceilNode;
            }
            // If target is less than current node, go left
            if (target > root->val)
            {
                ceilNode = root; // potential ceil
                root = root->right; // go right to find smaller value which is also >=target
            }

            // If value is greater than current node, go left to find smaller value
            else
            {
                root = root->left;
            }
        }

        // Return node if found, else nullptr
        return ceilNode;
    }

    // Recursive approach
    TreeNode *searchBST1(TreeNode *root, int val)
    {
        if (root == nullptr)
            return root;
        if (root->val == val)
            return root;

        if (root->val <= val)
        {
            //call goes to right sub tree till there is node in the right sub tree otherewise
            //it will either return null or the floor node 
            // if we get the node value less than or equal to val we go to right sub tree to find greater value which is also <=val
            TreeNode *rightFloor = searchBST1(root->right, val);
            // so here if rightFloor is null it means there is no floor in right sub tree so root is the floor or else rightFloor is the floor value exactly
            return (rightFloor != nullptr) ? rightFloor : root;
        }
        else
        {
            //so here we don't have greater value on left sub tree so we go to left sub tree to find floor
            return searchBST1(root->left, val); // ✅ return
        }
    }
};

// Driver code
int main()
{
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution obj;
    TreeNode *result = obj.searchBST(root, 6);
    cout << "Floor value is: ";
    if (result)
        cout << result->val << endl;
    else
        cout << "No floor value found" << endl;

    return 0;
}
