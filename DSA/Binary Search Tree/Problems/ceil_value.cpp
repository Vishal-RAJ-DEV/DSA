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
            if (target < root->val)
            {
                ceilNode = root; // potential ceil
                root = root->left; // go left to find smaller value which is also >=target
            }

            // If target is greater than current node, go right
            else
            {
                root = root->right;
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

        if (root->val >= val)
        {
            //call goes to left sub tree till there is node in the left sub tree otherewise
            //it will either return null or the ceil node 
            // if we get the node value greater than or equal to val we go to left sub tree to find smaller value which is also >=val
            TreeNode *leftCeil = searchBST1(root->left, val);
            // so here if leftCeil is null it means there is no ceil in left sub tree so root is the ceil or else leftCeil is the ceil value exactly
            return (leftCeil != nullptr) ? leftCeil : root;
        }
        else
        {
            //so here we don't have greater value on left sub tree so we go to right sub tree to find ceil
            return searchBST1(root->right, val); // ✅ return
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
    cout << "Ceil value is: ";
    if (result)
        cout << result->val << endl;
    else
        cout << "No ceil value found" << endl;


    return 0;
}
