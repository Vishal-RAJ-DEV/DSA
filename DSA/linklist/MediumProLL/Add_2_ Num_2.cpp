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

/* ============================================================
   PROBLEM : ADD TWO NUMBERS II (LeetCode 445)
   You are given two non-empty linked lists that represent two
   non-negative integers. The MOST significant digit comes FIRST
   (head of the list). Add the two numbers and return the sum as
   a linked list with the same "most significant first" order.

   Example:
     l1 = 7 -> 2 -> 4 -> 3     (= 7243)
     l2 =     5 -> 6 -> 4      (=  564)
     sum = 7807  ->  7 -> 8 -> 0 -> 7

   ============================================================
   APPROACH 1 : USING TWO STACKS
   ============================================================
   INTUITION :
   The lists are stored in NORMAL order (most significant digit
   first), but addition must start from the LEAST significant
   digit (the right end). A STACK is the perfect tool to reverse
   an order without actually reversing the list: push every digit
   of both lists onto two stacks, then pop them one by one. Popping
   gives us the digits from least significant to most significant
   -- exactly the order in which we must add them.

   The result is also built from the least significant side, and
   each new (more significant) digit is inserted at the FRONT
   (newNode->next = result). This way the final list automatically
   ends up in normal (most-significant-first) order -- no reverse
   needed at the end.

   ============================================================
   ALGORITHM
   ============================================================
   1. Push every digit of l1 onto stack1 and every digit of l2
      onto stack2.
      -> Now top of each stack = least significant digit.
   2. result = nullptr, carry = 0.
   3. While stack1 / stack2 are not empty OR carry != 0:
        digit1 = pop value of stack1 (0 if stack1 empty)
        digit2 = pop value of stack2 (0 if stack2 empty)
        sum    = digit1 + digit2 + carry
        digit  = sum % 10      (current digit of the answer)
        carry  = sum / 10      (digit to carry to next position)
        create newNode(digit) and push it to the FRONT of result
        (newNode->next = result; result = newNode)
        pop the used top values from both stacks
   4. Return result.

   ============================================================
   WORKING DIAGRAM (l1 = 7->2->4->3 , l2 = 5->6->4)
   ============================================================
     l1:  [ 7 ]->[ 2 ]->[ 4 ]->[ 3 ]      l2: [ 5 ]->[ 6 ]->[ 4 ]
     stack1 (bottom->top): 7 2 4 3        stack2 (bottom->top): 5 6 4
                                    |top                     |top

     Iteration 1: digit1=3 digit2=4 sum=3+4+0=7  digit=7 carry=0
       result: [ 7 ]
     Iteration 2: digit1=4 digit2=6 sum=4+6+0=10 digit=0 carry=1
       result: [ 0 ]->[ 7 ]
     Iteration 3: digit1=2 digit2=5 sum=2+5+1=8  digit=8 carry=0
       result: [ 8 ]->[ 0 ]->[ 7 ]
     Iteration 4: digit1=7 digit2=0 sum=7+0+0=7  digit=7 carry=0
       result: [ 7 ]->[ 8 ]->[ 0 ]->[ 7 ]

     Final answer: 7 -> 8 -> 0 -> 7      (7807)  CORRECT.

   ============================================================
   COMPLEXITY
   ============================================================
   Time  : O(m + n)  -- one pass to fill stacks, one pass to add.
   Space : O(m + n)  -- two stacks plus the result list.
   ============================================================ */
class Solution {
public:
    ListNode* Helper(ListNode* l1, ListNode* l2) {
        stack<int> stack1, stack2;

        while (l1 != nullptr) {
            stack1.push(l1->val);
            l1 = l1->next;
        }

        while (l2 != nullptr) {
            stack2.push(l2->val);
            l2 = l2->next;
        }

        ListNode* result = nullptr;
        int carry = 0;

        while (!stack1.empty() || !stack2.empty() || carry != 0) {
            int digit1 = !stack1.empty() ? stack1.top() : 0;
            int digit2 = !stack2.empty() ? stack2.top() : 0;

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = new ListNode(digit);
            newNode->next = result;
            result = newNode;

            if (!stack1.empty())
                stack1.pop();
            if (!stack2.empty())
                stack2.pop();
        }

        return result;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans = Helper(l1, l2);
        return ans;
    }
};

/* ============================================================
   APPROACH 2 : REVERSE THE LISTS, ADD, REVERSE BACK
   ============================================================
   INTUITION :
   If both lists were stored in REVERSE order (least significant
   digit first), adding them would be exactly the normal
   grade-school addition you do from right to left. So this
   approach first REVERSES both input lists, adds them digit by
   digit (like Approach 1 but iteratively, since the order is now
   already correct), and finally REVERSES the result back so it
   returns in the required most-significant-first order.

   ============================================================
   ALGORITHM
   ============================================================
   reverseList(head) :  (iterative 3-pointer reversal)
       1. prev = NULL.
       2. While head is not NULL:
            nxt      = head->next     (save the rest of the list)
            head->next = prev         (flip the current pointer)
            prev     = head           (prev moves forward)
            head     = nxt            (head moves forward)
       3. Return prev (the new head, i.e. old tail).

   Helper(l1, l2) :  (both lists now in REVERSED order)
       1. dummyHead (0) + tail pointer for building the answer.
       2. While l1 or l2 exists or carry != 0:
            digit1 = l1->val if l1 else 0
            digit2 = l2->val if l2 else 0
            sum    = digit1 + digit2 + carry
            digit  = sum % 10 ; carry = sum / 10
            append newNode(digit) to tail ; advance tail, l1, l2
       3. Return dummyHead->next (skipping the dummy).

   addTwoNumbers(l1, l2) :
       1. l1 = reverseList(l1)
       2. l2 = reverseList(l2)
       3. ans = Helper(l1, l2)      (already in reversed order)
       4. return reverseList(ans)   (flip it back to normal order)

   ============================================================
   WORKING DIAGRAM (l1 = 7->2->4->3 , l2 = 5->6->4)
   ============================================================
     Original lists:
       l1: [ 7 ]->[ 2 ]->[ 4 ]->[ 3 ]      (7243)
       l2: [ 5 ]->[ 6 ]->[ 4 ]             ( 564)

     Step 1 - reverse l1 and l2:
       l1: [ 3 ]->[ 4 ]->[ 2 ]->[ 7 ]      (now LSB first)
       l2: [ 4 ]->[ 6 ]->[ 5 ]

     Step 2 - add like normal (right to left), append to dummy:
       l1: [ 3 ]->[ 4 ]->[ 2 ]->[ 7 ]
       l2: [ 4 ]->[ 6 ]->[ 5 ]

         digit: 3+4=7  ->  ans: [ 7 ]
         digit: 4+6=10 -> digit 0 carry 1  ->  ans: [ 7 ]->[ 0 ]
         digit: 2+5+1=8  ->  ans: [ 7 ]->[ 0 ]->[ 8 ]
         digit: 7+0=7  ->  ans: [ 7 ]->[ 0 ]->[ 8 ]->[ 7 ]
         (l1,l2 both null, carry 0 -> stop)

       Intermediate ans: [ 7 ]->[ 0 ]->[ 8 ]->[ 7 ]   (LSB first)

     Step 3 - reverse the answer back:
       Final: [ 7 ]->[ 8 ]->[ 0 ]->[ 7 ]    (7807)  CORRECT.

   ============================================================
   COMPLEXITY
   ============================================================
   Time  : O(m + n)  -- reversal is O(len) each, addition O(m+n).
   Space : O(1) extra (excluding the answer list) -- no stacks,
           only pointer variables. Better than Approach 1.
   ============================================================ */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;

        while(head) {
            ListNode* nxt = head->next;
            head->next = prev;
            prev = head;
            head = nxt;
        }
        return prev;
    }

    ListNode* Helper(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* tail = dummyHead;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int digit1 = (l1 != nullptr) ? l1->val : 0;
            int digit2 = (l2 != nullptr) ? l2->val : 0;

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = new ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        ListNode* ans = Helper(l1, l2);
        return reverseList(ans);
    }
};


int main(){
    return 0;
}