#include <bits/stdc++.h>
using namespace std;
/*
Input: root1 = [5, 3, 6, 2, 4], root2 = [2, 1, 3, Null, Null, Null, 7, 6]
Output: [1, 2, 2, 3, 3, 4, 5, 6, 6, 7]
Explanation: After merging and sorting the two BST we get [1, 2, 2, 3, 3, 4, 5, 6, 6, 7].
Input: root1 = [12, 9, Null, 6, 11], root2 = [8, 5, 10, 2]
Output: [2, 5, 6, 8, 9, 10, 11, 12]
Explanation: After merging and sorting the two BST we get [2, 5, 6, 8, 9, 10, 11, 12].
*/
// Structure for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor to initialize node
    Node(int val) : data(val), left(NULL), right(NULL) {}
};
//brute force approach is to store the elements of both the BSTs in a vector and then sort the vector and return it
class Solution1 {
public:
    // Function to traverse a BST and store elements in list
    void traverse(Node* root, vector<int>& elements) {
        // If root is NULL, stop recursion
        if (!root) return;
        // Traverse left subtree
        traverse(root->left, elements);
        // Store current node's data
        elements.push_back(root->data);
        // Traverse right subtree
        traverse(root->right, elements);
    }

    // Function to merge elements of two BSTs
    vector<int> mergeBSTs(Node* root1, Node* root2) {
        // Vector to store all elements
        vector<int> elements;
        // Traverse first BST and collect elements
        traverse(root1, elements);
        // Traverse second BST and collect elements
        traverse(root2, elements);
        // Sort the collected elements
        sort(elements.begin(), elements.end());
        // Return the sorted elements
        return elements;
    }
};
//optimal solution is to store the elements of both the BSTs in a vector and then merge the two sorted vectors and return it
class Solution {
public:
    // Function to perform inorder traversal and store elements
    void inorderTraversal(Node* root, vector<int>& arr) {
        // Base case
        if (!root) return;
        // Traverse left subtree
        inorderTraversal(root->left, arr);
        // Store current node data
        arr.push_back(root->data);
        // Traverse right subtree
        inorderTraversal(root->right, arr);
    }

    // Function to merge two sorted arrays
    vector<int> mergeArrays(vector<int>& arr1, vector<int>& arr2) {
        // Initialize result array
        vector<int> merged;
        // Initialize pointers
        int i = 0, j = 0;
        // Merge until one array ends
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i] < arr2[j]) merged.push_back(arr1[i++]);
            else merged.push_back(arr2[j++]);
        }
        // Add remaining elements
        while (i < arr1.size()) merged.push_back(arr1[i++]);
        while (j < arr2.size()) merged.push_back(arr2[j++]);
        return merged;
    }

    // Function to merge two BSTs in sorted order
    vector<int> mergeBSTs(Node* root1, Node* root2) {
        // Arrays to store inorder traversals
        vector<int> arr1, arr2;
        // Perform inorder traversal on first BST
        inorderTraversal(root1, arr1);
        // Perform inorder traversal on second BST
        inorderTraversal(root2, arr2);
        // Merge and return the result
        return mergeArrays(arr1, arr2);
    }
};

// Driver code
int main() {
    // Create first BST
    Node* root1 = new Node(3);
    root1->left = new Node(1);
    root1->right = new Node(5);

    // Create second BST
    Node* root2 = new Node(4);
    root2->left = new Node(2);
    root2->right = new Node(6);

    // Create Solution object
    Solution sol;
    // Merge the BSTs
    vector<int> result = sol.mergeBSTs(root1, root2);

    // Print result
    for (int val : result) cout << val << " ";
    return 0;
}
