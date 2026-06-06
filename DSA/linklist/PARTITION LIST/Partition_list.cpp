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
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr)
            return head;

        ListNode * before = new ListNode(0);
        ListNode * after = new ListNode(0);

        ListNode* p1 = before;
        ListNode * p2 = after;
        ListNode * curr = head;

        while( curr != nullptr){
            if( curr->val >= x){
                p2->next = curr;
                p2 = p2->next;
            }
            else{
                p1->next = curr;
                p1 = p1->next;
            }

            curr = curr->next;
        }

        //now connect the nodes and merge it 
        p2->next = nullptr;
        p1->next = after->next;


        return before->next;
    }
};

void printList(ListNode *head)
{
    ListNode *temp = head;
    while (temp != nullptr)
    {
        cout << temp->val;
        if (temp->next != nullptr)
            cout << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main(){
    ListNode *head = new ListNode(1);
    head->next = new ListNode(4);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(2);

    int x = 3;

    Solution obj;
    ListNode *newHead = obj.partition(head, x);

    printList(newHead);

    return 0;
}
