// ============================================================
// PROBLEM: Find the Inorder Successor of a node in a BST
//
// The inorder successor of a node p is the node that comes
// IMMEDIATELY AFTER p in the inorder traversal (sorted order).
// In a BST, inorder traversal visits nodes in ASCENDING order,
// so the successor is the node with the SMALLEST value that is
// LARGER than p->val.
//
// LOGIC — Two cases:
//
//   CASE 1: p has a RIGHT subtree
//     → The successor is the LEFTMOST node in p's right subtree.
//     Why? All values in the right subtree are > p->val. The
//     leftmost node has the smallest value among them — that's
//     the closest value just above p->val.
//
//   CASE 2: p has NO right subtree
//     → The successor is the deepest ancestor where p lies in
//       its LEFT subtree (i.e., the last ancestor where we
//       took a left turn while searching for p).
//     How? Walk from root toward p:
//       - If p->val < root->val, this root COULD be the successor
//         (since root > p), so save it and go left to find p.
//       - If p->val > root->val, this root is too small (it's
//         before p), so go right without saving.
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

// Finds the inorder successor of node p in the BST rooted at 'root'
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {

    // ── CASE 1: p has a right subtree ──
    // The successor is the LEFTMOST node in the right subtree
    if (p->right) {
        TreeNode* cur = p->right;         // Start from right child
        while (cur->left)                 // Keep going left to find min
            cur = cur->left;              // (leftmost = smallest in right subtree)
        return cur;                       // This is the successor
    }

    // ── CASE 2: No right subtree ──
    // Walk from root to p, tracking the last node where we turned left
    TreeNode* succ = nullptr;             // Stores candidate successor

    while (root) {                        // Traverse from root toward p
        if (p->val < root->val) {         // root is larger than p
            succ = root;                  // root COULD be the successor (best candidate so far)
            root = root->left;            // move left to find p (smaller values)
        } else {                          // root is smaller than or equal to p
            root = root->right;           // move right (larger values), don't save root
        }
    }

    return succ;                          // Returns nullptr if no successor exists
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

    // Find successor of node with value 3
    TreeNode* p = root->left->right;       // node 3
    TreeNode* succ = inorderSuccessor(root, p);

    if (succ)
        cout << "Successor of " << p->val << " is " << succ->val << "\n";
    else
        cout << "No successor\n";

    return 0;
}
