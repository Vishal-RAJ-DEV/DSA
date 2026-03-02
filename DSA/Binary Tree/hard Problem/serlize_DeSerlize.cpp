#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize node value and child pointers
    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

// Function to perform in-order traversal and print the tree
void inorder(TreeNode* root) {
    // Base condition: if node is null, return
    if (!root) {
        return;
    }

    // Recursively traverse the left subtree
    inorder(root->left);

    // Print the current node's value
    cout << root->val << " ";

    // Recursively traverse the right subtree
    inorder(root->right);
}

class Solution {
public:

    // Function to serialize a binary tree into a string using level-order traversal
    string serialize(TreeNode* root) {

        // If tree is empty, return an empty string
        if (!root) {
            return "";
        }

        // Initialize string to store serialized result
        string s = "";

        // Initialize a queue to store nodes during level-order traversal
        queue<TreeNode*> q;

        // Push root node into the queue
        q.push(root);

        // Loop while queue is not empty
        while (!q.empty()) {

            // Get the current node from the front of the queue
            TreeNode* curNode = q.front();
            q.pop();

            // If current node is null, append "#" to string
            if (curNode == nullptr) {
                s += "#,";
            } 
            else {
                // Append node value to string
                s += to_string(curNode->val) + ",";

                // Push left child into queue
                q.push(curNode->left);

                // Push right child into queue
                q.push(curNode->right);
            }
        }

        // Return the serialized tree string
        return s;
    }

    // Function to deserialize a string and reconstruct the binary tree
    TreeNode* deserialize(string data) {

        // If data is empty, return null
        if (data.empty()) {
            return nullptr;
        }

        // Use stringstream to parse the input data
        stringstream s(data);
        string str;

        // Read the root value from the stream
        getline(s, str, ',');

        // Create the root node
        TreeNode* root = new TreeNode(stoi(str));

        // Initialize a queue to hold tree nodes for level-order reconstruction
        queue<TreeNode*> q;

        // Push root node into the queue
        q.push(root);

        // Loop through the stream to construct the tree
        while (!q.empty()) {

            // Get the current node from the front of the queue
            TreeNode* node = q.front();
            q.pop();

            // Read the left child value
            getline(s, str, ',');

            // If value is not "#", create left node and attach to current node
            if (str != "#") {
                TreeNode* leftNode = new TreeNode(stoi(str));
                node->left = leftNode;
                q.push(leftNode);
            }

            // Read the right child value
            getline(s, str, ',');

            // If value is not "#", create right node and attach to current node
            if (str != "#") {
                TreeNode* rightNode = new TreeNode(stoi(str));
                node->right = rightNode;
                q.push(rightNode);
            }
        }

        // Return the root of the reconstructed tree
        return root;
    }
};

// Driver code
int main() {

    // Manually construct the binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    // Create an instance of the solution class
    Solution solution;

    // Print original tree using in-order traversal
    cout << "Orignal Tree: ";
    inorder(root);
    cout << endl;

    // Serialize the tree into a string
    string serialized = solution.serialize(root);
    cout << "Serialized: " << serialized << endl;

    // Deserialize the string back into a tree
    TreeNode* deserialized = solution.deserialize(serialized);

    // Print tree after deserialization
    cout << "Tree after deserialisation: ";
    inorder(deserialized);
    cout << endl;

    return 0;
}
