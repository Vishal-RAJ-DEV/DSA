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


/*
================================================================================
 PROBLEM: Maximum Difference Between Node and Ancestor
================================================================================

 Given a binary tree, find the maximum value V such that there exist two nodes
 A and B where V = |A.val - B.val| and A is an ancestor of B.

 An ancestor of a node is any node on the path from root to that node (excluding
 the node itself, but including the root).

 KEY INSIGHT:
 For any root-to-node path, the maximum difference is:
     max_on_path - min_on_path

 So we only need to track the min and max values as we traverse down, and
 at each leaf compute the difference. The answer is the max of all such differences.

================================================================================
 SOLUTION 1: DFS (RECURSIVE) APPROACH
================================================================================

 APPROACH:
 1. Start DFS from root with minVal = maxVal = root->val
 2. At each node, update minVal and maxVal with current node's value
 3. At NULL (leaf's child), return maxVal - minVal (difference on that path)
 4. Return max of left and right subtree results

 DRY RUN on this tree:
            8
           / \
          3   10
         / \    \
        1   6   14
           / \
          4   7

 All root-to-leaf paths and their min/max/diff:
 ┌───────────────────────┬─────┬─────┬──────┬────────────────────┐
 │       Path            │ Min │ Max │ Diff │                    │
 ├───────────────────────┼─────┼─────┼──────┼────────────────────┤
 │ 8 → 3 → 1             │  1  │  8  │  7   │                    │
 │ 8 → 3 → 6 → 4         │  3  │  8  │  5   │                    │
 │ 8 → 3 → 6 → 7         │  3  │  8  │  5   │                    │
 │ 8 → 10 → 14           │  8  │ 14  │  6   │                    │
 └───────────────────────┴─────┴─────┴──────┴────────────────────┘
 Maximum Difference = 7 (from path 8→3→1, where |8-1|=7)

 DFS RECURSION TREE:
 ┌─────────────────────────────────────────────────────────────────┐
 │                                                                 │
 │  dfs(8, min=8, max=8)                                          │
 │     │                                                           │
 │     ├── dfs(3, min=3, max=8)          ← min updated: min(8,3)=3│
 │     │      │                                                    │
 │     │      ├── dfs(1, min=1, max=8)   ← min updated: min(3,1)=1│
 │     │      │      │                                             │
 │     │      │      ├── dfs(NULL) → return 8-1 = 7               │
 │     │      │      └── dfs(NULL) → return 8-1 = 7               │
 │     │      │      return max(7,7) = 7                          │
 │     │      │                                                    │
 │     │      └── dfs(6, min=3, max=8)   ← min stays 3            │
 │     │             │                                             │
 │     │             ├── dfs(4, min=3, max=8) ← min stays 3       │
 │     │             │      │                                      │
 │     │             │      ├── dfs(NULL) → return 8-3 = 5        │
 │     │             │      └── dfs(NULL) → return 8-3 = 5        │
 │     │             │      return max(5,5) = 5                   │
 │     │             │                                             │
 │     │             └── dfs(7, min=3, max=8) ← min stays 3       │
 │     │                    │                                      │
 │     │                    ├── dfs(NULL) → return 8-3 = 5        │
 │     │                    └── dfs(NULL) → return 8-3 = 5        │
 │     │                    return max(5,5) = 5                   │
 │     │             return max(5,5) = 5                          │
 │     │      return max(7,5) = 7                                 │
 │     │                                                           │
 │     └── dfs(10, min=8, max=10)         ← max updated: max(8,10)=10
 │            │                                                    │
 │            └── dfs(14, min=8, max=14)  ← max updated: max(10,14)=14
 │                   │                                             │
 │                   ├── dfs(NULL) → return 14-8 = 6              │
 │                   └── dfs(NULL) → return 14-8 = 6              │
 │                   return max(6,6) = 6                          │
 │            return max(6) = 6                                   │
 │     return max(7,6) = 7                                        │
 │                                                                 │
 └─────────────────────────────────────────────────────────────────┘

 FINAL ANSWER = 7 ✓

================================================================================
*/
// Complexity
// Time: O(N) — every node is visited once.
// Space: O(H) — recursion stack, where H is tree height.
class Solution {
public:

    // DFS function: returns max difference found in subtree rooted at 'root'
    // minVal = minimum value on path from root to current node
    // maxVal = maximum value on path from root to current node
    int dfs(TreeNode* root, int minVal, int maxVal) {

        // Base case: reached past a leaf (NULL child)
        // Return the difference between max and min on this complete path
        if (root == NULL) {
            return maxVal - minVal;
        }

        // Update min and max with current node's value
        // These represent the extremes on the path from tree root to this node
        minVal = min(minVal, root->val);
        maxVal = max(maxVal, root->val);

        // Recurse on left and right subtrees
        // Each subtree returns the max difference found within it
        int left = dfs(root->left, minVal, maxVal);
        int right = dfs(root->right, minVal, maxVal);

        // Return the larger of the two subtree results
        return max(left, right);
    }

    int maxAncestorDiff(TreeNode* root) {
        // Start DFS with both min and max set to root's value
        // As we go deeper, these will be updated
        return dfs(root, root->val, root->val);
    }
};

/*
================================================================================
 SOLUTION 2: BFS (LEVEL ORDER / ITERATIVE) APPROACH
================================================================================

 APPROACH:
 1. Use a queue to store tuples: {node, minSoFar, maxSoFar}
 2. For each node processed, calculate maxVal - minVal and update answer
 3. Push children with updated min/max values
 4. Continue until queue is empty

 DRY RUN on this tree:
            8
           / \
          3   10
         / \    \
        1   6   14
           / \
          4   7

 Queue operations (format: [node, min, max]):

 ┌─────┬──────────────────────────────────┬─────┬──────────────────────────────┐
 │Step │ Queue Before Processing          │Ans  │ Action                       │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  1  │ [(8,8,8)]                        │  0  │ Pop (8,8,8), diff=0, ans=0  │
 │     │                                  │     │ push L(3,3,8), R(10,8,10)   │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  2  │ [(3,3,8), (10,8,10)]             │  0  │ Pop (3,3,8), diff=5, ans=5  │
 │     │                                  │     │ push L(1,1,8), R(6,3,8)     │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  3  │ [(10,8,10), (1,1,8), (6,3,8)]    │  5  │ Pop (10,8,10), diff=2, ans=5│
 │     │                                  │     │ push R(14,8,14)             │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  4  │ [(1,1,8), (6,3,8), (14,8,14)]    │  5  │ Pop (1,1,8), diff=7, ans=7  │
 │     │                                  │     │ no children                 │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  5  │ [(6,3,8), (14,8,14)]             │  7  │ Pop (6,3,8), diff=5, ans=7  │
 │     │                                  │     │ push L(4,3,8), R(7,3,8)     │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  6  │ [(14,8,14), (4,3,8), (7,3,8)]    │  7  │ Pop (14,8,14), diff=6, ans=7│
 │     │                                  │     │ no children                 │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  7  │ [(4,3,8), (7,3,8)]               │  7  │ Pop (4,3,8), diff=5, ans=7  │
 │     │                                  │     │ no children                 │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  8  │ [(7,3,8)]                        │  7  │ Pop (7,3,8), diff=5, ans=7  │
 │     │                                  │     │ no children                 │
 ├─────┼──────────────────────────────────┼─────┼──────────────────────────────┤
 │  9  │ [] (empty)                       │  7  │ Queue empty, STOP           │
 └─────┴──────────────────────────────────┴─────┴──────────────────────────────┘
 FINAL ans = 7 ✓

 LEVEL-BY-LEVEL VISUAL:

         Level 0:    [8]          min=8, max=8, diff=0
                    /   \
         Level 1: [3]   [10]      diffs: |8-3|=5, |10-8|=2
                  / \      \
         Level 2: [1] [6]  [14]   diffs: |8-1|=7, |8-3|=5, |14-8|=6
                       / \
         Level 3:    [4] [7]      diffs: |8-3|=5, |8-3|=5

 Maximum difference found: 7 (at node 1, path 8→3→1)

================================================================================
*/
class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {

        // Queue stores tuples: {node_pointer, min_value_on_path, max_value_on_path}
        queue<tuple<TreeNode*, int, int>> q;

        // Start with root, min and max both = root's value
        q.push({root, root->val, root->val});

        int ans = 0;  // Tracks maximum difference found

        // Process nodes in level-order (BFS)
        while (!q.empty()) {

            auto it = q.front();  // Get front element
            q.pop();              // Remove from queue

            // Extract tuple values
            TreeNode* node = get<0>(it);
            int minVal = get<1>(it);    // Min value on path from root to this node
            int maxVal = get<2>(it);    // Max value on path from root to this node

            // Update answer with difference for current path
            // This is the max difference between any ancestor and current node
            ans = max(ans, maxVal - minVal);

            // Process left child: update min/max and enqueue
            if (node->left) {
                int newMin = min(minVal, node->left->val);  // Update min with left child
                int newMax = max(maxVal, node->left->val);  // Update max with left child

                q.push({
                    node->left,
                    newMin,     // New min for left subtree path
                    newMax      // New max for left subtree path
                });
            }

            // Process right child: update min/max and enqueue
            if (node->right) {
                int newMin = min(minVal, node->right->val);  // Update min with right child
                int newMax = max(maxVal, node->right->val);  // Update max with right child

                q.push({
                    node->right,
                    newMin,     // New min for right subtree path
                    newMax      // New max for right subtree path
                });
            }
        }

        return ans;
    }
};

int main(){
    return 0;
}