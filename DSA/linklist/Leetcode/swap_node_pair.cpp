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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        // take a dummy node
        ListNode *dummy = new ListNode(-1);
        ListNode *prev = dummy;
        ListNode *curr = head;
        while (curr && curr->next != nullptr)
        {
            prev->next = curr->next;
            curr->next = prev->next->next;
            prev->next->next = curr;

            // now replace the node
            prev = curr;
            curr = curr->next;
        }

        return dummy->next;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    Solution sol;
    ListNode *newHead = sol.swapPairs(head);
    ListNode *temp = newHead;
    while (temp != nullptr)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    return 0;
}
