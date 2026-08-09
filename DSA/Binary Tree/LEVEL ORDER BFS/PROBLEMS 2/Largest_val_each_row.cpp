#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// TreeNode: structure that represents a single node of a binary tree
struct TreeNode
{
    int val;          // Value stored in the node
    TreeNode *left;   // Pointer to the left child (nullptr if none)
    TreeNode *right;  // Pointer to the right child (nullptr if none)

    // Default constructor: creates a node with value 0 and no children
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Parameterized constructor: creates a node with the given value and no children
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Parameterized constructor: creates a node with the given value and children
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // largestValues: finds the maximum value present in each level (row) of the tree
    // Returns a vector where ans[i] = largest value among all nodes at depth i
    vector<int> largestValues(TreeNode* root) {
        // Base case: if the tree is empty, there are no levels, so return an empty vector
        if( root == nullptr) return {};

        // queue: used for Breadth-First Search (level order traversal).
        // It stores pointers to the nodes of the current level
        queue<TreeNode*>q;
        // Start traversal by pushing the root node into the queue
        q.push(root);
        // ans: will store the largest value of each level, in order
        vector<int>ans;

        // Keep processing levels until the queue becomes empty
        // (i.e. until all nodes of the tree have been visited)
        while( !q.empty()){
            // size: number of nodes currently present in the queue,
            // which is exactly the number of nodes in the current level
            int size = q.size();

            // maxval: temporarily holds the largest value of the current level.
            // Initialized to INT_MIN so that any node value is greater than it
            int maxval = INT_MIN;

            // Process exactly 'size' nodes = the entire current level
            for(int i =0 ; i < size ; i++){
                // top: the front node of the queue (a node of the current level)
                TreeNode * top = q.front();
                // Remove this node from the queue since it is being processed
                q.pop();

                // Update maxval if the current node's value is larger
                maxval = max( maxval , top->val);

                // Enqueue the left child (if it exists) so it is processed in the NEXT level
                if(top->left)q.push(top->left);

                // Enqueue the right child (if it exists) so it is processed in the NEXT level
                if(top->right)q.push(top->right);
            }

            // The loop above finished processing one full level,
            // so maxval now holds the largest value of that level -> store it in ans
            ans.push_back(maxval);
        }

        // Return the list of largest values, one per level
        return ans;
    }
};


int main(){
    return 0;
}
