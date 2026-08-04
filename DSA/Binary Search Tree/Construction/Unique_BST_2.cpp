#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};


/*
==================================================================

Intuition

solve(start, end)

returns ALL possible BSTs that can be formed
using values in the range [start...end].

Since one range can generate multiple BSTs,
the function returns

vector<TreeNode*>

instead of a single TreeNode*.

------------------------------------------------------------------

How does vector<TreeNode*> store trees?

The vector stores ONLY the root pointer (address)
of each generated BST.

Example

Tree 1          Tree 2

    2              3
     \            /
      3          2

Vector

[
    address of root(2),
    address of root(3)
]

Since every root is already connected to its
left and right children, storing the root pointer
is enough to access the entire tree.

------------------------------------------------------------------

Working

Choose every value as the root.

Recursively generate

• All possible left subtrees.
• All possible right subtrees.

Then combine every left subtree with every
right subtree by attaching them to the new root.

Every newly formed tree's root pointer is pushed
into the answer vector.

Finally,

solve(start, end)

returns all possible BSTs for that range.

==================================================================
*/


class Solution {
public:

    vector<TreeNode*> solve(int start, int end) {

        // No values left to form a tree.
        if (start > end)
            return {nullptr};

        vector<TreeNode*> ans;

        // Try every value as the root.
        for (int root = start; root <= end; root++) {

            // Generate all possible left subtrees.
            vector<TreeNode*> leftTrees = solve(start, root - 1);

            // Generate all possible right subtrees.
            vector<TreeNode*> rightTrees = solve(root + 1, end);

            // Combine every left subtree with every right subtree.
            for (TreeNode* left : leftTrees) {

                for (TreeNode* right : rightTrees) {

                    TreeNode* node = new TreeNode(root);

                    node->left = left;
                    node->right = right;

                    ans.push_back(node);
                }
            }
        }

        return ans;
    }

    vector<TreeNode*> generateTrees(int n) {

        if (n == 0)
            return {};

        return solve(1, n);
    }
};



int main(){
    return 0;
}