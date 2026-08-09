#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};



/*
=========================================================
Algorithm: Level Order Traversal (BFS)
=========================================================

Problem:
--------
Populate each node's 'next' pointer so that it points to its
next right node on the same level.
If there is no node to the right, the next pointer should be NULL.

---------------------------------------------------------
Intuition
---------------------------------------------------------

Nodes that belong to the same level are exactly the nodes
that appear together during a Level Order Traversal (BFS).

Example:

            1
          /   \
         2     3
        / \   / \
       4   5 6   7

BFS visits the tree level by level:

Level 0 : 1

Level 1 : 2 -> 3

Level 2 : 4 -> 5 -> 6 -> 7

Since all nodes of one level are processed together,
we can simply connect the previous node with the current node.

For every level:

prev -----> previous node already processed
top  -----> current node

Initially:

prev = NULL

Level:

2   3

Iteration 1:
-------------
top = 2

prev == NULL
No connection needed.

prev = 2

Iteration 2:
-------------
top = 3

prev->next = top

2 ------> 3

prev = 3

After finishing the level:

3 ------> NULL

Repeat this process for every level.

---------------------------------------------------------
Why Queue?
---------------------------------------------------------

A queue naturally processes nodes in FIFO order.

When processing one level:

1. Remove every node of the current level.
2. Push all of their children.
3. Those children automatically become the next level.

Thus, every iteration of the outer loop processes exactly
one tree level.

---------------------------------------------------------
Algorithm
---------------------------------------------------------

1. If tree is empty, return NULL.

2. Push the root into the queue.

3. While queue is not empty:

      • Store current level size.
      • prev = NULL.

      • Process exactly 'size' nodes.

            - Pop one node.
            - Connect prev -> current.
            - Update prev.
            - Push left child.
            - Push right child.

      • Last node's next becomes NULL.

4. Return root.

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

Each node is visited exactly once.

Time : O(N)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

Queue stores at most one level.

Worst Case : O(N)

=========================================================
*/

class Solution {
public:

    Node* connect(Node* root) {

        // If the tree is empty, nothing needs to be connected.
        if(root == nullptr)
            return nullptr;

        // Queue is used to perform Breadth First Search (Level Order Traversal).
        queue<Node*> q;

        // Start BFS from the root.
        q.push(root);

        // Continue until every node has been processed.
        while(!q.empty()){

            // Number of nodes present in the current level.
            int size = q.size();

            // Keeps track of the previous node in the current level.
            Node* prev = nullptr;

            // Process every node of the current level.
            for(int i = 0; i < size; i++){

                // Remove the front node from the queue.
                Node* top = q.front();
                q.pop();

                /*
                    If prev exists, connect it to the current node.

                    Example:

                    prev = 4
                    top  = 5

                    4 --------> 5
                */
                if(prev != nullptr)
                    prev->next = top;

                // Current node now becomes the previous node
                // for the next iteration.
                prev = top;

                // Push left child for processing in the next level.
                if(top->left)
                    q.push(top->left);

                // Push right child for processing in the next level.
                if(top->right)
                    q.push(top->right);
            }

            /*
                At this point 'prev' points to the last node
                of the current level.

                Example:

                4 -> 5 -> 6 -> 7

                prev points to 7.

                Since 7 has no node on its right,

                7 ------> NULL
            */
            prev->next = nullptr;
        }

        // Root is returned because the tree itself is modified in-place.
        return root;
    }
};



int main(){
    return 0;
}