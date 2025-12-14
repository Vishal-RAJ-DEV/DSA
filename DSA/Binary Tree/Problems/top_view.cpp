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

class Solution {
public:
    vector<int> topView( Node * root){
        vector<int> ans ; //this will store the final answer 

        //base case
        if( root == NULL) return ans;
        queue< pair<Node * , int>> q; //this will store the node along with its horizontal distance
        map< int , int > mp; //this will store the first node at each horizontal distance

        q.push({ root , 0}); //pushing the root node with horizontal distance 0
        
        while( ! q.empty()){
            //get the front element of the queue
            auto it = q.front();
            q.pop();

            Node * node = it .first;
            int level = it . second;
            //if this horizontal distance is not present in the map, then we add it
            if( mp.find( level) == mp.end()){
                mp[level] = node->data;
            }

            //now get the left and right children of the node and push them into the queue with their respective horizontal distances
            if( node ->left != NULL){
                q.push({ node->left , level -1 });
            }
            if( node ->right != NULL){
                q.push({ node->right , level  + 1});
            }

        }
        //now we need to traverse the map and store the values in the ans vector
        for ( auto it : mp){
            ans.push_back( it.second);
        }
        return ans;
    }
};
int main(){
        // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(10);
    root->left->left->right = new Node(5);
    root->left->left->right->right = new Node(6);
    root->right = new Node(3);
    root->right->right = new Node(10);
    root->right->left = new Node(9);

    Solution solution;
    vector<int> result = solution.topView(root);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
