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

// Morris Traversal for Inorder
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;        // Vector to store the inorder traversal result
    TreeNode* cur = root;   // Start traversal from the root node

    while (cur) {           // Continue until we've processed all nodes (cur becomes NULL)

        if (cur->left == NULL) {        // If no left child, this node is visited in inorder now
            ans.push_back(cur->val);    // Add current node's value to result (visit it)
            cur = cur->right;           // Move to the right child (or follow the thread back to ancestor)
        }
        else {                          // If left child exists, we need to establish threading

            TreeNode* prev = cur->left; // Start from left child; we'll find the rightmost node in the left subtree

            // Find the rightmost node in the left subtree (the inorder predecessor of cur)
            // Stop when either prev->right is NULL (no thread yet) or prev->right == cur (thread already exists)
            while (prev->right && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL) {   // If no thread exists yet
                prev->right = cur;       // Create a thread from predecessor to current node (for backtracking)
                cur = cur->left;         // Now go explore the left subtree
            }
            else {                       // Thread already exists (prev->right == cur), meaning left subtree is fully processed
                prev->right = NULL;      // Remove the thread (restore tree to original structure)
                ans.push_back(cur->val); // Visit current node (inorder: after left subtree)
                cur = cur->right;        // Move to the right subtree
            }
        }
    }

    return ans; // Return the inorder traversal result
}

// Morris Traversal for Preorder
vector<int> preorderTraversal(TreeNode* root) {

    vector<int> ans;        // Vector to store the preorder traversal result
    TreeNode* cur = root;   // Start traversal from the root node

    while (cur) {           // Continue until all nodes are processed

        if (cur->left == NULL) {        // If no left child
            ans.push_back(cur->val);    // Visit current node (preorder: visit before children)
            cur = cur->right;           // Move to the right child (or follow thread back)
        }
        else {                          // Left child exists

            TreeNode* prev = cur->left; // Start from left child

            // Find the rightmost node in the left subtree (inorder predecessor of cur)
            while (prev->right && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL) {           // No thread yet (first time visiting this subtree)
                ans.push_back(cur->val);         // Visit current node BEFORE going left (preorder: root first)
                prev->right = cur;               // Create a thread for backtracking to cur
                cur = cur->left;                 // Now traverse the left subtree
            }
            else {                               // Thread exists (left subtree already processed)
                prev->right = NULL;              // Remove the thread (restore tree)
                cur = cur->right;                // Move to the right subtree
            }
        }
    }

    return ans; // Return the preorder traversal result
}

// Morris Traversal for Postorder
vector<int> postorderTraversal(TreeNode* root) {

    vector<int> ans;        // Vector to store the postorder traversal result
    TreeNode* cur = root;   // Start traversal from the root node

    while (cur) {           // Continue until all nodes are processed

        if (cur->right == NULL) {       // If no right child (mirror of inorder: we process right side first)
            ans.push_back(cur->val);    // Add current node's value (collected in reverse order)
            cur = cur->left;            // Move to the left child (or follow thread back)
        }
        else {                          // Right child exists

            TreeNode* succ = cur->right; // Start from right child; find the leftmost node in the right subtree

            // Find the leftmost node in the right subtree (the inorder successor of cur)
            // Stop when succ->left is NULL (no thread) or succ->left == cur (thread exists)
            while (succ->left && succ->left != cur)
                succ = succ->left;

            if (succ->left == NULL) {    // No thread yet (first time visiting this subtree)
                ans.push_back(cur->val); // Collect current node's value (we will reverse at the end)
                succ->left = cur;        // Create a thread from successor to current node
                cur = cur->right;        // Now explore the right subtree
            }
            else {                       // Thread exists (right subtree is fully processed)
                succ->left = NULL;       // Remove the thread (restore tree)
                cur = cur->left;         // Move to the left subtree
            }
        }
    }

    reverse(ans.begin(), ans.end()); // Reverse the collected result to get correct postorder (LRV)

    return ans; // Return the postorder traversal result
}


int main(){
    return 0;
}
