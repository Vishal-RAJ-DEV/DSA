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
 SOLUTION 1: DFS (RECURSIVE) APPROACH
================================================================================

 CONCEPT:
 A "good" node is a node whose value is >= all values on the path from root to it.
 We track the maximum value seen so far (`prev`) as we traverse down.
 If current node's value >= prev, it's a good node.

 DRY RUN on this tree:
            3
           / \
          1   4
         /   / \
        3   1   5

 Path from root → each node, and check if node >= max on path:
 ┌──────────┬─────────────────┬──────────┬───────────┐
 │   Node   │  Path from Root │ Max on   │ Good Node?│
 │          │                 │  Path    │           │
 ├──────────┼─────────────────┼──────────┼───────────┤
 │    3     │      [3]        │    3     │  YES (3≥3)│
 │    1     │     [3,1]       │    3     │  NO  (1<3)│
 │    4     │     [3,4]       │    4     │  YES (4≥3)│
 │    3     │    [3,4,3]      │    4     │  NO  (3<4)│
 │    1     │    [3,4,1]      │    4     │  NO  (1<4)│
 │    5     │    [3,4,5]      │    5     │  YES (5≥4)│
 └──────────┴─────────────────┴──────────┴───────────┘
 Total Good Nodes = 3 (nodes: 3, 4, 5)

 DFS TRAVERSAL ORDER (Pre-order: Root → Left → Right):

 Step 1: Visit 3 (root)
         prev=3, 3>=3 → cnt=1, update prev=3
         Go left to 1

 Step 2: Visit 1
         prev=3, 1<3 → cnt=1 (no change)
         prev stays 3 (max(3,1)=3)
         Go left → nullptr, return
         Go right → nullptr, return

 Step 3: Back to 3, go right to 4

 Step 4: Visit 4
         prev=3, 4>=3 → cnt=2, update prev=4
         Go left to 1

 Step 5: Visit 1
         prev=4, 1<4 → cnt=2 (no change)
         Go left → nullptr, return
         Go right → nullptr, return

 Step 6: Back to 4, go right to 5

 Step 7: Visit 5
         prev=4, 5>=4 → cnt=3, update prev=5
         Go left → nullptr, return
         Go right → nullptr, return

 Step 8: Back to 4, back to 3, done.

 FINAL cnt = 3 ✓

 RECURSION TREE DIAGRAM:
                        dfs(3, prev=3)
                       /              \
              dfs(1, prev=3)      dfs(4, prev=3)
              /         \         /            \
         dfs(3,L)    dfs(3,R)  dfs(1,prev=4)  dfs(5,prev=4)
           [null]     [null]    /     \         /      \
                             null    null     null     null

================================================================================
*/
class Solution {
public:
    int cnt = 0;  // Counter for good nodes

    // DFS function: traverses tree, tracking max value seen so far (prev)
    void dfs(TreeNode *root, int prev) {
        // Base case: empty node, stop recursion
        if (root == nullptr) return;

        // Check if current node is "good":
        // A node is good if its value >= maximum value on path from root to it
        if (prev <= root->val) cnt++;

        // Update prev to be the max value seen so far on this path
        // This updated value is passed to children
        prev = max(prev, root->val);

        // Recurse on left subtree (child sees updated max)
        dfs(root->left, prev);
        // Recurse on right subtree (child sees updated max)
        dfs(root->right, prev);
    }

    int goodNodes(TreeNode* root) {
        // Start DFS from root with root's value as initial max
        int prev = root->val;
        dfs(root, prev);
        return cnt;
    }
};

/*
================================================================================
 SOLUTION 2: BFS (LEVEL ORDER / ITERATIVE) APPROACH
================================================================================

 CONCEPT:
 Same logic as DFS, but uses a QUEUE for level-order traversal.
 Each queue entry stores: {node_pointer, max_value_on_path_to_this_node}

 DRY RUN on this tree:
            3
           / \
          1   4
         /   / \
        3   1   5

 Queue operations (format: [node, maxSoFar]):

 ┌─────┬────────────────────────────┬─────┬──────────────────────────────┐
 │Step │ Queue Before Processing    │ Cnt │ Action                       │
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  1  │ [(3,3)]                    │  0  │ Pop (3,3), 3>=3 → cnt=1     │
 │     │                            │     │ newMax=3, push L(1,3),R(4,3)│
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  2  │ [(1,3), (4,3)]             │  1  │ Pop (1,3), 1<3 → cnt=1     │
 │     │                            │     │ newMax=3, push L(3,3)       │
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  3  │ [(4,3), (3,3)]             │  1  │ Pop (4,3), 4>=3 → cnt=2    │
 │     │                            │     │ newMax=4, push L(1,4),R(5,4)│
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  4  │ [(3,3), (1,4), (5,4)]      │  2  │ Pop (3,3), 3<4 → cnt=2     │
 │     │                            │     │ no children                 │
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  5  │ [(1,4), (5,4)]             │  2  │ Pop (1,4), 1<4 → cnt=2     │
 │     │                            │     │ no children                 │
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  6  │ [(5,4)]                    │  2  │ Pop (5,4), 5>=4 → cnt=3    │
 │     │                            │     │ no children                 │
 ├─────┼────────────────────────────┼─────┼──────────────────────────────┤
 │  7  │ [] (empty)                 │  3  │ Queue empty, STOP           │
 └─────┴────────────────────────────┴─────┴──────────────────────────────┘
 FINAL cnt = 3 ✓

 LEVEL-BY-LEVEL VISUAL:

         Level 0:    [3]  ← queue starts here, max=3, 3>=3 ✓ cnt=1
                    /   \
         Level 1: [1]   [4]  ← max=3 for both
                  /     /  \
         Level 2: [3] [1]  [5]  ← max=3,4,4 respectively

 Processing order: 3 → 1 → 4 → 3 → 1 → 5

================================================================================
*/
class Solution {
public:
    int goodNodes(TreeNode* root) {
        int cnt = 0;

        // Queue stores pairs: {node_pointer, max_value_on_path_to_this_node}
        queue<pair<TreeNode*, int>> q;

        // Start with root node, initial max = root's own value
        q.push({root, root->val});

        // Process nodes in level-order (BFS)
        while (!q.empty()) {
            auto it = q.front();  // Get front element
            q.pop();              // Remove from queue

            // Check if current node is "good":
            // Node value >= max value on path from root to this node
            if (it.first->val >= it.second)
                cnt++;

            // Calculate new max to pass to children:
            // It's the max of (path max so far) and (current node's value)
            int newMax = max(it.second, it.first->val);

            // If left child exists, enqueue it with updated max
            if (it.first->left)
                q.push({it.first->left, newMax});

            // If right child exists, enqueue it with updated max
            if (it.first->right)
                q.push({it.first->right, newMax});
        }

        return cnt;
    }
};


int main(){
    return 0;
}