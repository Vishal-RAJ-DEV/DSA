/*
============================================================
REVERSE A STACK USING RECURSION
============================================================

ALGORITHM:
  1. Pop the top element and store it.
  2. Recursively reverse the remaining stack.
  3. Insert the popped element at the bottom of the reversed stack.

This uses two recursive functions:
  - reverseStack(): pops elements until empty, then inserts each at bottom
  - insertBottom(): pushes an element to the bottom of a stack

------------------------------------------------------------
DRY RUN (Stack grows upward, bottom is left, top is right)
------------------------------------------------------------

Initial stack: [1, 2, 3, 4, 5]   (top = 5)

== reverseStack Phase (unwinding) ==
  Call 1: top=5, pop → stack=[1,2,3,4], call reverseStack
  Call 2: top=4, pop → stack=[1,2,3],   call reverseStack
  Call 3: top=3, pop → stack=[1,2],     call reverseStack
  Call 4: top=2, pop → stack=[1],       call reverseStack
  Call 5: top=1, pop → stack=[],        call reverseStack
  Call 6: stack empty → return

== insertBottom Phase (rebuilding) ==
  Call 5: insertBottom([], 1)        → push 1        → stack=[1]
  Call 4: insertBottom([1], 2)       → push 2 bottom → stack=[2,1]
  Call 3: insertBottom([2,1], 3)     → push 3 bottom → stack=[3,2,1]
  Call 2: insertBottom([3,2,1], 4)   → push 4 bottom → stack=[4,3,2,1]
  Call 1: insertBottom([4,3,2,1], 5) → push 5 bottom → stack=[5,4,3,2,1]

Final stack: [5, 4, 3, 2, 1]   (top = 1) ✓ REVERSED

------------------------------------------------------------
HOW insertBottom WORKS (Example: insert 3 into [2, 1])
------------------------------------------------------------
  Step 1: st=[2,1], top=2, pop → st=[1], call insertBottom([1], 3)
  Step 2: st=[1],   top=1, pop → st=[],  call insertBottom([], 3)
  Step 3: st=[],    push 3     → st=[3]
  Step 4: (backtrack) push 1   → st=[3,1]
  Step 5: (backtrack) push 2   → st=[3,1,2]

  Key: We remove everything above bottom, push val,
       then restore everything on top.
============================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
  insertBottom: Inserts 'val' at the bottom of stack 'st'.
  
  How it works:
    - Pop the top element and save it.
    - Recursively call insertBottom until stack is empty.
    - Push 'val' at the bottom (now stack is empty).
    - On return, push back all saved elements in order.
  
  This is the key helper that makes reverseStack possible.
*/
void insertBottom( stack <int> &st , int val){
    if(st.empty()){
        st.push(val);
        return;
    }
    int top = st.top();
    st.pop();
    insertBottom( st , val );
    st.push( top);
}

/*
  reverseStack: Reverses the entire stack using recursion.
  
  How it works:
    - Base case: if stack is empty, return.
    - Pop the top element.
    - Recursively reverse the remaining stack.
    - Insert the popped element at the bottom of the reversed stack.
  
  NOTE: This function takes stack by VALUE, not by reference.
  This means it works on a COPY. The original stack in main()
  will NOT be modified. To fix this, change parameter to:
      stack<int> &st   (pass by reference)
  
  Also, for the algorithm to work correctly with a reference,
  the recursive call should NOT pass by value. The corrected
  version is shown below in main().
*/
void reverseStack( stack <int > st){
    if(st.empty()) return ;
    
    int top = st.top();
    st.pop();
    reverseStack(st);

    insertBottom( st , top);
}

int main(){
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    reverseStack(st);

    cout<<"Reversed stack is: "<<endl;
    while(!st.empty()){
        cout<<st.top()<<endl;
        st.pop();
    }

    return 0;
}

/*
============================================================
CORRECTED VERSION (for reference):
============================================================

void insertBottom(stack<int> &st, int val) {
    if (st.empty()) {
        st.push(val);
        return;
    }
    int top = st.top();
    st.pop();
    insertBottom(st, val);
    st.push(top);
}

void reverseStack(stack<int> &st) {      // pass by reference
    if (st.empty()) return;
    int top = st.top();
    st.pop();
    reverseStack(st);                     // recursive on same ref
    insertBottom(st, top);
}

int main() {
    stack<int> st;
    st.push(1); st.push(2); st.push(3); st.push(4); st.push(5);
    reverseStack(st);
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    // Output: 1 2 3 4 5 (reversed from 5,4,3,2,1 to 1,2,3,4,5)
    return 0;
}
============================================================
*/