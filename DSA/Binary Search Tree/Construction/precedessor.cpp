// ============================================================
// PROBLEM: Find the Inorder Predecessor of a node in a BST
//
// The inorder predecessor of a node p is the node that comes
// IMMEDIATELY BEFORE p in the inorder traversal (sorted order).
// In a BST, inorder traversal visits nodes in ASCENDING order,
// so the predecessor is the node with the LARGEST value that
// is SMALLER than p->val.
//
// LOGIC — Two cases:
//
//   CASE 1: p has a LEFT subtree
//     → The predecessor is the RIGHTMOST node in p's left subtree.
//     Why? In a BST, all values in the left subtree are < p->val.
//     The rightmost node in that subtree has the largest value
//     among them — that's the closest value just below p->val.
//
//   CASE 2: p has NO left subtree
//     → The predecessor is the deepest ancestor where p lies in
//       its RIGHT subtree (i.e., the last ancestor where we
//       took a right turn while searching for p).
//     How? Walk from root toward p:
//       - If p->val > root->val, this root COULD be the predecessor
//         (since root < p), so save it and go right to find p.
//       - If p->val < root->val, this root is too large (it's after
//         p), so go left without saving.
//
// COMPLEXITY: O(h) time, O(1) space (h = height of BST)
// ============================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// TreeNode structure for BST
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Finds the inorder predecessor of node p in the BST rooted at 'root'
TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {

    // ── CASE 1: p has a left subtree ──
    // The predecessor is the RIGHTMOST node in the left subtree
    if (p->left) {
        TreeNode* cur = p->left;          // Start from left child
        while (cur->right)                // Keep going right to find max
            cur = cur->right;             // (rightmost = largest in left subtree)
        return cur;                       // This is the predecessor
    }

    // ── CASE 2: No left subtree ──
    // Walk from root to p, tracking the last node where we turned right
    TreeNode* pred = nullptr;             // Stores candidate predecessor

    while (root) {                        // Traverse from root toward p
        if (p->val > root->val) {         // root is smaller than p
            pred = root;                  // root COULD be the predecessor (best candidate so far)
            root = root->right;           // move right to find p (larger values)
        } else {                          // root is larger than or equal to p
            root = root->left;            // move left (smaller values), don't save root
        }
    }

    return pred;                          // Returns nullptr if no predecessor exists
}


int main() {
    // Example: BST = [5, 2, 8, 1, 3, 7, 9]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    // Find predecessor of node with value 3
    TreeNode* p = root->left->right;       // node 3
    TreeNode* pred = inorderPredecessor(root, p);

    if (pred)
        cout << "Predecessor of " << p->val << " is " << pred->val << "\n";
    else
        cout << "No predecessor\n";

    return 0;
}
