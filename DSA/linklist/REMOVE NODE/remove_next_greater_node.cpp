#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        /*
            Problem:
            Delete every node that has a greater value node on its right side.

            Example:
            5 -> 2 -> 13 -> 3 -> 8

            5 is removed because 13 is greater on the right.
            2 is removed because 13 is greater on the right.
            13 stays because no greater node exists on its right.
            3 is removed because 8 is greater on the right.
            8 stays.

            Final answer:
            13 -> 8
        */

        /*
            Intuition:
            We want to keep only those nodes that are not smaller than
            a node appearing later on the right.

            We use a stack and maintain useful nodes in decreasing order.

            If current node is greater than stack top,
            then stack top should be removed because a greater node
            has appeared on its right side.
        */

        ListNode* curr = head;
        stack<ListNode*> st;

        /*
            First pass:
            Traverse the list and remove weaker nodes from the stack.

            For every node:
            1. Pop all smaller nodes from the stack
            2. Push current node

            After this, the stack stores only the nodes that should remain.
        */
        while (curr != nullptr) {
            while (!st.empty() && st.top()->val < curr->val) {
                st.pop();
            }

            st.push(curr);
            curr = curr->next;
        }

        /*
            Second pass:
            Rebuild the linked list from the stack.

            Since stack returns nodes in reverse order,
            we reconnect them from back to front.
        */
        ListNode* nxt = nullptr;

        while (!st.empty()) {
            curr = st.top();
            st.pop();

            curr->next = nxt;
            nxt = curr;
        }

        return nxt;
    }
};

ListNode* createList(const vector<int>& arr) {
    if (arr.empty()) return nullptr;

    ListNode* head = new ListNode(arr[0]);
    ListNode* tail = head;

    for (int i = 1; i < (int)arr.size(); i++) {
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }

    return head;
}

void printList(ListNode* head) {
    ListNode* temp = head;

    while (temp != nullptr) {
        cout << temp->val;
        if (temp->next != nullptr) {
            cout << " -> ";
        }
        temp = temp->next;
    }

    cout << endl;
}

int main() {
    vector<int> arr = {5, 2, 13, 3, 8};

    ListNode* head = createList(arr);

    Solution obj;
    ListNode* ans = obj.removeNodes(head);

    printList(ans);

    return 0;
}
