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
    ListNode *swapNodes(ListNode *head, int k)
    {
        if (head == nullptr)
            return head;

        // find the first kth node from the start
        ListNode *prev = nullptr;
        ListNode *first = head;
        // now traverse kth time and place the first at kth node
        for (int i = 1; i < k; i++)
        {
            prev = first;
            first = first->next;
        }

        // now find the second ktn node from the end
        ListNode *prev2 = nullptr;
        ListNode *second = head;
        ListNode *temp = first;
        // we keep the k distance between the second and temp
        // so when temp becomes null second will at kth node from end
        while (temp->next != nullptr)
        {
            temp = temp->next;
            prev2 = second;
            second = second->next;
        }

        // now we have first and second node
        // relink the node
        if (prev != nullptr)
            prev->next = second;
        if (prev2 != nullptr)
            prev2->next = first;

        // reconnect node
        ListNode *tempNode = first->next;
        first->next = second->next;
        second->next = tempNode;

        // edge cases
        if (k == 1)
            return second;
        if (prev2 == nullptr)
            return first;

        return head;
    }
};
int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    int k = 2;
    Solution sol;
    ListNode *newHead = sol.swapNodes(head, k);
    ListNode *current = newHead;
    while (current != nullptr)
    {
        cout << current->val << " ";
        current = current->next;
    }
    return 0;
}
