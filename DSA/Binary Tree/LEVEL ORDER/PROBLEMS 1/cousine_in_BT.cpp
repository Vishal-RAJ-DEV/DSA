/*
Problem: LeetCode 993 - Cousins in Binary Tree
Given a binary tree and two node values x and y,
return true if they are cousins, false otherwise.

Cousins definition:
- Same depth (level) in the tree
- Different parents (i.e., not siblings)

The file contains THREE different approaches.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
Approach 1: Level-order BFS + track parent pointers
Algorithm:
1. BFS level by level using queue.
2. For each level, search for x and y among children of current nodes.
3. If a child matches x or y, record its parent (px or py).
4. After processing the entire level:
   - If both x and y found: return true if parents are different (px != py)
   - If only one found: they are at different depths → return false
5. If loop ends without finding both → return false.

Key distinction:
Tracks the PARENT of x and y (not the node itself), since
cousins must have different parents at the same level.
*/
class Solution
{
public:
    bool isCousins(TreeNode *root, int x, int y)
    {
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int sz = q.size();

            TreeNode *px = nullptr;
            TreeNode *py = nullptr;

            while (sz--)
            {
                TreeNode *node = q.front();
                q.pop();

                // Check left child
                if (node->left)
                {
                    if (node->left->val == x) px = node;
                    if (node->left->val == y) py = node;
                    q.push(node->left);
                }

                // Check right child
                if (node->right)
                {
                    if (node->right->val == x) px = node;
                    if (node->right->val == y) py = node;
                    q.push(node->right);
                }
            }

            // Both found at this level → cousins iff different parents
            if (px && py) return px != py;

            // Only one found → different depths → not cousins
            if (px || py) return false;
        }

        return false;
    }
};

/*
Approach 2: Level-order BFS + early sibling check
Algorithm:
1. BFS level by level using queue.
2. For each level, track whether x and y are found (flags).
3. Before checking children, verify they are not siblings:
   - If a node has both left and right children,
     check if those children are (x, y) or (y, x).
   - If yes → same parent → return false immediately.
4. After processing the level:
   - If both found: return true (they're at same depth, not siblings)
   - If only one found: return false (different depths)

Key distinction vs Approach 1:
Instead of tracking parent pointers, it checks the sibling case
directly by looking at each node's left/right children.
Simpler but does an extra check at every node.
*/
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            bool foundX = false, foundY = false;

            while (sz--) {
                TreeNode* node = q.front();
                q.pop();

                if (node->val == x) foundX = true;
                if (node->val == y) foundY = true;

                // If x and y are siblings (same parent), they are NOT cousins
                if (node->left && node->right) {
                    int l = node->left->val;
                    int r = node->right->val;
                    if ((l == x && r == y) || (l == y && r == x))
                        return false;
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Both found at same level → cousins (sibling case already ruled out)
            if (foundX && foundY) return true;

            // Only one found → different depths → not cousins
            if (foundX || foundY) return false;
        }

        return false;
    }
};

/*
Approach 3: DFS with depth & parent tracking
Algorithm:
1. Perform a single DFS traversal of the entire tree.
2. When the target node (x or y) is found:
   - Record its depth (dx/dy)
   - Record its parent (px/py)
3. After traversal completes, check:
   - Same depth (dx == dy)
   - Different parents (px != py)

Key distinction:
BFS approaches process level-by-level and can early-exit.
DFS does a full traversal first, then decides.
DFS is simpler to write but always visits the entire tree,
even if x and y are found early at shallow depths.
*/
class Solution
{
public:
    int dx = -1, dy = -1;
    TreeNode *px = nullptr, *py = nullptr;

    void dfs(TreeNode *node, TreeNode *parent, int depth, int x, int y)
    {
        if (!node) return;

        if (node->val == x)
        {
            dx = depth;
            px = parent;
        }

        if (node->val == y)
        {
            dy = depth;
            py = parent;
        }

        dfs(node->left, node, depth + 1, x, y);
        dfs(node->right, node, depth + 1, x, y);
    }

    bool isCousins(TreeNode *root, int x, int y)
    {
        dfs(root, nullptr, 0, x, y);

        return dx == dy && px != py;
    }
};

/* Summary of all three approaches:

   Approach   | Technique      | Traversal | Early Exit | Space
   -----------+----------------+-----------+------------+-------
   1          | Level-order    | BFS       | Yes        | O(w)
              | + parent track |           |            |
   2          | Level-order    | BFS       | Yes        | O(w)
              | + sibling check|           |            |
   3          | DFS +          | DFS       | No         | O(h)
              | depth & parent |           |            |

   w = max width of tree, h = height of tree
*/

int main()
{
    return 0;
}
