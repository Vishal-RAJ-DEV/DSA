#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if( head == NULL) return NULL;
        ListNode * prev = head ;
        ListNode * curr = head->next;
        while( prev->next != NULL){
            if( prev->val == curr->val){
                prev->next = curr->next;

                //change the curr node to the next node 
                curr = curr->next;
            }else{
                //if not same then just move forward the node 
                prev = prev->next;
                curr = curr->next;
            }
        }

        return head;
    }
};

int main(){
    // Create linked list: 1 -> 1 -> 2
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    Solution s;
    ListNode *newHead = s.deleteDuplicates(head);
    // Print the modified linked list
    ListNode *temp = newHead;
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    return 0;
}