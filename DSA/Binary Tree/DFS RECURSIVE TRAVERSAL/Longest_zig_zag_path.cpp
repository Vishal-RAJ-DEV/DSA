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
 PROBLEM: Longest ZigZag Path in a Binary Tree
================================================================================

 A zigzag path follows these rules:
 - Start from any node
 - Move LEFT then RIGHT then LEFT then RIGHT... (alternating)
 - OR move RIGHT then LEFT then RIGHT then LEFT... (alternating)
 - Each move to a child counts as 1 step

 Example:
         1
          \
           2
          / \
         3   4
        /     \
       5       6
              / \
             7   8

 Longest zigzag: 1 → 2 → 3 → (can't go further) = length 2
 Or:            1 → 2 → 4 → 6 → 7 = length 3

================================================================================
 SOLUTION 1: DIRECTION-BASED DFS
================================================================================

 APPROACH:
 - Track `direction`: 0 = last move was LEFT, 1 = last move was RIGHT
 - Track `length`: current zigzag path length
 - If last move was LEFT, next must be RIGHT to continue zigzag
 - If last move was RIGHT, next must be LEFT to continue zigzag
 - Can RESTART path by going in same direction (length resets to 1)

 DRY RUN on this tree:
         1
          \
           2
          / \
         3   4
        /
       5

 DFS CALLS:

 dfs(root->left=3, dir=0, len=1)   ← Starting left from root
    │  ans = max(0, 1) = 1
    │  dir=0 (last was LEFT), so:
    │  ├── dfs(5, dir=1, len=2)     ← Continue: go RIGHT
    │  │      ans = max(1, 2) = 2
    │  │      dir=1, so:
    │  │      ├── dfs(null) → return
    │  │      └── dfs(null) → return
    │  └── dfs(null, dir=0, len=1)  ← Restart: go LEFT (null)
    │         → return

 dfs(root->right=4, dir=1, len=1)  ← Starting right from root
    │  ans = max(2, 1) = 2
    │  dir=1 (last was RIGHT), so:
    │  ├── dfs(null, dir=0, len=2)  ← Continue: go LEFT (null)
    │  │      → return
    │  └── dfs(null, dir=1, len=1)  ← Restart: go RIGHT (null)
    │         → return

 FINAL ans = 2 ✓

 VISUAL OF DIRECTION LOGIC:

         1
          \
           2  ← from here, we can start:
          / \    LEFT to 3 (dir=0, len=1)
         3   4   RIGHT to 4 (dir=1, len=1)
        /
       5  ← from 3 (dir=0, must go RIGHT to continue)
            RIGHT to 5 (dir=1, len=2) ✓ continues zigzag

================================================================================
*/
class Solution {
public:
    int ans = 0;  // Tracks maximum zigzag length found

    // DFS with direction tracking
    // direction: 0 = last move was LEFT, 1 = last move was RIGHT
    // length: current zigzag path length
    void dfs(TreeNode* node, int direction, int length) {
        if (node == nullptr)
            return;

        // Update maximum length found so far
        ans = max(ans, length);

        if (direction == 0) {
            // Previous move was LEFT
            // To CONTINUE zigzag: must go RIGHT next
            dfs(node->right, 1, length + 1);

            // To RESTART path: go LEFT (same direction, reset length)
            dfs(node->left, 0, 1);
        }
        else {
            // Previous move was RIGHT
            // To CONTINUE zigzag: must go LEFT next
            dfs(node->left, 0, length + 1);

            // To RESTART path: go RIGHT (same direction, reset length)
            dfs(node->right, 1, 1);
        }
    }

    int longestZigZag(TreeNode* root) {
        if (root == nullptr)
            return 0;

        // Start zigzag paths from root in both directions
        // Going LEFT from root: direction=0, length=1
        dfs(root->left, 0, 1);
        // Going RIGHT from root: direction=1, length=1
        dfs(root->right, 1, 1);

        return ans;
    }
};

/*
================================================================================
 SOLUTION 2: LEFT/RIGHT PARAMETER DFS (ELEGANT APPROACH)
================================================================================

 KEY INSIGHT:
 Instead of tracking "direction" and "length" separately, we track TWO lengths:
   - `left`  = length of zigzag path that ENDED with a LEFT move to this node
   - `right` = length of zigzag path that ENDED with a RIGHT move to this node

 WHY THIS WORKS:
 At each node, we know:
   1. How long the zigzag path is if we arrived from the RIGHT (left parameter)
   2. How long the zigzag path is if we arrived from the LEFT (right parameter)

 When we move to a child:
   - Moving LEFT:  new_left = right + 1 (continue zigzag from right), new_right = 0 (reset)
   - Moving RIGHT: new_right = left + 1 (continue zigzag from left), new_left = 0 (reset)

 THE MAGIC OF SWAPPING:
   dfs(node->left, right + 1, 0)
   dfs(node->right, 0, left + 1)

   Notice: when going LEFT, we use `right + 1` (not left + 1)
   This is because to continue a zigzag, the PREVIOUS move must have been RIGHT!

 HOW LEFT AND RIGHT PARAMETERS WORK:

 ┌─────────────────────────────────────────────────────────────────────────────┐
 │                        STATE AT EACH NODE                                  │
 │                                                                             │
 │   left  = length of zigzag if last move was LEFT  (came from right child) │
 │   right = length of zigzag if last move was RIGHT (came from left child)  │
 │                                                                             │
 │   Example: At node 3 with left=5, right=0                                 │
 │   - There's a zigzag of length 5 ending at node 3 via a LEFT move         │
 │   - There's no zigzag ending at node 3 via a RIGHT move                   │
 └─────────────────────────────────────────────────────────────────────────────┘

 DRY RUN on this tree:
         1
          \
           2
          / \
         3   4
        /     \
       5       6
              / \
             7   8

 DFS TRAVERSAL:

 dfs(1, left=0, right=0)
    │  ans = max(0, 0, 0) = 0
    │
    │  Moving LEFT to 2:  new_left = right+1 = 0+1 = 1, new_right = 0
    ├── dfs(2, left=1, right=0)
    │      │  ans = max(0, 1, 0) = 1
    │      │
    │      │  Moving LEFT to 3:  new_left = right+1 = 0+1 = 1, new_right = 0
    │      ├── dfs(3, left=1, right=0)
    │      │      │  ans = max(1, 1, 0) = 1
    │      │      │
    │      │      │  Moving LEFT to 5:  new_left = right+1 = 0+1 = 1, new_right = 0
    │      │      ├── dfs(5, left=1, right=0)
    │      │      │      │  ans = max(1, 1, 0) = 1
    │      │      │      │  Moving LEFT to null → return
    │      │      │      │  Moving RIGHT to null → return
    │      │      │
    │      │      │  Moving RIGHT to null → return
    │      │
    │      │  Moving RIGHT to 4:  new_right = left+1 = 1+1 = 2, new_left = 0
    │      └── dfs(4, left=0, right=2)
    │             │  ans = max(1, 0, 2) = 2
    │             │
    │             │  Moving LEFT to null → return
    │             │
    │             │  Moving RIGHT to 6:  new_right = left+1 = 0+1 = 1, new_left = 0
    │             └── dfs(6, left=0, right=1)
    │                    │  ans = max(2, 0, 1) = 2
    │                    │
    │                    │  Moving LEFT to 7:  new_left = right+1 = 1+1 = 2, new_right = 0
    │                    ├── dfs(7, left=2, right=0)
    │                    │      │  ans = max(2, 2, 0) = 2
    │                    │      │  Moving LEFT to null → return
    │                    │      │  Moving RIGHT to null → return
    │                    │
    │                    │  Moving RIGHT to 8:  new_right = left+1 = 0+1 = 1, new_left = 0
    │                    └── dfs(8, left=0, right=1)
    │                           │  ans = max(2, 0, 1) = 2
    │                           │  Moving LEFT to null → return
    │                           │  Moving RIGHT to null → return

 FINAL ans = 2 ✓

 THE SWAP PATTERN VISUALIZED:

         1
          \
           2  ← (left=1, right=0)
          / \
   left=1↓   ↓right=2
         3   4
        /     \
   left=1↓     ↓right=1
       5       6
              / \
        left=2↓   ↓right=1
            7   8

 Notice the PATTERN:
 ┌─────────────────────────────────────────────────────────────────┐
 │  When moving LEFT:                                              │
 │    new_left = right + 1   ← SWAP! Use right to continue        │
 │    new_right = 0          ← Reset right                        │
 │                                                                 │
 │  When moving RIGHT:                                             │
 │    new_right = left + 1   ← SWAP! Use left to continue         │
 │    new_left = 0           ← Reset left                         │
 └─────────────────────────────────────────────────────────────────┘

 WHY SWAP?
 Because zigzag ALTERNATES! If you just went LEFT, the next zigzag
 move must be RIGHT. So the "left" counter at child comes from
 "right" counter at parent (the path that ended with RIGHT).

================================================================================
*/
class Solution {
public:
    int ans = 0;  // Tracks maximum zigzag length found

    // DFS tracking two path lengths:
    // left  = length of zigzag path ending with a LEFT move to this node
    // right = length of zigzag path ending with a RIGHT move to this node
    void dfs(TreeNode* node, int left, int right) {
        if (node == nullptr)
            return;

        // Update maximum with both left and right path lengths
        ans = max({ans, left, right});

        // Move LEFT to left child:
        // To continue zigzag, previous move must have been RIGHT
        // So new_left = right + 1 (extend the path that ended with RIGHT)
        // Reset new_right = 0 (can't end with RIGHT if we just moved LEFT)
        dfs(node->left, right + 1, 0);

        // Move RIGHT to right child:
        // To continue zigzag, previous move must have been LEFT
        // So new_right = left + 1 (extend the path that ended with LEFT)
        // Reset new_left = 0 (can't end with LEFT if we just moved RIGHT)
        dfs(node->right, 0, left + 1);
    }

    int longestZigZag(TreeNode* root) {
        // Start from root with no moves yet (left=0, right=0)
        dfs(root, 0, 0);
        return ans;
    }
};


int main(){
    return 0;
}