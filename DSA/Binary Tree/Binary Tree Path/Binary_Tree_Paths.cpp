#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Leetcode 257 - Binary Tree Paths):
Given the root of a binary tree, return ALL root-to-leaf paths in any order.
A leaf is a node with no children.

EXAMPLE:
    1
   / \
  2   3
   \
    5

Output: ["1->2->5", "1->3"]

ALGORITHM (DFS + Backtracking):

We perform a DFS traversal from root to leaf.
We maintain a string 's' representing the path from root to current node.

At each node:
1. If root is null -> return.
2. Append current node's value to the path string:
   - If path is empty -> just the value (e.g., "1")
   - Otherwise -> append "->value" (e.g., "1->2")
3. If current node is a LEAF (no left and no right):
   - Push the path string into answer vector.
   - Return (no need to go further).
4. Otherwise, recursively call solve() on left and right child.
   The string is passed BY VALUE, so each recursive branch gets its own
   copy of the path. This is implicit backtracking — no need to pop.

LOGIC:
- We explore every root-to-leaf path using DFS.
- At leaf nodes, we record the accumulated path.
- Passing string by value creates a new copy at each recursive call,
  so paths don't interfere with each other.
- Time: O(n^2) worst case — we traverse all n nodes and string copying
  costs O(path length) per node.
- Space: O(n) for recursion stack + O(n^2) for storing all paths.
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void solve(TreeNode* root , vector<string>& ans , string s){
        if(root == nullptr) return;

        // Append current node value to path
        if(s.empty()){
            s += to_string(root->val);
        }else{
            s += "->" + to_string(root->val);
        }

        // If leaf node -> record the path
        if(root->left == nullptr && root->right == nullptr){
            ans.push_back(s);
            return;
        }

        // Recurse on left and right
        solve(root->left , ans , s);
        solve(root->right , ans , s);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        string s = "";
        solve(root , ans , s);
        return ans;
    }
};

int main(){
    return 0;
}