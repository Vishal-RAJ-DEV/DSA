#include <iostream>
#include <bits/stdc++.h>
using namespace std;



/*
===========================================================
Algorithm (Postorder DFS)

1. Process left subtree.
2. Process right subtree.
3. Now decide whether current node should remain.

Cases:

1. Leaf Node
   Return the node.

2. Only Left Child
   Remove current node.
   Return left child.

3. Only Right Child
   Remove current node.
   Return right child.

4. Two Children
   Keep the node.

Why Postorder?

Because children must already be processed before
deciding whether the current node becomes a half node.

Time Complexity : O(N)

Space Complexity : O(H)
(H = Height of Tree)

===========================================================
*/

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Solution {
public:

    Node *RemoveHalfNodes(Node *root) {

        // Base Case
        if(root == nullptr)
            return nullptr;

        // Process left subtree first.
        root->left = RemoveHalfNodes(root->left);

        // Process right subtree.
        root->right = RemoveHalfNodes(root->right);

        // Case 1: Leaf node.
        if(root->left == nullptr && root->right == nullptr)
            return root;

        // Case 2: Only right child exists.
        if(root->left == nullptr) {

            Node* child = root->right;

            delete root;          // Optional on GFG but good practice.

            return child;
        }

        // Case 3: Only left child exists.
        if(root->right == nullptr) {

            Node* child = root->left;

            delete root;

            return child;
        }

        // Case 4: Both children exist.
        return root;
    }
};



int main(){
    return 0;
}