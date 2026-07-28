/*
Two Sum IV - Input is a BST
Solved
Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise
*/
#include <bits/stdc++.h>
using namespace std;

// This structure defines a node in a Binary Search Tree
struct TreeNode {
    // This stores the value of the node
    int val;
    // Pointer to the left child
    TreeNode* left;
    // Pointer to the right child
    TreeNode* right;

    // Constructor initializes node with value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// This class contains the brute force solution
class Solution {
public:
    // Function to check if there exists a pair with given sum in BST
    bool findTarget(TreeNode* root, int k) {
        // Vector stores inorder traversal of BST
        vector<int> inorder;

        // Call helper to fill vector
        inorderTraversal(root, inorder);

        // Initialize two pointers for searching in sorted inorder array
        int left = 0;
        int right = inorder.size() - 1;

        // Loop until pointers meet
        while (left < right) {
            // Calculate sum of current pair
            int sum = inorder[left] + inorder[right];

            // If sum equals k, we found a pair
            if (sum == k) {
                return true;
            }
            // If sum smaller than k, move left pointer forward
            else if (sum < k) {
                left++;
            }
            // If sum larger than k, move right pointer backward
            else {
                right--;
            }
        }

        // If no such pair found, return false
        return false;
    }

private:
    // Helper function to perform inorder traversal
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        // If root is null, stop recursion
        if (!root) return;

        // Traverse left subtree
        inorderTraversal(root->left, inorder);
        // Add current node value to vector
        inorder.push_back(root->val);
        // Traverse right subtree
        inorderTraversal(root->right, inorder);
    }
};

// Function to print inorder traversal of BST
void printInOrder(TreeNode* root) {
    // If node is null, stop recursion
    if (!root) return;
    // Visit left child
    printInOrder(root->left);
    // Print current node
    cout << root->val << " ";
    // Visit right child
    printInOrder(root->right);
}

// Driver code
int main() {
    // Create sample BST
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    // Print inorder traversal
    cout << "Tree Initialized: ";
    printInOrder(root);
    cout << endl;

    // Create solution object
    Solution solution;

    // Define target sum
    int target = 22;

    // Call function to check for pair
    bool exists = solution.findTarget(root, target);

    // Print result
    if (exists) cout << "Pair with sum " << target << " exists." << endl;
    else cout << "Pair with sum " << target << " does not exist." << endl;

    return 0;
}
