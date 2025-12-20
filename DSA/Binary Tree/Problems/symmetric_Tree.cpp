#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    bool check(Node *node1, Node *node2)
    {
        // only base case where reutrn true ( check for every node till last node )
        if (node1 == nullptr && node2 == nullptr)
            return true;
        // if anyone is null then return true  both are null means tree null at leaf
        // otherwise both are not equal,  one in null , then return false tree is not symmetric
        if (node1 == nullptr || node2 == nullptr)
            return node1 == node2;
        if (node1->data != node2->data)
            return false;

        // recursively check for left of node1 with right of node2 and right of node1 with left of node2
        // and return the and of both the calls so that if any one is false then overall will be false
        return check(node1->left, node2->right) && check(node1->right, node2->left);
    }
    bool isSymmetric(Node *root)
    {
        if (root == nullptr)
            return true;

        bool res = check(root->left, root->right);

        return res;
    }
};
int main()
{
    // Creating a sample binary tree
    Node *root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(11);
    root->left->left->right = new Node(5);
    root->left->left->right->right = new Node(6);
    root->right = new Node(3);
    root->right->right = new Node(10);
    root->right->left = new Node(9);

    Solution obj;
    bool ans = obj.isSymmetric(root);
    if (ans)
        cout << "The tree is symmetric " << endl;
    else
        cout << "The tree is not symmetric " << endl;

    return 0;
}
