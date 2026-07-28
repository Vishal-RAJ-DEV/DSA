#include <bits/stdc++.h>
using namespace std;

// Definition of TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data) {
        val = data;
        left = right = nullptr;
    }
};

class Solution {
public:
    // Function to search for a node with given key in BST
    TreeNode* searchBST(TreeNode* root, int target) {

        // Traverse until we reach a null node or the target is found
        while (root != nullptr && root->val != target) {

            // If target is less than current node, go left
            if (target < root->val) {
                root = root->left;
            }

            // If target is greater than current node, go right
            else {
                root = root->right;
            }
        }

        // Return node if found, else nullptr
        return root;
    }

    // Recursive approach
    TreeNode* searchBST1(TreeNode* root, int val) {
    if (root == nullptr || root->val == val)
        return root;

    if (root->val < val)
        return searchBST(root->right, val);  // ✅ return
    else
        return searchBST(root->left, val);   // ✅ return
}

};

// Driver code
int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution obj;
    TreeNode* result = obj.searchBST(root, 2);

    if (result)
        cout << "Node found: " << result->val << endl;
    else
        cout << "Node not found" << endl;

    return 0;
}
