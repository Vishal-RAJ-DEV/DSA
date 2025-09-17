#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Define the TreeNode structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Function to perform preorder traversal
    // of a binary tree iteratively
    vector<int> preorderTraversal(TreeNode* root) {
        // Initialize vector to store
        // the preorder traversal result
        vector<int> preorder;
        
        // If the root is null, return
        // an empty traversal result
        if(root == nullptr) {
            return preorder;
        }
        
        // Create a stack to store
        // nodes during traversal
        stack<TreeNode*> st;
        // Push the root node
        // onto the stack
        st.push(root);
        
        // Perform iterative preorder traversal
        while(!st.empty()) {
            // Get the current node
            // from the top of the stack
            root = st.top();
            // Remove the node
            // from the stack
            st.pop();
            
            // Add the node's value to
            // the preorder traversal result
            preorder.push_back(root->val);
            
            // Push the right child
            // onto the stack if exists
            if(root->right != nullptr) {
                st.push(root->right);
            }
            
            // Push the left child onto
            // the stack if exists
            if(root->left != nullptr) {
                st.push(root->left);
            }
        }
        
        // Return the preorder
        // traversal result
        return preorder;
    }
};

int main() {
    // Creating a binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // Initializing the Solution class
    Solution sol;

    // Getting the preorder traversal
    vector<int> result = sol.preorderTraversal(root);

    // Displaying the preorder traversal result
    cout << "Preorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Preorder Traversal (Iterative):
1. Start at the root.
2. Visit the node.
3. Push right child to stack (if exists).
4. Push left child to stack (if exists).
5. Repeat until stack is empty.

Take this binary tree:

        1
       / \
      2   3
     / \   4
    5   6


So preorder traversal should be:

[1, 2, 5, 6, 3, 4]

🔹 Dry Run
Step 1: Initialization

preorder = []

stack = [1]



Step 2: While loop starts (stack not empty)
Iteration 1:

Pop 1 → stack = []

Add 1 to preorder → preorder = [1]

Push right child 3 → stack = [3]

Push left child 2 → stack = [3, 2]



Iteration 2:

Pop 2 → stack = [3]

Add 2 → preorder = [1, 2]

Push right child 6 → stack = [3, 6]

Push left child 5 → stack = [3, 6, 5]



Iteration 3:

Pop 5 → stack = [3, 6]

Add 5 → preorder = [1, 2, 5]

No children



Iteration 4:

Pop 6 → stack = [3]

Add 6 → preorder = [1, 2, 5, 6]

No children



Iteration 5:

Pop 3 → stack = []

Add 3 → preorder = [1, 2, 5, 6, 3]

Push right child 4 → stack = [4]

No left child



Iteration 6:

Pop 4 → stack = []

Add 4 → preorder = [1, 2, 5, 6, 3, 4]

No children



Step 3: Stack is empty → End traversal

Final result:

[1, 2, 5, 6, 3, 4]
*/