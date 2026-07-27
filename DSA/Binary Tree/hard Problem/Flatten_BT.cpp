#include <iostream>
#include <bits/stdc++.h>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};


///this is the brute force approch  of the problem

class BruteForceSolution {
public:
    // Stores the head of the flattened list that has already been built.
    TreeNode* prev = nullptr;

    void flatten(TreeNode* root) {

        // If the current node is NULL, there is nothing to flatten.
        if (root == nullptr)
            return;

        // Flatten the right subtree first, followed by the left subtree.
        // This processes nodes in Reverse Preorder (Right -> Left -> Root).
        flatten(root->right);
        flatten(root->left);

        // During backtracking, attach the current node in front of the
        // already flattened list.
        root->right = prev;

        // The flattened tree must not contain any left child.
        root->left = nullptr;

        // Make the current node the new head of the flattened list,
        // so its parent can connect to it.
        prev = root;
    }
};

// solution class
class BetterSolution {
public:
    // keep same field as original (unused in iterative version)
    TreeNode* prev = nullptr;

    // flatten binary tree to right-skewed linked list (iterative)
    void flatten(TreeNode* root) {
        // handle empty tree
        if (root == nullptr) return;
        // create stack for DFS
        stack<TreeNode*> st;
        // push root to start traversal
        st.push(root);
        // process while stack has nodes
        while (!st.empty()) {
            // take top node
            TreeNode* cur = st.top();
            // pop it
            st.pop();
            // push right child first (so left is processed first)
            if (cur->right != nullptr) st.push(cur->right);
            // push left child next
            if (cur->left != nullptr) st.push(cur->left);
            // if stack not empty, link current's right to next node
            if (!st.empty()) cur->right = st.top();
            // nullify left to form right-only chain
            cur->left = nullptr;
        }
    }
};


class optimalSolution {
public:
    // Function to flatten a binary tree
    // to a right next Linked List structure
    void flatten(TreeNode* root) {
        // Initialize a pointer
        // 'curr' to the root of the tree
        TreeNode* curr = root;

        // Iterate until 'curr'
        // becomes NULL
        while (curr) {
            // Check if the current
            // node has a left child
            if (curr->left) {
                // If yes, find the rightmost
                // node in the left subtree
                TreeNode* pre = curr->left;
                while (pre->right) {
                    pre = pre->right;
                }

                // Connect the rightmost node in
                // the left subtree to the current
               //  node's right child
                pre->right = curr->right;

                // Move the entire left subtree to the
                // right child of the current node
                curr->right = curr->left;

                // Set the left child of
                // the current node to NULL
                curr->left = NULL;
            }

            // Move to the next node
            // on the right side
            curr = curr->right;
        }
    }
};


// print preorder traversal
void printPreorder(TreeNode* root) {
    // stop at null
    if (!root) return;
    // print current node
    cout << root->val << " ";
    // recurse left
    printPreorder(root->left);
    // recurse right
    printPreorder(root->right);
}

// print along right pointers
void printFlattenTree(TreeNode* root) {
    // stop at null
    if (!root) return;
    // print current node
    cout << root->val << " ";
    // move right
    printFlattenTree(root->right);
}

// program entry
int main() {
    // build sample tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->right = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->left = new TreeNode(8);

    // create solver
    BruteForceSolution sol;

    // show preorder before flatten
    cout << "Binary Tree Preorder: ";
    printPreorder(root);
    cout << endl;

    // perform flatten
    sol.flatten(root);

    // show right-chain after flatten
    cout << "Binary Tree After Flatten: ";
    printFlattenTree(root);
    cout << endl;

    // done
    return 0;
}


