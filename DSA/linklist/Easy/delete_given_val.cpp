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
class Solution
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        if (head == nullptr)
            return nullptr;
        ListNode *dummy = new ListNode(0);
        dummy->next = head; // connect the dummy node to the head , so that previous can traverse
        // previous node to attach the last node , node after delete node
        ListNode *prev = dummy;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            if (temp->val == val)
            {
                // connect the prev node to the deleted node next
                prev->next = temp->next;
                temp = temp->next;
            }
            else
            {
                // just move forward
                prev = prev->next;
                temp = temp->next;
            }
        }
        return dummy->next;
    }
};

int main()
{
    // Create linked list: 1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(6);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next->next = new ListNode(6);

    int val = 6; // Value to remove from the list
    Solution s;
    ListNode *newHead = s.removeElements(head, val);
    // Print the modified linked list
    ListNode *temp = newHead;
    while (temp != nullptr)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    return 0;
}