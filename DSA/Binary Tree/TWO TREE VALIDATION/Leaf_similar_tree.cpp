/*
 * Problem: "Leaf-Similar Trees"
 * Two binary trees are considered leaf-similar if their leaf value
 * sequences (from left to right) are identical.
 *
 * Below are 2 approaches:
 *   A1: LeafSimilarDFS       – Collect all leaves via DFS, then compare vectors.
 *   A2: LeafSimilarIterator  – Use a stack iterator to get leaves on the fly,
 *                              comparing one leaf at a time without storing all.
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ---------------------------------------------------------------
// Approach 1: DFS (collect all leaves, then compare vectors)
// ---------------------------------------------------------------
/*
 * Intuition:
 *   - Perform a DFS on each tree. When a leaf is found (no left/right
 *     child), record its value in a vector.
 *   - The DFS visits left subtree first, then right, so leaves are
 *     collected in left-to-right order.
 *   - After collecting both sequences, compare the two vectors.
 *
 * Algorithm:
 *   1. Define dfs(root, leafVector):
 *      - If root is null → return.
 *      - If root is a leaf → push root->val into leafVector, return.
 *      - Recurse on root->left, then root->right.
 *   2. leafSimilar(root1, root2):
 *      - Create empty leaf1, leaf2 vectors.
 *      - Call dfs(root1, leaf1) and dfs(root2, leaf2).
 *      - Return leaf1 == leaf2.
 *
 * Why this works:
 *   - Preorder DFS (left before right) naturally gives the correct
 *     left-to-right leaf order.
 *   - Vector equality checks both length and element-wise match.
 *
 * Example:
 *        Tree1            Tree2
 *          3                3
 *         / \              / \
 *        5   1            5   1
 *       / \              / \   \
 *      6   2            6   2   8
 *         / \              / \
 *        7   4            7   4
 *
 *   leaf1 = [6, 7, 4, 1, 8]  (wait, let me trace properly)
 *   Tree1 leaves (left-to-right): 6, 7, 4, 1, 8
 *   Tree1: 3→5→6 (leaf=6), back to 5→2→7 (leaf=7), then 2→4 (leaf=4), back to 3→1→8 (leaf=8)
 *   leaf1 = [6, 7, 4, 8]
 *   Tree2 leaves: 6, 7, 4, 8
 *   leaf2 = [6, 7, 4, 8] → same → true.
 *
 * TC: O(n1 + n2) time to traverse both trees.  |  SC: O(n1 + n2) for leaf vectors.
 */
class LeafSimilarDFS {
public:
    void dfs(TreeNode* root, vector<int>& leaf) {
        if (root == nullptr)
            return;
        if (root->left == nullptr && root->right == nullptr) {
            leaf.push_back(root->val);
            return;
        }
        dfs(root->left, leaf);
        dfs(root->right, leaf);
    }

    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaf1, leaf2;
        dfs(root1, leaf1);
        dfs(root2, leaf2);
        return leaf1 == leaf2;
    }
};

// ---------------------------------------------------------------
// Approach 2: Iterator (stack-based, compare leaves on the fly)
// ---------------------------------------------------------------
/*
 * Intuition:
 *   - Instead of storing all leaves, use an explicit stack to perform
 *     DFS and pause each time we find a leaf (like a generator/iterator).
 *   - Push right child first, then left child onto the stack so that
 *     left subtree is processed first (LIFO: left pushed last = popped first).
 *   - Get one leaf from each tree, compare. If mismatch → false.
 *   - At the end, both stacks must be empty (same number of leaves).
 *
 * Algorithm:
 *   1. getNextLeaf(stack):
 *      - While stack not empty:
 *          - Pop node.
 *          - If leaf → return it.
 *          - Push right child, then left child (right first so left pops first).
 *      - Return nullptr (no more leaves).
 *   2. leafSimilar(root1, root2):
 *      - Push root1 onto s1, root2 onto s2.
 *      - While both stacks non-empty:
 *          - leaf1 = getNextLeaf(s1), leaf2 = getNextLeaf(s2).
 *          - If leaf1->val != leaf2->val → return false.
 *      - Return s1.empty() && s2.empty().
 *
 * Why this works:
 *   - The stack-based DFS simulates the same left-to-right leaf order.
 *   - Early termination: as soon as a leaf mismatch is found, we stop,
 *     without processing the rest of the trees.
 *   - The final empty check ensures both trees have the same number of leaves.
 *
 * Example:
 *   Tree1:  [3,5,6,null,null,2,7,null,null,4,null,null,1,8,null,null]
 *   s1 = [3]
 *   pop 3 → push right(1), push left(5).  s1 = [1, 5]
 *   pop 5 → push right(2), push left(6).  s1 = [1, 2, 6]
 *   pop 6 → leaf, return 6.
 *   Similarly s2 yields 6. Compare 6==6 → continue.
 *   ... continues until all leaves matched.
 *
 * TC: O(n1 + n2) in worst case (all leaves match). Space: O(h1 + h2) for stacks.
 */
class LeafSimilarIterator {
public:
    TreeNode* getNextLeaf(stack<TreeNode*>& st) {
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            if (node->left == nullptr && node->right == nullptr)
                return node;
            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);
        }
        return nullptr;
    }

    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode*> s1, s2;
        s1.push(root1);
        s2.push(root2);

        while (!s1.empty() && !s2.empty()) {
            TreeNode* leaf1 = getNextLeaf(s1);
            TreeNode* leaf2 = getNextLeaf(s2);
            if (leaf1->val != leaf2->val)
                return false;
        }
        return s1.empty() && s2.empty();
    }
};

// ---------------------------------------------------------------
int main() {
    // Sample test
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(1);
    root1->left->left = new TreeNode(6);
    root1->left->right = new TreeNode(2);
    root1->left->right->left = new TreeNode(7);
    root1->left->right->right = new TreeNode(4);
    root1->right->right = new TreeNode(8);

    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(6);
    root2->left->right = new TreeNode(2);
    root2->left->right->left = new TreeNode(7);
    root2->left->right->right = new TreeNode(4);
    root2->right->right = new TreeNode(8);

    LeafSimilarDFS dfsSolver;
    LeafSimilarIterator iterSolver;

    cout << "A1 (DFS): " << (dfsSolver.leafSimilar(root1, root2) ? "Similar" : "Not Similar") << "\n";
    cout << "A2 (Iterator): " << (iterSolver.leafSimilar(root1, root2) ? "Similar" : "Not Similar") << "\n";

    return 0;
}
