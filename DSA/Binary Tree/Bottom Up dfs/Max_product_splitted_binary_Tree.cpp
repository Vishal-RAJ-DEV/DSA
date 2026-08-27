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
    const int MOD = 1e9 + 7;       // Modulo for large numbers (LeetCode requirement)
    long long totalSum = 0;         // Sum of ALL node values in the tree
    long long maxProductValue = 0;  // Track the best product found so far

    /*
     * PROBLEM: Remove ONE edge from the tree to split it into two parts.
     *          Maximize the product: (sum of part1) * (sum of part2).
     *
     * KEY INSIGHT:
     * -------------------------
     * When you remove any edge, the tree splits into:
     *   - A subtree (everything below the removed edge)
     *   - The remaining part (everything else = totalSum - subtreeSum)
     *
     * If we know totalSum, and we know subtreeSum,
     *   product = subtreeSum * (totalSum - subtreeSum)
     *
     * So we just need to try EVERY possible subtree (every edge removal)
     * and pick the maximum product.
     *
     * EXAMPLE:
     *         1
     *        / \
     *       2   3
     *      / \
     *     4   5
     *
     * totalSum = 1+2+3+4+5 = 15
     *
     * Possible splits (cut edge → subtree sum → remaining → product):
     *   cut (1,2) → subtree {2,4,5}=11 → remaining=4  → 11*4 = 44
     *   cut (1,3) → subtree {3}=3    → remaining=12 → 3*12 = 36
     *   cut (2,4) → subtree {4}=4    → remaining=11 → 4*11 = 44
     *   cut (2,5) → subtree {5}=5    → remaining=10 → 5*10 = 50  ← MAX
     *
     * Answer = 50
     */

    // PASS 1: Calculate total sum of all nodes in the tree
    long long calculateTotal(TreeNode* root) {
        if (root == nullptr)
            return 0;

        // Node's own value + sum from left subtree + sum from right subtree
        return root->val +
               calculateTotal(root->left) +
               calculateTotal(root->right);
    }

    // PASS 2: Bottom-up DFS - compute subtree sums and test every split
    long long calculateSubtree(TreeNode* root) {
        if (root == nullptr)
            return 0;

        // Bottom-up: get sums from children first
        long long leftSum = calculateSubtree(root->left);
        long long rightSum = calculateSubtree(root->right);

        // This subtree's total sum = own value + left subtree + right subtree
        long long subtreeSum = root->val + leftSum + rightSum;

        // If we cut the edge ABOVE this node:
        //   Part 1 = subtreeSum (this subtree becomes one piece)
        //   Part 2 = totalSum - subtreeSum (the rest of the tree)
        long long remainingSum = totalSum - subtreeSum;

        // Update max product if this split is better
        maxProductValue = max(
            maxProductValue,
            subtreeSum * remainingSum
        );

        // Return this subtree's sum to parent (for parent's calculation)
        return subtreeSum;
    }

    int maxProduct(TreeNode* root) {
        // Step 1: Find total sum of tree (one full traversal)
        totalSum = calculateTotal(root);

        // Step 2: Try every possible subtree split (second full traversal)
        // At each node, we consider: "what if I cut the edge above me?"
        calculateSubtree(root);

        // Step 3: Return result with modulo (only at the end to avoid overflow)
        return maxProductValue % MOD;
    }
};


int main(){
    return 0;
}