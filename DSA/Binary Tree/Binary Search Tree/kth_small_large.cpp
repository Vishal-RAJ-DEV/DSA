#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ============================================================
// APPROACH 1 (Brute Force): Store all values in a vector
//
// LOGIC:
//   Inorder traversal of a BST visits nodes in ASCENDING order.
//   So if we store all node values via inorder into a sorted vector,
//   then:
//     - kth smallest = values[k-1]          (0-indexed)
//     - kth largest  = values[size - k]     (kth from the end)
//
// Intuition: Exploit the fact that inorder = sorted order in a BST.
//            After collecting, it's O(1) array lookup.
//
// Time:  O(n) for traversal, O(1) for lookup
// Space: O(n) for the vector
// ============================================================
class Solution1 {
public:
    void inorderTraversal(TreeNode* node, vector<int>& values) {
        if (node) {
            inorderTraversal(node->left, values);
            values.push_back(node->data);
            inorderTraversal(node->right, values);
        }
    }
    
    vector<int> kLargesSmall(TreeNode* root, int k) {
        vector<int> values;
        inorderTraversal(root, values);               // values is now sorted (ascending)
        
        int kth_smallest = values[k - 1];             // kth from the start (0-indexed)
        int kth_largest = values[values.size() - k];  // kth from the end
        
        return {kth_smallest, kth_largest};
    }
};

// ============================================================
// APPROACH 2 (Optimal): Early-termination inorder traversal
//
// LOGIC:
//   Instead of storing ALL values, we traverse and COUNT as we go.
//   The moment our counter reaches k, we've found our answer and
//   can STOP early — no need to traverse the rest of the tree.
//
//   For kth SMALLEST: use standard inorder (L → Root → R)
//     Inorder visits nodes in ascending order, so the kth visited
//     node is the kth smallest. We decrement k as we visit; when
//     k reaches 0, we've found it.
//
//   For kth LARGEST: use reverse inorder (R → Root → L)
//     Reverse inorder visits nodes in DESCENDING order.
//     The kth visited node is the kth largest.
//
//   How early termination works:
//     After finding the result, we set result = node->data and return
//     without recursing into the remaining children. The call stack
//     unwinds quickly because no further work is done.
//
// Intuition:
//   In a BST, the inorder traversal visits nodes in sorted order.
//   We just need to stop at the kth element. For largest, we reverse
//   the traversal direction (right first) to get descending order.
//
// Time:  O(h + k) average — h to reach the first node, then k steps
//         O(n) worst-case (skewed tree)
// Space: O(h) for recursion stack
// ============================================================
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        inorder(root);                    // Start inorder traversal
        return result;
    }

    int kthLargest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        reverse_inorder(root);            // Start reverse inorder
        return result;
    }

    vector<int> kLargesSmall(TreeNode* root, int k) {
        return {kthSmallest(root, k), kthLargest(root, k)};
    }

private:
    int k;          // Remaining count — decremented as we visit nodes
    int result;     // Stores the answer when k reaches 0

    // ── Inorder (Left → Root → Right): yields ASCENDING order ──
    // Used for kth SMALLEST.
    // Each time we visit a node, we decrement k. When k == 0,
    // this node is the kth one visited → it's the kth smallest.
    void inorder(TreeNode* node) {
        if (node != nullptr) {
            inorder(node->left);          // Traverse left subtree first (smaller elements)
            if (--k == 0) {               // Visit current: decrement k; if 0, found answer
                result = node->data;
                return;                   // Early termination — no more recursion needed
            }
            inorder(node->right);         // Traverse right subtree (larger elements)
        }
    }

    // ── Reverse Inorder (Right → Root → Left): yields DESCENDING order ──
    // Used for kth LARGEST.
    // Same logic but we go right first (largest elements come first).
    void reverse_inorder(TreeNode* node) {
        if (node != nullptr) {
            reverse_inorder(node->right); // Traverse right subtree first (larger elements)
            if (--k == 0) {               // Visit current: when k == 0, found answer
                result = node->data;
                return;                   // Early termination
            }
            reverse_inorder(node->left);  // Traverse left subtree (smaller elements)
        }
    }
};

// Main method to demonstrate the function
int main() {
    // Constructing the tree: [3, 1, 4, nullptr, 2]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(4);
    
    Solution solution;
    int k = 1;
    vector<int> result = solution.kLargesSmall(root, k);
    
    // Output the result
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [1, 4]
    
    return 0;
}
