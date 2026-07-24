#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Check if Subtree):
Given two binary trees root1 and root2, check if root2 is a subtree of root1.
A subtree of root1 is a tree consisting of a node in root1 and all its descendants.
The tree root2 is a subtree of root1 if there exists a node in root1 such that
the subtree rooted at that node is IDENTICAL to root2.

EXAMPLE:
root1 =         root2 = 
    3              4
   / \            / \
  4   5          1   2
 / \
1   2

root2 is a subtree of root1 (root1->left matches root2).
But if root2 = [4, 1, null] -> not a subtree.

ALGORITHM:

The solution uses a two-step recursive approach:

Step 1 - isSubTree(root1, root2):
   Check if root2 is a subtree anywhere in root1.
   - If root2 is null -> always true (null tree is subtree of any tree).
   - If root1 is null but root2 isn't -> false.
   - If current root1 matches root2 (canValid) -> true.
   - Otherwise, recursively check root1->left and root1->right.
   Returns true if found in either subtree.

Step 2 - canValid(node1, node2):
   Check if two trees are IDENTICAL.
   - If both null -> identical (true).
   - If one is null and the other isn't -> not identical (false).
   - If data doesn't match -> not identical (false).
   - Recurse: check left == left AND right == right.

LOGIC:
- We traverse root1 looking for a node that matches root2's root value.
- At each node, we call canValid() to check if the entire tree rooted
  at that node is structurally identical to root2.
- If canValid fails at current node, we go left or right in root1.
- This is O(n * m) in worst case where n = size of root1, m = size of root2.
*/

// Structure of a Tree Node
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

    // Check if two trees are IDENTICAL (same structure and values)
    bool canValid(Node* node1, Node* node2)
    {
        // Both null -> identical
        if (node1 == nullptr && node2 == nullptr)
            return true;

        // One null, other not -> not identical
        if (node1 == nullptr || node2 == nullptr)
            return false;

        // Data mismatch -> not identical
        if (node1->data != node2->data)
            return false;

        // Recursively check left and right subtrees
        return canValid(node1->left, node2->left) &&
               canValid(node1->right, node2->right);
    }

    // Check if root2 is a subtree of root1
    bool isSubTree(Node* root1, Node* root2)
    {
        // Null tree is always a subtree
        if (root2 == nullptr)
            return true;

        // root1 exhausted, root2 still exists -> no match
        if (root1 == nullptr)
            return false;

        // Check if current node matches root2
        if (canValid(root1, root2))
            return true;

        // Otherwise, check left and right subtrees of root1
        return isSubTree(root1->left, root2) ||
               isSubTree(root1->right, root2);
    }
};

int main(){
    return 0;
}