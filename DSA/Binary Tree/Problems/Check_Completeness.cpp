#include <iostream>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /*
    LOGIC: BFS (level-order) with null tracking

    A complete binary tree has all levels filled except possibly
    the last, and the last level has nodes as left as possible.

    Key observation: In a level-order traversal of a complete tree,
    once we encounter a nullptr, there should be NO more non-null
    nodes after it in the queue.

    Steps:
    1. Push root into queue.
    2. Keep popping front and pushing BOTH children (including null
       children) until we hit a nullptr at the front.
    3. After hitting the first nullptr, pop all remaining nullptrs
       from the queue.
    4. If the queue is now empty -> complete tree (no non-null seen
       after the first null).
       If queue still has non-null nodes -> not complete.
    */
    bool isCompleteTree(TreeNode* root) {
        if(!root) return true;

        queue<TreeNode*> q;
        q.push(root);

        //Phase 1: push children (including null) until we hit a null
        while(!q.empty() && q.front() != nullptr) {
            TreeNode* node = q.front();
            q.pop();

            q.push(node->left);
            q.push(node->right);
        }

        //Phase 2: skip all trailing nulls after the first null
        while(!q.empty() && q.front() == nullptr) {
            q.pop();
        }

        //If any non-null remains after a null was seen -> incomplete
        return q.empty();
    }
};

int main() {
    Solution sol;

    /* Test 1: Complete tree
            1
           / \
          2   3
         / \  /
        4  5 6
        Expected: true
    */
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->left = new TreeNode(6);

    cout << "Test 1 (complete): " << boolalpha << sol.isCompleteTree(root1)
         << " (expected: true)" << endl;

    /* Test 2: Not complete (gap in last level)
            1
           / \
          2   3
         / \   \
        4  5    7   <-- 7 is right child but left child 6 missing
        Expected: false
    */
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->right->right = new TreeNode(7);

    cout << "Test 2 (not complete - gap): " << sol.isCompleteTree(root2)
         << " (expected: false)" << endl;

    /* Test 3: Single node
            1
        Expected: true
    */
    TreeNode* root3 = new TreeNode(1);
    cout << "Test 3 (single): " << sol.isCompleteTree(root3)
         << " (expected: true)" << endl;

    /* Test 4: Empty tree
        Expected: true
    */
    cout << "Test 4 (empty): " << sol.isCompleteTree(nullptr)
         << " (expected: true)" << endl;

    return 0;
}
