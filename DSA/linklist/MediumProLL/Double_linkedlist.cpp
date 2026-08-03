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


 
/*
===============================================================================
                    Logic Behind the Recursive Solution
===============================================================================

We need to double the number represented by the linked list.

Example:
    1 -> 8 -> 9

represents the number 189.

After doubling:
    189 × 2 = 378

Answer:
    3 -> 7 -> 8

------------------------------------------------------------------------------
Why do we use recursion?
------------------------------------------------------------------------------

When multiplying a number, we always start from the least significant digit
(the last digit).

Example:

        1 -> 8 -> 9
                 ^
             Start here

However, a singly linked list only allows us to move from left to right.
We cannot traverse backwards.

Recursion solves this problem.

During the recursive calls we simply travel to the last node.

            helper(1)
                |
            helper(8)
                |
            helper(9)
                |
            helper(NULL)

Nothing is calculated while going down.

------------------------------------------------------------------------------
Backtracking
------------------------------------------------------------------------------

Once we reach NULL, recursion starts returning.

The last node is processed first.

Suppose the list is:

    9 -> 9 -> 9

Backtracking happens like this:

Last node:
    9 × 2 + 0 = 18
    digit = 8
    carry = 1

Middle node:
    9 × 2 + 1 = 19
    digit = 9
    carry = 1

First node:
    9 × 2 + 1 = 19
    digit = 9
    carry = 1

The recursion finally returns carry = 1.

Since there is still a carry remaining after processing the head,
we create a new node at the beginning.

Result:

    1 -> 9 -> 9 -> 8

------------------------------------------------------------------------------
Meaning of helper()
------------------------------------------------------------------------------

helper(node)

Returns:
    carry generated after doubling the current node and all nodes after it.

At every node:

1. Get carry from the next node.
2. Compute:

        value = currentDigit * 2 + carry

3. Store:

        currentDigit = value % 10

4. Return:

        carry = value / 10

------------------------------------------------------------------------------
Time Complexity
------------------------------------------------------------------------------

O(n)

Every node is visited exactly once.

------------------------------------------------------------------------------
Space Complexity
------------------------------------------------------------------------------

O(n)

Recursive call stack stores one function call for every node.
===============================================================================
*/

class Solution {
public:
    int helper(ListNode* head) {
        if (head == nullptr)
            return 0;

        int carry = helper(head->next);

        int prod = head->val * 2 + carry;
        head->val = prod % 10;

        return prod / 10;
    }

    ListNode* doubleIt(ListNode* head) {
        ListNode* temp = head;

        int carry = helper(temp);

        if (carry > 0) {
            ListNode* node = new ListNode(carry);
            node->next = head;
            head = node;
        }

        return head;
    }
};


/*
===============================================================================
                    Iterative Approach using Reversal
===============================================================================

Instead of recursion, we first reverse the linked list so that the least
significant digit comes first.

Example:

Original:
    1 -> 8 -> 9

Reverse:
    9 -> 8 -> 1

Now we can process digits exactly like normal multiplication from right to left.

Algorithm:

1. Reverse the linked list.
2. Traverse the reversed list.
3. For every node:
       value = digit * 2 + carry
       digit = value % 10
       carry = value / 10
4. If carry still exists after the last node,
   append a new node containing the carry.
5. Reverse the list again.

Example:

Original:
    9 -> 9 -> 9

Reverse:
    9 -> 9 -> 9

Process:

9 × 2 + 0 = 18
digit = 8
carry = 1

9 × 2 + 1 = 19
digit = 9
carry = 1

9 × 2 + 1 = 19
digit = 9
carry = 1

Append carry:

8 -> 9 -> 9 -> 1

Reverse:

1 -> 9 -> 9 -> 8

Time Complexity : O(n)
Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }

    ListNode* doubleIt(ListNode* head) {
        head = reverse(head);

        ListNode* curr = head;
        ListNode* prev = nullptr;

        int carry = 0;

        while (curr) {
            int value = curr->val * 2 + carry;
            curr->val = value % 10;
            carry = value / 10;

            prev = curr;
            curr = curr->next;
        }

        if (carry) {
            prev->next = new ListNode(carry);
        }

        return reverse(head);
    }
};


int main(){
    return 0;
}