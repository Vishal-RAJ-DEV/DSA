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

    // Constructor initializes the node with a given value
    // and sets left and right child pointers to null
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// This class is an iterator for traversing the BST
//core idea using
//bst inorder traversal gives the sorted order of the elements in the BST where node goes left -> node -> right
//bst reverse inorder traversal gives the reverse sorted order of the elements in the BST where node goes right -> node -> left
//by using two iterators one for inorder and another for reverse inorder we can get the smallest and largest element in the BST and then we can use two pointer technique to find the target sum    
class BSTIterator {
private:
    // A stack is used to keep track of nodes while traversing the tree
    //each inorder and reverse inorder traversal will have its own stack to keep track of the nodes
    stack<TreeNode*> myStack;
    // This flag tells whether we are moving forward (inorder) or backward (reverse inorder)
    bool reverse;

public:
    // Constructor initializes the iterator with the root node and traversal direction
    BSTIterator(TreeNode* root, bool isReverse) {
        // Push all nodes on one side (left or right) into the stack
        reverse = isReverse; // Set the traversal direction either forward (inorder) or backward (reverse inorder)
        pushAll(root);
    }

    // This function checks if there are more nodes left to visit
    bool hasNext() {
        // If the stack is not empty, there are still nodes left
        return !myStack.empty();
    }

    // This function returns the next node’s value in the chosen order
    int next() {
        // Get the node on top of the stack
        TreeNode* tmpNode = myStack.top();
        // Remove this node from the stack
        myStack.pop();

        // If we are not in reverse mode, we need to go right after visiting a node
        if (!reverse) {
            pushAll(tmpNode->right);
        }
        // If we are in reverse mode, we need to go left after visiting a node
        else {
            pushAll(tmpNode->left);
        }

        // Return the value of the node that was just visited
        return tmpNode->val;
    }

private:
    // This helper function pushes all nodes from the current node down to the left/right edge
    void pushAll(TreeNode* node) {
        // Keep going until we reach a null node
        while (node != nullptr) {
            // Push the node onto the stack
            myStack.push(node);
            // If reverse is true, move to the right child
            if (reverse) {
                node = node->right;
            }
            // Otherwise, move to the left child
            else {
                node = node->left;
            }
        }
    }
};

// This class contains the solution logic to check if a target sum exists in BST
class Solution {
public:
    // This function checks if two nodes in BST sum to k
    bool findTarget(TreeNode* root, int k) {
        // If tree is empty, return false immediately
        if (!root) return false;

        // Create two iterators: one for smallest-to-largest order, another for largest-to-smallest
        BSTIterator l(root, false);
        BSTIterator r(root, true);

        // Get first values from both ends
        int i = l.next();
        int j = r.next();

        // Loop until the two pointers meet
        while (i < j) {
            // If the two numbers add up to k, we found a pair
            if (i + j == k) return true;
            // If sum is too small, move left iterator forward
            else if (i + j < k) i = l.next();
            // If sum is too large, move right iterator backward
            else j = r.next();
        }

        // If no pair found, return false
        return false;
    }
};

// This function prints the tree in inorder traversal
void printInOrder(TreeNode* root) {
    // If current node is null, stop recursion
    if (!root) return;
    // Visit left child
    printInOrder(root->left);
    // Print current node value
    cout << root->val << " ";
    // Visit right child
    printInOrder(root->right);
}

// Driver function to test the program
int main() {
    // Create a sample BST
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    // Print the BST in inorder to confirm tree structure
    cout << "Tree Initialized: ";
    printInOrder(root);
    cout << endl;

    // Create solution object
    Solution solution;

    // Define target sum
    int target = 22;

    // Check if pair exists
    bool exists = solution.findTarget(root, target);

    // Print result
    if (exists) cout << "Pair with sum " << target << " exists." << endl;
    else cout << "Pair with sum " << target << " does not exist." << endl;

    return 0;
}
