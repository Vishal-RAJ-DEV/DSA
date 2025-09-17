#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    // Function to perform preorder traversal
    // of a binary tree iteratively
    vector<int> InorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> st;
        TreeNode *node = root;
        vector<int> inorder;
        while (true)
        {
            if (node != NULL)   // till the leftmost node at null push the node in the stack and go to the left 
            {
                st.push(node);
                node = node->left;
            }
            else   //at the node become the null 
            {
                if (st.empty() == true)  // if the stack is empty the break it iteration is over 
                    break;
                node = st.top();  //get the top elenment and pop it out 
                st.pop();
                inorder.push_back(node->val);  //push the value of that node in the inorder 
                node = node->right;   //go to the right subtree and if it get null again the get the top elenment and pop it out 
            }
        }
        return inorder;
    }
};
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<int> inorder = sol.InorderTraversal(root);
    cout<<"inorder traversal : ";
    for (int val : inorder)
    {
        cout << val << " ";
    }
    return 0;
}
