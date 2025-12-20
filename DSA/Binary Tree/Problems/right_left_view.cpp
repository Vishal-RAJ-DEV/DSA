#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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


//simple algorithm
/*
1.for right view we do a pre order traversal but we first go to the right subtree and then to the left subtree
2. for left view we do a pre order traversal but we first go to the left subtree and then to the right subtree
3.and we keep track of the level of the node we are currently at
4.if the level is equal to the size of the ans vector then we add the current node's data to the ans vector
5.while returning back from right to left or left to right we do not add any node's data to the ans vector as we have already added the node's data at that level 
6.this is checked by the condition if( level == ans.size()) where level will be decresed because we are returning back from the recursion stack and ans.size() will remain same as we have already added the node's data at that level
*/


class Solution {
public:
    void depthFirstSearchRIGHT ( Node * root , int level , vector<int> & ans){
        //base case 
        if( root == nullptr) return;

        //if level is equal to the size of the ans vector then we add the current node's data to the ans vector
        if( level == ans.size()){
            ans.push_back( root ->data);
        }
        //first we go to the right subtree and then to the left subtree
        depthFirstSearchRIGHT( root ->right , level + 1 , ans );

        //and if there is no right subtree of that node then we go to the left subtree 
        depthFirstSearchRIGHT( root ->left , level  + 1 , ans );
    }
    void depthFirstSearchLEFT ( Node * root , int level , vector<int> & ans){
        //base case 
        if( root == nullptr) return;

        //if level is equal to the size of the ans vector then we add the current node's data to the ans vector
        if( level == ans.size()){
            ans.push_back( root ->data);
        }
        //first we go to the left subtree and then to the right subtree
        depthFirstSearchLEFT( root ->left , level + 1 , ans );

        //and if there is no left subtree of that node then we go to the right subtree 
        depthFirstSearchLEFT( root ->right , level  + 1 , ans );
    }
    vector<int> rightView( Node * root){
        vector<int> ans;
        int level = 0 ;
        depthFirstSearchRIGHT( root , level , ans);
        return ans;
        
    }
    vector<int> leftView( Node * root){
        vector<int> ans;
        int level = 0 ;
        depthFirstSearchLEFT( root , level , ans);
        return ans;
        
    }
};
int main(){
        // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(11);
    root->left->left->right = new Node(5);
    root->left->left->right->right = new Node(6);
    root->right = new Node(3);
    root->right->right = new Node(10);
    root->right->left = new Node(9);

    Solution solution;
    vector<int> result = solution.rightView(root);
    cout << "Right View of the Binary Tree: ";
    for (int val : result) {
        cout << val << " ";
    }
    vector<int> resultLeft = solution.leftView(root);
    cout << "\nLeft View of the Binary Tree: ";
    for (int val : resultLeft) {
        cout << val << " ";
    }

    cout << endl;
    return 0;
}
