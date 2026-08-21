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
    int ans = 0;          // Stores the sum of all nodes at the deepest level
    int maxdepth = -1;    // Tracks the deepest level encountered so far (starts below 0)
    // DFS traversal that tracks current depth and finds sum of deepest leaves
    void dfs(TreeNode* root, int depth) {
        // Base case: if node is NULL, stop recursion
        if (root == nullptr) return;

        // Case 1: If current depth equals the deepest level found so far,
        //         this node is at the deepest level → add its value to sum
        if (depth == maxdepth) {
            ans += root->val;
        }
        // Case 2: If current depth is greater than the deepest level found,
        //         we discovered a NEW deeper level → reset sum to this node's
        //         value and update maxdepth to current depth
        else if (depth > maxdepth) {
            ans = root->val;        // Reset sum (previous deepest nodes are no longer deepest)
            maxdepth = depth;       // Update deepest level seen
        }
        // Case 3 (implicit): If depth < maxdepth, this node is shallower
        //         than the deepest level → do nothing, skip this node

        // Recurse on left and right children with depth + 1
        // Each child is one level deeper than current node
        dfs(root->left, depth + 1);
        dfs(root->right, depth + 1);
    }

    // Main function: starts DFS from root at depth 0, returns sum of deepest leaves
    int deepestLeavesSum(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }
};


// BFS approach to find sum of deepest leaves , level order traversal is used to traverse the tree level by level and sum the values of nodes at the deepest level.
int deepestLeavesSum(TreeNode* root) {
	int sum = 0, n;
	queue<TreeNode*> q; // required for level-order traversal
	q.push(root);
	while(!q.empty()){
		sum = 0, n = q.size(); // reset sum when deeper level is reached and accumulate for that level
		for(int i = 0; i < n; i++){
			auto top = q.front(); q.pop();
			sum += top -> val;     
			if(top -> left) q.push(top -> left);
			if(top -> right) q.push(top -> right);
		}                
	}
	return sum; // final value held by 'sum' will be sum of values of nodes at the deepest level
}




int main(){
    return 0;
}