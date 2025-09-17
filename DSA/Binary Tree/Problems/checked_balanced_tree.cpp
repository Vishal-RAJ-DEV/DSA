#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor to initialize
    // the node with a value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {                        // Optimized approach where time complexity is O(n) and space complexity is O(h) where h is the height of the tree.

public:
    // Function to check if a binary tree is balanced
    bool isBalanced(Node* root) {
        // Check if the tree's height difference
        // between subtrees is less than 2
        // If not, return false; otherwise, return true
        return dfsHeight(root) != -1;
    }

    // Recursive function to calculate
    // the height of the tree
    int dfsHeight(Node* root) {
        // Base case: if the current node is NULL,
        // return 0 (height of an empty tree)
        if (root == NULL) return 0;

        // Recursively calculate the
        // height of the left subtree
        int leftHeight = dfsHeight(root->left);

        // If the left subtree is unbalanced,
        // propagate the unbalance status
        if (leftHeight == -1) 
            return -1;

        // Recursively calculate the
        // height of the right subtree
        int rightHeight = dfsHeight(root->right);

        // If the right subtree is unbalanced,
        // propagate the unbalance status
        if (rightHeight == -1) 
            return -1;

        // Check if the difference in height between
        // left and right subtrees is greater than 1
        // If it's greater, the tree is unbalanced,
        // return -1 to propagate the unbalance status
        if (abs(leftHeight - rightHeight) > 1)  
            return -1;

        // Return the maximum height of left and
        // right subtrees, adding 1 for the current node
        return max(leftHeight, rightHeight) + 1;
    }
};

class Solution1 {                    //Brute force approach where time complexity is O(n^2) and space complexity is O(h) where h is the height of the tree.
public:
    // Function to check if a binary tree is balanced
    bool isBalanced(Node* root) {
        // If the tree is empty, it's balanced
        if (root == nullptr) {
            return true;
        }

        // Calculate the height of left and right subtrees
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        // Check if the absolute difference in heights
        // of left and right subtrees is <= 1
        if (abs(leftHeight - rightHeight) <= 1 &&
            isBalanced(root->left) &&
            isBalanced(root->right)) {
            return true;
        }

        // If any condition fails, the tree is unbalanced
        return false;
    }

    // Function to calculate the height of a subtree
    int getHeight(Node* root) {
        // Base case: if the current node is NULL,
        // return 0 (height of an empty tree)
        if (root == nullptr) {
            return 0;
        }

        // Recursively calculate the height
        // of left and right subtrees
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        // Return the maximum height of left and right subtrees
        // plus 1 (to account for the current node)
        return max(leftHeight, rightHeight) + 1;
    }
};





// Main function
int main() {
    // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    // Creating an instance of the Solution class
    Solution solution;

    // Checking if the tree is balanced
    if (solution.isBalanced(root)) {
        cout << "The tree is balanced." << endl;
    } else {
        cout << "The tree is not balanced." << endl;
    }

    return 0;
}