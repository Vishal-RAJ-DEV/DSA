#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
  struct TreeNode {
      int data;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
 };
//brute force approach by storing the values of the nodes in a vector and then finding the kth smallest and kth largest element
//time complexity : O(n) for the inorder traversal and O(1) for finding the kth smallest and kth largest element
//space complexity : O(n) for storing the values of the nodes in a vector
class Solution1 {
public:
    // Helper function to perform an in-order traversal of the BST
    void inorderTraversal(TreeNode* node, vector<int>& values) {
        if (node) {
            inorderTraversal(node->left, values);
            values.push_back(node->data);
            inorderTraversal(node->right, values);
        }
    }
    
    vector<int> kLargesSmall(TreeNode* root, int k) {
        // Vector to store the node values
        vector<int> values;
        // Perform in-order traversal and collect values
        inorderTraversal(root, values);
        
        // Find the kth smallest and kth largest values
        int kth_smallest = values[k - 1];
        int kth_largest = values[values.size() - k];
        
        return {kth_smallest, kth_largest};
    }
};

//optimal approach by using the properties of the binary search tree and performing an inorder traversal to find the kth smallest element and a reverse inorder traversal to find the kth largest element
//time complexity : O(h) where h is the height of the tree in the average case and O(n) in the worst case (when the tree is skewed)
//space complexity : O(h) for the recursive stack in the average case and O(n) in the worst case (when the tree is skewed)
class Solution {
public:
    // Function to find the kth smallest element
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        inorder(root);
        return result;
    }

    // Function to find the kth largest element
    int kthLargest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        reverse_inorder(root);
        return result;
    }

    // Function to return kth smallest and kth largest elements
    vector<int> kLargesSmall(TreeNode* root, int k) {
        return {kthSmallest(root, k), kthLargest(root, k)};
    }

private:
    int k;
    int result;

    // Helper function for inorder traversal
    void inorder(TreeNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            if (--k == 0) {
                result = node->data;
                return;
            }
            inorder(node->right);
        }
    }

    // Helper function for reverse inorder traversal
    void reverse_inorder(TreeNode* node) {
        if (node != nullptr) {
            reverse_inorder(node->right);
            if (--k == 0) {
                result = node->data;
                return;
            }
            reverse_inorder(node->left);
        }
    }
};

// Main method to demonstrate the function
int main() {
    // Constructing the tree: [3, 1, 4, nullptr, 2]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(4);
    
    Solution solution;
    int k = 1;
    vector<int> result = solution.kLargesSmall(root, k);
    
    // Output the result
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [1, 4]
    
    return 0;
}