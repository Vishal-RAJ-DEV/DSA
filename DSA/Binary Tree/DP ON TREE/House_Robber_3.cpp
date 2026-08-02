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
    ===========================================================================
                        TREE DP (POSTORDER DFS)

    Every node returns TWO values.

        first  -> Maximum money if we DO NOT rob this node.
        second -> Maximum money if we DO rob this node.

    Why?

    Because the parent needs both possibilities to make its decision.

    ---------------------------------------------------------------------------

    Suppose current node is X.

                 X
               /   \
            Left   Right

    Assume children already solved.

    Left returns

        {notRobLeft , robLeft}

    Right returns

        {notRobRight , robRight}

    ---------------------------------------------------------------------------

    CASE 1 : Rob current node

        If we rob current node,

        we CANNOT rob its children.

        Therefore,

        robCurrent

        = current value
        + left.notRob
        + right.notRob

    ---------------------------------------------------------------------------

    CASE 2 : Don't rob current node

        Now every child becomes independent.

        Each child may

            Rob itself

                OR

            Not rob itself

        Choose whichever gives more money.

        notRobCurrent

        = max(left.rob , left.notRob)
        + max(right.rob , right.notRob)

    ---------------------------------------------------------------------------

    Return

        {notRobCurrent , robCurrent}

    This is exactly the DP state of the current subtree.

    ===========================================================================
    */

class Solution {
public:

    // Returns a pair:
    // first  -> Maximum money if the current node IS robbed.
    // second -> Maximum money if the current node is NOT robbed.
    pair<int, int> dfs(TreeNode* root) {

        // Base case:
        // An empty subtree contributes 0 whether we rob it or not.
        if (root == nullptr)
            return {0, 0};

        // Solve the left and right subtrees first (Postorder DFS).
        // Their DP states are needed to compute the current node's state.
        pair<int, int> left = dfs(root->left);
        pair<int, int> right = dfs(root->right);

        // ---------------------------------------------------------
        // Case 1: Rob the current node.
        //
        // If we rob the current node, we CANNOT rob its immediate
        // children. Therefore, we can only take the "notRob"
        // values returned by both children.
        // ---------------------------------------------------------
        int robCurrent =
            root->val
            + left.second
            + right.second;

        // ---------------------------------------------------------
        // Case 2: Do NOT rob the current node.
        //
        // Now each child is free to either rob itself or not rob
        // itself. For each child, choose whichever option gives
        // the maximum amount.
        // ---------------------------------------------------------
        int notRobCurrent =
            max(left.first, left.second)
            + max(right.first, right.second);

        // Return the DP state of the current subtree.
        return {robCurrent, notRobCurrent};
    }

    int rob(TreeNode* root) {

        // Each node computes two DP states:
        // 1. Maximum money if this node is robbed.
        // 2. Maximum money if this node is not robbed.
        //
        // Since a parent's answer depends on its children's states,
        // we solve the tree using Postorder DFS
        // (Left -> Right -> Node).

        pair<int, int> ans = dfs(root);

        // The root may be robbed or may not be robbed.
        // Return the better of the two possibilities.
        return max(ans.first, ans.second);
    }
};


int main(){
    return 0;
}