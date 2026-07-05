#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        /*
        Intuition:
        In array insertion sort, we keep the left part sorted and insert the current
        element into its correct position inside that sorted part.

        We do the same idea for a linked list:
        1. Take one node from the original list at a time.
        2. Insert that node into the correct position of a new sorted list.

        Why do we use a dummy node?
        - dummy is an extra node placed before the sorted list.
        - It makes insertion at the beginning easy.
        - Without dummy, inserting before the first real node would need a separate case.

        How original nodes are used:
        - We do NOT create new nodes for sorting.
        - We reuse the same nodes from the original list.
        - We only change next pointers to move nodes into the sorted part.
        */

        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // dummy->next will always point to the head of the sorted list.
        ListNode* dummy = new ListNode(0);

        // curr moves through the original list, one node at a time.
        ListNode* curr = head;

        while (curr != nullptr) {
            // Save the next original node before changing curr->next.
            ListNode* nextNode = curr->next;

            // prev is used to find the correct insertion position in the sorted list.
            ListNode* prev = dummy;

            /*
            Search from the start of the sorted list.
            Stop at the node after which curr should be inserted.

            Example:
            sorted list: 1 -> 3 -> 5
            curr value : 4
            prev will stop at node 3, so 4 is inserted after 3.
            */
            while (prev->next != nullptr && prev->next->val < curr->val) {
                prev = prev->next;
            }

            /*
            Insert curr between prev and prev->next

            Before:
            prev -> A
            curr -> ...

            After:
            prev -> curr -> A
            */
            curr->next = prev->next;
            prev->next = curr;

            // Continue with the remaining original list.
            curr = nextNode;
        }

        ListNode* sortedHead = dummy->next;
        delete dummy;
        return sortedHead;
    }
};

ListNode* createList(const vector<int>& values) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int value : values) {
        ListNode* newNode = new ListNode(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << '\n';
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    ListNode* head = createList(values);

    cout << "Linked list before sorting:\n";
    printList(head);

    Solution obj;
    head = obj.insertionSortList(head);

    cout << "Linked list after insertion sort:\n";
    printList(head);

    deleteList(head);
    return 0;
}
