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
===============================================================================
                LeetCode 513 - Find Bottom Left Tree Value
                          DFS (Preorder Traversal)
===============================================================================

IDEA
====

We need to find:

    1. The deepest node.
    2. If multiple nodes exist at the deepest level,
       choose the LEFTMOST one.

----------------------------------------------------------------------------
Key Observation
----------------------------------------------------------------------------

Suppose we perform a DFS traversal.

The order will be:

                Root
               /    \
            Left    Right

Since we ALWAYS visit the left subtree before the right subtree,

the FIRST node that we encounter at every depth is automatically
the LEFTMOST node of that depth.

Example

                1
              /   \
             2     3
            /     / \
           4     5   6
                /
               7

Traversal order:

1
2
4
3
5
7
6

Notice something:

Depth 0:
First node = 1

Depth 1:
First node = 2

Depth 2:
First node = 4

Depth 3:
First node = 7

These first nodes are exactly the leftmost nodes of every level.

----------------------------------------------------------------------------
Main Idea
----------------------------------------------------------------------------

Maintain two variables:

maxDepth
---------
The deepest level we have seen so far.

answer
-------
The value of the first node discovered at maxDepth.

Whenever we reach a node,

if(currentDepth > maxDepth)

then

    maxDepth = currentDepth
    answer = node->val

We DO NOT use >=.

Reason:

Suppose

          1
        /   \
       2     3
      /     /
     4     5

Traversal

1
2
4
3
5

At depth = 2

First node = 4

Later we also visit 5.

If we used

depth >= maxDepth

then

5 would overwrite 4

which is WRONG.

Using

depth > maxDepth

means

ONLY THE FIRST NODE AT EVERY DEPTH
is stored.

----------------------------------------------------------------------------
Why does "first node" mean "leftmost node"?
----------------------------------------------------------------------------

Because recursion always does

dfs(left)

before

dfs(right)

The left subtree is completely explored before the right subtree.

Therefore,

the first node discovered at a depth must lie as far left as possible.

----------------------------------------------------------------------------
Complexity
----------------------------------------------------------------------------

Time  : O(N)

Every node visited exactly once.

Space : O(H)

H = Height of tree

Recursion stack.
===============================================================================
*/

class Solution {
public:

    // Stores the maximum depth visited so far.
    int maxDepth = -1;

    // Stores the answer.
    int ans = 0;

    // ------------------------------------------------------------
    // DFS Function
    //
    // node  -> current node
    // depth -> current depth
    // ------------------------------------------------------------
    void dfs(TreeNode* node, int depth)
    {
        // Base Case
        // If node is NULL, simply return.
        if(node == nullptr)
            return;

        // --------------------------------------------------------
        // If this is the first node we have reached at a deeper level,
        // update the answer.
        //
        // Since DFS always explores the LEFT subtree before the RIGHT subtree,
        // the first node encountered at any depth is guaranteed to be the
        // leftmost node of that level.
        // --------------------------------------------------------
        if(depth > maxDepth)
        {
            maxDepth = depth;
            ans = node->val;
        }

        // Explore the left subtree first.
        // This ensures that if multiple nodes exist at the same depth,
        // the leftmost node is visited before any right-side node.
        dfs(node->left, depth + 1);

        // Explore the right subtree after the left subtree.
        // If a node in the right subtree has the same depth as an already
        // visited left-side node, it will NOT replace the answer because
        // we only update when depth > maxdepth (strictly greater).
        dfs(node->right, depth + 1);
    }

    int findBottomLeftValue(TreeNode* root)
    {
        dfs(root, 0);

        return ans;
    }
};

/*
===============================================================================
                LeetCode 513 - Find Bottom Left Tree Value
                        BFS (Level Order Traversal)
===============================================================================

IDEA
====

We process the tree level by level.

Example

                1
              /   \
             2     3
            /     / \
           4     5   6
                /
               7

Level 0

1

Level 1

2 3

Level 2

4 5 6

Level 3

7

----------------------------------------------------------------------------
Observation
----------------------------------------------------------------------------

For every level,

the FIRST node in the queue

is always the LEFTMOST node of that level.

So

At every level

answer = queue.front()->val

When BFS finishes,

the last stored answer is the leftmost node of the deepest level.

----------------------------------------------------------------------------
Complexity
----------------------------------------------------------------------------

Time

O(N)

Space

O(W)

W = Maximum width of tree.
===============================================================================
*/

class Solution {
public:

    int findBottomLeftValue(TreeNode* root)
    {
        queue<TreeNode*> q;

        // Start BFS with root.
        q.push(root);

        int ans = root->val;

        while(!q.empty())
        {
            // Number of nodes in the current level.
            int size = q.size();

            // ------------------------------------------------------
            // The FIRST node in this level is the LEFTMOST node.
            // Save it.
            // ------------------------------------------------------
            ans = q.front()->val;

            // Process the entire current level.
            while(size--)
            {
                TreeNode* node = q.front();
                q.pop();

                // Push left child first.
                if(node->left)
                    q.push(node->left);

                // Then push right child.
                if(node->right)
                    q.push(node->right);
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}