#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Use a queue to store nodes.

Process nodes level by level.

For each level:

Take all nodes currently in the queue.

Store their values.

Push their children into the queue.

Repeat until queue is empty.
*/

// TreeNode struct represents
// a node in a binary tree
struct TreeNode {
    int val; 
    TreeNode* left; 
    TreeNode* right;

    // Default constructor for TreeNode
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor with a value
    // parameter for TreeNode
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Constructor with value, left
    // child, and right child
    // parameters for TreeNode
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    // Function to perform level-order
    // traversal of a binary tree
    vector<vector<int>> levelOrder(TreeNode* root) {
        // Create a 2D vector to store levels
        vector<vector<int>> ans; 
        if (root == nullptr) {
            // If the tree is empty,
            // return an empty vector
            return ans; 
        }
        
        // Create a queue to store nodes
        // for level-order traversal
        queue<TreeNode*> q; 
        // Push the root node to the queue
        q.push(root); 

        while (!q.empty()) {
            // Get the size of the current level
            int size = q.size(); 
            // Create a vector to store
            // nodes at the current level
            vector<int> level; 


            //so here clearing te confusion beacuse we have to store the all the current ele in the queue in a level vector so use the loop for store one level and then push that level vector into the ans vector and for further levels store the childern ele in the queue and repeat the same process
            for (int i = 0; i < size; i++) {
                // Get the front node in the queue
                TreeNode* node = q.front(); 
                // Remove the front node from the queue
                q.pop(); 
                // Store the node value
                // in the current level vector
                level.push_back(node->val); 

                // Enqueue the child nodes if they exist
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            // Store the current level
            // in the answer vector
            ans.push_back(level); 
        }
        // Return the level-order
        // traversal of the tree
        return ans; 
    }
};

// Function to print
// the elements of a vector
void printVector(const vector<int>& vec) {
    // Iterate through the
    // vector and print each element
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}


int main(){
    // Creating a sample binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode( 6);

    // Create an instance
    // of the Solution class
    Solution solution; 
    // Perform level-order traversal
    vector<vector<int>> result = solution.levelOrder(root); 

    cout << "Level Order Traversal of Tree: "<< endl;

    // Printing the level order traversal result
    for (const vector<int>& level : result) {
        printVector(level);
    }
    return 0;
}

/*
        1
       / \
      2   3
     / \   \
    4   5   6

    Step 1: Initialization

ans = []

queue = [1]



Step 2: First while loop iteration

Queue size = 1 → (only root)

level = []

Process node 1

Pop → queue becomes []

Add value → level = [1]

Push children → queue = [2, 3]

Add level → ans = [[1]]



Step 3: Second iteration

Queue size = 2 → (2 nodes at this level: 2, 3)

level = []

Process node 2

Pop → queue = [3]

Add value → level = [2]

Push children → queue = [3, 4, 5]

Process node 3

Pop → queue = [4, 5]

Add value → level = [2, 3]

Push child → queue = [4, 5, 6]

Add level → ans = [[1], [2, 3]]



Step 4: Third iteration

Queue size = 3 → (nodes: 4, 5, 6)

level = []

Process node 4

Pop → queue = [5, 6]

Add value → level = [4]

No children

Process node 5

Pop → queue = [6]

Add value → level = [4, 5]

No children

Process node 6

Pop → queue = []

Add value → level = [4, 5, 6]

No children

Add level → ans = [[1], [2, 3], [4, 5, 6]]



Step 5: Queue empty → Exit loop

Final result:

[[1], [2, 3], [4, 5, 6]]
*/
