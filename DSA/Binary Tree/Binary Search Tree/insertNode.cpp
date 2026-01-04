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
    TreeNode *insertIntoBST1(TreeNode *root, int val)
    {
        // Base case: empty spot found
        if (root == NULL)
        {
            return new TreeNode(val);
        }

        if (val < root->val)
        {
            root->left = insertIntoBST(root->left, val);
        }
        else
        {
            root->right = insertIntoBST(root->right, val);
        }

        return root;
    }

    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        TreeNode *node = new TreeNode(val);

        if (root == NULL)
            return node;

        TreeNode *curr = root;

        while (true)
        {
            if (val < curr->val)
            {
                if (curr->left == NULL)
                {
                    curr->left = node;
                    break;
                }
                curr = curr->left;
            }
            else
            {
                if (curr->right == NULL)
                {
                    curr->right = node;
                    break;
                }
                curr = curr->right;
            }
        }

        return root;
    }
};


// Function to perform inorder traversal
// of the tree and store values in 'arr'
void inorder(TreeNode* root, vector<int> &arr){
    // If the current node is NULL
    // (base case for recursion), return
    if(root == nullptr){
        return;
    }
    // Recursively traverse the left subtree
    inorder(root->left, arr);
    // Push the current node's
    // value into the vector
    arr.push_back(root->val);
    // Recursively traverse 
    // the right subtree
    inorder(root->right, arr);
}

// Function to initiate inorder traversal
// and return the resulting vector
vector<int> inOrder(TreeNode* root){
    // Create an empty vector to
    // store inorder traversal values
    vector<int> arr;
    // Call the inorder traversal function
    inorder(root, arr);
    // Return the resulting vector
    // containing inorder traversal values
    return arr;
}

// Driver code
int main()
{
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution obj;
    TreeNode *result = obj.insertIntoBST1(root, 6);
    vector<int> arr = inOrder(result);
    for(int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
