#include <iostream>
#include <bits/stdc++.h>
using namespace std;


 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class BSTIterator {
    stack<TreeNode*>st;
private:
    void pushAll( TreeNode* root){
        st.push(root);
        while(root->left){
            root = root->left;
            st.push(root);
        }
    }
public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }
    
    int next() {
        TreeNode* next = st.top();
        st.pop();
        if(next->right)pushAll( next->right);
        return next->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main(){
        TreeNode* root = new TreeNode(7);
        root->left = new TreeNode(3);
        root->right = new TreeNode(15);
        root->right->left = new TreeNode(9);
        root->right->right = new TreeNode(20);
        BSTIterator* obj = new BSTIterator(root);
        cout << obj->next() << endl;    // returns 3
        cout << obj->next() << endl;    // returns 7
        cout << obj->hasNext() << endl; // returns true
        cout << obj->next() << endl;    // returns 9
        cout << obj->hasNext() << endl; // returns true
        cout << obj->next() << endl;    // returns 15
        cout << obj->hasNext() << endl; // returns true
        cout << obj->next() << endl;    // returns 20
        cout << obj->hasNext() << endl; // returns false
        
    return 0;
}