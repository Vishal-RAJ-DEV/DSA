#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   APPROACH 1 : DOUBLY LINKED LIST
   ============================================================
   LOGIC :
   The entire browser history is represented as a doubly
   linked list. Each Node stores one visited URL along with a
   pointer to the previous node (prev) and the next node (next).
   A single pointer 'curr' always points to the node of the page
   the user is currently viewing.

   - Constructor : Creates the very first node holding the
     homepage and points 'curr' to it. (Size of list = 1)

   - visit(url)  :
       1. When a new page is visited, all the "forward" history
          becomes invalid. So we first delete every node that
          exists AFTER the current node (i.e. destroy the
          forward list).
       2. Then a brand new node is created for the given url and
          it is linked as the next node of the current node.
       3. Finally 'curr' is moved to this new node.

   - back(steps) :
       Walk backwards through the list using the 'prev'
       pointers. We keep moving 'curr' to its previous node as
       long as a previous node exists and we still have steps
       remaining. We can never go before the homepage because
       the first node has prev == nullptr.

   - forward(steps) :
       Symmetric to back(). Walk forwards using the 'next'
       pointers as long as a next node exists and steps remain.
       After visiting a new page the forward list is cleared,
       so forward() naturally stops at the newest page.

   ALGORITHM :
       Doubly Linked List traversal with O(1) insertion/deletion
       at the current position.

   COMPLEXITY :
       Constructor  : O(1)
       visit(url)   : O(N)  (worst case - deleting a long forward list)
       back/forward : O(min(steps, list length))  -> O(N)
   ============================================================ */

class Node {
public:
    string url;

    Node *prev;
    Node *next;

    Node(string u) {
        url = u;
        prev = nullptr;
        next = nullptr;
    }
};

class BrowserHistory {
public:

    Node* curr;

    BrowserHistory(string homepage) {
        curr = new Node(homepage);
    }

    void visit(string url) {

        // Delete forward history (destroy all nodes after current)
        Node* temp = curr->next;

        while (temp) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }

        curr->next = nullptr;

        // Create a new node and link it after the current node
        Node* node = new Node(url);

        curr->next = node;
        node->prev = curr;

        // Move current pointer to the newly visited page
        curr = node;
    }

    string back(int steps) {

        // Walk backwards while steps remain and a previous node exists
        while (steps-- && curr->prev)
            curr = curr->prev;

        return curr->url;
    }

    string forward(int steps) {

        // Walk forwards while steps remain and a next node exists
        while (steps-- && curr->next)
            curr = curr->next;

        return curr->url;
    }
};

/* ============================================================
   APPROACH 2 : TWO STACKS
   ============================================================
   LOGIC :
   History is managed using two stacks:
     - backStack    : stores pages you can go BACK to.
                      The bottom of the stack is the homepage and
                      the top of the stack is the current page.
     - forwardStack : stores pages you can go FORWARD to.
                      The top of the stack is the page closest to
                      the current one.

   - Constructor : Pushes the homepage into the backStack.

   - visit(url)  :
       1. Visiting a brand new page destroys all forward history,
          so the forwardStack is completely emptied.
       2. The new url is pushed on top of the backStack.
       (Now the new url is the current page - it is the top of
        the backStack.)

   - back(steps) :
       Move pages from backStack to forwardStack. Each move takes
       the current page (top of backStack) and puts it on top of
       the forwardStack. We keep doing this while steps remain AND
       the backStack has more than 1 element (we must never pop
       the homepage from the bottom). The page at the top of the
       backStack afterwards is the page we land on.

   - forward(steps) :
       Mirror image of back(). Move pages from the forwardStack
       back onto the backStack while steps remain and the
       forwardStack is not empty.

   ALGORITHM :
       Two LIFO stacks simulating the two halves of a linear
       history split at the current position.

   COMPLEXITY :
       Constructor  : O(1)
       visit(url)   : O(N)  (worst case - clearing forwardStack)
       back/forward : O(min(steps, stack size))  -> O(N)
   ============================================================ */

class BrowserHistory {
public:

    stack<string> backStack;
    stack<string> forwardStack;

    BrowserHistory(string homepage) {
        backStack.push(homepage);
    }

    void visit(string url) {

        // New visit destroys all forward history
        while (!forwardStack.empty())
            forwardStack.pop();

        backStack.push(url);
    }

    string back(int steps) {

        // Pop pages from backStack onto forwardStack, but never
        // pop the homepage (bottom element, so size > 1 needed)
        while (steps-- && backStack.size() > 1) {

            forwardStack.push(backStack.top());
            backStack.pop();
        }

        return backStack.top();
    }

    string forward(int steps) {

        // Pop pages from forwardStack back onto backStack
        while (steps-- && !forwardStack.empty()) {

            backStack.push(forwardStack.top());
            forwardStack.pop();
        }

        return backStack.top();
    }
};

/* ============================================================
   APPROACH 3 : VECTOR WITH (curr, last) INDEXES  -- NO ERASE
   ============================================================
   LOGIC :
   The whole history lives in a single vector 'history'.
     - 'curr' is the index of the currently viewed page.
     - 'last' is the index of the newest page ever visited.
   When you go back and then visit a new page, the forward
   entries are NOT erased. Instead the new url simply OVERWRITES
   history[curr]. Because of this, all stale forward entries
   beyond 'last' are harmless and can be ignored.

   - Constructor : Pushes homepage into the vector, sets
                   curr = 0 and last = 0.

   - visit(url)  :
       1. Move one step forward: curr++.
       2. If curr has reached the end of the vector, push_back
          the new url (extend the vector).
          Otherwise reuse the existing slot by overwriting
          history[curr] = url (this kills the forward history by
          overwriting it).
       3. Set last = curr, because this new page is now the
          newest one.

   - back(steps) :
       Move curr backward by 'steps' but clamp it to 0 (the
       homepage). Returns history[curr].

   - forward(steps) :
       Move curr forward by 'steps' but clamp it to 'last'
       (the newest page). Returns history[curr].

   ALGORITHM :
       Array-index based history with lazy overwriting of the
       forward history. No element shifting is ever performed.

   COMPLEXITY :
       Constructor  : O(1)
       visit(url)   : O(1)  amortized (overwrite or push_back)
       back/forward : O(1)  (simple index clamping)
   ============================================================ */

class BrowserHistory {
public:
    vector<string> history;

    int curr;
    int last;

    BrowserHistory(string homepage) {
        history.push_back(homepage);
        curr = 0;
        last = 0;
    }

    void visit(string url) {

        curr++;

        // If we are at the end of the vector, grow it; otherwise
        // overwrite the stale forward entry with the new url
        if (curr == history.size())
            history.push_back(url);
        else
            history[curr] = url;

        // This page is now the newest page in history
        last = curr;
    }

    string back(int steps) {

        curr = max(0, curr - steps);

        return history[curr];
    }

    string forward(int steps) {

        curr = min(last, curr + steps);

        return history[curr];
    }
};

/* ============================================================
   APPROACH 4 : VECTOR WITH ERASE (SIMPLEST / BRUTE FORCE)
   ============================================================
   LOGIC :
   History is a vector 'history' plus an index 'curr'.
   This version KEEPS the invariant that the vector always
   contains exactly the valid history -- any forward entries that
   become invalid are physically removed with erase().

   - Constructor : Pushes homepage and sets curr = 0.

   - visit(url)  :
       1. erase() removes every element from index (curr + 1)
          to the end of the vector, i.e. all forward history is
          physically deleted from the container.
       2. The new url is pushed at the back of the vector.
       3. curr is incremented to point to the new page.

   - back(steps) :
       curr = max(0, curr - steps). Clamps at the homepage.

   - forward(steps) :
       curr = min(size - 1, curr + steps). Clamps at the last
       (newest) element, which is exactly the latest visited page
       because of the erase() in visit().

   ALGORITHM :
       Linear vector with real deletion of the forward history
       (erase() shifts the remaining elements). Intuitively the
       easiest to understand but does the most work.

   COMPLEXITY :
       Constructor  : O(1)
       visit(url)   : O(N)  (erase() shifts all elements after curr)
       back/forward : O(1)  (simple index clamping)
   ============================================================ */

class BrowserHistory {
public:
    vector<string> history;
    int curr;

    BrowserHistory(string homepage) {
        history.push_back(homepage);
        curr = 0;
    }

    void visit(string url) {
        // Physically delete all forward history, then append
        history.erase(history.begin() + curr + 1, history.end());
        history.push_back(url);
        curr++;
    }

    string back(int steps) {
        curr = max(0, curr - steps);
        return history[curr];
    }

    string forward(int steps) {
        curr = min((int)history.size() - 1, curr + steps);
        return history[curr];
    }
};



int main(){
    return 0;
}