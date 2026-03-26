#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Brute force approach: Collect all values, sort them, and create a new list
// Time complexity: O(N log N) where N is the total number of nodes across all lists
class Solution {
public:
    // Function to merge k sorted linked lists using brute force
    ListNode* mergeKSortedLists(vector<ListNode*>& lists) {
        // Vector to store all values from every node
        vector<int> allValues;

        // Loop through each linked list
        for (auto list : lists) {
            // Traverse the current list and store its values
            while (list != NULL) {
                allValues.push_back(list->val);
                list = list->next;
            }
        }

        // Sort all collected values
        sort(allValues.begin(), allValues.end());

        // Create a dummy head for the final result list
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;

        // Create new linked list nodes from sorted values
        for (int val : allValues) {
            curr->next = new ListNode(val);
            curr = curr->next;
        }

        // Return head of the merged linked list
        return dummy->next;
    }
};


class Compare {
public:
    // Comparator to order ListNode pointers based on node values
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

// Optimal approach: Using a min-heap (priority queue) to merge k sorted linked lists
// Time complexity: O(N log k) where N is the total number of nodes and k is the number of lists
class Solution {
public:
    // Function to merge k sorted linked lists using a min-heap
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Create a min-heap (priority queue) with custom comparator
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        // Push the head of each non-empty list into the heap
        for (auto list : lists) {
            if (list != NULL)
                pq.push(list);
        }

        // Create a dummy node to build the result list
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        // While the heap is not empty
        while (!pq.empty()) {
            // Extract the node with the smallest value
            ListNode* smallest = pq.top();
            pq.pop();

            // Add it to the result list
            tail->next = smallest;
            tail = tail->next;

            // If there's a next node, push it into the heap
            if (smallest->next != NULL)
                pq.push(smallest->next);
        }

        // Return the head of the merged list
        return dummy->next;
    }
};

// Driver code
int main() {
    Solution sol;
    //there is k sorted linked lists , list 1 , list 2 and list 3 and we have to merge these lists into one sorted linked list
    // Creating three linked lists:
    // list1: 1 -> 4 -> 5   
    // list2: 1 -> 3 -> 4
    // list3: 2 -> 6

    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode* list3 = new ListNode(2);
    list3->next = new ListNode(6);

    vector<ListNode*> lists = {list1, list2, list3};
    ListNode* result = sol.mergeKLists(lists);

    // Print the merged list
    while (result != NULL) {
        cout << result->val << " ";
        result = result->next;
    }
    return 0;
}
