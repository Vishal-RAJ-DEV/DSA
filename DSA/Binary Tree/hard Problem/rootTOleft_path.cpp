#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Note: No two nodes in the tree have the same data value and it is assured that the given node is present and a path always exists.
*/
class Node{
    public :
    int data ;
    Node* left;
    Node* right;
    Node( int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

//alternate approach using backtracking 
// Class containing the solution
class Solution {
public:
    // Function to find the path from root to node with value x
    bool getPath(Node* root, vector<int>& arr, int x) {
        // If current node is NULL, return false
        if (!root) {
            return false;
        }

        // Add current node's value to the path
        arr.push_back(root->data);

        // If current node's value is equal to x, return true
        if (root->data == x) {
            return true;
        }

        // Recursively search in left or right subtree
        if (getPath(root->left, arr, x) ||
            getPath(root->right, arr, x)) {
            return true;
        }

        // If not found, backtrack and remove current node
        arr.pop_back();
        return false;
    }

    // Function to get the path from root to node with value B
    vector<int> solve(Node* A, int B) {
        // Vector to store the path
        vector<int> arr;

        // If root is NULL, return empty path
        if (A == NULL) {
            return arr;
        }

        // Call helper function to fill the path
        getPath(A, arr, B);

        // Return the resulting path
        return arr;
    }
};

class Solution {
public:
    //key idea is find the path for both left and right at node_x and if we found the leaf  node then we return 
    // otherwise we pop the node_x from path , 
    // beacuse using that node path will not lead to leaf node so pop it from path
    void helper ( Node * root , int leaf , vector<int> &path){
        if( root == nullptr) return;

        path.push_back( root->data);

        if( root->data == leaf) return;

        //here we are exploring both left and right subtree to find the leaf node beacuse we do not know the position of leaf node is it in left subtree or right subtree
        helper( root -> left , leaf , path);
        helper( root -> right , leaf , path);
        //if the last element in path is not leaf then we need to pop it beacuse this path is not leading to leaf node at the end of both calls
        if( path.back() != leaf){
            path.pop_back();
        }

    }
    vector<int> Root_to_LeafNode( Node * root , int leaf){

        vector<int> path;
        //helper function to find the path from root to leaf
        if( leaf == root -> data){
            path.push_back( root -> data);
            return path;
        }

        helper( root , leaf , path);

        return path;
        
    }
};
int main(){
        // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(7);
    root->left->right->right = new Node(10);
    root->left->left->right = new Node(5);   
    root->left->left->right->right = new Node(6);
    root->right = new Node(3);
    root->right->right = new Node(11);
    root->right->left = new Node(9);

    int leaf  = 10 ; // leaf node whose path we have to find

    Solution solution;
    vector<int> result = solution.Root_to_LeafNode(root , leaf);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
