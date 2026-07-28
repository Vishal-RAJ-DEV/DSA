#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

 
class Solution {
public:
    ListNode* middle( ListNode* curr){
        ListNode* slow = curr;
        ListNode* fast = curr;
        ListNode* prev =  nullptr;

        while( fast != nullptr && fast->next != nullptr){
            //here prev will track the just previous node before the middle 
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        prev->next = nullptr;

        return slow;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if( head == nullptr) return nullptr;

        if( head->next == nullptr) return new TreeNode(head->val);

        //now find the middle of the current linklist
        ListNode* middleNode = middle(head);

        //create the tree node 
        TreeNode* root = new TreeNode(middleNode->val);
        //now the left part of linklist is left subtree 
        //and right part of the linklist is the right subtree
        //so call the left part and right part of the linklist find their middle
        //that will be left and right node of the tree

        root->left = sortedListToBST(head); //left part starts from head 
        root->right = sortedListToBST( middleNode->next); //right part is start from the after middle node

        return root;
    }
};


int main(){
    return 0;
}