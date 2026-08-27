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


class Solution {
public:
    int moves = 0;

    /*
     * PROBLEM: Distribute coins in a binary tree so every node has exactly 1 coin.
     * Each move = passing 1 coin across 1 edge. Find minimum moves.
     *
     * KEY IDEA (Bottom-Up DFS):
     * -------------------------
     * For each node, we ask: "Does my subtree have excess coins or a deficit?"
     * This is called the "balance".
     *
     *   balance = (coins in subtree) - (nodes in subtree)
     *
     * If balance > 0 → subtree has EXTRA coins, send them UP to parent.
     * If balance < 0 → subtree NEEDS coins, parent must send DOWN.
     * If balance = 0 → subtree is perfectly balanced, nothing moves.
     *
     * Every coin that crosses an edge counts as 1 move.
     * The ABSOLUTE value of balance tells us how many coins moved across
     * the edge connecting this subtree to its parent.
     *
     * EXAMPLE:
     *        3
     *       / \
     *      0   0
     *
     * - Root has 3 coins, left has 0, right has 0.
     * - Root needs to send 1 coin left and 1 coin right = 2 moves.
     * - DFS returns: root has excess of 1 (3 - 2 = 1 extra).
     */

    int dfs(TreeNode* root) {
        // Base case: empty node contributes 0 balance
        if (root == nullptr) {
            return 0;
        }

        // STEP 1: Recursively get balance from children (bottom-up)
        // Left subtree tells us its excess/deficit
        int leftBalance = dfs(root->left);

        // Right subtree tells us its excess/deficit
        int rightBalance = dfs(root->right);

        // STEP 2: Count moves
        // If leftBalance = +2, it means 2 coins moved from this node down to left subtree
        // If leftBalance = -1, it means 1 coin moved from left subtree up to this node
        // Either way, abs(leftBalance) coins crossed the edge between this node and left child
        moves += abs(leftBalance);
        moves += abs(rightBalance);

        // STEP 3: Return THIS subtree's balance to parent
        // root->val = coins currently at this node
        // -1 = we keep 1 coin for this node
        // leftBalance + rightBalance = net coins flowing in/out from children
        //
        // Example: node has 3 coins, left sent up 0, right sent up 0
        //   return 3 - 1 + 0 + 0 = +2 (excess: send 2 coins up to parent)
        //
        // Example: node has 0 coins, left needs -1, right needs -1
        //   return 0 - 1 + (-1) + (-1) = -3 (deficit: parent must send 3 coins down)
        return root->val - 1 + leftBalance + rightBalance;
    }

    int distributeCoins(TreeNode* root) {
        dfs(root);
        return moves;
    }
};


int main(){
    return 0;
}