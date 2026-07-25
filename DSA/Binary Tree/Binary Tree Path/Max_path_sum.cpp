#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// TreeNode structure for the binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};


 /*
        ALGORITHM: Maximum Path Sum (Step-by-Step)

        Goal: Find the maximum sum of any path in the binary tree.
              A path can start and end at ANY node (not just leaves),
              and each node can appear only once in the path.

        Step 1 - Define the problem for each node:
            - At any node, there are two roles it plays:
            (a) It could be the HIGHEST point (turning point) of the path.
                => Path goes: left branch → node → right branch
                => Candidate sum = max(0, leftGain) + node->val + max(0, rightGain)
            (b) It could be part of a path that goes UP to its parent.
                => The parent can only take ONE branch (left OR right, not both).
                => Return value = node->val + max(leftGain, rightGain)

        Step 2 - DFS post-order traversal:
            - Recursively compute the best gain from left and right subtrees.
            - Ignore negative gains (max(0, gain)) because they reduce the sum.

        Step 3 - At each node:
            - Update a global answer:
                ans = max(ans, leftGain + node->val + rightGain)

        Step 4 - Return to parent:
            - Return the maximum single-branch sum starting from this node:
                return node->val + max(leftGain, rightGain)

        Step 5 - Start DFS from root:
            - dfs(root) processes every node and updates ans.
            - Return ans.
    */
   
class Solution {
public:

    // Stores the maximum path sum found anywhere in the tree.
    // Initialized with INT_MIN because node values can all be negative.
    int ans = INT_MIN;

    // dfs() returns ONE thing:
    //
    // "Maximum path sum starting from the current node
    //  that can be extended upward to its parent."
    //
    // IMPORTANT:
    // It DOES NOT return the answer of the entire subtree.
    // It only returns the best single branch.
    int dfs(TreeNode* root) {

        // Base case.
        // If there is no node, its contribution is 0.
        if (root == nullptr)
            return 0;


        // Solve the left subtree first.
        //
        // dfs(root->left) returns the maximum gain
        // that the left child can contribute.
        //
        // Example:
        //
        //      5
        //     /
        //    3
        //
        // dfs(3) returns 3.
        //
        // If left subtree gives a negative value,
        // we ignore it because taking a negative path
        // only decreases our answer.
        //
        // Example:
        //
        //     -20
        //
        // dfs(-20) = -20
        //
        // max(0,-20)=0
        //
        // Meaning:
        // "Don't include this subtree."
        int left = max(0, dfs(root->left));


        // Same logic for the right subtree.
        int right = max(0, dfs(root->right));


        // -------------------------
        // This node becomes the
        // HIGHEST point of the path.
        //
        // Path looks like
        //
        // left
        //   \
        //   root
        //   /
        // right
        //
        // Candidate answer
        //
        // left + root + right
        //
        // Example
        //
        //      1
        //     / \
        //    2   3
        //
        // left =2
        // right=3
        //
        // candidate=2+1+3=6
        //
        // Compare with previous answer.
        ans = max(ans, left + right + root->val);


        // -------------------------
        // Now return something to parent.
        //
        // Parent CANNOT take both children.
        //
        // Example
        //
        //        10
        //       /
        //      5
        //     / \
        //    4   8
        //
        // Parent cannot use
        //
        // 4->5->8->10
        //
        // because the path forks.
        //
        // Parent can choose ONLY ONE branch.
        //
        // Either
        //
        // root + left
        //
        // or
        //
        // root + right
        //
        // Therefore return
        //
        // root + max(left,right)
        return root->val + max(left, right);
    }


    int maxPathSum(TreeNode* root) {

        // Starts DFS from the root.
        //
        // During recursion,
        // 'ans' keeps getting updated.
        dfs(root);

        // Finally return the largest path found.
        return ans;
    }
};


int main(){
    return 0;
}