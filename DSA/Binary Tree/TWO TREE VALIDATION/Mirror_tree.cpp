#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};


/*
==========================================================
Algorithm (Recursive DFS)
==========================================================

1. If current node is NULL, return.

2. Swap its left and right child.

3. Recursively mirror the left subtree.

4. Recursively mirror the right subtree.

Since every node performs exactly one swap,
the whole tree becomes its mirror image.

Time Complexity : O(N)

Space Complexity : O(H)
(H = height of tree)
==========================================================
*/

class Solution {
public:

    void mirror(Node* root){

        // Base Case
        // If node is NULL, nothing to mirror.
        if(root == nullptr)
            return;

        // Swap the left and right child.
        swap(root->left, root->right);

        // Mirror the new left subtree.
        mirror(root->left);

        // Mirror the new right subtree.
        mirror(root->right);
    }
};

/*
==========================================================
Algorithm (BFS)

1. If tree is empty, return.

2. Push root into queue.

3. While queue is not empty

      Pop one node.

      Swap its left and right child.

      Push its left child.

      Push its right child.

4. Repeat until queue becomes empty.

Time Complexity : O(N)

Space Complexity : O(N)
==========================================================
*/

class Solution{
public:

    void mirror(Node* root){

        // Empty tree
        if(root == nullptr)
            return;

        // Queue for level order traversal
        queue<Node*> q;

        // Start from root
        q.push(root);

        // Continue until every node is processed
        while(!q.empty()){

            // Current node
            Node* current = q.front();
            q.pop();

            // Swap children
            swap(current->left, current->right);

            // Push left child if it exists
            if(current->left)
                q.push(current->left);

            // Push right child if it exists
            if(current->right)
                q.push(current->right);
        }
    }
};


int main(){
    return 0;
}