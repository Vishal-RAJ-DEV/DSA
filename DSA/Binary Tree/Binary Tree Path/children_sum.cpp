#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left, *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; 

/*
    ALGORITHM: Children Sum Property (Step-by-Step)

    Definition: For every node in the binary tree,
                node->data == (node->left->data + node->right->data).
                A leaf node or null node automatically satisfies it.

    Step 1 - Base case:
        - If root is null, return true (no node to violate the property).
        - If root is a leaf (no left AND no right), return true.

    Step 2 - Recurse on subtrees:
        - Recursively check if the left subtree satisfies the property.
        - Recursively check if the right subtree satisfies the property.
        - This is a post-order check: children are verified before the parent.

    Step 3 - Propagate failure:
        - If either subtree has already violated the property,
          return false immediately (no need to check further).

    Step 4 - Check current node:
        - Get left child's data (0 if null).
        - Get right child's data (0 if null).
        - If left + right == current node's data, return true.
        - Otherwise, return false.
*/
class Solution {
public:
    bool isSumProperty(Node *root) {
        // null node or leaf - automatically satisfies the property
        if (!root || (root->left == nullptr && root->right == nullptr))
            return true;

        // Recursively check left and right subtrees first (post-order)
        bool leftOk = isSumProperty(root->left);   // check left subtree
        bool rightOk = isSumProperty(root->right); // check right subtree

        // If any subtree failed, propagate failure upward
        if (!leftOk || !rightOk)
            return false;

        // Get left child's data (0 if left child doesn't exist)
        int leftVal = (root->left) ? root->left->data : 0;
        // Get right child's data (0 if right child doesn't exist)
        int rightVal = (root->right) ? root->right->data : 0;

        // Check children sum property at the current node
        if (leftVal + rightVal == root->data)
            return true;

        // Property violated at this node
        return false;
    }
};


int main(){
    return 0;
}