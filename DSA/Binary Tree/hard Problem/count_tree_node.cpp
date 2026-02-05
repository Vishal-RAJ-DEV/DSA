#include <iostream>
#include <vector>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor to initialize
    // the node with a value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void solve ( Node* root , int& cnt){
        if( root == nullptr) return ;

        solve( root->left , cnt );
        solve(root->right , cnt);
        cnt++;
    }
    int countNodes(Node* root) {
        int cnt = 0 ;
        solve(root , cnt );
        return cnt;
    }
};

//using the heigth of the tree to count the nodes 
class Solution {
public:
    // Function to count the number of nodes in a complete binary tree
    int countNodes(Node* root) {
        // If tree is empty, return 0
        if (root == NULL) {
            return 0;
        }
        // Get height from left side
        int lh = findHeightLeft(root);
        // Get height from right side
        int rh = findHeightRight(root);
        // If heights are equal, it's a perfect binary tree
        if (lh == rh) {
            // Use formula: 2^h - 1
            return (1 << lh) - 1;
        }
        // Otherwise, recursively count left and right subtrees
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Helper function to find height of leftmost path
    int findHeightLeft(Node* node) {
        int height = 0;
        while (node) {
            height++;
            node = node->left;
        }
        return height;
    }

    // Helper function to find height of rightmost path
    int findHeightRight(Node* node) {
        int height = 0;
        while (node) {
            height++;
            node = node->right;
        }
        return height;
    }
};

int main() {
    // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution solution;
    int result = solution.countNodes(root);
    cout << "Total number of nodes in the binary tree: " << result << endl; 

    return 0;
}