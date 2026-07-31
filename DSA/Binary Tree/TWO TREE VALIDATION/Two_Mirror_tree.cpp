#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// =========================================================================
// QUESTION: Check if Two Trees are Mirrors of Each Other
//
// Given the roots of two binary trees, determine if they are mirror
// images of each other. Two trees are mirrors when:
//   - Root values are equal.
//   - Left subtree of tree A is a mirror of right subtree of tree B.
//   - Right subtree of tree A is a mirror of left subtree of tree B.
// =========================================================================

// =========================================================================
// INTUITION & ALGORITHM
// =========================================================================
//
// WHAT IS A MIRROR?
//   Imagine holding a mirror vertically beside the first tree. The
//   reflection you see should match the second tree exactly.
//
//   For two trees to be mirror images:
//     1. Their root values must be the same.
//     2. The LEFT child of Tree A must mirror the RIGHT child of Tree B.
//     3. The RIGHT child of Tree A must mirror the LEFT child of Tree B.
//
//   This is a recursive definition that continues all the way down to
//   the leaves.
//
// RECURSIVE LOGIC (areMirror(a, b)):
//   - Base case 1: BOTH are null → they are mirrors (both empty). → true
//   - Base case 2: ONE is null, other is not → not mirrors.       → false
//   - Base case 3: values differ → not mirrors.                   → false
//   - Recursive case:
//       areMirror(a->left,  b->right)  ← left of A vs right of B
//       AND
//       areMirror(a->right, b->left)   ← right of A vs left of B
//
// VISUALIZATION:
//
//     Tree A:         Tree B (mirror of A):
//         1                1
//        / \              / \
//       2   3            3   2
//      / \   \         /   / \
//     4   5   7       7   5   4
//
//   Check: a->left (2) vs b->right (2)
//          a->right (3) vs b->left (3)
//          ...recursively continues
//
// TIME:  O(n)  where n = min(size of a, size of b)
// SPACE: O(h)  recursion stack, h = height of tree
// =========================================================================

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
    Node(int x, Node* l, Node* r) : data(x), left(l), right(r) {}
};

class Solution {
public:

    // ---------------------------------------------------------------
    // Check if two trees are mirror images of each other
    // ---------------------------------------------------------------
    bool areMirror(Node* a, Node* b) {

        // Both null → both empty trees are trivially mirrors
        if (a == nullptr && b == nullptr)
            return true;

        // One null, other not → structure differs, cannot be mirrors
        if (a == nullptr || b == nullptr)
            return false;

        // Root values must match
        if (a->data != b->data)
            return false;

        // KEY MIRROR CONDITION:
        //   Left of A must mirror Right of B
        //   AND
        //   Right of A must mirror Left of B
        //
        //   This is the CROSS comparison that defines mirror symmetry.
        //   (Unlike "same tree" where we compare left-left and right-right)
        bool leftRight = areMirror(a->left, b->right);
        bool rightLeft = areMirror(a->right, b->left);

        return leftRight && rightLeft;
    }
};


// =========================================================================
// MAIN — Test Cases
// =========================================================================
//
// Helper to build a level-order tree from vector (-1 = null)
//
// Example:
//   tree = [1, 2, 3, 4, 5, -1, 7]
//        1
//       / \
//      2   3
//     / \   \
//    4   5   7
// =========================================================================

Node* buildTree(vector<int> &nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;

    Node* root = new Node(nodes[0]);
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)nodes.size()) {
        Node* cur = q.front();
        q.pop();

        if (nodes[i] != -1) {
            cur->left = new Node(nodes[i]);
            q.push(cur->left);
        }
        i++;

        if (i < (int)nodes.size() && nodes[i] != -1) {
            cur->right = new Node(nodes[i]);
            q.push(cur->right);
        }
        i++;
    }

    return root;
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    cout << "=== Check Mirror Trees ===\n\n";

    // ---------------------------------------------------------------
    // Test 1: Two trees that ARE mirrors
    //
    //     Tree A:         Tree B (mirror):
    //         1                1
    //        / \              / \
    //       2   3            3   2
    //      / \   \         /   / \
    //     4   5   7       7   5   4
    //
    //   Expected: true
    // ---------------------------------------------------------------
    {
        // Build Tree A
        vector<int> valsA = {1, 2, 3, 4, 5, -1, 7};
        Node* treeA = buildTree(valsA);

        // Build Tree B (mirror image of A)
        // Level order of mirrored tree: [1, 3, 2, 7, 5, 4]
        vector<int> valsB = {1, 3, 2, 7, -1, 5, 4};
        Node* treeB = buildTree(valsB);

        Solution s;
        bool res = s.areMirror(treeA, treeB);
        cout << "Test 1: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(treeA);
        deleteTree(treeB);
    }

    // ---------------------------------------------------------------
    // Test 2: Two trees that ARE NOT mirrors (values differ)
    //
    //     Tree A:         Tree B:
    //         1                1
    //        / \              / \
    //       2   3            9   2
    //
    //   Expected: false (2 != 9 at the cross-check position)
    // ---------------------------------------------------------------
    {
        Node* treeA = new Node(1, new Node(2), new Node(3));
        Node* treeB = new Node(1, new Node(9), new Node(2));

        Solution s;
        bool res = s.areMirror(treeA, treeB);
        cout << "Test 2: " << (res ? "true" : "false") << " (expected: false)\n";

        deleteTree(treeA);
        deleteTree(treeB);
    }

    // ---------------------------------------------------------------
    // Test 3: Two trees that ARE mirrors (symmetric single nodes)
    //
    //     Tree A:   1        Tree B:   1
    //
    //   Expected: true
    // ---------------------------------------------------------------
    {
        Node* treeA = new Node(1);
        Node* treeB = new Node(1);

        Solution s;
        bool res = s.areMirror(treeA, treeB);
        cout << "Test 3: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(treeA);
        deleteTree(treeB);
    }

    // ---------------------------------------------------------------
    // Test 4: Both trees empty
    //
    //   Expected: true
    // ---------------------------------------------------------------
    {
        Solution s;
        bool res = s.areMirror(nullptr, nullptr);
        cout << "Test 4: " << (res ? "true" : "false") << " (expected: true)\n";
    }

    // ---------------------------------------------------------------
    // Test 5: Structure differs (one has extra child)
    //
    //     Tree A:   1        Tree B:   1
    //              /                  \
    //             2                    2
    //
    //   Expected: false (left child of A vs right child of B are
    //   both "2" but the other sides: right of A is null, left of B
    //   is null → that cross-pair matches. But wait, let's trace:
    //     areMirror(A, B):
    //       1==1 ok
    //       areMirror(A->left=2, B->right=2):
    //         2==2 ok
    //         areMirror(2->left=null, 2->right=null) → true
    //         areMirror(2->right=null, 2->left=null) → true
    //         → true
    //       areMirror(A->right=null, B->left=null) → true
    //     → true!
    //   Actually this IS a mirror! Let's use a different case:
    //
    //     Tree A:   1        Tree B:   1
    //              /                  \
    //             2                    3
    //   Expected: false (2 != 3)
    // ---------------------------------------------------------------
    {
        Node* treeA = new Node(1, new Node(2), nullptr);
        Node* treeB = new Node(1, nullptr, new Node(3));

        Solution s;
        bool res = s.areMirror(treeA, treeB);
        cout << "Test 5: " << (res ? "true" : "false") << " (expected: false)\n";

        deleteTree(treeA);
        deleteTree(treeB);
    }

    // ---------------------------------------------------------------
    // Test 6: Same tree (not mirror unless symmetric!)
    //
    //     Tree A = Tree B =     1
    //                          / \
    //                         2   2
    //   A symmetric tree IS its own mirror.
    //   Expected: true
    // ---------------------------------------------------------------
    {
        Node* tree = new Node(1, new Node(2), new Node(2));

        Solution s;
        bool res = s.areMirror(tree, tree);
        cout << "Test 6: " << (res ? "true" : "false") << " (expected: true)\n";

        deleteTree(tree);
    }

    return 0;
}
