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
    /* ============================================================
       PROBLEM : PARTITION LIST (LeetCode 86)
       Reorder the given linked list so that every node with a value
       LESS than x comes BEFORE every node with a value >= x. The
       relative order inside each group must be preserved.

       ============================================================
       INTUITION
       ============================================================
       We cannot simply reorder values in the array because this is
       a linked list and we must keep the original nodes. The trick
       is to SPLIT the original list into TWO separate lists while
       walking through it ONCE:

         - "before" list : collects all nodes with val <  x
         - "after"  list : collects all nodes with val >= x

       Each node is UNHOOKED from the original order and re-attached
       to the tail of the correct group. Because we always append at
       the tail, the relative order inside each group is preserved
       automatically. Finally we just LINK the "after" list to the
       end of the "before" list.

       Two DUMMY nodes (val 0) are used so that both lists always
       have a valid starting point. This avoids special-casing "is
       the list empty?" when appending. At the end, the real result
       starts at dummy->next.

       ============================================================
       ALGORITHM (2-POINTER / DUAL-LIST SPLIT)
       ============================================================
       1. Create two dummy nodes: before and after.
          p1 points to the tail of "before", p2 to the tail of
          "after". curr = head starts walking the input list.
       2. For each node in the list:
            - if curr->val >= x : append curr to "after"
                                 (p2->next = curr; p2 = p2->next)
            - else              : append curr to "before"
                                 (p1->next = curr; p1 = p1->next)
            - advance curr = curr->next
       3. Terminate the "after" list: p2->next = nullptr.
          (This cuts any cycle formed by the last appended node,
           which still pointed to a node of the original list.)
       4. Merge: p1->next = after->next.
       5. Return before->next (skipping the dummy head).

       ============================================================
       WORKING DIAGRAM  (Input: 1 -> 4 -> 3 -> 2 -> 5 -> 2 , x = 3)
       ============================================================

        Input list:
          [ 1 ] -> [ 4 ] -> [ 3 ] -> [ 2 ] -> [ 5 ] -> [ 2 ] -> null
           ^
          curr

        Step 1 : curr->val = 1  (< 3)  -> attach to "before"
          before(0) -> [ 1 ]            after(0) -> null
           ^p1
          curr moves to 4

        Step 2 : curr->val = 4  (>= 3) -> attach to "after"
          before(0) -> [ 1 ]            after(0) -> [ 4 ]
                               ^p1                   ^p2
          curr moves to 3

        Step 3 : curr->val = 3  (>= 3) -> attach to "after"
          before(0) -> [ 1 ]            after(0) -> [ 4 ] -> [ 3 ]
                               ^p1                             ^p2
          curr moves to 2

        Step 4 : curr->val = 2  (< 3)  -> attach to "before"
          before(0) -> [ 1 ] -> [ 2 ]   after(0) -> [ 4 ] -> [ 3 ]
                                  ^p1                        ^p2
          curr moves to 5

        Step 5 : curr->val = 5  (>= 3) -> attach to "after"
          before(0) -> [ 1 ] -> [ 2 ]   after(0) -> [ 4 ] -> [ 3 ] -> [ 5 ]
                                  ^p1                                   ^p2
          curr moves to 2

        Step 6 : curr->val = 2  (< 3)  -> attach to "before"
          before(0) -> [ 1 ] -> [ 2 ] -> [ 2 ]   after(0) -> [ 4 ] -> [ 3 ] -> [ 5 ]
                                          ^p1                                  ^p2
          curr = nullptr -> loop ends

        Final merge:  p2->next = nullptr ;  p1->next = after->next

          before(0) -> [ 1 ] -> [ 2 ] -> [ 2 ] -> [ 4 ] -> [ 3 ] -> [ 5 ] -> null
          return before->next  ==  [ 1 ] -> [ 2 ] -> [ 2 ] -> [ 4 ] -> [ 3 ] -> [ 5 ]

       Result   : 1 -> 2 -> 2 -> 4 -> 3 -> 5      (all < 3 first, then >= 3)
       Relative order is preserved in both halves.

       ============================================================
       COMPLEXITY
       ============================================================
       Time  : O(N)  -- single pass over the list.
       Space : O(1)  -- only a few pointers, no extra nodes copied
                      (the two dummies are the only new allocations).
       ============================================================ */
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
