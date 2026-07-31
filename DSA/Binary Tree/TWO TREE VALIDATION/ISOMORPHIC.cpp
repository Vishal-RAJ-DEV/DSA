#include <iostream>
#include <bits/stdc++.h>
using namespace std;



class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};



/*
==========================================================
Algorithm (Recursive DFS)

Two trees are isomorphic if:

1. Both are empty.
2. Both roots have the same value.
3. Either:

   Case 1 (No Flip)
   ----------------
   left subtree  <-> left subtree
   right subtree <-> right subtree

   OR

   Case 2 (Flip)
   -------------
   left subtree  <-> right subtree
   right subtree <-> left subtree

If either case returns true,
the trees are isomorphic.

----------------------------------------------------------

Time Complexity:
Worst Case : O(2^N)

Space Complexity:
O(H)
H = Height of the tree (recursion stack)

==========================================================
*/

/*

Intuition in One Sentence

For every pair of corresponding nodes, you have exactly two choices:

Don't flip:
Left ↔ Left
Right ↔ Right

Flip:
Left ↔ Right
Right ↔ Left

If either arrangement works recursively for every node, then the two trees are isomorphic.

Time Complexity
Without memoization, the recursive solution explores both possibilities (flip and no flip) at many nodes. In the worst case, this can lead to exponential time, approximately O(2ⁿ) for n nodes.

However, in many practical trees, recursion stops early because:
node values differ,
one node is NULL while the other isn't,
subtree shapes don't match.

If additional constraints (like unique node values) or memoization are used, the practical performance can be much better.

*/

class Solution {
public:

    bool isIsomorphic(Node* root1, Node* root2) {

        // Case 1:
        // Both trees are empty.
        if(root1 == nullptr && root2 == nullptr)
            return true;

        // Case 2:
        // One tree is empty while the other isn't.
        if(root1 == nullptr || root2 == nullptr)
            return false;

        // Case 3:
        // Current node values don't match.
        if(root1->data != root2->data)
            return false;

        /*
            Case 1 : No Flip

                 root1                root2

                   A                    A
                 /   \                /   \
                B     C              B     C

            Compare:

            left  <-> left
            right <-> right
        */
        bool noFlip =
            isIsomorphic(root1->left, root2->left) &&
            isIsomorphic(root1->right, root2->right);

        /*
            Case 2 : Flip

                 root1                root2

                   A                    A
                 /   \                /   \
                B     C              C     B

            Compare:

            left  <-> right
            right <-> left
        */
        bool flip =
            isIsomorphic(root1->left, root2->right) &&
            isIsomorphic(root1->right, root2->left);

        // If either possibility works,
        // trees are isomorphic.
        return noFlip || flip;
    }
};



int main(){
    return 0;
}