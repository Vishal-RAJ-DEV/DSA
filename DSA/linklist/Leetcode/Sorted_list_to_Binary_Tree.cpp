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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution
{
public:
    /*
        Intuition:

        We are given a sorted linked list and we need to convert it into a
        height-balanced BST.

        In a BST:
        - left subtree contains smaller values
        - root is the middle value
        - right subtree contains greater values

        Since the linked list is already sorted, the best choice for the root
        is the middle node:
        - nodes before middle become the left subtree
        - nodes after middle become the right subtree

        This is exactly the same idea as building BST from a sorted array,
        but here we first need to find the middle node of the linked list.
    */
    ListNode *middle(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *prev = nullptr;

        /*
            Algorithm to find middle node:

            - slow moves one step at a time
            - fast moves two steps at a time
            - when fast reaches the end, slow will be at the middle

            prev is used to keep track of the node just before slow.
            This helps us break the linked list into two halves.
        */
        while (fast != nullptr && fast->next != nullptr)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        /*
            After the loop:
            - slow points to the middle node
            - prev points to the node before middle

            We cut the list here so:
            left half  -> starts from head
            middle     -> slow
            right half -> starts from slow->next
        */
        if (prev != nullptr)
            prev->next = nullptr;

        return slow;
    }

    /*
        Algorithm:

        1. If list is empty, return NULL
        2. If list has one node, that node becomes a leaf tree node
        3. Find middle node of the linked list
        4. Make middle node the root of current BST
        5. Recursively build left subtree from left half of list
        6. Recursively build right subtree from right half of list

        Why this gives a height-balanced BST:
        - Every time we choose the middle node as root,
          both left and right halves are almost equal in size.
        - So the tree remains balanced.

        Time Complexity:
        - Finding middle takes O(n)
        - This happens for each recursive split
        - Overall time complexity is O(n log n) in average recursive splitting

        Space Complexity:
        - O(log n) recursion stack for balanced recursion
    */
    TreeNode *sortedListToBST(ListNode *head)
    {
        // Base case 1:
        // Empty linked list means no tree node can be formed.
        if (head == nullptr)
            return nullptr;

        // Base case 2:
        // If only one node is present, it becomes a leaf node of BST.
        if (head->next == nullptr)
            return new TreeNode(head->val);

        // Find the middle node of the current linked list.
        ListNode *middleNode = middle(head);

        // Middle value becomes the root because list is sorted.
        TreeNode *root = new TreeNode(middleNode->val);

        /*
            Recursive construction:

            head to node before middle   -> left subtree
            node after middle to end     -> right subtree

            Since middle() already disconnected the left half,
            passing head builds the left subtree safely.
        */
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(middleNode->next);

        return root;
    }
};

ListNode *createList(vector<int> &arr)
{
    // If array is empty, linked list is also empty.
    if (arr.empty())
        return nullptr;

    // Create head from first value, then keep attaching new nodes.
    ListNode *head = new ListNode(arr[0]);
    ListNode *mover = head;

    for (size_t i = 1; i < arr.size(); i++)
    {
        mover->next = new ListNode(arr[i]);
        mover = mover->next;
    }

    return head;
}

void printList(ListNode *head)
{
    // Utility function to print the linked list.
    while (head != nullptr)
    {
        cout << head->val;
        if (head->next != nullptr)
            cout << " ";
        head = head->next;
    }
    cout << endl;
}

void inorder(TreeNode *root)
{
    /*
        Inorder traversal of BST prints values in sorted order.
        This helps us verify that the constructed tree is correct.
    */
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main()
{
    vector<int> arr = {-10, -3, 0, 5, 9};
    ListNode *head = createList(arr);

    cout << "Sorted Linked List: ";
    printList(head);

    Solution obj;
    TreeNode *root = obj.sortedListToBST(head);

    cout << "Inorder of BST: ";
    inorder(root);
    cout << endl;

    return 0;
}
