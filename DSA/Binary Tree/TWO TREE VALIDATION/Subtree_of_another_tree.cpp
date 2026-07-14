#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// =========================================================================
// QUESTION: Subtree of Another Tree (LeetCode 572)
//
// Given the roots of two binary trees `root` and `subRoot`, check if
// `subRoot` is a subtree of `root`. A subtree matches the structure AND
// all node values of the original tree, including all descendants.
// A subtree of a tree T is a tree consisting of a node in T and all of
// its descendants.
// =========================================================================

// =========================================================================
// INTUITION & ALGORITHM
// =========================================================================
//
// KEY INSIGHT:
//   A subtree of `root` is just a node in `root` whose entire tree
//   (including all descendants) is IDENTICAL to `subRoot`.
//
//   So the problem reduces to:
//     1. Traverse every node in `root`.
//     2. At each node, check if the tree rooted at that node is
//        exactly the same as `subRoot`.
//     3. If yes → return true.
//
// HOW IT WORKS:
//   isSubtree(root, subRoot):
//     - If root is null → no match possible at this path, return false.
//     - Check if the tree starting at `root` is identical to `subRoot`
//       using `isSameTree(root, subRoot)`.
//     - If yes → return true.
//     - Otherwise, recursively check left and right subtrees.
//     - Return true if EITHER left OR right contains the subtree.
//
//   isSameTree(p, q):
//     - If both are null → identical (both empty), return true.
//     - If one is null and other is not → different, return false.
//     - If values differ → different, return false.
//     - Recursively check left==left AND right==right.
//     - Return true only if BOTH sides match.
//
// WHY THIS WORKS:
//   "Subtree" means the entire sub-structure from some node downward
//   must match `subRoot` exactly. We can't just match values — the
//   shape must match too. `isSameTree` enforces both shape AND values.
//   And we try every node as a potential starting point via traversal.
//
// TIME:  O(m * n)  worst-case where m = nodes in root, n = nodes in subRoot
//        (for each node in root, we may call isSameTree which visits n nodes)
// SPACE: O(m)      recursion stack depth in worst case (skewed tree)
// =========================================================================

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    // Default constructor: value 0, no children
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor with value: no children
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Constructor with value and children
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:

    // ---------------------------------------------------------------
    // Helper: check if two trees are structurally identical
    // ---------------------------------------------------------------
    // Recursively compares:
    //   - Both null?     → identical (base case for leaf children)
    //   - One null?      → not identical (structure differs)
    //   - Values differ? → not identical
    //   - Otherwise → check left subtree AND right subtree both match
    // ---------------------------------------------------------------
    bool isSameTree(TreeNode* p, TreeNode* q) {

        // Both null → reached matching leaves, this path is identical
        if (!p && !q) return true;

        // One is null but the other isn't → structure differs
        if (!p || !q) return false;

        // Values at this node must match
        if (p->val != q->val) return false;

        // Recursively check left and right children
        // BOTH must match for the trees to be identical
        bool leftMatch  = isSameTree(p->left,  q->left);
        bool rightMatch = isSameTree(p->right, q->right);

        return leftMatch && rightMatch;
    }

    // ---------------------------------------------------------------
    // Main: check if subRoot is a subtree of root
    // ---------------------------------------------------------------
    // Traverses every node of `root`. At each node, checks if the
    // tree rooted there is identical to `subRoot`.
    // If any node matches → the subtree exists → return true.
    // ---------------------------------------------------------------
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {

        // Per LeetCode: an empty tree is always a subtree
        if (!subRoot) return true;

        // If root is null (but subRoot is not), no match possible
        if (!root) return false;

        // Check if the tree starting at this node matches subRoot
        if (isSameTree(root, subRoot)) return true;

        // Otherwise, try the left and right subtrees
        // Return true if EITHER side contains the subtree
        return isSubtree(root->left, subRoot) ||
               isSubtree(root->right, subRoot);
    }
};


// =========================================================================
// MAIN — Test Cases
// =========================================================================
//
// Helper function to build a tree from a level-order vector.
// -1 represents null node.
//
// Example:
//   root = [3,4,5,1,2]  represents:
//        3
//       / \
//      4   5
//     / \
//    1   2
//
//   subRoot = [4,1,2]  represents:
//        4
//       / \
//      1   2
//   → true (4-1-2 is a subtree of root)
// =========================================================================

TreeNode* buildTree(vector<int> &nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)nodes.size()) {
        TreeNode* cur = q.front();
        q.pop();

        // Left child
        if (nodes[i] != -1) {
            cur->left = new TreeNode(nodes[i]);
            q.push(cur->left);
        }
        i++;

        // Right child
        if (i < (int)nodes.size() && nodes[i] != -1) {
            cur->right = new TreeNode(nodes[i]);
            q.push(cur->right);
        }
        i++;
    }

    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    cout << "=== Subtree of Another Tree ===\n\n";

    // ---------------------------------------------------------------
    // Test 1: Basic subtree match
    //   root:       3          subRoot:   4
    //              / \                  / \
    //             4   5                1   2
    //            / \
    //           1   2
    //   Expected: true
    // ---------------------------------------------------------------
    {
        vector<int> rootVals    = {3, 4, 5, 1, 2};
        vector<int> subRootVals = {4, 1, 2};

        TreeNode* root    = buildTree(rootVals);
        TreeNode* subRoot = buildTree(subRootVals);

        Solution s;
        bool res = s.isSubtree(root, subRoot);
        cout << "Test 1: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(root);
        deleteTree(subRoot);
    }

    // ---------------------------------------------------------------
    // Test 2: Subtree match with extra depth
    //   root:       3          subRoot:   4
    //              / \                  / \
    //             4   5                1   2
    //            / \
    //           1   2
    //          /
    //         0
    //   The 4-subtree in root has an extra left child (0), so not identical.
    //   Expected: false
    // ---------------------------------------------------------------
    {
        vector<int> rootVals    = {3, 4, 5, 1, 2, -1, -1, 0};
        vector<int> subRootVals = {4, 1, 2};

        TreeNode* root    = buildTree(rootVals);
        TreeNode* subRoot = buildTree(subRootVals);

        Solution s;
        bool res = s.isSubtree(root, subRoot);
        cout << "Test 2: " << (res ? "true" : "false") << " (expected: false)\n";

        deleteTree(root);
        deleteTree(subRoot);
    }

    // ---------------------------------------------------------------
    // Test 3: Single node match
    //   root:   1        subRoot:   1
    //   Expected: true
    // ---------------------------------------------------------------
    {
        vector<int> rootVals    = {1};
        vector<int> subRootVals = {1};

        TreeNode* root    = buildTree(rootVals);
        TreeNode* subRoot = buildTree(subRootVals);

        Solution s;
        bool res = s.isSubtree(root, subRoot);
        cout << "Test 3: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(root);
        deleteTree(subRoot);
    }

    // ---------------------------------------------------------------
    // Test 4: subRoot is null (by problem definition, null is a subtree)
    //   Expected: true
    // ---------------------------------------------------------------
    {
        vector<int> rootVals = {1, 2, 3};
        TreeNode* root = buildTree(rootVals);

        Solution s;
        bool res = s.isSubtree(root, nullptr);
        cout << "Test 4: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(root);
    }

    // ---------------------------------------------------------------
    // Test 5: Value match but structure mismatch
    //   root:   1          subRoot:   1
    //          /                      \
    //         2                        2
    //   Expected: false (left child vs right child = different structure)
    // ---------------------------------------------------------------
    {
        TreeNode* root    = new TreeNode(1, new TreeNode(2), nullptr);
        TreeNode* subRoot = new TreeNode(1, nullptr, new TreeNode(2));

        Solution s;
        bool res = s.isSubtree(root, subRoot);
        cout << "Test 5: " << (res ? "true" : "false") << " (expected: false)\n";

        deleteTree(root);
        deleteTree(subRoot);
    }

    return 0;
}
