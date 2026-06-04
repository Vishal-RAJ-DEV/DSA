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
    ListNode* deleteDuplicates(ListNode* head) {
        /*
            Problem:
            Remove all nodes that have duplicate values
            from a sorted linked list.

            Important:
            If a value appears more than once,
            then all nodes having that value must be deleted.

            Example:
            1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5

            Here 3 is duplicate, so both 3 nodes are removed.
            Here 4 is duplicate, so both 4 nodes are removed.

            Final answer:
            1 -> 2 -> 5
        */

        /*
            Intuition:
            Since the list is sorted, duplicates always come together.

            So when we are at a node:
            1. If current node value is different from next node value,
               then current node is safe and should remain in answer.
            2. If current node value is same as next node value,
               then this value is duplicate.
               We must skip every node having this value.

            To handle deletion from the beginning safely,
            we use a dummy node before head.
        */

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        /*
            prev:
            last confirmed node that should remain in the final list.

            curr:
            node currently being checked.
        */
        ListNode* prev = dummy;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* front = curr->next;

            /*
                If curr and next have same value,
                then this value is duplicate.
            */
            if (front != nullptr && curr->val == front->val) {
                int value = curr->val;

                /*
                    Skip all nodes having this duplicate value.

                    Example:
                    curr = 3 -> 3 -> 3 -> 4

                    After this loop:
                    curr will point to 4
                */
                while (curr != nullptr && curr->val == value) {
                    curr = curr->next;
                }

                /*
                    Connect prev directly to the first non-duplicate node.
                    This removes all duplicate nodes of that value.
                */
                prev->next = curr;
            } else {
                /*
                    Current node is unique,
                    so move prev forward.
                */
                prev = curr;
                curr = curr->next;
            }
        }

        return dummy->next;
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
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<int> arr = {1, 2, 3, 3, 4, 4, 5};

    ListNode* head = createList(arr);

    Solution obj;
    ListNode* ans = obj.deleteDuplicates(head);

    printList(ans);

    return 0;
}
